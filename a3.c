#include <stdio.h>

int front=-1;
int rear=-1;
int cfront=0;
int crear=0;
int n=0;
int m=0;

int isFull(int q[n]){
    if(rear==n-1){
        return 1;
    }
    else{
        return 0;
    }
}

int CisFull(int q[m]){
    if((crear+1)%m==cfront){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty(int q[n]){
    if(front==rear){
        return 1;
    }
    else{
        return 0;
    }
}

int CisEmpty(int q[m]){
    if((cfront%m)==(crear%m)){
        return 1;
    }
    else{
        return 0;
    }
}

int enqueue(int q[n],int elem){
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

int Cenqueue(int q[m],int elem){
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

int dequeue(int q[n]){
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

int Cdequeue(int q[m]){
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

void display(int q[n]){
    printf("[");
    for(int i=front+1;i<=rear;i++){
        printf("%d ",q[i]);
    }
    printf("]\n");
}

void Cdisplay(int q[m]){
    printf("[");
    for(int i=cfront+1;i<=crear;i++){
        printf("%d ",q[i]);
    }
    printf("]\n");
}


int main(){
    printf("enter the size of the linear queue\n");
    scanf("%d",&n);
    int a[n];

    printf("enter the size of the circular queue\n");
    scanf("%d",&m);
    int b[m];

    for(int i=0;i<n;i++){
        a[i]=-1;
    }

    for(int i=0;i<m;i++){
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