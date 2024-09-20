#include "AST1.h"
int indentValue = 1;

void printIndent(int level) {
    for (int i = 0; i < level; i++) {
        printf("-");
    }
}

void traverseAST(ASTNode* node, int level) {
    if (!node) {
        printf ("Nothing to traverse\n");
        return;
    }
        // printf("Node is not null!\n");
    printIndent(level);
    // printf("Traversing node of type %d\n", node->type);
    switch (node->type) {
        case NodeType_Program:
            printf("Program\n");
            traverseAST(node->program.varDeclList, level + indentValue);
            traverseAST(node->program.stmtList, level + indentValue);
            printf("|\n");
            break;
        case NodeType_VarDeclList:
            printf("Variable Declaration List\n");
            traverseAST(node->varDeclList.varDecl, level + indentValue);
            traverseAST(node->varDeclList.varDeclList, level + indentValue);
            break;
        case NodeType_VarDecl:
            printf("Variable Declaration: %s %s\n", node->varDecl.varType, node->varDecl.varName);
            break;
        case NodeType_SimpleExpr:
            printf("Simple Expression: %d\n", node->simpleExpr.number);
            break;
        case NodeType_Expr:
            // printf("Expression: %c\n", node->expr.operator);
            // printf("Expression: %s\n", node->expr.operator);
            printf("Expression\n", node->expr.operator);
            traverseAST(node->expr.left, level + indentValue);
            traverseAST(node->expr.operator, level + indentValue);
            traverseAST(node->expr.right, level + indentValue);
            break;
        case NodeType_StmtList:
            printf("Statement List\n");
            traverseAST(node->stmtList.stmt, level + indentValue);
            traverseAST(node->stmtList.stmtList, level + indentValue);
            break;
        case NodeType_Stmt:
            printf("Statement: %s %s\n", node->stmt.varName, node->stmt.operator);
            traverseAST(node->stmt.expr, level + indentValue);
            break;
        case NodeType_BinOp:
            printf("Binary Operator: %s\n", node->binOp.operator);
            break;
    }
}

// print one node
void printASTNode(ASTNode* node) {
    if (!node) {
        printf ("Nothing to print\n");
        return;
    }
    printf("Traversing node of type %d\n", node->type);
    switch (node->type) {
        case NodeType_Program:
            printf("Program\n");
            break;
        case NodeType_VarDeclList:
            printf("Variable Declaration List\n");
            break;
        case NodeType_VarDecl:
            printf("Variable Declaration: %s %s\n", node->varDecl.varType, node->varDecl.varName);
            break;
        case NodeType_SimpleExpr:
            printf("Simple Expression\n");
            break;
        case NodeType_Expr:
            printf("Expression\n");
            break;
        case NodeType_StmtList:
            printf("Statement List\n");
            break;
        case NodeType_Stmt:
            printf("Statement: %s %s\n", node->stmt.varName, node->stmt.operator);
            break;
    }
} 

void freeAST(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NodeType_Program:
            free(node->program.varDeclList);
            free(node->program.stmtList);
            break;
        case NodeType_VarDeclList:
            free(node->varDeclList.varDecl);
            free(node->varDeclList.varDeclList);
            break;
        case NodeType_VarDecl:
            free(node->varDecl.varType);
            free(node->varDecl.varName);
            break;
        case NodeType_SimpleExpr:
            free(node->simpleExpr.number);
            break;
        case NodeType_Expr:
            free(node->expr.left);
            free(node->expr.right);
            free(node->expr.operator);
            break;
        case NodeType_StmtList:
            free(node->stmtList.stmt);
            free(node->stmtList.stmtList);
            break;
        case NodeType_Stmt:
            free(node->stmt.varName);
            free(node->stmt.operator);
            free(node->stmt.expr);
            break;
    }

    free(node);
}

ASTNode* createNode(NodeType type) {
    ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
    if (newNode == NULL) {
        // Handle memory allocation failure if needed
        return NULL;
    }

    newNode->type = type;

    // Initialize the node based on its type
    switch (type) {
        case NodeType_Program:
            newNode->program.varDeclList = NULL;
            newNode->program.stmtList = NULL;
            break;
        case NodeType_VarDeclList:
            newNode->varDeclList.varDecl = NULL;
            newNode->varDeclList.varDeclList = NULL;
            break;
        case NodeType_VarDecl:
            newNode->varDecl.varType = NULL;
            newNode->varDecl.varName = NULL;
            break;
        case NodeType_SimpleExpr:
            newNode->simpleExpr.number = NULL;
            break;
        case NodeType_Expr:
            newNode->expr.operator = NULL;  // Placeholder value
            newNode->expr.left = NULL;
            newNode->expr.right = NULL;
            break;
        case NodeType_StmtList:
            newNode->stmtList.stmt = NULL;  // Example initialization
            newNode->stmtList.stmtList = NULL;
            break;
        case NodeType_Stmt:
            newNode->stmt.operator = NULL;  // Example initialization
            newNode->stmt.varName = NULL;
            newNode->stmt.expr = NULL;
            break;
        // Add more cases as necessary for other node types
    }

    return newNode;
}
