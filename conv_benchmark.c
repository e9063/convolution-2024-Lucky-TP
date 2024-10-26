#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for (int i = 0; i < NA; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < NF; i++) {
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    int *FF = malloc(sizeof(int) * NF);
    for (int i = 0; i < NF; i++) {
        FF[i] = F[NF - 1 - i];
    }

    int NR = NA - NF + 1;
    int *R_sequential = malloc(sizeof(int) * NR);
    int *R_parallel = malloc(sizeof(int) * NR);

    double start_sequential = omp_get_wtime();
    for (int i = 0; i < NR; i++) {
        int result = 0;
        for (int j = 0; j < NF; j++) {
            result += A[i + j] * FF[j];
        }
        R_sequential[i] = result;
    }
    double end_sequential = omp_get_wtime();
    double time_sequential = end_sequential - start_sequential;

    double start_parallel = omp_get_wtime();
    #pragma omp parallel for num_threads(8)
    for (int i = 0; i < NR; i++) {
        int result = 0;
        for (int j = 0; j < NF; j++) {
            result += A[i + j] * FF[j];
        }
        R_parallel[i] = result;
    }
    double end_parallel = omp_get_wtime();
    double time_parallel = end_parallel - start_parallel;

    printf("Sequential Time: %f seconds\n", time_sequential);
    printf("Parallel Time: %f seconds\n", time_parallel);
    printf("Speedup: %f\n", time_sequential / time_parallel);

    // ---- free memory ----
    free(F);
    free(A);
    free(FF);
    free(R_sequential);
    free(R_parallel);
    // ---- end free ----

    return 0;
}
