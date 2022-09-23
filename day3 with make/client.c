#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bill_generate.h"
#include "date.h"
#include "read.h"
#include "display.h"

int main(){
    FILE* fp1;
    FILE* fp2;
    fp1 = fopen("customer.dat", "r"); 
    struct person p[MAX_CUST];
    read_cust_data(fp1, p);

    fp2 = fopen("item_master.csv", "r"); 
    struct item item[MAX_ITEM];
    read_item_data(fp2, item);

    int start_day;
    struct date start_date;
    struct date end_date;
    read_dates(&start_day, &start_date, &end_date);

    if(! is_valid_range(&start_date, &end_date)){
        printf("Invalid range provided!!!\n");
        exit(1);
    }
    int n = date_diff(&start_date, &end_date);
    struct bill b[n];

    generate_bill(b, &start_date, start_day, n, p, item);

    while(1){
        display_by_choices(b, n, p, item);    
    }
}