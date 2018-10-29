#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode, *SearchTree;

SearchTree create_tree(int value) {
    SearchTree tree = malloc(sizeof(TreeNode));
    if (tree == NULL)
        fatal_error("out of space");
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

SearchTree make_empty(SearchTree tree) {
    if (tree == NULL)
        return NULL;

    make_empty(tree->left);
    make_empty(tree->right);
    free(tree);
    return NULL;
}

SearchTree find(int value, SearchTree tree) {
    if (tree == NULL)
        return NULL;

    if (tree->value > value)
        return find(value, tree->left);
    if (tree->value < value)
        return find(value, tree->right);

    return tree;
}

SearchTree insert(int value, SearchTree tree) {
    if (tree == NULL) {
        tree = malloc(sizeof(TreeNode));
        if (tree == NULL)
            fatal_error("out of space");
        tree->value = value;
        tree->left = tree->right = NULL;
        return tree;
    }

    if (tree->value < value) 
        tree->right = insert(value, tree->right);
    else if (tree->value > value)
        tree->left = insert(value, tree->left);
    return tree;
    
}
