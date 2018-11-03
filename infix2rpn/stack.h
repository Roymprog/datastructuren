/* Handle to stack */
struct stack;

/* The stack has a fixed size. The size is exposed in the interface because
 * it is needed by the unit tests. */
#define STACK_SIZE 100

/* Return a pointer to a stack data structure if succesful, otherwise
 * return NULL.
 * Size of stack is fixed. */
struct stack *stack_init(void);

/* Cleanup stack.
 * Also prints the statistics. */
void stack_cleanup(struct stack *stack);

/* Push item onto the stack.
 * Return 0 if succesful, 1 otherwise. */
int stack_push(struct stack *stack, int e);

/* Pop item from stack and return it.
 * Return top item if succesful, -1 otherwise. */
int stack_pop(struct stack *stack);

/* Return top of item from stack. Leave stack unchanged.
 * Return top item if succesful, -1 if stack is empty. */
int stack_peek(struct stack *stack);

/* Return 1 if stack is empty, 0 otherwise. */
int stack_empty(struct stack *stack);
