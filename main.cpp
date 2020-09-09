#include <iostream>

#include "antlr4-runtime.h"
#include "JavaScriptLexer.h"
#include "JavaScriptParser.h"
#include "MyVisitor.h"
#include "gen/JavaScriptParserBaseVisitor.h"

using namespace antlr4;

int main(int , const char **) {
  ANTLRInputStream input(u8"var x = 6");
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
  for(const auto& st: res){
      std::cout << st << std::endl;
  }
 // std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  return 0;
}
