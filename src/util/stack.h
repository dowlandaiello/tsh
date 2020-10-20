/**
 * A node in a stack.
 */
typedef struct StackNode {
    void *contents;
    struct StackNode *prev;
} StackNode;

/**
 * Basically what you think it is. A bunch of plates (void*) on a stack.
 */
typedef struct Stack {
    StackNode *head;
} Stack;

/**
 * Pushes a new entry onto the stack.
 *
 * @param s the stack onto which the item should be pushed
 * @param item the item that should be pushed onto the stack
 */
void push_stack(Stack *s, void *item);

/**
 * Pops the last item form the stack.
 */
void *pop_stack(Stack *s);
