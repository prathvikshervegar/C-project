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
    return(res);
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

static void disp_data_by_day(const struct details* det,int limit){
    printf("\tNAME\t\t\tAMOUNT\n");
    float total_amt = 0;
    for(int i=0; i<limit; i++){
        total_amt += det[i].amt;
        printf("%d.\t%s\t\tRs.%.2f\n", i+1, det[i].name, det[i].amt);
    }
    printf("Total amount: Rs.%.2f\n", total_amt);
}

static void disp_data_by_person(struct bill* b, int days){
    printf("\tNAME\t\t\tTOTAL AMOUNT\n");
    double total[50] = {0};
    for(int i=0; i<days; i++){
        for(int k=0; k<50; k++){
            for(int j=0; j<40; j++){    
                if(!(strcmp(b[i].d[j].name,p[k].name))){
                    total[k] += b[i].d[j].amt;
                }
            }
        }
    }
    for(int x=0; x<50; x++){
        printf("%d.\t%s\t\tRs.%.2f\n", x+1, p[x].name, total[x]);
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
        printf("\nBill details of %d-%d-%d\n", start_date->dd+i, start_date->mm, start_date->yy);
        disp_data_by_day(b[i].d, limit);
    }
    printf("\nBill details of all persons\n");
    disp_data_by_person(b,n+1);
}

