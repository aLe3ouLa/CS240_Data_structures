#ifndef STACK__
#define STACK__

struct stack { 
	void *ptr;
	struct stack *next; 
};

void push(struct stack **, void *);
void *pop(struct stack **);

#endif