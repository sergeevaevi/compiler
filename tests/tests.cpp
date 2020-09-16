#include <gtest/gtest.h>
#include <fstream>
#include "antlr4-runtime.h"
#include "JavaScriptLexer.h"
#include "../MyVisitor.h"

using namespace std;
using namespace antlr4;



vector<string> getStringTree(const string& path) {
    ANTLRFileStream input(path);
    antlrcpptest::JavaScriptLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();
    JavaScriptParser parser(&tokens);
    MyVisitor visitor;
    tree::ParseTree* tree = parser.statementList();
    visitor.visit(tree);

    auto res = visitor.getTreeString();

    string another_path = path;
    another_path.erase(path.length()-2);
    another_path.replace(9, 3, "out");
    another_path+= "txt";
    ofstream in(another_path);
    if(in.is_open()){
        for(const auto& mem: res){
            in << mem << endl;
        }
    }else{
        cout << "Trouble " + another_path;
    }

    in.close();
    return res;
}

vector<string> readFile(const string& path){
    ifstream in(path);
    vector<string> result;
    if(in.is_open()){
        string str;
        while(getline(in, str,'\n')){
            result.push_back(str);
        }
        return result;
    }
    return vector<string>();
}

int getFilesNum(const string& path){
    ifstream in;
    int num = 0;
    bool exists = false;
    do{
        string path_to = path+to_string(num)+".js";
        in.open(path_to);
        exists = in.is_open();
        num++;
        in.close();
    }while(exists);

    return num-1;
}

void compareOut(const string& path){
    int n =  getFilesNum(path);
    for(int i = 0; i < n; i++){
        auto string_tree = getStringTree(path+to_string(i)+".js");
        auto result = readFile(path+to_string(i)+".txt");
        ASSERT_EQ(string_tree, result);
    }
}

TEST(grammarTest, classTest){
    compareOut("../tests/src/class/");
}

TEST(expressionTest, additiveTest){
    compareOut("../tests/src/expression/additive/");
}

TEST(expressionTest, arrayTest){
    compareOut("../tests/src/expression/array/");
}

TEST(expressionTest, assignmentTest){
    compareOut("../tests/src/expression/assignment/");
}

TEST(expressionTest, binaryTest){
    compareOut("../tests/src/expression/binary/");
}

TEST(expressionTest, binarybitwiseTest){
    compareOut("../tests/src/expression/binary-bitwise/");
}

TEST(expressionTest, binarylogicalTest){
    compareOut("../tests/src/expression/binary-logical/");
}

TEST(expressionTest, bitwiseshiftTest){
    compareOut("../tests/src/expression/bitwise-shift/");
}

TEST(expressionTest, equalityTest){
    compareOut("../tests/src/expression/equality/");
}

TEST(expressionTest, complexTest){
    compareOut("../tests/src/expression/complex/");
}

TEST(expressionTest, groupingTest){
    compareOut("../tests/src/expression/grouping/");
}

TEST(expressionTest, lefthandsideTest){
    compareOut("../tests/src/expression/left-hand-side/");
}

TEST(expressionTest, literalTest){
    compareOut("../tests/src/expression/literal/");
}

TEST(expressionTest, multiplicativeTest){
    compareOut("../tests/src/expression/multiplicative/");
}

TEST(expressionTest, objectTest){
    compareOut("../tests/src/expression/object/");
}

TEST(expressionTest, otherTest){
    compareOut("../tests/src/expression/other/");
}

TEST(expressionTest, relationalTest){
    compareOut("../tests/src/expression/relational/");
}

TEST(expressionTest, unaryTest){
    compareOut("../tests/src/expression/unary/");
}

TEST(expressionTest, breakTest){
    compareOut("../tests/src/statement/break/");
}

TEST(expressionTest, functiondeclTest){
    compareOut("../tests/src/function decl/");
}

TEST(expressionTest, blockTest){
    compareOut("../tests/src/statement/block/");
}

TEST(expressionTest, continueTest){
    compareOut("../tests/src/statement/continue/");
}

TEST(expressionTest, emptyTest){
    compareOut("../tests/src/statement/empty/");
}

TEST(expressionTest, expressionTest){
    compareOut("../tests/src/statement/expression/");
}

TEST(expressionTest, ifTest){
    compareOut("../tests/src/statement/if/");
}

TEST(expressionTest, iterationTest){
    compareOut("../tests/src/statement/iteration/");
}

TEST(expressionTest, returnTest){
    compareOut("../tests/src/statement/return/");
}

TEST(expressionTest, varTest){
    compareOut("../tests/src/statement/variable/");
}

TEST(expressionTest, whileTest){
    compareOut("../tests/src/statement/while/");
}

TEST(expressionTest, tokenizeTest){
    compareOut("../tests/src/tokenize/");
}

TEST(expressionTest, vardeclTest){
    compareOut("../tests/src/var decl/");
}

TEST(expressionTest, whitespaceTest){
    compareOut("../tests/src/whitespace/");
}

int test(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}