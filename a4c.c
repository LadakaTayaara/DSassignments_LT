#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
char stack1[100][100];
char postfix[100];
char prefix[100];
int top = -1;
int top1 = -1;
int n = 100;
char popel;
char popstr[100];
char result[100];

void reverseString(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;

    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

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

int pre_icp(char c) {
    if (c == '(') return 5;
    if (c == '^') return 3;
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

int pre_isp(char c) {
    if (c == '(') return 0;
    if (c == '^') return 4;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void infix_to_postfix(char input[]) {
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

void infix_to_prefix(char input[]) {
    int i = 0;
    int j = 0;
    char temp_prefix[100];
    reverseString(input);
    while (input[i] != '\0') {
        if (input[i] == '(') {
            input[i] = ')';
        } else if (input[i] == ')') {
            input[i] = '(';
        }
        i++;
    }
    i = 0;
    while (input[i] != '\0') {
        char current_char = input[i];
        if (isalnum(current_char)) {
            temp_prefix[j++] = current_char;
        } else if (current_char == '(') {
            push(current_char);
        } else if (current_char == ')') {
            while (!isEmpty(top) && stack[top] != '(') {
                temp_prefix[j++] = pop();
            }
            if (!isEmpty(top) && stack[top] == '(') {
                pop();
            }
        } else {
            while (!isEmpty(top) && pre_isp(stack[top]) > pre_icp(current_char)) {
                temp_prefix[j++] = pop();
            }
            push(current_char);
        }
        i++;
    }
    while (!isEmpty(top)) {
        temp_prefix[j++] = pop();
    }
    temp_prefix[j] = '\0';
    reverseString(temp_prefix);
    strcpy(prefix, temp_prefix);
}

void postfix_to_infix(char input[]) {
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

void postfix_to_prefix(char input[]) {
    int len = strlen(input);
    char op1[100];
    char op2[100];
    char temp[100];

    for(int i = 0; i < len; i++) {
        char tkn = input[i];
        if (isalnum(tkn)) {
            char temp_str[2] = {tkn, '\0'};
            push1(temp_str);
        } else {
            pop1(op2);
            pop1(op1);
            strcpy(temp, "");
            char tkn_to_str[2] = {tkn, '\0'};
            strcat(temp, tkn_to_str);
            strcat(temp, op1);
            strcat(temp, op2);
            push1(temp);
        }
    }
}

void prefix_to_infix(char input[]) {
    int len = strlen(input);
    char op1[100];
    char op2[100];
    char temp[100];

    for(int i = len - 1; i >= 0; i--) {
        char tkn = input[i];
        if (isalnum(tkn)) {
            char temp_str[2] = {tkn, '\0'};
            push1(temp_str);
        } else {
            pop1(op1);
            pop1(op2);
            strcpy(temp, "(");
            strcat(temp, op1);
            char tkn_to_str[2] = {tkn, '\0'};
            strcat(temp, tkn_to_str);
            strcat(temp, op2);
            strcat(temp, ")");
            push1(temp);
        }
    }
}

void prefix_to_postfix(char input[]) {
    int len = strlen(input);
    char op1[100];
    char op2[100];
    char temp[100];

    for(int i = len - 1; i >= 0; i--) {
        char tkn = input[i];
        if (isalnum(tkn)) {
            char temp_str[2] = {tkn, '\0'};
            push1(temp_str);
        } else {
            pop1(op1);
            pop1(op2);
            strcat(temp, op1);
            strcat(temp, op2);
            char tkn_to_str[2] = {tkn, '\0'};
            strcat(temp, tkn_to_str);
            push1(temp);
        }
    }
}

int main() {
    char infix[100];
    char input_postfix[100];
    char input_prefix[100];
    char output[100];
    int ch = 0;
    char elem;
    while (ch != -1) {
        printf("\nFollowing are the stack operations that can be performed via this program on \n1.Infix to postfix\n2.Postfix to Infix\n3.Postfix to prefix\n4.Prefix to Infix\n5.Prefix to Postfix\n6.Infix to Prefix\n7.Exit\nEnter your choice\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter an infix expression: ");
                scanf("%s", infix);
                infix_to_postfix(infix);
                printf("The postfix expression is: %s\n", postfix);
                break;
            case 2:
                printf("Enter a postfix expression: ");
                scanf("%s", input_postfix);
                postfix_to_infix(input_postfix);
                pop1(output);
                printf("The infix expression is %s\n", output);
                output[0]='\0';
                break;
            case 3:
                printf("Enter a postfix expression: ");
                scanf("%s", input_postfix);
                postfix_to_prefix(input_postfix);
                pop1(output);
                printf("The prefix expression is %s\n", output);
                output[0]='\0';
                break;
            case 4:
                printf("Enter a prefix expression: ");
                scanf("%s", input_prefix);
                prefix_to_infix(input_prefix);
                pop1(output);
                printf("The infix expression is %s\n", output);
                output[0]='\0';
                break;
            case 5:
                printf("Enter a prefix expression: ");
                scanf("%s", input_prefix);
                prefix_to_postfix(input_prefix);
                pop1(output);
                printf("The postfix expression is %s\n", output);
                output[0]='\0';
                break;
            case 6:
                printf("Enter an infix expression: ");
                scanf("%s", infix);
                infix_to_prefix(infix);
                printf("The prefix expression is: %s\n", prefix);
                break;
            case 7:
                ch = -1;
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}