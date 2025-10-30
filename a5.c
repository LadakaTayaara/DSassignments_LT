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

struct node *head = NULL;

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
        curr->prn=a;
        strcpy(curr->name, b);
        strcpy(curr->designation, c);
        curr->next = NULL;
        temp->next = curr;
        temp = curr;
        printf("Do you want to enter more entries? (y/n): ");
        scanf(" %c", &ch); 
    }
}

void display(struct node *head){
    if(head==NULL){
        printf("List is empty\n");
        return;
    }
    else{
        struct node *curr = head;
        while(curr!=NULL){
            printf("\nPRN: %d\nName: %s\nDesignation: %s\n",curr->prn,curr->name,curr->designation);
            curr=curr->next;
        }
    }
}

void insertbypos(struct node *head){
    int i=1;
    struct node *curr = head;
    struct node *nnode = (struct node *)malloc(sizeof(struct node));
    int a,pos;
    char b[100],c[100];
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

void sortlist(struct node *head){
    if(head==NULL){
        printf("List is empty\n");
        return;
    }
    struct node *i=head,*j=NULL;
    for(i=head;i!=NULL;i=i->next){
        for(j=i->next;j!=NULL;j=j->next){
            if(i->prn > j->prn){
                int tprn = i->prn;
                char tname[50],tdesig[100];
                strcpy(tname,i->name);
                strcpy(tdesig,i->designation);
                i->prn=j->prn;
                strcpy(i->name,j->name);
                strcpy(i->designation,j->designation);
                j->prn=tprn;
                strcpy(j->name,tname);
                strcpy(j->designation,tdesig);
            }
        }
    }
    printf("\nList sorted successfully\n");
}

void reverselist(struct node **headref){
    struct node *prev=NULL,*curr=*headref,*next=NULL;
    while(curr!=NULL){
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    *headref=prev;
    printf("\nList reversed successfully\n");
}

struct node* mergelist(struct node *h1, struct node *h2){
    if(h1==NULL) return h2;
    if(h2==NULL) return h1;
    struct node *merged=NULL;
    if(h1->prn < h2->prn){
        merged=h1;
        merged->next=mergelist(h1->next,h2);
    }else{
        merged=h2;
        merged->next=mergelist(h1,h2->next);
    }
    return merged;
}

int main(){
    head = (struct node *)malloc(sizeof(struct node));
    int cch=0;
    while(cch!=-1){
        printf("\nFollowing are the Linked List operations that can be performed via this program on \n1.Create\n2.Display\n3.Length of the entry\n4.Insert at a position\n5.Sort list\n6.Reverse list\n7.Merge two lists\n8.Exit\nEnter your choice\n");
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
                sortlist(head);
                break;
            case 6:
                reverselist(&head);
                break;
            case 7:{
                struct node *head2 = (struct node *)malloc(sizeof(struct node));
                printf("\nEnter details for second list:\n");
                create(head2);
                printf("\nMerging lists...\n");
                head = mergelist(head,head2);
                printf("Lists merged successfully\n");
                break;
            }
            case 8:
                cch=-1;
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
