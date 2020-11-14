/* Defining the strucutre of the transform in a way that it can sees what surrounds it locally in order to achieve a performant collision detection in worlds that has above average entities
 * We keep the ecs query as it when looping globally over entities that satisfies collision system, and with this kind of structure of the transform we can find nearest entities that might collide
 * which will prevent us from looping over all entities eitther by abroad or narrow detecttion
 *
 * */
#include <stdio.h>
#include <stdlib.h>

struct Transform {
	int x;
  int y;
	struct Transform* next_x;
	struct Transform* next_y;
};

struct Transform* sortedInsert(struct Transform** head_ref, int x, int y) {
  struct Transform* new_trans = (struct Transform*)malloc( sizeof(struct Transform));

  new_trans->x = x;
  new_trans->y = y;

  struct Transform* current_x;
  struct Transform* current_y;

  int searching = 2;

  current_x = *head_ref;
  current_y = *head_ref;

  while (searching) {
    if (current_x->next_x != NULL
        && current_x->next_x->x < new_trans->x) {
      current_x = current_x->next_x;
      searching = 2;
    } else {
      searching = 1;
    }

    if (current_y->next_y != NULL
        && current_y->next_y->y < new_trans->y) {
      current_y = current_y->next_y;
      searching = 2;
    } else {
      searching--;
    }
  }

  new_trans->next_x = current_x->next_x;
  current_x->next_x = new_trans;

  new_trans->next_y = current_y->next_y;
  current_y->next_y = new_trans;

  return new_trans;
}

void printListx(struct Transform* head) {
  struct Transform* temp = head;
  while (temp != NULL) {
    printf("%d ", temp->x);
    temp = temp->next_x;
  }
}

void printListy(struct Transform* head) {
  struct Transform* temp = head;
  while (temp != NULL) {
    printf("%d ", temp->y);
    temp = temp->next_y;
  }
}

// Test
int main() {
  struct Transform* head = (struct Transform*)malloc( sizeof(struct Transform));
  head->x = -1000000000;
  head->y = -1000000000;
  for (int i = 0; i < 10000; i++) {
    sortedInsert(&head, i, i);
  }

  printListx(head);
  printf("\n");
  printListy(head);
  printf("\n");

  return 0;
}
