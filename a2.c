#include <stdio.h>

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
    for (int i = 0; i <= value; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%d ", sp[i][j]);
        }
        printf("|\n");
    }
}

void simple_transpose(int a[4][4],int m,int n){
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

    int tsp[value+1][3];
    tsp[0][0] = n;
    tsp[0][1] = m;
    tsp[0][2] = value;


    int q=1;
    for(int i=0;i<4;i++){
        for(int j=1;j<value+1;j++){
            if(sp[j][1]==i){
                tsp[q][0]=sp[j][1];
                tsp[q][1]=sp[j][0];
                tsp[q][2]=sp[j][2];
                q++;
            }
        }
    }

    printf("\nSimple transpose display:\n");
    for (int i = 0; i <= value; i++) {
        printf("| ");
        for (int j = 0; j < 3; j++) {
            printf("%d ", tsp[i][j]);
        }
        printf("|\n");
    }
}

void accept(int a[4][4], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter value for element [%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
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

int main() {
    int m = 4, n = 4;
    int a[4][4];

    accept(a, m, n);
    int ch=0;
    while(ch!=-1){
        printf("\nEnter your choice:\n1.display the entered matrix\n2.compact form display\n3.simple transpose\n4.Exit\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:display(a,m,n);
            break;
            case 2:compact_form(a,m,n);
            break;
            case 3:simple_transpose(a,m,n);
            break;
            case 4:ch=-1;
            break;
            default:printf("Invalid input ");
            break;
        }
    }
    return 0;
}