#include "MyVisitor.h"
#include "antlr4-runtime.h"

void notImplemented() {
    std::cout << "not implemented" << std::endl;
}

std::string getTermMode(antlr4::tree::TerminalNode *ctx) {
    if (ctx) {
        return ctx->getText();
    }
    return "";
}

void MyVisitor::addTermNode(antlr4::tree::TerminalNode *ctx) {
    if (ctx) {
        std::string text = ctx->getText();
        addToTree(text);
    }
}

antlrcpp::Any MyVisitor::visitBlock(JavaScriptParser::BlockContext *ctx) {
    offset++;
    addTermNode(ctx->OpenBrace());
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseBrace());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitImportStatement(JavaScriptParser::ImportStatementContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitExportDeclaration(JavaScriptParser::ExportDeclarationContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitExportDefaultDeclaration(JavaScriptParser::ExportDefaultDeclarationContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitVariableDeclarationList(JavaScriptParser::VariableDeclarationListContext *ctx) {
    offset++;
    std::string text = "VariableDeclarationList";
    addToTree(text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitIfStatement(JavaScriptParser::IfStatementContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->OpenParen());
    auto text = "IfStatement " + ctx->If()->getText() + paren;
    addToTree(text);
    if (ctx->expressionSequence()) {
        visitExpressionSequence(ctx->expressionSequence());
    }
    for (int i = 0; i < ctx->statement().size(); i++) {
        visitStatement(ctx->statement(i));
//        if (ctx->Else()) {
//            auto text = ctx->Else()->getText();
//            addToTree(text);
//        }
    }
    addTermNode(ctx->CloseParen());
    offset--;
    return 1;
}

antlrcpp::Any MyVisitor::visitDoStatement(JavaScriptParser::DoStatementContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->OpenParen());
    bool nested = false;
    auto text = "DoStatement " + ctx->Do()->getText() + paren;
    addToTree(text);
    if (ctx->statement()) {
        visitStatement(ctx->statement());
    }
    if (ctx->While()) {
        paren = getTermMode(ctx->OpenParen());
        text = ctx->While()->getText() + paren;
        nested = true;
    }
    if (ctx->expressionSequence()) {
        visitExpressionSequence(ctx->expressionSequence());
    }
    if (nested && ctx->CloseParen()) {
        text = ctx->CloseParen()->getText();
        addToTree(text);
    }
    addTermNode(ctx->CloseParen());
    offset--;
    return 1;
}

antlrcpp::Any MyVisitor::visitWhileStatement(JavaScriptParser::WhileStatementContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->CloseParen());
    auto text = "WhileStatement " + ctx->While()->getText() + paren;
    addToTree(text);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseParen());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitForStatement(JavaScriptParser::ForStatementContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->OpenParen());
    auto text = "ForStatement " + ctx->For()->getText() + paren;
    addToTree(text);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseParen());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitForInStatement(JavaScriptParser::ForInStatementContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->OpenParen());
    auto text = "ForInStatement " + ctx->For()->getText() + paren;
    addToTree(text);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseParen());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitForOfStatement(JavaScriptParser::ForOfStatementContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->OpenParen());
    auto text = "ForOfStatement " + ctx->For()->getText() + paren;
    addToTree(text);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseParen());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitVarModifier(JavaScriptParser::VarModifierContext *ctx) {
    offset++;
    if (ctx->let()) {
        notImplemented();
        return 1;
    }
    if (ctx->Var()) {
        auto text = ctx->Var()->getText();
        addToTree(text);
    }
    if (ctx->Const()) {
        auto text = ctx->Var()->getText();
        addToTree(text);
    }
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitContinueStatement(JavaScriptParser::ContinueStatementContext *ctx) {
    offset++;
    auto text = "ContinueStatement " + ctx->Continue()->getText();
    addToTree(text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitBreakStatement(JavaScriptParser::BreakStatementContext *ctx) {
    offset++;
    auto text = "BreakStatement " + ctx->Break()->getText();
    addToTree(text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitReturnStatement(JavaScriptParser::ReturnStatementContext *ctx) {
    offset++;
    auto text = "Statement " + ctx->Return()->getText();
    addToTree(text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitYieldStatement(JavaScriptParser::YieldStatementContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitWithStatement(JavaScriptParser::WithStatementContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitSwitchStatement(JavaScriptParser::SwitchStatementContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitThrowStatement(JavaScriptParser::ThrowStatementContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitTryStatement(JavaScriptParser::TryStatementContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitDebuggerStatement(JavaScriptParser::DebuggerStatementContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitFunctionDeclaration(JavaScriptParser::FunctionDeclarationContext *ctx) {
    offset++;
    std::string text;
    if (ctx->Function()) {
        text = ctx->Function()->getText();
    }
    if (ctx->Async()) {
        notImplemented();
        return 1;
    }
    addToTree("FunctionDecl " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitClassDeclaration(JavaScriptParser::ClassDeclarationContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitFormalParameterArg(JavaScriptParser::FormalParameterArgContext *ctx) {
    offset++;
    std::string text;
    if (ctx->Assign()) {
        text = ctx->Assign()->getText();
    }
    text = "FormalParameterArg " + text;
    addToTree(text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitFunctionBody(JavaScriptParser::FunctionBodyContext *ctx) {
    offset++;
    addToTree("FunctionBody");
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitElementList(JavaScriptParser::ElementListContext *ctx) {
    offset++;
    addToTree("ElementList");
    auto vc = visitChildren(ctx);
    if (!ctx->children.size()) {
        offset++;
        addToTree("Null");
        offset--;
    }
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPropertyExpressionAssignment(JavaScriptParser::PropertyExpressionAssignmentContext *ctx) {
    offset++;
    addToTree("PropertyExpressionAssignment");
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any
MyVisitor::visitComputedPropertyExpressionAssignment(
        JavaScriptParser::ComputedPropertyExpressionAssignmentContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->OpenBracket());
    addToTree("ComputedPropertyExpressionAssignment " + paren);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseBracket());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitFunctionProperty(JavaScriptParser::FunctionPropertyContext *ctx) {
    offset++;
    addToTree("FunctionProperty");
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPropertySetter(JavaScriptParser::PropertySetterContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->OpenParen());
    paren += " " + getTermMode(ctx->OpenBrace());
    addToTree("PropertySetter " + paren);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseParen());
    addTermNode(ctx->CloseBrace());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPropertyName(JavaScriptParser::PropertyNameContext *ctx) {
    offset++;
    std::string nm;
    addToTree("PropertyName");
    addTermNode(ctx->OpenBracket());
    addTermNode(ctx->StringLiteral());
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseBracket());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitArguments(JavaScriptParser::ArgumentsContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->OpenParen());
    addToTree("Arguments " + text);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseParen());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitTernaryExpression(JavaScriptParser::TernaryExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitLogicalAndExpression(JavaScriptParser::LogicalAndExpressionContext *ctx) {
    offset++;
    addToTree("BitLogicalAndExpression " + ctx->And()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPowerExpression(JavaScriptParser::PowerExpressionContext *ctx) {
    offset++;
    addToTree("PowerExpression " + ctx->Power()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPreIncrementExpression(JavaScriptParser::PreIncrementExpressionContext *ctx) {
    offset++;
    addToTree("PreIncrementExpression " + ctx->PlusPlus()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitObjectLiteralExpression(JavaScriptParser::ObjectLiteralExpressionContext *ctx) {
    offset++;
    addToTree("ObjectLiteral");
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitInExpression(JavaScriptParser::InExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->In());
    addToTree("InExpression " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitLogicalOrExpression(JavaScriptParser::LogicalOrExpressionContext *ctx) {
    offset++;
    addToTree("BitLogicalOrExpression " + ctx->Or()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitNotExpression(JavaScriptParser::NotExpressionContext *ctx) {
    offset++;
    addToTree("NotExpression " + ctx->Not()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPreDecreaseExpression(JavaScriptParser::PreDecreaseExpressionContext *ctx) {
    offset++;
    addToTree("PreDecreaseExpression " + ctx->MinusMinus()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitAwaitExpression(JavaScriptParser::AwaitExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitThisExpression(JavaScriptParser::ThisExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->This());
    addToTree("ThisExpression " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitUnaryMinusExpression(JavaScriptParser::UnaryMinusExpressionContext *ctx) {
    offset++;
    addToTree("UnaryMinusExpression " + ctx->Minus()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitAssignmentExpression(JavaScriptParser::AssignmentExpressionContext *ctx) {
    offset++;
    addToTree("AssignmentExpression " + ctx->Assign()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPostDecreaseExpression(JavaScriptParser::PostDecreaseExpressionContext *ctx) {
    offset++;
    addToTree("PostDecreaseExpression " + ctx->MinusMinus()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitTypeofExpression(JavaScriptParser::TypeofExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitInstanceofExpression(JavaScriptParser::InstanceofExpressionContext *ctx) {
    notImplemented();
    auto vc = visitChildren(ctx);
    return vc;
}

antlrcpp::Any MyVisitor::visitUnaryPlusExpression(JavaScriptParser::UnaryPlusExpressionContext *ctx) {
    offset++;
    addToTree("UnaryPlusExpression " + ctx->Plus()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitDeleteExpression(JavaScriptParser::DeleteExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitImportExpression(JavaScriptParser::ImportExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitEqualityExpression(JavaScriptParser::EqualityExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->Equals_());
    if (text.empty()) {
        text = getTermMode(ctx->NotEquals());
        if (text.empty()) {
            text = getTermMode(ctx->IdentityEquals());
        }
    }
    addToTree("EqualityExpression " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitBitXOrExpression(JavaScriptParser::BitXOrExpressionContext *ctx) {
    offset++;
    addToTree("BitXOrExpression " + ctx->BitXOr()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitMultiplicativeExpression(JavaScriptParser::MultiplicativeExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->Multiply());
    if (text.empty()) {
        text = getTermMode(ctx->Divide());
    }
    ctx->Modulus()->getText();
    addToTree("MultiplicativeExpression " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitBitShiftExpression(JavaScriptParser::BitShiftExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->LeftShiftArithmetic());
    if (text.empty()) {
        text = getTermMode(ctx->RightShiftArithmetic());
    }
    addToTree("BitShiftExpression " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitParenthesizedExpression(JavaScriptParser::ParenthesizedExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->OpenParen());
    addToTree("ParenthesizedExpression " + text);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseParen());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitAdditiveExpression(JavaScriptParser::AdditiveExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->Plus());
    if (text.empty()) {
        text = getTermMode(ctx->Minus());
    }
    addToTree("AdditiveExpression " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitRelationalExpression(JavaScriptParser::RelationalExpressionContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->LessThan());
    if (text.empty()) {
        text = getTermMode(ctx->MoreThan());
        if (text.empty()) {
            text = getTermMode(ctx->LessThanEquals());
            if (text.empty()) {
                text = getTermMode(ctx->GreaterThanEquals());
            }
        }

    }
    addToTree("EqualityExpression " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitPostIncrementExpression(JavaScriptParser::PostIncrementExpressionContext *ctx) {
    offset++;
    addToTree("PostIncrementExpression " + ctx->PlusPlus()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitBitNotExpression(JavaScriptParser::BitNotExpressionContext *ctx) {
    offset++;
    addToTree("BitNotExpression " + ctx->BitNot()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitNewExpression(JavaScriptParser::NewExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitMemberDotExpression(JavaScriptParser::MemberDotExpressionContext *ctx) {
    offset++;
    std::string paren = getTermMode(ctx->Dot());
    addToTree("Arguments " + paren);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitClassExpression(JavaScriptParser::ClassExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitMemberIndexExpression(JavaScriptParser::MemberIndexExpressionContext *ctx) {
    offset++;
    addTermNode(ctx->OpenBracket());
    auto vc = visitChildren(ctx);
    addTermNode(ctx->CloseBracket());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitBitAndExpression(JavaScriptParser::BitAndExpressionContext *ctx) {
    offset++;
    addToTree("BitAndExpression " + ctx->BitAnd()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitBitOrExpression(JavaScriptParser::BitOrExpressionContext *ctx) {
    offset++;
    addToTree("BitOrExpression " + ctx->BitOr()->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitVoidExpression(JavaScriptParser::VoidExpressionContext *ctx) {
    notImplemented();
    return 1;
}

antlrcpp::Any MyVisitor::visitAssignable(JavaScriptParser::AssignableContext *ctx) {
    return visitChildren(ctx);
}

antlrcpp::Any MyVisitor::visitAnoymousFunctionDecl(JavaScriptParser::AnoymousFunctionDeclContext *ctx) {
    if (ctx->Async()) {
        notImplemented();
        return 1;
    }
    offset++;
    std::string text = getTermMode(ctx->OpenParen());
    if (text.empty()) {
        text = getTermMode(ctx->OpenBrace());
    }
    if (ctx->Function()) {
        text += getTermMode(ctx->Function());
    }
    addToTree("AnoymousFunctionDecl " + text);
    auto vc = visitChildren(ctx);
    addTermNode(ctx->OpenParen());
    addTermNode(ctx->CloseBrace());
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitArrowFunction(JavaScriptParser::ArrowFunctionContext *ctx) {
    notImplemented();
//    auto vc = visitChildren(ctx);
    return 1;
}

antlrcpp::Any MyVisitor::visitArrowFunctionParameters(JavaScriptParser::ArrowFunctionParametersContext *ctx) {
    notImplemented();
//    auto vc = visitChildren(ctx);
    return 1;
}

antlrcpp::Any MyVisitor::visitAssignmentOperator(JavaScriptParser::AssignmentOperatorContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->PowerAssign());
    text += getTermMode(ctx->BitOrAssign());
    text += getTermMode(ctx->BitXorAssign());
    text += getTermMode(ctx->BitAndAssign());
    text += getTermMode(ctx->RightShiftLogicalAssign());
    text += getTermMode(ctx->RightShiftArithmeticAssign());
    text += getTermMode(ctx->LeftShiftArithmeticAssign());
    text += getTermMode(ctx->PlusAssign());
    text += getTermMode(ctx->ModulusAssign());
    text += getTermMode(ctx->DivideAssign());
    text += getTermMode(ctx->MultiplyAssign());
    addToTree(text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitLiteral(JavaScriptParser::LiteralContext *ctx) {
    offset++;
    std::string text;
    text = getTermMode(ctx->NullLiteral());
    text += getTermMode(ctx->BooleanLiteral());
    text += getTermMode(ctx->StringLiteral());
    text += getTermMode(ctx->TemplateStringLiteral());
    text += getTermMode(ctx->RegularExpressionLiteral());
    addToTree("Literal " + text);
    auto vc = visitChildren(ctx);
    offset -= 2;
    return vc;
}

antlrcpp::Any MyVisitor::visitNumericLiteral(JavaScriptParser::NumericLiteralContext *ctx) {
    offset++;
    addToTree("NumericLiteral " + ctx->getText());
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitGetter(JavaScriptParser::GetterContext *ctx) {
    offset++;
    addToTree("Getter");
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitSetter(JavaScriptParser::SetterContext *ctx) {
    offset++;
    addToTree("Setter");
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitIdentifier(JavaScriptParser::IdentifierContext *ctx) {
    if (ctx->NonStrictLet()) {
        notImplemented();
        return 1;
    }
    if (ctx->Async()) {
        notImplemented();
        return 1;
    }
    offset++;
    std::string text = getTermMode(ctx->Identifier());
    addToTree("Identifier " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitReservedWord(JavaScriptParser::ReservedWordContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->BooleanLiteral());
    text += getTermMode(ctx->NullLiteral());
    addToTree("ReservedWord " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

antlrcpp::Any MyVisitor::visitKeyword(JavaScriptParser::KeywordContext *ctx) {
    offset++;
    std::string text = getTermMode(ctx->If());
    text += getTermMode(ctx->Break());
    text += getTermMode(ctx->Do());
    text += getTermMode(ctx->Typeof());
    text += getTermMode(ctx->Else());
    text += getTermMode(ctx->Continue());
    text += getTermMode(ctx->For());
    text += getTermMode(ctx->While());
    text += getTermMode(ctx->Function());
    text += getTermMode(ctx->This());
    text += getTermMode(ctx->Default());
    text += getTermMode(ctx->Delete());
    text += getTermMode(ctx->In());
    text += getTermMode(ctx->Class());
    text += getTermMode(ctx->Enum());
    text += getTermMode(ctx->Extends());
    text += getTermMode(ctx->Super());
    text += getTermMode(ctx->Const());
    text += getTermMode(ctx->Export());
    text += getTermMode(ctx->Import());
    text += getTermMode(ctx->Implements());
    text += getTermMode(ctx->Private());
    text += getTermMode(ctx->Public());
    text += getTermMode(ctx->Interface());
    text += getTermMode(ctx->Package());
    text += getTermMode(ctx->Protected());
    text += getTermMode(ctx->From());
    text += getTermMode(ctx->As());
    addToTree("Keyword " + text);
    auto vc = visitChildren(ctx);
    offset--;
    return vc;
}

void MyVisitor::addWhiteSpace(std::string &str) const {
    for (int i = 0; i < offset * 4; i++) {
        str.insert(str.begin(), ' ');
    }
}

void MyVisitor::addToTree(std::string str) {
    addWhiteSpace(str);
    stringTree.push_back(str);
}

