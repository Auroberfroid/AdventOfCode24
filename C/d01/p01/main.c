/* ################# includes ################# */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

/* ################## macro ################### */


#define NB_PAIRS 1000u
#define MAX_INPUT_SIZE 256u
#define INTEGER_SIZE_IN_CHAR 5u
#define NB_SPACES_BETWEEN_PAIRS 3u

static uint32_t pair_table[2][NB_PAIRS] = {0};
static char* input_filepath = "../files/input";


int main()
{
    FILE* input_file = NULL; 
    uint32_t result = 0;


    process_input(input_file);

    sort_pair_table();

    // print_pair_table();

    for (int i = 0; i < NB_PAIRS; i++)
    {
        result += (u_int32_t) abs((int) (pair_table[0][i] - pair_table[1][i]));
    }

    printf("%u\n", result);

    return EXIT_SUCCESS;
}




/********************************* */
/* Get inputfile content fonctions */
/********************************* */

int openfile(char* input_filepath, FILE** p_f)
{
    if (access(input_filepath, R_OK) != 0)
    {
        printf("ERROR: The file %s isn't accessible...\n", input_filepath);
        return EXIT_FAILURE;
    }

    *p_f = fopen(input_filepath, "r");

    return EXIT_SUCCESS;
}

int process_input(FILE* input_file)
{
    char buffer[INTEGER_SIZE_IN_CHAR];

    if (openfile(input_filepath, &input_file) != 0)
    {
        printf("ERROR while openfile...\n");
    }

    for (int i = 0; i < NB_PAIRS; i++)
    {
        fread(buffer, INTEGER_SIZE_IN_CHAR, sizeof(char), input_file);
        pair_table[0][i] = (uint32_t) atoi(buffer);
        fseek(input_file, NB_SPACES_BETWEEN_PAIRS , SEEK_CUR); // Skip the 3 spaces
        fread(buffer, INTEGER_SIZE_IN_CHAR, sizeof(char), input_file);
        pair_table[1][i] = (uint32_t) atoi(buffer);
        fseek(input_file, 1 , SEEK_CUR); // Skip the \n
    }

}

int print_pair_table()
{
    for (int i = 0; i < NB_PAIRS; i++)
    {
        printf("pair_table[%d] = [%u, %u]\n", i, pair_table[0][i], pair_table[1][i]);
    }
    return 0;
}

/********************************* */
/* Process the data functions      */
/********************************* */

int compare(const void* a, const void* b)
{
    return (*(uint32_t*) a - *(uint32_t*) b);
}

int sort_pair_table()
{
    qsort(pair_table[0], NB_PAIRS, sizeof(uint32_t), &compare);
    qsort(pair_table[1], NB_PAIRS, sizeof(uint32_t), &compare);
}