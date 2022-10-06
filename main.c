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
//        fseek(p_file, 42L, SEEK_SET);
        while ((line = fgets(buf,sizeof(buf), p_file))!=NULL){
            record = strtok(line, ",");
            while (record != NULL){
                sheet[m][n] = strtod(record,NULL);
                printf("%s ",record);
                record = strtok(NULL, ",");
                n++;
            }
            m++;
        }
        fclose(p_file);
        p_file = NULL;
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 7; ++j) {
            printf("%lf",sheet[i][j]);
        }
    }
    return 0;
}
