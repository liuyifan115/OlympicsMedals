#include <stdio.h>
#include "string.h"
#include "stdlib.h"

int main() {
    double sheet[6][8];
    FILE *p_file = NULL;
    p_file = fopen("data.csv","r");
    char *line, *record = NULL;
    char buf[1000];
    int m = 0,n = 0;
    if(p_file != NULL){
        while ((line = fgets(buf,sizeof(buf), p_file))!=NULL){
            record = strtok(line, ",");
            while (record != NULL){
                printf("%s ",record);
                sheet[m][n] = strtod(record,NULL);
                record = strtok(NULL, ",");
                n++;
            }
            n = 0;
            m++;
        }
        fclose(p_file);
        p_file = NULL;
    }
    printf("\n\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 7; ++j) {
            printf("%.0lf ",sheet[i][j]);
        }
        printf("\n");
    }
    return 0;
}
