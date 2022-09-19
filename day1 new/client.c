#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
    FILE* fp;
    fp = fopen("customer.dat", "r"); 
    struct person p[MAX_CUST];
    read_cust_data(fp, p);

    struct date start_date;
    printf("Enter billing start date(dd mm yyyy): ");
    scanf("%d %d %d", &start_date.dd, &start_date.mm, &start_date.yy);

    struct date end_date;
    printf("Enter billing end date(dd mm yyyy): ");
    scanf("%d %d %d", &end_date.dd, &end_date.mm, &end_date.yy);

    if(! is_valid_dates(&start_date, &end_date)){
        printf("Invalid date provided!!!");
        exit(1);
    }

    int n = date_diff(&start_date, &end_date);
    struct bill b[n+1];

    generate_bill(b, &start_date, n+1, p);
    disp_data_by_day(b, n+1, p);
    disp_data_by_person(b, n+1, p);

    fclose(fp);
}