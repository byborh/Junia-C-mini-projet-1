#include <stdio.h>

int main() {
    // Sort by insertion !
    int tab[6] = {561, 465, 0, 21, 354, 3};
    int n = sizeof(tab) / sizeof(tab[0]);

    // printf("Sort by insertion: \n");
    // for(int i=0; i<n; i++) {
    //     int index_min = i;
    //     for(int j=i+1; j<n; j++) {
    //         if(tab[j] < tab[index_min]) {
    //             index_min = j;
    //         }
    //     }
    //     // tab[i], tab[index_min] = tab[index_min], tab[i];
    //     int tmp = tab[i];
    //     tab[i] = tab[index_min];
    //     tab[index_min] = tmp;
    // }

    
    // Bubble sort
    printf("Sort by insertion: \n");
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(tab[j] > tab[j+1]) {
                int tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }
        }
    }

    printf("Tableau trié: ");
    for(int k = 0; k < n; k++) {
        printf("%d ", tab[k]);
    }
    printf("\n");
}