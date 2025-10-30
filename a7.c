#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

struct treenode
{
    char data[10];
    struct treenode *left;
    struct treenode *right;
};

struct treenode* stack[STACK_SIZE];
int top = -1;

struct treenode* queue[100];
int front=-1,rear=-1;

int isStackEmpty(){
    return top == -1;
}

int isStackFull(){
    return top == STACK_SIZE - 1;
}

void push(struct treenode* node) {
    if (isStackFull()) {
        printf("Stack overflow!\n");
        return;
    }
    stack[++top] = node;
}

struct treenode* pop() {
    if (isStackEmpty()) {
        return NULL;
    }
    return stack[top--];
}

struct treenode* peek() {
    if (isStackEmpty()) return NULL;
    return stack[top];
}

struct treenode* createnode(char *data)
{
    struct treenode* newnode= (struct treenode*)malloc(sizeof(struct treenode));
    if (newnode == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    strcpy(newnode->data, data);
    newnode->left=newnode->right=NULL;
    return newnode;
}

struct treenode* createTree()
{
    char data[10];
    char choice;

    printf("Enter data for node (or '.' for NULL) : ");
    scanf(" %s",data);

    if (strcmp(data, ".")== 0){
        return NULL;
    }

    struct treenode* node= createnode(data);

    printf("Does %s have a left child? (y/n) : ", data);
    scanf(" %c", &choice);
    if (choice=='y' || choice == 'Y'){
        node->left=createTree();
    }

    printf("Does %s have a right child (y/n): ", data);
    scanf(" %c", &choice);
    if (choice=='y' || choice == 'Y'){
        node->right=createTree();
    }
    return node;
}

void inorder(struct treenode* root)
{
    if (root!=NULL)
    {
        inorder(root->left);
        printf(" %s", root->data);
        inorder(root->right);
    }
}

void preorder(struct treenode* root)
{
    if (root!=NULL)
    {
        printf(" %s", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct treenode* root)
{
    if (root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf(" %s",root->data);
    }
}

void enqueue(struct treenode* node)
{
    if (rear == 99) {
        printf("\nQueue overflow, cannot enqueue %s!\n", node->data);
        return;
    }
    if (node==NULL) return;
    queue[++rear]=node;
}

struct treenode* dequeue()
{
    if (front==rear) return NULL;
    return queue[++front];
}

void levelorder(struct treenode* root)
{
    if (root == NULL) return;

    front = -1;
    rear = -1;

    enqueue(root);
    while (front != rear)
    {
        struct treenode* temp= dequeue();
        printf("%s ", temp->data);
        if (temp->left) enqueue(temp->left);
        if (temp->right) enqueue(temp->right);
    }
}

void inorderNonRec(struct treenode* root) {
    top = -1;
    
    struct treenode* curr = root;
    while (1) {
        while (curr != NULL) {
            push(curr);
            curr = curr->left;
        }
        if (isStackEmpty()) break;
        curr = pop();
        printf("%s ", curr->data);
        curr = curr->right;
    }
}

void preorderNonRec(struct treenode* root) {
    if (root == NULL) return;
    
    top = -1;

    push(root);
    while (!isStackEmpty()) {
        struct treenode* curr = pop();
        printf("%s ", curr->data);

        if (curr->right) push(curr->right);
        if (curr->left) push(curr->left);
    }
}

void postorderNonRec(struct treenode* root) {
    if (root == NULL) return;

    struct treenode* s1[STACK_SIZE];
    struct treenode* s2[STACK_SIZE];
    int top1 = -1, top2 = -1;

    s1[++top1] = root;
    while (top1 != -1) {
        struct treenode* curr = s1[top1--];
        s2[++top2] = curr;

        if (curr->left) s1[++top1] = curr->left;
        if (curr->right) s1[++top1] = curr->right;
    }

    while (top2 != -1) {
        struct treenode* node = s2[top2--];
        printf("%s ", node->data);
    }
}


int main()
{
    struct treenode* root = NULL;
    int choice;

    do {
        printf("1. Create/Recreate Tree\n2. Recursive Traversal\n3. Non-Recursive Traversal\n4. Level Order Traversal\n5. Exit\nEnter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:
                root = NULL;
                printf("\n--- Create Tree ---\n");
                root = createTree();
                if (root) {
                    printf("\nTree creation complete.\n");
                } else {
                    printf("\nTree is empty.\n");
                }
                break;

            case 2:
                if (root == NULL) {
                    printf("\nTree is empty. Please create a tree first (Option 1).\n");
                    break;
                }
                printf("\n--- Recursive Traversal Results ---\n");
                printf("Inorder Traversal : ");
                inorder(root);
                printf("\nPreorder Traversal: ");
                preorder(root);
                printf("\nPostorder Traversal : ");
                postorder(root);
                printf("\n");
                break;

            case 3:
                if (root == NULL) {
                    printf("\nTree is empty. Please create a tree first (Option 1).\n");
                    break;
                }
                printf("\n--- Non-Recursive Traversal Results ---\n");
                printf("Non-Recursive Inorder : ");
                inorderNonRec(root);
                
                printf("\nNon-Recursive Preorder: ");
                preorderNonRec(root);

                printf("\nNon-Recursive Postorder : ");
                postorderNonRec(root);
                printf("\n");
                break;

            case 4:
                if (root == NULL) {
                    printf("\nTree is empty. Please create a tree first (Option 1).\n");
                    break;
                }
                printf("\n--- Level Order Traversal Result ---\n");
                levelorder(root);
                printf("\n");
                break;

            case 5:
                printf("\nExiting program. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
