#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//Kennedy Ly

void weight_sort(int *n, int *weight, int j, float *total_weight, int *new_array, int *repeat_array)
{
    printf("Doing the weighted sort... This may take a while...\n");
    clock_t t;
    t = clock();
    int x,i,origin,sum;
    float middle;
    printf("Calculating weights.. This may take a while...\n");
    //Calculating the weights and total weights


    for(i=0;i<j;i++)
    {
        weight[i] =0;
    }


    for(i=0;i<j;i++)
    {
        for(x=0;x<j;x++) /* Comparing the ith number with the whole array*/
                {
                    if (n[i] == n[x])
                    {
                        weight[i] += 0;
                    }
                    else if(n[i] > n[x])
                    {
                        weight[i] += 1;
                    }
                    else if(n[i] < n[x])
                    {
                        weight[i] -= 1;
                    }
                }
    total_weight[i] = (float)weight[i]/2;
    if (total_weight[i] > 0)
    {
        total_weight[i] = round(total_weight[i]);
    }
    else if (total_weight[i] < 0)
    {
        total_weight[i] = floor(total_weight[i]);
    }
    }



    middle = round((float)j/2);
    origin = (int)middle;//Calculating the origin point
    printf("The origin is %d\n", origin);

    //Populating the new_array with -1 to indicate we have not written anything in that index.
    for(i=0;i<j;i++)
    {
        new_array[i] = -1; //Initializing the new)a
    }

    for(i=0;i<j+1;i++)
    {
        repeat_array[i] = 0;
    }
    //




    for(i=0;i<j;i++)
    {
        if (i == j)
        {
            continue;
        }
        if(new_array[origin + (int)total_weight[i]] == -1)
        {
            new_array[origin + (int)total_weight[i]] = n[i];
        }
        else if(new_array[origin + (int)total_weight[i]] != -1)
        {
            repeat_array[origin + (int)total_weight[i]] +=1;
        }
    }


        printf("Sorting... May take a while\n");
        for(i=0;i<j;i++) //Will loop through the new_array to search for -1's
        {
            if(new_array[i] == -1)
            {
                for(x=0;x<j;x++) //will loop through the repeat_array to search for 0's
                {
                    if(repeat_array[x] != 0)
                    {
                        if(new_array[x] == new_array[i+1])
                        {
                            new_array[i] = new_array[x];
                            repeat_array[x] -=1;

                        }
                        else if(new_array[x] == new_array[i-1])
                        {
                            new_array[i] = new_array[x];
                            repeat_array[x] -=1;

                        }
                    }
                }
            }
        }

    for(i=0;i<j;i++)
    {
        if(new_array[i] == -1)
        {
            if(new_array[i-1] == -1)
            {
                new_array[i] = new_array[i+1];
            }
            else
            {
                new_array[i] = new_array[i-1];
            }

        }
    }

    t = clock() - t;
    double time_elapsed = (double)t/CLOCKS_PER_SEC;
    printf("It took %f seconds to do the weight sort.\n", time_elapsed);

    //for(i=0;i<j;i++)
    //{

    //    printf("new_array[%d] = %d\n",i, new_array[i]);
    //}


}


void sort(int *n,int j )
{
    printf("Doing the bubble sort... This may take a while...\n");
    clock_t t;
    t = clock();
    int ph,fh,i; /* Placeholders and counters */
    int counter = 1; /*Counter is to check if the list was successfully bubble sorted. */
    while (counter != 0) /* Only breaks if bubble sort is done */
    {
        counter = 0;
        for(i=0;i<j;i++)
        {
            ph = n[i];
            fh = n[i + 1];

            if (n[i] > n[i + 1]) /* Comparing adjacent numbers */
            {
                if (i == (j-1)) /* When we reach the last iteration loop through the array again.*/
                {
                    continue;
                }
                n[i] = fh; /* Switching if the ith iteration is bigger than the next iteration.*/
                n[i+1] = ph;
                counter += 1;
            }

        }
    }
    t = clock() - t;
    double time_elapsed = (double)(t)/CLOCKS_PER_SEC;

    //for(i=0;i<j;i++) /* Printing out the sorted array.*/
    //{
    //    printf("%d\n", n[i]);
    //}

    printf("It took %f seconds to complete the bubble sort\n", time_elapsed);

}

int main()
{
    srand((unsigned)time(NULL) * getpid());
    //int j = rand() % 1000;
    int j = 100000;
    int *n; /* Creating pointer*/
    int *weight, *new_array, *repeat_array;
    float *total_weight;
    int i;

    //Setting aside memory for the pointers
    n = (int*)malloc(j * sizeof(int));
    weight = (int*)calloc(j, sizeof(int)); //Will be used to hold the raw weights
    total_weight = (int*)calloc(j,sizeof(float)); //Will be used to hold the new total weights
    new_array = (int*)calloc((j+1), sizeof(int)); //Will be used to store our new n+1 element array
    repeat_array = (int*)calloc(j,sizeof(int)); //Will be used to store overwrite information.
    //

    printf("We have a total of %d elements\n", j);

    for(i=0;i<j;i++) /* Populating array elements */
    {
        n[i] = (rand() % 500) + (rand() % 500);
    }



    //sort(n,j);
    //printf("10 seconds until the weighted sort...\n");
    //sleep(10);
    weight_sort(n, weight, j ,total_weight, new_array, repeat_array);



    free(n);
    free(weight);
    free(total_weight);
    free(new_array);
    free(repeat_array);


    return 0;
}
