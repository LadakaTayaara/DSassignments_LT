//corrections required

#include <stdio.h>
char stack[100];
char postfix[100];
char infix[100];
char popel;

//infix
int top1=-1;
int n1=100;
//postfix
int top2=-1;
int n2=100;
//stack
int top3=-1;
int n3=100;

int isFull(char stack[100],int top,int n){
    if (top==n-1){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(char stack[100],int top,int n){
    if (top==-1){
        return 1;
    }
    else{
        return 0;
    }
}

void push(char stack[100],char elem,int top,int n){
    if(isFull(stack,top,n)){
        printf("\nStack is full\n");
    }
    else{
        top++;
        stack[top]=elem;
        printf("\n%c\n",elem);
    }
}

void pop(char stack[100],int top,int n){
    if(isEmpty(stack,top,n)){
        printf("\nStack is empty\n");
    }
    else{
        popel=stack[top];
        top--;
        printf("element removed: %c",popel);
    }
}

void display(char stack[100],int top,int n){
    printf("\n===STACK DISPLAY===\n");
    for(int i=0;i<=top;i++){
        printf("\n%d\n======",stack[i]);
}}

int icp(char c){
    if(c=='('){
        return 5;
    }
    else if(c=='^'){
        return 4;
    }
    else if(c=='*'||c=='/'||c='%'){
        return 2;
    }
    else if(c=='+'||c=='-'){
        return 1;
    }
    else{
        return 0;
    }
}

int isp(char c){
    if(c=='('){
        return 0;
    }
    else if(c=='^'){
        return 3;
    }
    else if(c=='*'||c=='/'||c='%'){
        return 2;
    }
    else if(c=='+'||c=='-'){
        return 1;
    }
    else{
        return 0;
    }
}

int conversion(char c[100]){
    int id=0;
    while(c[id]!='\0'){
        if (isAlpha(c[id])){
            push(postfix,c[id],top2,n2);
        }
        else if(c[id]=='('){
            push(stack,c[id],top3,n3);
        }
        else if(c[id]==')'){
            while(popel!='('){
                postfix[top2]=c[id];
                top2++;
            }
            while((isEmpty(stack,top3,n3)==0)&&isp(stack[top3])>=icp(c[id])){
                pop(stack,top3,top3);
                push(postfix,popel,top2,n2);
            }
            push(stack,c[id],top3,n3);
        }
        else if(c[id]=='+'||c[id]=='-'||c[id]=='*'||c[id]=='/'||c[id]=='-'||c[id]=='%'||c[id]=='^'){
            if(icp(c[id])>=isp(stack[top3])){
                pop(stack,top3,n3);
                push(postfix,popel,top2,n2);
                push(stack,c[id],top3,n3);
        }
        else{
            push(stack,c[id],top3,n3);
        }
    }
        id++;
    }
}

int main(){
    char elem;
    int ch=0;
    while(ch!=-1){
        printf("\nFollowing are the stack operations that can be performed via this program on \n1.Display\n2.Push\n3.Pop\n4.Exit\nEnter your choice\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                display(stack,top1,n1);
                break;
            case 2:
                if(isFull(stack,top1,n1)){
                    printf("Stack is full\n");
                }
                else{
                    printf("\nenter the element to push\n");
                    scanf(" %c",&elem);
                    push(stack,elem,top1,n1);
                }
                break;
            case 3:
                if(isEmpty(stack,top1,n1)){
                    printf("Stack is empty\n");
                }
                else{
                    pop(stack,top1,n1);
                }
                break;
            case 4:
                ch=-1;
                break;
                default:printf("Invalid choice\n");
        }
    }
}