#include "s21_smart_calc.h"

Node *list_create() { return NULL; }

// void print_stack(Node * list){
//     for (Node * p = list; p != NULL; p = p->next) {
//         printf("| %s |", p->data);
//     }
//     printf("\n");
// }

int is_empty_stack(Node *list) { return list == NULL; }

char *peek_stack(struct Node *list) {
  if (list) return list->data;
  return NULL;
}

// int  stack_size(struct Node * list)
// {
//     Node * t;
//     int size = 0;
//     for (t=list; t!=NULL; t = t->next)
//         size ++;
//     return size;
// }

void clear_stack(struct Node **plist) {
  Node *t;
  while (*plist != NULL) {
    t = *plist;
    *plist = (*plist)->next;
    // free(t->data);
    free(t);
  }
}

void push(Node **list, char *x) {
  Node *p = malloc(sizeof(Node));
  strcpy(p->data, x);

  p->next = *list;
  *list = p;
}

char *pop(Node **list) {
  if (*list != NULL) {
    Node *p = *list;
    char *res = (char *)malloc(20);
    memset(res, 0, 20);
    strcpy(res, (*list)->data);
    *list = p->next;
    free(p);
    return res;
  }
  return NULL;
}