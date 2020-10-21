#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

/**
 * Pushes a new entry onto the stack.
 *
 * @param s the stack onto which the item should be pushed
 * @param item the item that should be pushed onto the stack
 */
void push_stack(Stack *s, void *item)
{
    // Make a new entry in the stack
    StackNode *new_node = malloc(sizeof(StackNode));
    new_node->contents = item;
    new_node->prev = s->head;

    s->head = new_node;
}

/**
 * Pops the last item form the stack.
 */
void *pop_stack(Stack *s)
{
    StackNode *temp = s->head;
    s->head = temp->prev;

    return temp;
}
