#include <iostream>

#include "antlr4-runtime.h"
#include "JavaScriptLexer.h"
#include "MyVisitor.h"
#include "../gen/JavaScriptParserBaseVisitor.h"
#include "../tests/tests.h"

using namespace antlr4;

int main(int argc, char *argv[]) {
  ANTLRInputStream input(u8"\"Hello\";\n"
                         "\"\\n\\r\\t\\v\\b\\f\\\\\\'\\\"\\0\";\n"
                         "\"\\x61\";\n"
                         "\"Hello\\n world\";\n"
                         "\"Hello\\02 World\";\n"
                         "\"Hello\\\n"
                         "world\";");
  antlrcpptest::JavaScriptLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
//  for (auto token : tokens.getTokens()) {
//    std::cout << token->toString() << std::endl;
//  }

  JavaScriptParser parser(&tokens);
  MyVisitor visitor;
  tree::ParseTree* tree = parser.statementList();
  visitor.visit(tree);

  auto res = visitor.getTreeString();
//  for(const auto& st: res){
//      std::cout << st << std::endl;
//  }
 // std::cout << tree->toStringTree(&parser) << std::endl << std::endl;
  test(argc, argv);
  return 0;
}
