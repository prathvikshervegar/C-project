#include <stdio.h>
#include "list.h"

int main(){
    FILE* fp;
    fp = fopen("customer.dat", "r"); 

    read_cust_data(fp);

    struct date start_date;
    printf("Enter the year of billing: ");
    scanf("%d", &start_date.yy);
    printf("Enter billing start date(dd mm): ");
    scanf("%d %d", &start_date.dd, &start_date.mm);

    struct date end_date;
    end_date.yy = start_date.yy;
    printf("Enter billing end date(dd mm): ");
    scanf("%d %d", &end_date.dd, &end_date.mm);

    generate_bill(&start_date, &end_date);
}