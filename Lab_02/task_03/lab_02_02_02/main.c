#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define MIN_SIZE 1
#define NUMBER_OF_ARGUMENTS 1

int input_array(int *array, size_t array_size);

int is_same_digit(int element);

int copy_same_digit_elements(int *array, int *formed_array, size_t array_size, size_t *formed_array_size);

void print_formed_array(int *formed_array, size_t formed_array_size);

int main(void)
{
    printf("APP2.EXE.\n");
    int array[MAX_SIZE];
    int formed_array[MAX_SIZE];
    size_t array_size;
    size_t formed_array_size;
    int exit_code = EXIT_SUCCESS;

    printf("(APP2.EXE)Enter the number of elements: ");
    if (scanf("%zu", &array_size) != NUMBER_OF_ARGUMENTS || array_size > MAX_SIZE || array_size < MIN_SIZE)
    {
        printf("(APP2.EXE)Error, invalid input for the size of the array\n");
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
            printf("(APP2.EXE)Inputted array size: %ld.\n", array_size);
            if (copy_same_digit_elements(array, formed_array, array_size, &formed_array_size) == EXIT_FAILURE)
            {
                exit_code = EXIT_FAILURE;
            }
            else
            {
                printf("(APP2.EXE)The formed array is: ");
                print_formed_array(formed_array, formed_array_size);           
            }
        }
    }

    return exit_code;
}


int input_array(int *array, size_t array_size)
{
    int exit_code_input_array = EXIT_SUCCESS;

    printf("(APP2.EXE)Enter the elements: ");
    for (size_t i = 0; i < array_size && exit_code_input_array == EXIT_SUCCESS; i++)
    {
        printf("(APP2.EXE)Input the %ld element: ", i);
        if (scanf("%d", (array + i)) != NUMBER_OF_ARGUMENTS)
        {
            printf("(APP2.EXE)Error: incorrect input array\n");
            exit_code_input_array = EXIT_FAILURE;
        }
        else
        {
            printf("(APP2.EXE)Inputted %ld element: %d.\n", i, *(array + i));
        }
    }
    
    return exit_code_input_array;
}


int is_same_digit(int element)
{
    int last_digit = abs(element % 10);
    int first_digit;
    int exit_code = EXIT_FAILURE;

    while (abs(element) >= 10)
    {
        element /= 10;
    }

    first_digit = abs(element);

    if (first_digit == last_digit)
    {
        exit_code = EXIT_SUCCESS;
    }

    return exit_code;
}


int copy_same_digit_elements(int *array, int *formed_array, size_t array_size, size_t *formed_array_size)
{
    int exit_code_copy_array = EXIT_FAILURE;
    *formed_array_size = 0;

    for (size_t i = 0; i < array_size; i++)
    {
        if (is_same_digit(array[i]) == EXIT_SUCCESS)
        {
            formed_array[(*formed_array_size)++] = array[i];
        }
    }

    if (*formed_array_size > 0)
    {
        exit_code_copy_array = EXIT_SUCCESS;
    }
    
    return exit_code_copy_array;
}


void print_formed_array(int *formed_array, size_t formed_array_size)
{
    for (size_t i = 0; i < formed_array_size; i++)
    {
        printf("%d ", formed_array[i]);
    }
    printf("\n");
}