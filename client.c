#include <stdio.h>
#include "list.h"

int main(){
    FILE* fp;
    fp = fopen("customer.dat", "r"); 

    read_cust_data(fp);

    struct date start_date;
    printf("Enter billing start date(dd mm yyyy): ");
    scanf("%d %d %d", &start_date.dd, &start_date.mm, &start_date.yy);

    struct date end_date;
    printf("Enter billing end date(dd mm yyyy): ");
    scanf("%d %d %d", &end_date.dd, &end_date.mm, &end_date.yy);

    generate_bill(&start_date, &end_date);
}