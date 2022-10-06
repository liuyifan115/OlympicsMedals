#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

double average(double *arg,int length);

static double data[6][8]={
        70,91,100,63,58,50,54,28,
        11.23,8.53,4.59,1.96,1.21,0.86,0.43,0.31,
        121,104,100,101,93,101,108,94,
        18.7,16.25,14.77,12.22,10.25,8.07,6.52,5.24,
        56,67,72,90,89,63,112,132,
        1.28,2.21,1.66,0.59,0.26,0.39,0.46,0.55
};
static double year[8]={2016,2012,2008,2004,2000,1996,1992,1988};

int main(){
    double rMG[3];
    double coefficientMG[3][2];

    double rMY[3];
    double coefficientMY[3][2];

    double rGY[3];
    double coefficientGY[3][2];

    for (int i = 0; i < 6; i+=2) {
        double covMG=0,covMY=0,covGY=0,stdvG=0,stdvM=0,stdvY=0,variG=0,variM=0,variY=0;
        double averageM = average(data[i],8);
        double averageG = average(data[i+1],8);
        double averageY = average(year,8);
        for (int j = 0; j < 8; ++j) {
            covMG += (data[i + 1][j] - averageG) * (data[i][j] - averageM);
            covMY += (data[i + 1][j] - averageG) * (year[j] - averageY);
            covGY += (data[i][j] - averageG) * (year[j] - averageY);

            stdvG += (data[i + 1][j] - averageG) * (data[i + 1][j] - averageG);
            variG = sqrt(stdvG);

            stdvM += (data[i][j] - averageM) * (data[i][j] - averageM);
            variM = sqrt(stdvM);

            stdvY += (year[j] - averageY) * (year[j] - averageY);
            variY = sqrt(stdvY);
        }
        coefficientMG[i / 2][1] = covMG / variG;
        coefficientMG[i / 2][0] = averageM - coefficientMG[i / 2][1] * averageG;
        rMG[i / 2]= covMG / (variG * variM);

        coefficientMY[i / 2][1] = covMY / variY;
        coefficientMY[i / 2][0] = averageM - coefficientMY[i / 2][1] * averageY;
        rMY[i / 2]= covMY / (variM * variY);

        coefficientGY[i / 2][1] = covGY / variY;
        coefficientGY[i / 2][0] = averageG - coefficientGY[i / 2][1] * averageY;
        rGY[i / 2]= covGY / (variG * variY);
    }
    printf("%.2lf %.2lf %.2lf\n", rMG[0], rMG[1], rMG[2]);
    for (int i = 0; i < 3; ++i) {
        printf("%.2lf %.2lf\n", coefficientMG[i][0], coefficientMG[i][1]);
    }

    //打印相关系数和线性回归方程
    printf("\tChina\tUSA\tRussia\n");
    printf("rMG\t%.2lf\t%.2lf\t%.2lf\n", rMG[0], rMG[1], rMG[2]);
    printf("equation\ty=%.2lfx+%.2lf\ty=%.2lfx+%.2lf\ty=%.2lfx+%.2lf", coefficientMG[0][1], coefficientMG[0][0], coefficientMG[1][1], coefficientMG[1][0], coefficientMG[2][1], coefficientMG[2][0]);
    printf("\n\n");

    printf("\tChina\tUSA\tRussia\n");

    //打印实际奖牌数
    for (int i = 0; i < 8; ++i) {
        printf("%d\t%.0lf\t%.0lf\t%.0lf\n",1988+4*i,data[0][7-i],data[2][7-i],data[4][7-i]);
    }

    //打印预测的奖牌数
    for (int i = 0; i < 5; ++i) {
        printf("%d\t%.0lf\t%.0lf\t%.0lf\n",2020+4*i,coefficientMY[0][1]*2022+4*i+coefficientMY[0][0],coefficientMY[1][1]*2022+4*i+coefficientMY[1][0],coefficientMY[2][1]*2022+4*i+coefficientMY[2][0]);
    }

    printf("\n\n");
    printf("\tChina\tUSA\tRussia\n");

    //打印实际GDP
    for (int i = 0; i < 8; ++i) {
        printf("%d\t%.2lf\t%.2lf\t%.2lf\n",1988+4*i,data[1][7-i],data[3][7-i],data[5][7-i]);
    }

    //打印预测的GDP
    for (int i = 0; i < 5; ++i) {
        printf("%d\t%.2lf\t%.2lf\t%.2lf\n",2020+4*i,coefficientGY[0][1]*2022+4*i+coefficientGY[0][0],coefficientGY[1][1]*2022+4*i+coefficientGY[1][0],coefficientGY[2][1]*2022+4*i+coefficientGY[2][0]);
    }



    FILE *fp;
    fp = fopen("result.xls","w");
    fprintf(fp,"\tChina\tUSA\tRussia\n");
    fprintf(fp, "rMG\t%.2lf\t%.2lf\t%.2lf\n", rMG[0], rMG[1], rMG[2]);
    fprintf(fp, "equation\ty=%.2lfx%.2lf\ty=%.2lfx%.2lf\ty=%.2lfx%.2lf", coefficientMG[0][1], coefficientMG[0][0], coefficientMG[1][1], coefficientMG[1][0], coefficientMG[2][1], coefficientMG[2][0]);
}

double average(double *arg,int length){
    double sum=0;
    for (int i = 0; i < length; ++i) {
        sum += *arg;
        arg++;
    }
    sum *= 1.0/length;
    return sum;
}