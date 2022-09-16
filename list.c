#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

struct person p[50];

void read_cust_data(FILE* fp){
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    while(! feof(fp)){
        for(int i=0;i<50; i++){
            fgets(p[i].name, 49, fp);
            p[i].name[strcspn(p[i].name, "\n")] = 0;
            //printf("%d %s\n", i+1, p[i].name);
        }
    }
    //printf("%s", p[i].name);
}

static int date_diff(const struct date* start_date,const  struct date* end_date){
    int res = 0;
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((start_date->yy%4 ==0 && start_date->yy%100 != 0) || (start_date->yy%400 == 0) ){
        month[1]=29;
    }
    if(start_date->mm == end_date->mm){
        return end_date->dd - start_date->dd;
    }
    res = res + month[start_date->mm - 1] - start_date->dd;
    //printf("%d\n", res);
    for(int i=start_date->mm+1; i<end_date->mm; i++){
        res = res + month[i];
        //printf("%d\n", res);
    }
    //printf("%d\n", res);
    res = res + end_date->dd;
    //printf("%d\n", res);
    return res;
}

static void disp_data(struct details* det,int limit){
    printf("NAME\t\t\tAMOUNT\n");
    for(int i=0; i<limit; i++){
        printf("%s\t\tRs.%.2f\n", det[i].name, det[i].amt);
    }
    printf("\n");
}

void generate_bill(const struct date* start_date,const  struct date* end_date){
    int n = date_diff(start_date, end_date);
    //printf("%d", n);
    struct bill b[n+1];
    int limit;
    for(int i=0; i<=n; i++){
        limit = 20 + rand()%21;
        int temp[limit];
        for(int j=0; j<limit; j++){
            temp[j] = rand()%limit;
            strcpy(b[i].d[j].name, p[temp[j]].name);
            b[i].d[j].amt = (100+ rand()%(5000-100)) + (double)rand()/100;
        }
        printf("Bill day: %d\n", i+1);
        disp_data(b[i].d, limit);
    }
    // for(int k=0;k<limit; k++){
    //         printf("%s, Rs.%.2f\n", b[0].d[k].name, b[0].d[k].amt);
    // }
}

