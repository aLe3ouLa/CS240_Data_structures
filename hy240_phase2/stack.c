#include<stdlib.h>
#include "stack.h"

void push(struct stack **p, void *value) {
	struct stack *temp = (struct node*)malloc(sizeof(struct stack));
	temp->ptr = value;
    temp->next = *p == NULL ? NULL : *p;
	*p = temp;
}

void *pop(struct stack **p) { 
	struct stack *temp = *p;
	void *value = temp->ptr;
	*p = temp->next;
	free(temp);
	return value;
}