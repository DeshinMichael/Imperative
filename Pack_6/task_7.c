#include <stdio.h>
#include <stdlib.h>

typedef struct Node_s {
    void *value;
    struct Node_s *prev;
    struct Node_s *next;
} Node;

typedef Node List;

void initList(List *list) {
    list->value = NULL;
    list->prev = list;
    list->next = list;
}

Node *addAfter(Node *node, void *ptr) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->value = ptr;
    new_node->next = node->next;
    new_node->prev = node;
    node->next = new_node;
    new_node->next->prev = new_node;
    return new_node;
}

Node *addBefore(Node *node, void *ptr) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->value = ptr;
    new_node->prev = node->prev;
    new_node->next = node;
    node->prev = new_node;
    new_node->prev->next = new_node;
    return new_node;
}

void *erase(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node->value);
    free(node);
    node = NULL;
}

void print_list(List *list) {
    for (List *i = list->next; i != list; i = i->next) {
        printf("%d\n", *(int *) i->value);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t, q;
    int oper, curr_i;
    int cnt;
    int val;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        scanf("%d", &q);
        
        List *head = (List *) malloc(sizeof(List));
        Node **list = (Node **) malloc(q * sizeof(Node *));
        int *intPtr;
        void *ptr;
        cnt = 0;

        initList(head);

        for (int i = 0; i < q; i++) {
            scanf("%d", &oper);

            switch (oper) {
                case 1:
                    scanf("%d %d", &curr_i, &val);
                    intPtr = (int *) malloc(sizeof(int));
                    *intPtr = val;  
                    ptr = (void *) intPtr;
                    if (curr_i == -1) list[cnt] = addAfter(head, ptr);
                    else list[cnt] = addAfter(list[curr_i], ptr);
                    cnt++;
                    break;
                case -1:
                    scanf("%d %d", &curr_i, &val);
                    intPtr = (int *) malloc(sizeof(int));
                    *intPtr = val;
                    ptr = (void *) intPtr;
                    if (curr_i == -1) list[cnt] = addBefore(head, ptr);
                    else list[cnt] = addBefore(list[curr_i], ptr);
                    cnt++;
                    break;
                case 0:
                    scanf("%d", &curr_i);
                    erase(list[curr_i]);
                    break;
            }
        }
        print_list(head);
        printf("===\n");

        Node *current = head->next;
        while (current != head) {
            Node *next = current->next;
            if (current != NULL) {
                free(current->value);
                free(current);
            }
            current = next;
        }
        free(head);
        free(list);
    }

    return 0;
}