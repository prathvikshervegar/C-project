#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(){
    FILE* fp;
    fp = fopen("customer.dat", "r"); 
    struct person p[MAX_CUST];
    read_cust_data(fp, p);

    int start_day;
    printf("Enter billing start day(Mon-1/Tue-2/Wed-3/Thur-4/Fri-5/Sat-6/Sun-7): ");
    scanf("%d", &start_day);
    struct date start_date;
    printf("Enter billing start date(dd mm yyyy): ");
    scanf("%d %d %d", &start_date.dd, &start_date.mm, &start_date.yy);
    if(! is_valid_date(&start_date)){
        printf("Invalid date provided!!!\n");
        exit(1);
    }
    struct date end_date;
    printf("Enter billing end date(dd mm yyyy): ");
    scanf("%d %d %d", &end_date.dd, &end_date.mm, &end_date.yy);
    if(! is_valid_date(&end_date)){
        printf("Invalid date provided!!!\n");
        exit(1);
    }
    if(! is_valid_range(&start_date, &end_date)){
        printf("Invalid range provided!!!\n");
        exit(1);
    }
    int n = date_diff(&start_date, &end_date);
    //printf("%d", n);
    struct bill b[n+1];

    generate_bill(b, &start_date, start_day, n+1, p);

    int choice;
    struct date cur_date;
    char full_name[30], last_name[30];
    while(1){
        printf("\n1 - Bills of all dates\n2 - Bills of all persons\n3 - Bills of all days\n4 - Bills of all intervals\n5 - Bills of given date\n6 - Bills of given person\n7 - Exit\n\nEnter the choice for report: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: disp_data_all_dates(b, n+1);
                    break;
            case 2: disp_data_all_persons(b, n+1, p);
                    break;
            case 3: disp_data_all_days(b, n+1);
                    break;
            case 4: disp_data_all_hours(b, n+1);
                    break;
            case 5: printf("Enter the date(dd mm yyyy): ");
                    scanf("%d %d %d",&cur_date.dd, &cur_date.mm, &cur_date.yy);
                    disp_data_by_date(b, n+1, cur_date);
                    break;
            case 6: printf("Enter the name of person(Firstname Lastname): ");
                    //fgets(cur_name, sizeof(cur_name), stdin);
                    scanf("%s", full_name);
                    scanf("%s", last_name);
                    strcat(full_name, " ");
                    strcat(full_name, last_name);
                    disp_data_by_person(b, n+1, full_name);
                    break;
            case 7: exit(1);
            default: printf("Invalid choice!!!\n");
        }    
    }
    fclose(fp);
}