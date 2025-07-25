#include <stdio.h>
#include <stdlib.h>

int accept(int a[4][4], int m, int n) {
    int value = 0;
    printf("Enter matrix elements (%d x %d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter value for element [%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
            if (a[i][j] != 0) {
                value++;
            }
        }
    }

    if (value < (m * n) / 3) {
        printf("\nMatrix is sparse (Non-zero elements: %d out of %d).\n", value, m * n);
        return 1;
    } else {
        printf("\nMatrix is not considered sparse for this demonstration (Non-zero elements: %d out of %d).\n", value, m * n);
        return 0;
    }
}

void display(int a[4][4], int m, int n) {
    printf("\nOriginal Matrix:\n");
    for (int i = 0; i < m; i++) {
        printf("| ");
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("|\n");
    }
}

void compact_form(int a[4][4], int m, int n) {
    int value = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                value++;
            }
        }
    }

    int sp[value + 1][3];

    sp[0][0] = m;
    sp[0][1] = n;
    sp[0][2] = value;

    int k = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                sp[k][0] = i;
                sp[k][1] = j;
                sp[k][2] = a[i][j];
                k++;
            }
        }
    }

    printf("\nCompact form display:\n");
    printf("| Row | Col | Value |\n");
    printf("---------------------\n");
    for (int i = 0; i <= value; i++) {
        printf("| %3d | %3d | %5d |\n", sp[i][0], sp[i][1], sp[i][2]);
    }
}

void simple_transpose(int a[4][4], int m, int n) {
    int value = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                value++;
            }
        }
    }

    int sp[value + 1][3];

    sp[0][0] = m;
    sp[0][1] = n;
    sp[0][2] = value;

    int k = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                sp[k][0] = i;
                sp[k][1] = j;
                sp[k][2] = a[i][j];
                k++;
            }
        }
    }

    int tsp[value + 1][3];
    tsp[0][0] = n;
    tsp[0][1] = m;
    tsp[0][2] = value;

    if (value > 0) {
        int q = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= value; j++) {
                if (sp[j][1] == i) {
                    tsp[q][0] = sp[j][1];
                    tsp[q][1] = sp[j][0];
                    tsp[q][2] = sp[j][2];
                    q++;
                }
            }
        }
    }

    printf("\nSimple transpose display:\n");
    printf("| Row | Col | Value |\n");
    printf("---------------------\n");
    for (int i = 0; i <= value; i++) {
        printf("| %3d | %3d | %5d |\n", tsp[i][0], tsp[i][1], tsp[i][2]);
    }
}

void fast_transpose(int a[4][4], int m, int n) {
    int value = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                value++;
            }
        }
    }

    if (value == 0) {
        printf("\nFast transpose: Matrix is empty.\n");
        return;
    }

    int sp[value + 1][3];

    sp[0][0] = m;
    sp[0][1] = n;
    sp[0][2] = value;

    int k = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                sp[k][0] = i;
                sp[k][1] = j;
                sp[k][2] = a[i][j];
                k++;
            }
        }
    }

    int row_terms[n];
    for(int i = 0; i < n; i++) {
        row_terms[i] = 0;
    }

    int starting_pos[n];

    for (int i = 1; i <= value; i++) {
        row_terms[sp[i][1]]++;
    }

    starting_pos[0] = 1;
    for (int i = 1; i < n; i++) {
        starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
    }

    int fsp[value + 1][3];

    fsp[0][0] = n;
    fsp[0][1] = m;
    fsp[0][2] = value;

    for (int i = 1; i <= value; i++) {
        int original_col = sp[i][1];
        int current_pos = starting_pos[original_col];

        fsp[current_pos][0] = sp[i][1];
        fsp[current_pos][1] = sp[i][0];
        fsp[current_pos][2] = sp[i][2];

        starting_pos[original_col]++;
    }

    printf("\nFast transpose display:\n");
    printf("| Row | Col | Value |\n");
    printf("---------------------\n");
    for (int i = 0; i <= value; i++) {
        printf("| %3d | %3d | %5d |\n", fsp[i][0], fsp[i][1], fsp[i][2]);
    }
}

int main() {
    int m = 4, n = 4;
    int a[4][4];

    int is_sparse = accept(a, m, n);

    int ch = 0;
    while (ch != 5) {
        printf("\n\nSelect an operation:\n");
        printf("1. Display the entered matrix\n");
        printf("2. Compact form display\n");
        printf("3. Simple Transpose\n");
        printf("4. Fast Transpose\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &ch) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (ch) {
            case 1:
                display(a, m, n);
                break;
            case 2:
                if (is_sparse) {
                    compact_form(a, m, n);
                } else {
                    printf("Matrix is not considered sparse, compact form might not be as beneficial.\n");
                }
                break;
            case 3:
                if (is_sparse) {
                    simple_transpose(a, m, n);
                } else {
                    printf("Transpose operations are typically optimized for sparse matrices. This matrix is not considered sparse.\n");
                }
                break;
            case 4:
                if (is_sparse) {
                    fast_transpose(a, m, n);
                } else {
                    printf("Transpose operations are typically optimized for sparse matrices. This matrix is not considered sparse.\n");
                }
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid input. Please enter a number between 1 and 5.\n");
                break;
        }
    }
    return 0;
}