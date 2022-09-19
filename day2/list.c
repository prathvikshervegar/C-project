#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"


void read_cust_data(FILE* fp, struct person* p){
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    while(! feof(fp)){
        for(int i=0;i<MAX_CUST; i++){
            fgets(p[i].name, MAX_CUST-1, fp);
            p[i].name[strcspn(p[i].name, "\n")] = 0;
            //printf("%d %s\n", i+1, p[i].name);
        }
    }
}

int is_valid_dates(const struct date* start_date, const struct date* end_date){
    int month[MAX_MONTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((start_date->yy%4 ==0 && start_date->yy%100 != 0) || (start_date->yy%400 == 0) ){
        month[1]=29;
    }

    if(start_date->yy > end_date->yy)
        return 0;
    if(start_date->yy == end_date->yy && start_date->mm > end_date->mm)
        return 0;
    if(start_date->yy == end_date->yy && start_date->mm == end_date->mm && start_date->dd > end_date->dd)
        return 0;
    if(start_date->dd < 1 || start_date->dd > month[start_date->mm-1])
        return 0;
    if(start_date->mm < 1 || start_date->mm > MAX_MONTH)
        return 0;
    if(start_date->yy < MIN_YEAR || start_date->yy > MAX_YEAR)
        return 0;
    return 1;
}

int date_diff(const struct date* start_date,const  struct date* end_date){
    int res = 0;
    int month[MAX_MONTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
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

static int get_random_val(int min, int max){
    return rand()%(max - min + 1) + min;
}

static void generate_array_of_unique_indices(int* arr, int max){
    int used[MAX_CUST] = {0};
    int i = 0;
    while(i<max){
        int num = rand()%MAX_CUST;
        if(used[num] == 0){
            arr[i]= num;
            used[num]=1;
            ++i;
        }
    }
}

void disp_data_by_day(struct bill* b, int days, struct person* p){
    for(int i=0; i<days; i++){
        printf("\nBill details of %d-%d-%d\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        printf("\tNAME\t\t\tAMOUNT\n");
        float total_amt = 0;
        for(int j=0; j<b[i].limit; j++){
            total_amt += b[i].d[j].amt;
            printf("%d.\t%s\t\tRs.%.2f\n", j+1, b[i].d[j].name, b[i].d[j].amt);
        }
        printf("Total amount: Rs.%.2f\n", total_amt);
    }
}

void disp_data_by_person(struct bill* b, int days, struct person* p){
    printf("\nBill details of all persons\n");
    printf("\tNAME\t\t\tTOTAL AMOUNT\n");
    double total[MAX_CUST] = {0};
    for(int i=0; i<days; i++){
        for(int k=0; k<MAX_CUST; k++){
            for(int j=0; j<MAX_BILLS_PER_DAY; j++){    
                if(!(strcmp(b[i].d[j].name,p[k].name))){
                    total[k] += b[i].d[j].amt;
                }
            }
        }
    }
    for(int x=0; x<MAX_CUST; x++){
        printf("%d.\t%s\t\tRs.%.2f\n", x+1, p[x].name, total[x]);
    }
}

void generate_bill(struct bill* b, const struct date* start_date, int days, struct person* p){
    
    //printf("%d", n);
    //int limit;
    int month[MAX_MONTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((start_date->yy%4 ==0 && start_date->yy%100 != 0) || (start_date->yy%400 == 0) ){
        month[1]=29;
    }
    struct date bill_date = *start_date;
    for(int i=0; i<days; i++){
        b[i].limit = get_random_val(MIN_BILLS_PER_DAY, MAX_BILLS_PER_DAY);
        b[i].dt = bill_date;
        int temp[b[i].limit];
        generate_array_of_unique_indices(temp, b[i].limit);
        for(int j=0; j<b[i].limit; j++){
            //temp[j] = rand()%limit;
            strcpy(b[i].d[j].name, p[temp[j]].name);
            b[i].d[j].amt = (MIN_BILL_AMT+ rand()%(MAX_BILL_AMT-MIN_BILL_AMT)) + (double)rand()/100;
        }
        if(bill_date.dd == month[bill_date.mm-1]){
            if(bill_date.mm == MAX_MONTH){
                bill_date.mm = 1;
                ++bill_date.yy;
            }
            else
                ++bill_date.mm;
            bill_date.dd = 1;
        }
        else{
            ++bill_date.dd;
        }
    }
}

