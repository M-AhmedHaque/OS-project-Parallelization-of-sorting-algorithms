#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define SIZE 100

int n1[SIZE];
int n2[SIZE];

struct timeval stop2, start2;

typedef struct dim {
    int start;
    int end;
} limit;

typedef struct joined {
    int Start;
    int mid;
    int End;
} join;

void merge(int start, int mid, int end) {
    int i = start, j = mid, tpos = start;

    while (i < mid && j < end) {
        if (n1[i] < n1[j])
            n2[tpos++] = n1[i++];
        else
            n2[tpos++] = n1[j++];
    }

    while (i < mid)
        n2[tpos++] = n1[i++];

    while (j < end)
        n2[tpos++] = n1[j++];
}

void insertion(int start, int end) {
    int i = start + 1;
    int j, move;

    while (i < end) {
        j = i - 1;
        move = n1[i];
        while (j >= start && move < n1[j]) {
            n1[j + 1] = n1[j];
            j--;
        }
        n1[j + 1] = move;
        i++;
    }
}

void fillarray(int size) {
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++)
        n1[i] = rand() % 100;
}

void print_array(int list[], int size) {
    int i;
    for (i = 0; i < size - 1; i++)
        printf("%d, ", list[i]);
    printf("%d\n", list[i]);
}

void file_create(double start, double stop) {
    FILE *ptr;
    ptr = fopen("Insertion.txt", "a+");
    if (ptr == NULL) {
        printf("Unable to Open File");
        exit(EXIT_FAILURE);
    } else {
        double total = (stop - start);
        fprintf(ptr, "Time Taken(Burst Time) by OpenMP: %lf\n", total);
        fprintf(ptr, "Time Taken(Clock Time) by OpenMP: %lu\n", (unsigned long)((stop - start) * 1000000));
    }
    fclose(ptr);
}


int main() {
    fillarray(SIZE);
    print_array(n1, SIZE);

    limit l1, l2;

    l1.start = 0;
    l1.end = SIZE / 2;

    l2.start = l1.end;
    l2.end = SIZE;

    join j1;
    j1.Start = l1.start;
    j1.mid = l2.start;
    j1.End = l2.end;

    double Start1 = omp_get_wtime();
    gettimeofday(&start2, NULL);

    #pragma omp parallel sections
    {
        #pragma omp section
        insertion(l1.start, l1.end);
        #pragma omp section
        insertion(l2.start, l2.end);
    }

    #pragma omp parallel
    {
        #pragma omp single
        merge(j1.Start, j1.mid, j1.End);
    }

    gettimeofday(&stop2, NULL);
    double stop1 = omp_get_wtime();

    print_array(n2, SIZE);
    file_create(Start1, stop1);

    return 0;
}
