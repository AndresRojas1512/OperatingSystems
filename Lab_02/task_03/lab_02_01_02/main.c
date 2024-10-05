#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_SIZE 10
#define MIN_SIZE 1
#define NUMBER_OF_ARGUMENTS 1

int input_array(int *array, size_t array_size);

int average_negative_numbers(int *array, size_t array_size, double *average);

int main()
{
    // printf("APP1.EXE.\n");
    int array[MAX_SIZE];
    double average = 0.0;
    size_t array_size;
    int exit_code = EXIT_SUCCESS;
    
    printf("(%d)Enter the number of elements: ", getpid());
    if (scanf("%zu", &array_size) != NUMBER_OF_ARGUMENTS || array_size > MAX_SIZE || array_size < MIN_SIZE)
    {
        printf("(%d)Error, invalid input for the size of the array\n", getpid());
        exit_code = EXIT_FAILURE;
    }
    else
    {
        if (input_array(array, array_size) == EXIT_FAILURE)
        {
            exit_code = EXIT_FAILURE;
        }
        else
        {
            printf("(%d)Inputted array size: %ld.\n", getpid(), array_size);
            exit_code = average_negative_numbers(array, array_size, &average);
            if (exit_code == EXIT_SUCCESS)
            {
                printf("(%d)Average: ", getpid());
                printf("(%d)%f\n", getpid(), average);
            }
            else
            {
                printf("(%d)The average couldnt be calculated: no negative elements\n", getpid());
            }
        }
    }

    return exit_code;
}


int input_array(int *array, size_t array_size)
{
    int exit_code_input_array = EXIT_SUCCESS;

    printf("(%d)Enter the elements: ", getpid());
    for (size_t i = 0; i < array_size && exit_code_input_array == EXIT_SUCCESS; i++)
    {
        printf("(%d)Input the %ld element: ", getpid(), i);
        if (scanf("%d", (array + i)) != NUMBER_OF_ARGUMENTS)
        {
            printf("(%d)Error: incorrect input array\n", getpid());
            exit_code_input_array = EXIT_FAILURE;
        }
        else
        {
            printf("(%d)Inputted %ld element: %d.\n", getpid(), i, *(array + i));
        }
    }
    
    return exit_code_input_array;
}


int average_negative_numbers(int *array, size_t array_size, double *average)
{
    int count = 0;
    double sum = 0.0;
    int exit_code_find_average = EXIT_FAILURE;
    *average = 0.0;

    for (size_t i = 0; i < array_size; i++)
    {
        if (array[i] < 0)
        {
            count++;
            sum += array[i];
        }
    }
    if (count > 0)
    {
        *average = sum / count;
        exit_code_find_average = EXIT_SUCCESS;
    }

    return exit_code_find_average;
}