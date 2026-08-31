// Adapted from https://github.com/munificent/craftinginterpreters

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stringNode {
  struct stringNode* prev;
  struct stringNode* next;
  char* string;
} Node;

// insert a new string node after prev or at prev if prev is null
void insert(Node** list, Node* prev, const char* string) {
  // create new node and copy string to heap
  Node* node = malloc(sizeof(Node));
  node->string = malloc(strlen(string) + 1);
  strcpy(node->string, string);

  if (prev == NULL) {
    if (*list != NULL) (*list)->prev = node;
    node->prev = NULL;
    node->next = *list;
    *list = node;
  } else {
    node->next = prev->next;
    if (node->next != NULL) node->next->prev = node;
    prev->next = node;
    node->prev = prev;
  }
}

Node* find(Node* list, const char* string) {
  while (list != NULL) {
    if (strcmp(string, list->string) == 0) {
      return list;
    }
    
    list = list->next;
  }
  
  // string not found
  return NULL;
}

void delete(Node** list, Node* node) {
  // unlink
  if (node->prev != NULL) node->prev->next = node->next;
  if (node->next != NULL) node->next->prev = node->prev;
  
  // update head node if we are deleting it
  if (*list == node) *list = node->next;
  
  // clean up
  free(node->string);
  free(node);
}

void printList(Node* list) {
  int count = 0;
  while (list != NULL) {
    printf("Node %d: %p || prev %p || next %p || string: %s\n",
    count, list, list->prev, list->next, list->string);
    list = list->next;
  count = count + 1;
  }
}

int main(int argc, const char* argv[]) {
  printf("Hello World!\n");
  
  Node* list = NULL;
  insert(&list, NULL, "four");
  insert(&list, NULL, "one");
  insert(&list, find(list, "one"), "two");
  insert(&list, find(list, "two"), "three");
  
  printList(list);
  printf("DELETE \"three\"\n");
  delete(&list, find(list, "three"));
  printList(list);

  printf("DELETE \"one\"\n");
  delete(&list, find(list, "one"));
  printList(list);

  return 0;
}