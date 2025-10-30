#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BST
{
    char word[10];
    char meaning[20];
    struct BST *left;
    struct BST *right;
}BST;

BST* createNode( char word[], char meaning[])
{	BST* newNode=(BST*)malloc(sizeof(BST));
	strcpy(newNode->word,word);
	strcpy(newNode->meaning,meaning);
	newNode->left = newNode->right= NULL;
	return newNode;
}

BST* insert(BST* root, char word[], char meaning[])
{	if (root==NULL){
        return createNode(word, meaning);
    }
	if (strcmp(word, root->word)<0){
        root->left = insert(root->left,word,meaning);
    }
	else if (strcmp(word, root->word) > 0){
        root->right=  insert(root->right, word, meaning);
    }
	return root;
}

BST* search_nr(BST* root, char word[])
{
	BST* temp = root;
	while (temp !=NULL)
	{
		if (strcmp(word, temp->word)==0){
            return temp;
        }
		else if (strcmp(word, temp->word) < 0){
            temp=temp->left;
        }
		else {
            temp=temp->right;
        }
	}
	return NULL;
}

BST* minValueNode(BST* node)
{	BST* curr = node;
	while (curr!=NULL && curr->left!=NULL)
	{
		curr=curr->left;
	}
	return curr;
}

BST* deleteNode(BST* root, char word[]) {
    if (root == NULL) return root;
    if (strcmp(word, root->word) < 0)root->left = deleteNode(root->left, word);
    else if (strcmp(word, root->word) > 0)root->right = deleteNode(root->right, word);

    else {
        if (root->left == NULL) {
            BST* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            BST* temp = root->left;
            free(root);
            return temp;
        }
        BST* temp = minValueNode(root->right);
        strcpy(root->word, temp->word);
        strcpy(root->meaning, temp->meaning);
        root->right = deleteNode(root->right, temp->word);
    }
    return root;
}

void inorder(BST* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s : %s\n", root->word, root->meaning);
        inorder(root->right);
    }
}

void preorder(BST* root) {
    if (root != NULL) {
        printf("%s : %s\n", root->word, root->meaning);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(BST* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s : %s\n", root->word, root->meaning);
    }
}

// Copy tree (recursive)
BST* copyTree(BST* root) {
    if (root == NULL) return NULL;
    BST* newNode = createNode(root->word, root->meaning);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);
    return newNode;
}

// Mirror tree (recursive)
BST* mirrorTree(BST* root) {
    if (root == NULL) return NULL;
    BST* mirrored = createNode(root->word, root->meaning);
    mirrored->left = mirrorTree(root->right);
    mirrored->right = mirrorTree(root->left);
    return mirrored;
}

// Driver function
int main() {
    BST* root = NULL;
    BST* copyRoot = NULL;
    BST* mirrorRoot = NULL;

    int choice;
    char word[20], meaning[50];

    do {
        printf("\n--- Dictionary using BST ---\n1. Insert a word\n2. Search a word\n3. Delete a word\n4. Inorder Traversal\n5. Preorder Traversal\n6. Postorder Traversal\n7. Make a Copy of Tree\n8. Make Mirror Image of Tree\n9. Exit\nEnter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline left by scanf

        switch (choice) {
            case 1:
                printf("Enter word: ");
                scanf("%s", word);
                getchar();
                printf("Enter meaning: ");
                fgets(meaning, sizeof(meaning), stdin);
                meaning[strcspn(meaning, "\n")] = 0;
                root = insert(root, word, meaning);
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%s", word);
                {
                    BST* found = search_nr(root, word);
                    if (found)
                        printf("Found: %s -> %s\n", found->word, found->meaning);
                    else
                        printf("Word not found!\n");
                }
                break;

            case 3:
                printf("Enter word to delete: ");
                scanf("%s", word);
                root = deleteNode(root, word);
                printf("Deleted (if existed).\n");
                break;

            case 4:
                printf("\nInorder Traversal (sorted dictionary):\n");
                inorder(root);
                break;

            case 5:
                printf("\nPreorder Traversal:\n");
                preorder(root);
                break;

            case 6:
                printf("\nPostorder Traversal:\n");
                postorder(root);
                break;

            case 7:
                copyRoot = copyTree(root);
                printf("\nCopy of Tree (Inorder Traversal):\n");
                inorder(copyRoot);
                break;

            case 8:
                mirrorRoot = mirrorTree(root);
                printf("\nMirror Image Tree (Inorder Traversal):\n");
                inorder(mirrorRoot);
                break;

            case 9:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 9);

    return 0;
}