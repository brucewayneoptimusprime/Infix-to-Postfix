#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a stack of characters
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Function to create a new stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return '\0'; // Return null character for an empty stack
}

// Function to return the top element of the stack without popping it
char peek(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top];
    }
    return '\0'; // Return null character for an empty stack
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to get the precedence of an operator
int precedence(char ch) {
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

// Function to convert an infix expression to a postfix expression
void infixToPostfix(char* infix) {
    int i, j;
    struct Stack* stack = createStack(strlen(infix));
    if (!stack) {
        return; // Error handling for stack creation failure
    }

    printf("Postfix Expression: ");
    for (i = 0, j = -1; infix[i]; ++i) {
        char c = infix[i];
        if (isalnum(c)) {
            printf("%c", c);
        } else if (c == '(') {
            push(stack, c);
        } else if (c == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                printf("%c", pop(stack));
            }
            if (!isEmpty(stack) && peek(stack) != '(') {
                printf("Invalid Expression\n");
                return; // Error handling for mismatched parentheses
            } else {
                pop(stack);
            }
        } else { // Operator
            while (!isEmpty(stack) && precedence(c) <= precedence(peek(stack))) {
                printf("%c", pop(stack));
            }
            push(stack, c);
        }
    }

    while (!isEmpty(stack)) {
        printf("%c", pop(stack));
    }
    printf("\n");
    free(stack->array);
    free(stack);
}

int main() {
    char infix[100];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix);
    return 0;
}

