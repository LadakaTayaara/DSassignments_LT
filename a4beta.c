#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
char stack1[100][100];
char postfix[100];
int top = -1;
int top1 = -1;
int n = 100;
char popel;
char popstr[100];



int isFull(int current_top, int max_size) {
    return current_top == max_size - 1;
}

int isEmpty(int current_top) {
    return current_top == -1;
}

void push(char elem) {
    if (isFull(top, n)) {
        printf("\nStack is full\n");
    } else {
        top++;
        stack[top] = elem;
    }
}

char pop() {
    if (isEmpty(top)) {
        return '\0';
    } else {
        popel = stack[top];
        top--;
        return popel;
    }
}

void push1(char elem[]) {
    if (isFull(top1, n)) {
        printf("\nStack is full\n");
    } else {
        top1++;
        strcpy(stack1[top1], elem);
    }
}

void pop1(char result[]) {
    if (isEmpty(top1)) {
        result[0] = '\0';
    } else {
        strcpy(result, stack1[top1]);
        top1--;
    }
}

void display_char_stack() {
    if (isEmpty(top)) {
        printf("\nStack is empty\n");
    } else {
        printf("\n%c <------ TOP\n", stack[top]);
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

void pstfix(char input[]) {
    int i = 0;
    int j = 0;
    while (input[i] != '\0') {
        char current_char = input[i];
        if (isalnum(current_char)) {
            postfix[j++] = current_char;
        } else if (current_char == '(') {
            push(current_char);
        } else if (current_char == ')') {
            while (!isEmpty(top) && stack[top] != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty(top) && stack[top] == '(') {
                pop();
            }
        } else {
            while (!isEmpty(top) && isp(stack[top]) >= icp(current_char)) {
                postfix[j++] = pop();
            }
            push(current_char);
        }
        i++;
    }
    while (!isEmpty(top)) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

void infx(char input[]) {
    int i = 0;
    char op1[100];
    char op2[100];
    char temp[100];

    while (input[i] != '\0') {
        char tkn = input[i];
        if (isalnum(tkn)) {
            char temp_str[2] = {tkn, '\0'};
            push1(temp_str);
        } else {
            pop1(op2);
            pop1(op1);
            strcpy(temp, "(");
            strcat(temp, op1);
            char tkn_to_str[2] = {tkn, '\0'};
            strcat(temp,tkn_to_str);
            strcat(temp, op2);
            strcat(temp, ")");
            push1(temp);
        }
        i++;
    }
}

int main() {
    char infix[100];
    char input_postfix[100];
    char result_infix[100];
    int ch = 0;
    char elem;
    while (ch != -1) {
        printf("\nFollowing are the stack operations that can be performed via this program on \n1.Display Top\n2.Push\n3.Pop\n4.Exit\nEnter your choice\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                display_char_stack();
                break;
            case 2:
                if (isFull(top, n)) {
                    printf("Stack is full\n");
                } else {
                    printf("\nenter the element to push\n");
                    scanf(" %c", &elem);
                    push(elem);
                }
                break;
            case 3:
                if (isEmpty(top)) {
                    printf("Stack is empty\n");
                } else {
                    pop();
                }
                break;
            case 4:
                ch = -1;
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}