#include "stdio.h"
#include "math.h"

double average(double *arr, int length);
double variance(double *arr, int length);
double stddevi(double *arr, int length);
double cov(double *arrX, double *arrY, int length);
double relation(double *arrX, double *arrY, int length);
void coefficient(double *arrX, double *arrY, int length, double *coefficient);

static double data[36][8]={
        70,91,100,63,58,50,54,28,
        11.23,8.53,4.59,1.96,1.21,0.86,0.43,0.31,
        121,104,100,101,93,101,108,94,
        18.7,16.25,14.77,12.22,10.25,8.07,6.52,5.24,
        56,67,72,90,89,63,112,132,
        1.28,2.21,1.66,0.59,0.26,0.39,0.46,0.55,
        4,4,6,6,4,3,1,2,
        0.56,0.55,0.36,0.16,0.28,0.27,0.23,0.13,
        29,35,46,50,58,41,27,14,
        1.21,1.55,1.06,0.61,0.42,0.4,0.33,0.24,
        19,17,15,10,12,15,3,6,
        1.8,2.47,1.7,0.67,0.66,0.85,0.33,0.26,
        22,18,18,12,14,22,18,10,
        1.53,1.83,1.55,1.03,0.74,0.63,0.59,0.51,
        42,35,40,33,38,37,29,16,
        2.47,2.68,2.93,2.12,1.37,1.61,1.4,1.02,
        42,44,41,49,56,65,82,142,
        3.47,3.53,3.75,2.81,1.95,2.5,2.13,1.4,
        2,6,3,1,1,1,0,0,
        2.29,1.83,1.2,0.71,0.47,0.4,0.29,0.3,
        3,3,5,4,6,4,5,1,
        0.93,0.92,0.51,0.26,0.17,0.23,0.13,0.08,
        28,28,28,32,34,35,19,14,
        1.88,2.09,2.41,1.81,1.15,1.31,1.32,0.89,
        41,38,25,37,18,14,22,14,
        5,6.27,5.11,4.89,4.97,4.92,3.91,3.07,
        21,30,31,30,28,27,29,33,
        1.5,1.28,1.05,0.79,0.58,0.61,0.36,0.2,
        5,8,3,4,6,1,1,2,
        1.08,1.2,1.11,0.78,0.71,0.41,0.36,0.18,
        10,6,1,6,5,5,2,0,
        0.32,0.43,0.32,0.26,0.15,0.16,0.15,0.1,
        8,3,8,10,5,6,6,2,
        0.87,0.88,0.77,0.41,0.27,0.18,0.16,0.09,
        67,65,47,30,28,15,20,24,
        2.72,2.72,2.94,2.42,1.66,1.42,1.18,0.91
};
static double year[8]={2016,2012,2008,2004,2000,1996,1992,1988};

static char countryname[]="\tChina\tUSA\tRussia\tArgentina\tAustralia\tBrazil\tCanada\tFrance\tGerman\tIndia\tIndonesia\tItalia"
                          "\tJapan\tKorean\tMexico\tNorth Africa\tTurkey\n";

int main(){
    double rMG[18];
    double coefficientMG[18][2];

    double rMY[18];
    double coefficientMY[18][2];

    double rGY[18];
    double coefficientGY[18][2];

    for (int i = 0; i < 36; i+=2) {
        //计算线性回归方程系数a,b
        coefficient(data[i+1],data[i],8,coefficientMG[i/2]);
        coefficient(year,data[i],8,coefficientMY[i/2]);
        coefficient(year,data[i+1],8,coefficientGY[i/2]);
        //计算相关系数r
        rMG[i/2] = relation(data[i+1],data[i],8);
        rMY[i/2] = relation(year,data[i],8);
        rGY[i/2] = relation(year,data[i+1],8);
    }
//控制台输出区

    //打印相关系数和线性回归方程
    printf("%s", countryname);
    printf("r\t");
    for (int i = 0; i < 18; ++i) {
        printf("%.2lf\t",rMG[i]);
    }
    printf("\n");
    printf("equation\t");
    for (int i = 0; i < 18; ++i) {
        if(coefficientMG[i][0]>0){
            printf("y=%.2lfx+%.2lf\t",coefficientMG[i][1], coefficientMG[i][0]);
        }
        else{
            printf("y=%.2lfx%.2lf\t",coefficientMG[i][1], coefficientMG[i][0]);
        }
    }
    printf("\n\n");
    printf("%s", countryname);

    //打印实际奖牌数
    for (int i = 0; i < 8; ++i) {
        printf("%d\t",1988+4*i);
        for (int j = 0; j < 36; j+=2) {
            printf("%.0lf\t",data[j][7-i]);
        }
        printf("\n");
    }

    //打印预测的奖牌数
    for (int i = 0; i < 10; ++i) {
        printf("%d\t",2020+4*i);
        for (int j = 0; j < 18; ++j) {
            printf("%.0lf\t",coefficientMY[j][1]*2022+4*i+coefficientMY[j][0]);
        }
        printf("\n");
    }

    printf("\n\n");
    printf("%s", countryname);

    //打印实际GDP
    for (int i = 0; i < 8; ++i) {
        printf("%d\t",1988+4*i);
        for (int j = 0; j < 36; j+=2) {
            printf("%.2lf\t",data[j+1][7-i]);
        }
        printf("\n");
    }

    //打印预测的GDP
    for (int i = 0; i < 10; ++i) {
        printf("%d\t",2020+4*i);
        for (int j = 0; j < 18; ++j) {
            printf("%.2lf\t",coefficientGY[j][1]*2022+4*i+coefficientGY[j][0]);
        }
        printf("\n");
    }


//文件输出区
    FILE *fp;
    fp = fopen("result.xls","w");

    //输出相关系数
    fprintf(fp,"%s", countryname);
    fprintf(fp,"r\t");
    for (int i = 0; i < 18; ++i) {
        fprintf(fp,"%.2lf\t",rMG[i]);
    }
    fprintf(fp,"\n");

    //输出线性回归方程
    fprintf(fp,"equation\t");
    for (int i = 0; i < 18; ++i) {
        if(coefficientMG[i][0]>0){
            fprintf(fp,"y=%.2lfx+%.2lf\t",coefficientMG[i][1], coefficientMG[i][0]);
        }
        else{
            fprintf(fp,"y=%.2lfx%.2lf\t",coefficientMG[i][1], coefficientMG[i][0]);
        }
    }
    fprintf(fp,"\n\n");

    fprintf(fp,"Medal\n");

    fprintf(fp,"%s", countryname);


    //输出实际奖牌数
    for (int i = 0; i < 8; ++i) {
        fprintf(fp,"%d\t",1988+4*i);
        for (int j = 0; j < 36; j+=2) {
            fprintf(fp,"%.0lf\t",data[j][7-i]);
        }
        fprintf(fp,"\n");
    }

    //输出预测的奖牌数
    for (int i = 0; i < 10; ++i) {
        fprintf(fp,"%d\t",2020+4*i);
        for (int j = 0; j < 18; ++j) {
            fprintf(fp,"%.0lf\t",coefficientMY[j][1]*2022+4*i+coefficientMY[j][0]);
        }
        fprintf(fp,"\n");
    }

    fprintf(fp,"\n\n");
    fprintf(fp,"GDP\n");
    fprintf(fp,"\tChina\tUSA\tRussia\n");

    //输出实际GDP
    for (int i = 0; i < 8; ++i) {
        fprintf(fp,"%d\t",1988+4*i);
        for (int j = 0; j < 36; j+=2) {
            fprintf(fp,"%.2lf\t",data[j+1][7-i]);
        }
        fprintf(fp,"\n");
    }

    //输出预测的GDP
    for (int i = 0; i < 10; ++i) {
        fprintf(fp,"%d\t",2020+4*i);
        for (int j = 0; j < 18; ++j) {
            fprintf(fp,"%.2lf\t",coefficientGY[j][1]*2022+4*i+coefficientGY[j][0]);
        }
        fprintf(fp,"\n");
    }

}

//计算平均数
double average(double *arr, int length){
    double sum=0;
    for (int i = 0; i < length; ++i) {
        sum += *arr;
        arr++;
    }
    sum *= 1.0/length;
    return sum;
}

//计算方差
double variance(double *arr, int length){
    double aver=average(arr, length);
    double sum=0;
    for (int i = 0; i < length; ++i) {
        sum += (*arr - aver) * (*arr - aver);
        arr++;
    }
    return sum;
}

//计算标准差
double stddevi(double *arr, int length){
    return sqrt(variance(arr,length));
}

//计算cov
double cov(double *arrX, double *arrY, int length){
    double averX = average(arrX,length);
    double averY = average(arrY,length);
    double sum = 0;
    for (int i = 0; i < length; ++i) {
        sum += (*arrX - averX)*(*arrY - averY);
        arrX++;
        arrY++;
    }
    return sum;
}

//计算相关系数
double relation(double *arrX, double *arrY, int length){
    return cov(arrX,arrY,length)/(stddevi(arrX,length)* stddevi(arrY,length));
}

//计算线性回归方程的系数
void coefficient(double *arrX, double *arrY, int length, double *coefficient){
    double b = cov(arrX,arrY,length)/ variance(arrX,length);
    *coefficient = average(arrY,length)-b* average(arrX,length);
    coefficient++;
    *coefficient=b;
}

