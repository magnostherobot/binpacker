#include <stdio.h>
typedef struct { int w; int h; } rect;
typedef struct node { struct node *a; struct node *b; rect r; int id; } node;

node *insert(node *n, rect r, node **alloc) {
    if (!n->id) {
        if (n->r.w - r.w < 0 || n->r.h - r.h < 0) return 0;
        n->a = (*alloc)++;
        n->b = (*alloc)++;
        n->a->r = (rect){ .w = n->r.w - r.w, .h = r.h };
        n->b->r = (rect){ .w = n->r.w, .h = n->r.h - r.h };
        return n;
    }
    node *new_node = insert(n->a, r, alloc);
    return new_node ? new_node : insert(n->b, r, alloc);
}

void print_tree(node *n, int x, int y) {
    printf("%i: (%i, %i)\n", n->id, x, y);
    if (n->a && n->a->id) print_tree(n->a, x + n->r.w - n->a->r.w, y);
    if (n->b && n->b->id) print_tree(n->b, x, y + n->r.h - n->b->r.h);
}

int main() {
    node alloc[100] = {0};
    node *np = &alloc[1];
    alloc[0].r.w = 1000;
    alloc[0].r.h = 1000;

    rect r;
    r.w = 201;
    r.h = 100;

    for (int i = 0; i < 21; i++) {
        insert(&alloc[0], r, &np)->id = i+1;
    }
    print_tree(&alloc[0], 0, 0);
}
