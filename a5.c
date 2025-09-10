#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//president head , secretary last , every data is stored in form of prn , name , designation and address field 
struct node{
    int prn;
    char name[50];
    char designation[100];
    struct node *next;
};

struct node *head=(struct node *)malloc(sizeof(struct node));

int lenl(struct node *head){
    struct node *curr = (struct node *)malloc(sizeof(struct node));
    curr=head;
    int i=0;
    while(curr!=NULL){
        i++;
        curr=curr->next;
    }
    return i;
}

void create(struct node *head) {
    printf("Enter the prn and name of the president:\n");
    scanf("%d %s", &head->prn, head->name);
    strcpy(head->designation, "president");
    head->next = NULL;
    struct node *temp = head;
    char ch = 'y';
    while (ch != 'n') {
        struct node *curr = (struct node *)malloc(sizeof(struct node));
        if (curr == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        printf("\nEnter prn, name and designation:\n");
        int a;
        char b[100];
        char c[100];
        scanf("%d %s %s", &a, b, c);
        if(strcmp(c,"secretary")==0){//segmentation error
            int i=0;
            while(curr!=NULL && i<lenl(head)-1){
                i++;
                curr=curr->next;
            }
            curr->prn=a;
            strcpy(curr->name, b);
            strcpy(curr->designation, c);
            curr->next = NULL;
        }
        else{
            curr->prn=a;
            strcpy(curr->name, b);
            strcpy(curr->designation, c);
            curr->next = NULL;
            temp->next = curr;
            temp = curr;
            printf("Do you want to enter more entries? (y/n): ");
            scanf(" %c", &ch); 
        }   
    }}

void display(struct node *head){
    if(head->next==NULL){
        printf("List is empty\n");
        return;
    }
    else{
        struct node *curr = (struct node *)malloc(sizeof(struct node));
        printf("\nPRN: %d\nName: %s\nDesignation: %s\n",head->prn,head->name,head->designation);
        curr=head->next;
        while(curr!=NULL){
            printf("\nPRN: %d\nName: %s\nDesignation: %s\n",(int)curr->prn,curr->name,curr->designation);
            curr=curr->next;
        }
    }
}

void insertbypos(struct node *head){
    int i=1;
    struct node *curr = (struct node *)malloc(sizeof(struct node));
    curr=head;
    struct node *nnode = (struct node *)malloc(sizeof(struct node));
    int a;
    char b[100];
    char c[100];
    int pos;
    printf("\nEnter the data you want to put along with the position\n");
    scanf("%d %s %s %d",&a,b,c,&pos);
    int k=lenl(head);
    if(pos>k+1){
        printf("data can't be inserted\n");
        return;
    }
    else{
        while(curr!=NULL && i<pos){
            i++;
            curr=curr->next;
        }
        nnode->prn=a;
        strcpy(nnode->name, b);
        strcpy(nnode->designation, c);
        nnode->next=curr->next;
        curr->next=nnode;
    }
}

int main(){
    int cch=0;
    while(cch!=-1){
        printf("\nFollowing are the Linked List operations that can be performed via this program on \n1.Create\n2.Display\n3.Length of the entry\n4.Insert at a position\n5.Exit\nEnter your choice\n");
        scanf("%d",&cch);
        switch(cch){
            case 1:
                create(head);
                break;
            case 2:
                display(head);
                break;
            case 3:
                printf("Length of the linked list is :%d\n",lenl(head));
                break;
            case 4:
                insertbypos(head);
                break;
            case 5:
                cch=-1;
                break;
                default:printf("Invalid choice\n");
        }
    }
    return 0;
}