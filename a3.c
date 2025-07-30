#include <stdio.h>

int front=-1;
int rear=-1;
int cfront=0;
int crear=0;

int isFull(int q[5]){
    if(rear==4){
        return 1;
    }
    else{
        return 0;
    }
}

int CisFull(int q[5]){
    if((crear+1)%5==cfront){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(int q[5]){
    if(front==rear){
        return 1;
    }
    else{
        return 0;
    }
}

int CisEmpty(int q[5]){
    if((cfront%5)==(crear%5)){
        return 1;
    }
    else{
        return 0;
    }
}

int enqueue(int q[5],int elem){
    if(isFull(q)){
        printf("queue is full\n");
        return 0;
    }
    else{
        rear=rear+1;
        q[rear]=elem;
        return 0;
    }
}

int Cenqueue(int q[5],int elem){
    if(CisFull(q)){
        printf("queue is full\n");
        return 0;
    }
    else{
        crear=crear+1;
        q[crear]=elem;
        return 0;
    }
}

int dequeue(int q[5]){
    if(isEmpty(q)){
        printf("queue is empty\n");
        return 0;
    }
    else{
        int elem;
        front=front+1;
        elem=q[front];
        q[front]=-1;
        return elem;
    }
}

int Cdequeue(int q[5]){
    if(CisEmpty(q)){
        printf("queue is empty\n");
        return 0;
    }
    else{
        int elem;
        cfront=cfront+1;
        elem=q[cfront];
        q[cfront]=-1;
        return elem;
    }
}

void display(int q[5]){
    printf("[");
    for(int i=front+1;i<=rear;i++){
        printf("%d ",q[i]);
    }
    printf("]\n");
}

void Cdisplay(int q[5]){
    printf("[");
    for(int i=cfront+1;i<=crear;i++){
        printf("%d ",q[i]);
    }
    printf("]\n");
}


int main(){
    int a[5];
    int b[5];

    for(int i=0;i<5;i++){
        a[i]=-1;
    }

    for(int i=0;i<5;i++){
        b[i]=-1;
    }

    int ch=0;
    int chl=0;
    int elem;
    printf("enter your choice\n1.Linear Queue\n2.Circular Queue\n");
    scanf("%d",&chl);
    switch(chl){
        case 1:
        while(ch!=-1 && chl!=-1){
            printf("\nFollowing are the queue operations that can be performed via this program on Linear Queue\n1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\nEnter your choice\n");
            scanf("%d",&ch);
            switch(ch){
                case 1:
                if(isFull(a)){
                    printf("\nqueue is full \n");
                }
                else{
                    printf("\nenter the element you want to enqueue ");
                    scanf("%d",&elem);
                    enqueue(a,elem);
                }
                break;
                case 2:
                dequeue(a);
                break;
                case 3:
                display(a);
                break;
                case 4:ch=-1;
                chl=-1;
                break;
                default:printf("Invalid choice\n");
                break;
            }
        }
        break;
        case 2:
        while(ch!=-1){
            printf("\nFollowing are the queue operations that can be performed via this program on Circular Queue\n1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\nEnter your choice\n");
            scanf("%d",&ch);
            switch(ch){
                case 1:
                if(CisFull(b)){
                    printf("\nqueue is full \n");
                }
                else{
                    printf("\nenter the element you want to enqueue ");
                    scanf("%d",&elem);
                    Cenqueue(b,elem);
                }
                break;
                case 2:
                Cdequeue(b);
                break;
                case 3:
                Cdisplay(b);
                break;
                case 4:ch=-1;
                chl=-1;
                break;
                default:printf("Invalid choice\n");
            }
        }
    }
    return 0;
}