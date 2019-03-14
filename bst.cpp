/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include "general.h"
#include "bst.h"

struct Node{
    int value;
    Node* left;
    Node* right;
};

Bst new_bst() {
    return 0;
}

void delete_bst(Bst bst) {
    if (bst != 0) {
        delete_bst(bst->right);
        delete_bst(bst->left);
        sfree(bst);
    }
}

int get_depth(Bst bst) {
    if (bst == 0) return 0;

    if(bst->right == 0 && bst->left == 0) return 1;

    if(get_depth(right_subtree(bst)) > get_depth(left_subtree(bst))) return 1 + get_depth(right_subtree(bst));

    return 1 + get_depth(left_subtree(bst));
}

Bst create_new_node(Bst* bst, int value){
    Bst newNode = (Bst)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = 0;
    newNode->right = 0;
    return newNode;
}

void add(Bst* bst, int value) {
    if (*bst == 0) *bst = create_new_node(bst, value);
    else if (value <= (*bst)->value) {
        if((*bst)->left == 0){
            (*bst)->left = create_new_node(bst, value);
        }
        else{
            add(&(*bst)->left, value);
        }
    } else {
        if((*bst)->right == 0){
            (*bst)->right = create_new_node(bst, value);
        }
        else{
            add(&(*bst)->right, value);
        }
    }
}

int root_value(Bst bst) {
    if (bst == 0) return 0;
    return bst->value;
}

Bst left_subtree(Bst root) {
    return root->left;
}

Bst right_subtree(Bst root) {
    return root->right;
}

int traverse_pre_order(Bst bst, int *elements, int start) {
    if(bst != 0) {
        elements[start] = bst->value;
        if(get_depth(bst) > 0){
            start++;
            start = traverse_pre_order(bst->left, elements, start);
            start = traverse_pre_order(bst->right, elements, start);
        }
    }
    return start;
}

int traverse_in_order(Bst bst, int *elements, int start) {
    if (bst != 0) {
        if (bst->left != 0) {
            start = traverse_in_order(bst->left, elements, start);
        }
        elements[start] = bst->value;
        start ++;
        if (bst->right != 0) {
            start = traverse_in_order(bst->right, elements, start);
        }
    }
    return start;
}

int traverse_post_order(Bst bst, int *elements, int start) {
    if (bst != 0) {
        if (bst->left != 0) {
            start = traverse_post_order(bst->left, elements, start);
        }

        if (bst->right != 0) {
            start = traverse_post_order(bst->right, elements, start);
        }
        elements[start]= bst->value;
        start++;
    }
    return start;
}

bool are_equal(Bst bst1, Bst bst2) {
    if (bst1 == 0) {
        return bst2 == 0;
    }
    else if (get_depth(bst1) == get_depth(bst2)) {
        if (bst1->value == bst2->value) {
            return are_equal(bst1->right, bst2->right) && are_equal(bst1->left, bst2->left);
        }
    }
    return false;
}

void most_left_longest_branch(Bst bst, Bst* branch) {
    if (bst != 0) {
        if (get_depth(bst->left) >= get_depth(bst->right)) {
            add(branch, bst->value);
            most_left_longest_branch(bst->left, branch);
        } else {
            add(branch, bst->value);
            most_left_longest_branch(bst->right, branch);
        }
    }
}

int get_number_of_subtrees(Bst bst) {
    if(bst != 0){
        int* elements = new int[get_depth(bst)];
        return traverse_post_order(bst, elements, 0) -1;
    }
    return -1;
}
