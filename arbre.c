#include <stdlib.h>
#include <stdio.h>

struct Node {
    char operator; // '+', '-', '*', '/' ou '\0' pour les feuilles
    char var_name; // nom de la variable pour les feuilles
    double value;  // valeur pour les feuilles
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;

typedef struct Variable {
    char varName;
    double varValue;
} Variable;

typedef struct Context
{
    size_t size;
    Variable *vars;
} Context;

void registerValue(Context *ctx, char vname, double value){
    ctx->size += 1;
    Variable* ptr = realloc(ctx->vars, ctx->size * sizeof(Variable));
    if (ptr != NULL){
        ctx->vars = ptr;    
        Variable var = { .varName = vname, .varValue = value };
        ctx->vars[ctx->size -1] = var;
    }
}

Variable *getValue(Context *ctx, char vname){
    for (size_t i = 0; i < ctx->size; i++){
        if (ctx->vars[i].varName == vname){
            return &ctx->vars[i];
        }
    }
    return NULL;  
}

Node* create_leaf(double value){
    Node* feuille = malloc(sizeof(Node));
    feuille->operator = '\0';
    feuille->var_name = NULL;
    feuille->value = value;
    feuille->left = NULL;
    feuille->right = NULL;
    return feuille;
}

Node* create_operator_node(char operator, Node* left, Node* right){
    Node* noeud = malloc(sizeof(Node));
    noeud->operator = operator;
    noeud->left = left;
    noeud->right = right;
    noeud->value = 0.0;
    noeud->var_name = NULL;
    return noeud;
}

Node* create_variable_node(char var_name){
    Node* variable = malloc(sizeof(Node));
    variable->operator = '\0';
    variable->left = NULL;
    variable->right = NULL;
    variable->value = 0.0;
    variable->var_name = var_name;
    return variable;
}

double evaluate(const Node* root, Context* ctx){
    if (root->operator != '\0'){
        char op = root->operator;
        switch(op){
            case '+':
                return( evaluate(root->left, ctx) + evaluate(root->right, ctx));
            case '-':
                return( evaluate(root->left, ctx) - evaluate(root->right, ctx));
            case '*':
                return( evaluate(root->left, ctx) * evaluate(root->right, ctx));
            case '/':
                return( evaluate(root->left, ctx) / evaluate(root->right, ctx));
        }
        
    }
    if (root->var_name == NULL){
        return root->value;
    }
    else {
        Variable *var = getValue(ctx, root->var_name);
        return var->varValue;
    }
}

void free_tree(Node* root){
    if (root == NULL){
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}


int main(){
    return 42;
}