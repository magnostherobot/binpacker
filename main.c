#include <stdio.h>
typedef struct { int top; int left; int width; int height; } rect;
typedef struct node { struct node *left; struct node *right; rect rc; int id;
} node;

node *insert(node *n, rect r, node **alloc) {
    if (!n->id) {
        if (n->rc.width - r.width < 0 || n->rc.height - r.height < 0) return 0;
        n->left = (*alloc)++;
        n->right = (*alloc)++;
        n->left->rc.top = n->rc.top;
        n->left->rc.left = n->rc.left + r.width;
        n->left->rc.width = n->rc.width - r.width;
        n->left->rc.height = r.height;
        n->right->rc.top = n->rc.top + r.height;
        n->right->rc.left = n->rc.left;
        n->right->rc.width = n->rc.width;
        n->right->rc.height = n->rc.height - r.height;
        return n;
    } else {
        node *new_node = insert(n->left, r, alloc);
        if (new_node) return new_node;
        else return insert(n->right, r, alloc);
    }
}

void print_tree(node *n) {
    if (!n->id) return;
    printf("%i: (%i, %i)\n", n->id, n->rc.left, n->rc.top);
    if (n->left) print_tree(n->left);
    if (n->right) print_tree(n->right);
}

int main() {
    node alloc[100] = {0};
    node *np = &alloc[1];
    alloc[0].rc.top = 0;
    alloc[0].rc.left = 0;
    alloc[0].rc.width = 1000;
    alloc[0].rc.height = 1000;

    rect r;
    r.width = 201;
    r.height = 100;

    for (int i = 0; i < 21; i++) {
        insert(&alloc[0], r, &np)->id = i+1;
        printf("\n");
        print_tree(&alloc[0]);
    }
}
