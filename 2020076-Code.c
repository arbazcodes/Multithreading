#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{

    int st_index, end_index;
    void *tid;

} arg;

void *formula(void *args)
{
    arg *argu = (arg *)args;

    int *myid = (int *)argu->tid;
    double y = 0;

    printf("Start: %d, End: %d\n", argu->st_index, argu->end_index);

    for (double x = argu->st_index; x <= argu->end_index; x++)
    {
        y += (((x - 1) * (x - 1)) / 5);
    }

    printf("Thread: %d, Result: %lf\n", *myid, y);

    double *result = malloc(sizeof(double));
    *result = y;
    return (void *)result;
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    pthread_t tid[n];
    arg a[n];

    for (int i = 0; i < n; i++)
    {

        a[i].tid = (void *)&tid[i];
        a[i].st_index = 1 + (i * m) / n;
        a[i].end_index = ((i + 1) * m) / n;
        pthread_create(&tid[i], NULL, formula, &a[i]);
    }

    double *return_val[n], sum = 0;

    for (int i = 0; i < n; i++)
    {
        pthread_join(tid[i], (void **)&return_val[i]);
        sum += (double)*return_val[i];
    }

    printf("Total Sum: %lf\n", sum);
    free(*return_val);

    return 0;
}