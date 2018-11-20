/* Handle to stack */
struct stack;

/* Return a pointer to a stack data structure if succesful, return
 * NULL on failure.
 * Size of stack is fixed. */
struct stack *stack_init(void);

/* Cleanup stack. */
void stack_cleanup(struct stack* stack);

/* Push item onto the stack.
 * Return 0 if succesful, 1 otherwise. */
int stack_push(struct stack* stack, void* e);

/* Pop item from stack and return it.
 * Return top item if succesful, NULL otherwise. */
void* stack_pop(struct stack* stack);

/* Return top of item from stack. Leave stack unchanged.
 * Return top item if succesful, NULL if stack is empty. */
void* stack_peek(struct stack* stack);

/* Return 1 if stack is empty, 0 otherwise. */
int stack_empty(struct stack* stack);
