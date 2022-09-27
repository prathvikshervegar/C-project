#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "item.h"
#include "date.h"
#include "bill_generate.h"

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
    printf("Enter billing start day(Mon-1/Tue-2/Wed-3/Thur-4/Fri-5/Sat-6/Sun-7): ");
    scanf("%d", &start_day);
    if(! is_valid_day(start_day)){
        printf("Invalid day provided!!!\n");
        exit(1);
    }

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

    generate_bill(b, &start_date, start_day, n+1, p, item);

    int choice;
    struct date cur_date;
    char full_name[30], last_name[30];
    int v;
    int start, end;
    while(1){
        printf("\n1 - Bills of all dates"
                "\n2 - Bills of all persons"
                "\n3 - Bills of all items"
                "\n4 - Bills of all days"
                "\n5 - Bills of all intervals"
                "\n6 - Bills of items all dates"
                "\n7 - Bills of given date"
                "\n8 - Bills of given person"
                "\n9 - Detailed bill report"
                "\nPress 0 to exit\n"
                "\nEnter the choice for report: ");
        scanf("%d", &choice);
        switch(choice){
            case 0: printf("Exiting...\n");
                    exit(1);
            case 1: disp_data_all_dates(b, n+1);
                      break;
            case 2: disp_data_all_persons(p);
                      break;
            case 3: disp_data_all_items(item);
                      break;
            case 4: disp_data_all_days(b, n+1);
                      break;
            case 5: disp_data_all_hours(b, n+1);
                      break;
            case 6: printf("Datewise(0) or Periodwise(1)?:");
                    scanf("%d", &v);
                    struct date d1;
                    struct date d2;
                    if(v == 0){
                        printf("Enter the date: ");
                        scanf("%d %d %d", &d1.dd, &d1.mm, &d1.yy);
                        if(! is_valid_date(&d1)){
                            printf("Invalid date provided!!!\n");
                            break;
                            //exit(1);
                        }
                        d2 = d1;
                    }
                    else if(v == 1){
                        printf("Enter Date 1: ");
                        scanf("%d %d %d", &d1.dd, &d1.mm, &d1.yy);
                        if(! is_valid_date(&d1)){
                            printf("Invalid date provided!!!\n");
                            break;
                            //exit(1);
                        }
                        printf("Enter Date 2: ");
                        scanf("%d %d %d", &d2.dd, &d2.mm, &d2.yy);
                        if(! is_valid_date(&d2)){
                            printf("Invalid date provided!!!\n");
                            break;
                            //exit(1);
                        }
                        if(! is_valid_range(&d1, &d2)){
                            printf("Invalid range provided!!!\n");
                            break;
                            //exit(1);
                        }
                    }
                    else{
                        printf("Invalid choice\n");
                        exit(1);
                    }
                    start = date_diff(&start_date, &d1);
                    end = n - date_diff(&d2, &end_date);
                    if(start < 0 || end > n+1){
                        printf("Date out of range\n");
                        break;
                    }
                    disp_data_by_dates_and_items(b, start, end, item);
                    break;        
            case 7: printf("Enter the date(dd mm yyyy): ");
                    scanf("%d %d %d",&cur_date.dd, &cur_date.mm, &cur_date.yy);
                    if(! is_valid_date(&cur_date)){
                        printf("Invalid date provided!!!\n");
                        break;
                        //exit(1);
                    }
                    disp_data_by_date(b, n+1, cur_date);
                    break;
            case 8: printf("Enter the name of person(Firstname Lastname): ");
                    scanf("%s", full_name);
                    strcat(full_name, " ");
                    scanf("%s", last_name);
                    strcat(full_name, last_name);
                    //gets(full_name);
                    disp_data_by_person(b, n+1, full_name);
                    break;
            case 9: disp_detailed_bill(b,n+1);
                      break;
            default: printf("Invalid choice");
        }    
    }
}