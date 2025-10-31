#include <stdio.h>
#include <stdlib.h>

// Node structure for Threaded Binary Tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lbit;
    int rbit;
} Node;

// Function prototypes
Node* Inordersucc(Node* temp);
void Inorder(Node* head);
void Preorder(Node* head);

// Function to create a threaded binary tree
Node* create(Node* head, int key) {
    Node* root = (Node*)malloc(sizeof(Node));
    head->lbit = 1;
    root->data = key;
    root->lbit = 0;
    root->rbit = 0;
    root->left = root->right = head;
    head->left = root;

    char cnt = 'y';
    do {
        Node* temp = root;
        Node* curr = (Node*)malloc(sizeof(Node));
        printf("Enter data for curr: ");
        scanf("%d", &curr->data);
        curr->lbit = 0;
        curr->rbit = 0;

        int inserted = 0; // track insertion success
        while (!inserted) {
            char ch;
            printf("Enter your choice, left or right (l/r): ");
            scanf(" %c", &ch);

            if (ch == 'l') {
                if (temp->lbit == 0) {
                    curr->right = temp;
                    curr->left = temp->left;
                    temp->left = curr;
                    temp->lbit = 1;
                    inserted = 1; //  break after inserting
                } else if (temp->lbit == 1) {
                    temp = temp->left;
                }
            } 
            else if (ch == 'r') {
                if (temp->rbit == 0) {
                    curr->left = temp;
                    curr->right = temp->right;
                    temp->right = curr;
                    temp->rbit = 1;
                    inserted = 1; // break after inserting
                } 
                else if (temp->rbit == 1) { // only follow right child
                    temp = temp->right;
                }
            } 
            else {
                printf("Invalid choice! Enter 'l' or 'r'.\n");
            }
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &cnt);
    } while (cnt != 'n');

    return head;
}

Node* Inordersucc(Node* temp) {
    Node* x = temp->right;
    if (temp->rbit == 1) {
        while (x->lbit == 1)
            x = x->left;
    }
    return x;
}

void Inorder(Node* head) {
    Node* temp = head;
    while (1) {
        temp = Inordersucc(temp);
        if (temp == head)
            break;
        printf("%d ", temp->data);
    }
}

void Preorder(Node* head) {
    Node* temp = head->left;  // start at root
    while (temp != head) {
        printf("%d ", temp->data);

        if (temp->lbit == 1)
            temp = temp->left;
        else {
            while (temp->rbit == 0 && temp->right != head)
                temp = temp->right;
            temp = temp->right;
        }
    }
}

// Menu-driven main function
int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->lbit = 0;
    head->rbit = 1;
    head->left = head->right = head;

    int choice, key;

    do {
        printf("\n=== Threaded Binary Tree Menu ===\n");
        printf("1. Create Tree\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (head->lbit == 0) {
                printf("Enter root data: ");
                scanf("%d", &key);
                head = create(head, key);
            } else {
                printf("Tree already created.\n");
            }
            break;

        case 2:
            printf("Inorder Traversal: ");
            Inorder(head);
            printf("\n");
            break;

        case 3:
            printf("Preorder Traversal: ");
            Preorder(head);
            printf("\n");
            break;

        case 4:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}