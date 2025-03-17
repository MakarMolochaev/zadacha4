#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "Matrix.c"

int Func(const char* filename, const char* output)
{
    FILE *file;
    char line[1024];
    int col_capacity = 8;
    int maxLength = 0;
    int* toDelete;
    Matrix m;

    m.count = 0;
    m.lens = malloc(col_capacity * sizeof(int));
    m.els = malloc(col_capacity * sizeof(int *));

    file = fopen(filename, "r");

    if (!file) {
        perror("Error in opening file");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (m.count >= col_capacity) {
            col_capacity *= 2;
            m.lens = realloc(m.lens, col_capacity * sizeof(int));
            m.els = realloc(m.els, col_capacity * sizeof(int *));
        }

        int col_count = 0;
        int elem_capacity = 8;
        m.els[m.count] = malloc(elem_capacity * sizeof(int));

        char *token = strtok(line, " \t\n");
        while (token) {
            if (col_count >= elem_capacity) {
                elem_capacity *= 2;
                m.els[m.count] = realloc(m.els[m.count], elem_capacity * sizeof(int));
            }

            m.els[m.count][col_count] = atoi(token);
            col_count++;

            token = strtok(NULL, " \t\n");
        }

        m.lens[m.count] = col_count;
        m.count++;
    }

    fclose(file);

    toDelete = (in)

    for(int i=0; i<m.count; i++)
    {
        maxLength = (m.lens[i] > maxLength) ? m.lens[i] : maxLength;
    }

    for(int i=0;i<maxLength;i++)
    {
        //printf("Column: %d\n", i);
        int countInColumn = 0;
        int sum = 0;
        for(int j=0;j<m.count;j++){
            if(m.lens[j] <= i) {
                continue;
            }
            sum += m.els[j][i];
            printf("%d ", m.els[j][i]);
            countInColumn++;
        }
        printf("\n");
        for(int j=0;j<m.count;j++){
            if(m.lens[j] <= i) {
                continue;
            }

            if(m.els[j][i] == 0){
                if(sum == 0){
                    printf("%d in row %d\n", m.els[j][i], i);
                }
            }
            else if(sum % m.els[j][i] == 0) {
               printf("%d in row %d\n", m.els[j][i], i); 
            }
        }
    }


    // free negros (memory)
    for (int i = 0; i < m.count; i++) {
        free(m.els[i]);
    }
    free(m.els);
    free(m.lens);

    return 0;
}