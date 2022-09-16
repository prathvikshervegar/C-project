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
    for(int i=start_date->mm+1; i<end_date->mm; i++){
        res = res + month[i];
    }
    res = res + end_date->dd;
    return res;
}

static void disp_data_by_day(struct details* det,int limit){
    printf("NAME\t\t\tAMOUNT\n");
    float total_amt = 0;
    for(int i=0; i<limit; i++){
        total_amt += det[i].amt;
        printf("%s\t\tRs.%.2f\n", det[i].name, det[i].amt);
    }
    printf("Total amount: Rs.%.2f\n", total_amt);
}

static int get_random_val(int min, int max){
    return rand()%(max - min + 1) + min;
}

static void generate_array_of_unique_indices(int* arr, int max){
    int used[50] = {0};
    int i = 0;
    while(i<max){
        int num = rand()%50;
        if(used[num] == 0){
            arr[i]= num;
            used[num]=1;
            ++i;
        }
    }
}

void generate_bill(const struct date* start_date,const  struct date* end_date){
    int n = date_diff(start_date, end_date);
    //printf("%d", n);
    struct bill b[n+1];
    int limit;
    for(int i=0; i<=n; i++){
        //limit = 20 + rand()%21;
        limit = get_random_val(20, 40);
        int temp[limit];
        generate_array_of_unique_indices(temp, limit);
        for(int j=0; j<limit; j++){
            //temp[j] = rand()%limit;
            strcpy(b[i].d[j].name, p[temp[j]].name);
            b[i].d[j].amt = (100+ rand()%(5000-100)) + (double)rand()/100;
        }
        printf("\nDay %d : Bill details\n", i+1);
        disp_data_by_day(b[i].d, limit);
    }
}

