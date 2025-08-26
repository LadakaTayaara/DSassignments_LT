#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
char postfix[100];
int top = -1;
int n = 100;
char popel;

int isFull(char stack[100], int current_top, int max_size) {
    if (current_top == max_size - 1) {
        return 1;
    } else {
        return 0;
    }
}

int isEmpty(char stack[100], int current_top, int max_size) {
    if (current_top == -1) {
        return 1;
    } else {
        return 0;
    }
}

void push(char elem) {
    if (isFull(stack, top, n)) {
        printf("\nStack is full\n");
    } else {
        top++;
        stack[top] = elem;
    }
}

char pop() {
    if (isEmpty(stack, top, n)) {
        return '\0';
    } else {
        popel = stack[top];
        top--;
        return popel;
    }
}

int icp(char c) {
    if (c == '(') return 5;
    if (c == '^') return 4;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int isp(char c) {
    if (c == '(') return 0;
    if (c == '^') return 3;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void conversion(char input_infix[]) {
    int i = 0;
    int j = 0;
    while (input_infix[i] != '\0') {
        char current_char = input_infix[i];
        if (isalnum(current_char)) {
            postfix[j++] = current_char;
        } else if (current_char == '(') {
            push(current_char);
        } else if (current_char == ')') {
            while (!isEmpty(stack, top, n) && stack[top] != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty(stack, top, n) && stack[top] == '(') {
                pop();
            }
        } else {
            while (!isEmpty(stack, top, n) && isp(stack[top]) >= icp(current_char)) {
                postfix[j++] = pop();
            }
            push(current_char);
        }
        i++;
    }
    while (!isEmpty(stack, top, n)) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main() {
    char infix[100];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    conversion(infix);
    printf("The postfix expression is: %s\n", postfix);
    return 0;
}
