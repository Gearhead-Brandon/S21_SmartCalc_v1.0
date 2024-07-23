#include "s21_smart_calc.h"

struct Node *newNode(char *item) {
  // выделяем новый узел в куче
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));

  strcpy(node->data, item);
  node->next = NULL;
  return node;
}

int is_empty_queue(Queue *q) { return q->tail == NULL && q->head == NULL; }

char *peek_queue(Queue *q) {
  // проверяем наличие пустой queue
  if (q->head != NULL) return q->head->data;

  return NULL;
}

void enqueue(Queue *q, char *item) {
  struct Node *node = newNode(item);

  // особый случай: queue пуста
  if (q->head == NULL) {
    // инициализируем и переднюю, и заднюю часть
    q->head = node;
    q->tail = node;
  } else {
    // обновить заднюю часть
    q->tail->next = node;
    q->tail = node;
  }
}

char *dequeue(Queue *q) {
  if (q->head != NULL) {
    Node *temp = q->head;

    // продвигаемся вперед к следующему узлу
    q->head = q->head->next;

    // если список станет пустым
    if (q->head == NULL) q->tail = NULL;

    // освобождаем память удаленного узла и при необходимости возвращаем
    // удаленный элемент

    char *res = (char *)malloc(20);
    memset(res, 0, 20);
    strcpy(res, temp->data);
    free(temp);
    return res;
  }
  return NULL;
}

void print_queue(Queue *lst) {
  Node *i;

  for (i = lst->head; i != NULL; i = i->next) {
    printf("| %s |", i->data);

    // if (i->next != lst->tail->next)
    //     printf(" -> ");
  }

  printf("\n");
}

void clear_queue(Queue *lst) {
  while (is_empty_queue(lst) != 1) {
    char *r = dequeue(lst);
    free(r);
  }
}