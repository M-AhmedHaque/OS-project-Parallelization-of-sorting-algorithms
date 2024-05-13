#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

void selectionSort(int* arr, int n);
void swap(int* a, int* b);
void display(int* arr, int n);
void file_create(double start, double stop, double elapsed);

int main() {
    int number, iter = 0;
    printf("\nEnter the Size of the Array: ");
    scanf("%d", &number);
    int Arr[number];
    for (; iter < number; iter++) {
        printf("\nElement No. %d: ", iter + 1);
        Arr[iter] = rand() % 100;
        printf("%d", Arr[iter]);
    }

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    #pragma omp parallel shared(Arr, number)
    {
        selectionSort(Arr, number);
    }

    gettimeofday(&stop, NULL);
    display(Arr, number);

    double elapsed = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    file_create(start.tv_sec, stop.tv_sec, elapsed);
    //printf("Execution Time: %lf microseconds\n", elapsed);
    return 0;
}

void selectionSort(int* arr, int n) {
    for (int startpos = 0; startpos < n - 1; startpos++) {
        int maxpos = startpos;
        for (int i = startpos + 1; i < n; ++i) {
            if (arr[i] < arr[maxpos]) {
                maxpos = i;
            }
        }
        if (maxpos != startpos)
            swap(&arr[startpos], &arr[maxpos]);
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display(int* arr, int n) {
    printf("\nARRAY: {");
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            printf("%d, ", arr[i]);
        } else {
            printf("%d}\n\n", arr[i]);
        }
    }
}
void file_create(double start, double stop, double elapsed) {
    FILE* ptr;
    ptr = fopen("Selection.txt", "a+");
    if (ptr == NULL) {
        printf("Unable to Open File");
        exit(EXIT_FAILURE);
    } else {
        double burst_time = stop - start;
        fprintf(ptr, "Openmp Burst Time: %lf seconds\n", burst_time);
        fprintf(ptr, "Openmp Execution Time: %lf microseconds\n", elapsed);
    }
    fclose(ptr);
    }



