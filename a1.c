#include <stdio.h>
#include <string.h>

typedef struct stud {
    int rno;
    char name[10];
    int marks;
} stud;

void accept(struct stud s[], int n) {
    printf("\n Enter the students details (Roll No, Name, Marks):\n");
    for (int i = 0; i < n; i++) {
        printf("Student %d: ", i + 1);
        scanf("%d %s %d", &s[i].rno, s[i].name, &s[i].marks);
    }
}

void display(struct stud s[], int n) {
    if (n == 0) {
        printf("\nNo records to display. Please accept student details first.\n");
        return;
    }
    printf("\n---------------------------------\n");
    printf("| Roll No | Name       | Marks |\n");
    printf("---------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %-7d | %-10s | %-5d |\n", s[i].rno, s[i].name, s[i].marks);
    }
    printf("---------------------------------\n");
}

void bubblesort(stud s[], int n) {
    stud temp;
    int swapcount = 0;
    printf("\n--- Performing Bubble Sort ---\n");
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (s[j].rno > s[j + 1].rno) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
                swapcount++;
            }
        }
    }
    printf("Bubble Sort completed. Total swaps: %d\n", swapcount);
}

void selectionsort(stud s[], int n) {
    int minpos;
    stud temp;
    printf("\n--- Performing Selection Sort ---\n");
    for (int i = 0; i < n - 1; i++) {
        minpos = i;
        for (int j = i + 1; j < n; j++) {
            if (s[j].rno < s[minpos].rno) {
                minpos = j;
            }
        }
        if (minpos != i) {
            temp = s[minpos];
            s[minpos] = s[i];
            s[i] = temp;
        }
    }
    printf("Selection Sort completed.\n");
}

void insertionsort(stud s[], int n) {
    int i, j;
    stud key;
    printf("\n--- Performing Insertion Sort ---\n");
    for (i = 1; i < n; i++) {
        key = s[i];
        j = i - 1;

        while (j >= 0 && s[j].rno > key.rno) {
            s[j + 1] = s[j];
            j = j - 1;
        }
        s[j + 1] = key;
    }
    printf("Insertion Sort completed.\n");
}

int main() {
    stud s1[10];
    int n = 0;
    int choice;

    do {
        printf("\n--- Student Record Management ---\n");
        printf("1. Accept Student Details\n");
        printf("2. Display Student Details\n");
        printf("3. Sort by Roll No (Bubble Sort)\n");
        printf("4. Sort by Roll No (Selection Sort)\n");
        printf("5. Sort by Roll No (Insertion Sort)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Total number of records (max 10): ");
                scanf("%d", &n);
                if (n > 10 || n <= 0) {
                    printf("Invalid number of records. Please enter a number between 1 and 10.\n");
                    n = 0;
                } else {
                    accept(s1, n);
                }
                break;
            case 2:
                display(s1, n);
                break;
            case 3:
                if (n == 0) {
                    printf("Please accept student details first.\n");
                } else {
                    bubblesort(s1, n);
                    display(s1, n);
                }
                break;
            case 4:
                if (n == 0) {
                    printf("Please accept student details first.\n");
                } else {
                    selectionsort(s1, n);
                    display(s1, n);
                }
                break;
            case 5:
                if (n == 0) {
                    printf("Please accept student details first.\n");
                } else {
                    insertionsort(s1, n);
                    display(s1, n);
                }
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}