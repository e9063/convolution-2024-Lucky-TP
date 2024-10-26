#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // implement here
    int *FF = malloc(sizeof(int) * NF);
    for(int i = 0; i < NF; i++){
        FF[i] = F[NF-1-i];
    }

    int NR = NA-NF+1;
    int *R = malloc(sizeof(int)*NR);
    #pragma omp parallel for num_threads(8)
    for(int i = 0 ; i<NR ; i++){
        int result = 0;
        for(int j = 0 ; j<NF ; j++){
            result += A[i+j] * FF[j];
        }
        R[i] = result;
    };

    for(int i = 0 ; i<NR ; i++){
        printf("%d\n", R[i]);
    }

    // ---- free memory ----
    free(F);
    free(A);
    free(FF);
    free(R);
    // ---- end free ----
    return 0;
}

