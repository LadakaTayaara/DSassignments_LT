#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct treenode
{
	char data[10];
	struct treenode *left;
	struct treenode *right;
};
struct treenode* createnode(char *data)
{
	struct treenode* newnode= (struct treenode*)malloc(sizeof(struct treenode));
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
	if  (strcmp(data, ".")== 0)
	{return NULL;}
	struct treenode* node= createnode(data);
	printf("Does %s have a left child? (y/n) : ", data);
	scanf(" %c", &choice);
	if (choice=='y')
	{node->left=createTree();}
	printf("Does %s have a right child (y/n): ", data);
	scanf(" %c", &choice);
	if (choice=='y')
	{node->right=createTree();}
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
struct treenode* queue[100];
int front=-1,rear=-1;
void enqueue(struct treenode* node)
{
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
	enqueue(root);
	while (front!=rear)
	{
		struct treenode* temp= dequeue();
		printf("%s", temp->data);
		if (temp->left) enqueue(temp->left);
		if (temp->right) enqueue(temp->right);
	}
}
#define STACK_SIZE 100
struct treenode* stack[STACK_SIZE];
int top = -1;

int isStackEmpty() { return top == -1; }
int isStackFull()  { return top == STACK_SIZE - 1; }

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

void inorderNonRec(struct treenode* root) {
    struct treenode* curr = root;
    while (1) {
        while (curr != NULL) {   // go to extreme left
            push(curr);
            curr = curr->left;
        }
        if (isStackEmpty()) break;
        curr = pop();
        printf("%s ", curr->data);  // visit
        curr = curr->right;         // then go right
    }
}

void preorderNonRec(struct treenode* root) {
    if (root == NULL) return;

    push(root);
    while (!isStackEmpty()) {
        struct treenode* curr = pop();
        printf("%s ", curr->data);   // visit

        // push right first so left is processed first
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
	printf("Create the binary tree: \n");
	root=createTree();
	printf("\nInorder Traversal: ");
	inorder(root);
	printf("\nPreorder Traversal: ");
	preorder(root);
	printf("\nPostorder Traversal: ");
	postorder(root);
	printf("\nLevel order Traversal: ");
	levelorder(root);
	printf("\nNon-Recursive Inorder   : ");
inorderNonRec(root);

printf("\nNon-Recursive Preorder  : ");
preorderNonRec(root);

printf("\nNon-Recursive Postorder : ");
postorderNonRec(root);
	return 0;
}