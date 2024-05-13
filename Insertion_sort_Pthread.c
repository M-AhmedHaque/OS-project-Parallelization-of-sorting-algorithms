#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#define SIZE 100

int num1[SIZE];
struct timeval stop2,start2;

void insertion_sort()
{
	int i,j,temp;

    for(i = 1; i < SIZE; i++)
    {
        j = i - 1;
        temp = num1[i];
        while(j >= 0 && num1[j] > temp)
        {
            num1[j + 1] = num1[j];
            j--;
        }
        num1[j + 1] = temp;
    }
}

void fill_array(int size)
{
    int i;
    srand(time(NULL));
    for (i=0; i<size; i++)
        num1[i] = rand() % 100;
}

void file_create(double start,double stop)
{
	FILE *ptr;
	ptr=fopen("Insertion.txt","a+");
	if(ptr==NULL)
	{
		printf("Unable to Open File");
		exit(1);
	}
	else
	{
		double total= (double)(stop-start);
		fprintf(ptr,"Time Taken(Burst Time) by Pthread: %lf\n",total);
		fprintf(ptr,"Time Taken(Clock Time) by Pthread: %lu\n",(stop2.tv_sec-start2.tv_sec)*1000000+stop2.tv_usec-start2.tv_usec);
	}
	fclose(ptr);
}

int main()
{

	fill_array(SIZE);
	double Start1=clock();

	gettimeofday(&start2,NULL);

	insertion_sort();

	gettimeofday(&stop2,NULL);

	double stop1=clock();

	for(int i=0;i<SIZE;i++)
	{
		printf("%d ",num1[i]);
	}
    putchar('\n');

	file_create(Start1,stop1);
	return 0;
}
