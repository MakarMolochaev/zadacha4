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
    int toDeleteCount = 0;
    int delCounter = 0;
    int flag = 0;
    int C = 0;
    int* newLengths;
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


    for(int i=0; i<m.count; i++)
    {
        maxLength = (m.lens[i] > maxLength) ? m.lens[i] : maxLength;
    }

    toDelete = (int*)malloc(maxLength * sizeof(int));
    newLengths = (int*)malloc(m.count * sizeof(int));

    for(int i=0;i<m.count;i++){
        newLengths[i] = m.lens[i];
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
            //printf("%d ", m.els[j][i]);
            countInColumn++;
        }
        //printf("\n\n");
        for(int j=0;j<m.count;j++){
            if(m.lens[j] <= i) {
                continue;
            }

            if(m.els[j][i] == 0){
                if(sum == 0){
                    toDelete[toDeleteCount] = i;
                    toDeleteCount++;
                    break;
                    //printf("%d in row %d\n", m.els[j][i], i);
                }
            }
            else if(sum % m.els[j][i] == 0) {
                toDelete[toDeleteCount] = i;
                toDeleteCount++;
                break;
                //printf("%d in row %d\n", m.els[j][i], i);
            }
        }
    }

    for(int i=0;i<toDeleteCount;i++){
        printf("%d ", toDelete[i]);
    }
    printf("\n"); 

    while(flag < maxLength){
        if(toDelete[delCounter] == flag)
        {
            delCounter++;
            flag++;
            continue;
        }
        printf("%d -> %d\n", flag, C);
        for(int j=0;j<m.count;j++){
            if(m.lens[j] <= C) {
                continue;
            }
            m.els[j][C] = m.els[j][flag];
        }
        C++;
        flag++;
    }

    
    for(int i=0;i<toDeleteCount;i++)
    {
        for(int j=0;j<m.count;j++)
        {
            if(m.lens[j] > toDelete[i]){
                newLengths[j] = m.lens[j] - i - 1;
            }
        }
    }
    

    // Вывод данных для проверки
    for (int i = 0; i < m.count; i++) {
        printf("Len: %d:  ", newLengths[i]);
        for (int j = 0; j < newLengths[i]; j++) {
            printf("%d ", m.els[i][j]);
        }
        printf("\n");
    }


    // free negros (memory)
    for (int i = 0; i < m.count; i++) {
        free(m.els[i]);
    }
    free(m.els);
    free(m.lens);

    return 0;
}