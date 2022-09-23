#include <stdio.h>
#include "display.h"
#include "bill_generate.h"
#include "date.h"
#include "read.h"

void display_by_choices(struct bill* b, int n, struct person* p, struct item* item){
    int choice;
    struct date cur_date;
    char full_name[30];
    printf("\n1 - Bills of all dates"
            "\n2 - Bills of all persons"
            "\n3 - Bills of all items"
            "\n4 - Bills of all days"
            "\n5 - Bills of all intervals"
            "\n6 - Bills of given date"
            "\n7 - Bills of given person"
            "\n8 - Exit\n"
            "\nEnter the choice for report: ");
    scanf("%d", &choice);
    switch(choice){
        case 1: disp_data_all_dates(b, n);
                break;
        case 2: disp_data_all_persons(b, n, p);
                break;
        case 3: disp_data_all_items(b, n, item);
                break;
        case 4: disp_data_all_days(b, n);
                break;
        case 5: disp_data_all_hours(b, n);
                break;
        case 6: printf("Enter the date(dd mm yyyy): ");
                scanf("%d %d %d",&cur_date.dd, &cur_date.mm, &cur_date.yy);
                disp_data_by_date(b, n, cur_date);
                break;
        case 7: printf("Enter the name of person(Firstname Lastname): ");
                gets(full_name);
                disp_data_by_person(b, n, full_name);
                break;
        case 8: exit(1);
        default: printf("Invalid choice!!!\n");
    }
}

static void set_period(int* hr1, char* p1, int* hr2, char* p2){
    if(*hr1 > 12){
        *hr1 %= 12;
        *hr2 %= 12;
        strcpy(p1, "pm");
        strcpy(p2, "pm");
    }
    else if(*hr1 == 12){
        *hr2 %= 12;
        strcpy(p1, "pm");
        strcpy(p2, "pm");
    }
    else if(*hr2 == 12){
        strcpy(p2, "pm");
    }
    else{
        strcpy(p1, "am");
        strcpy(p2, "am");
    }
}

void disp_data_all_dates(const struct bill* b, int days){
    int hr1, hr2;
    char p1[3], p2[3];
    int time[MAX_INTERVALS] = {8, 9, 10, 11, 12, 16, 17, 18, 19, 20, 21};
    for(int i=0; i<days; i++){
        printf("\nBill details of %d-%d-%d\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        if(b[i].day != 2){
            printf("\tTime\t\t\tNAME\t\t\tAMOUNT\n");
            for(int j=0; j<b[i].limit; j++){
                hr1 = time[b[i].d[j].interval];
                hr2 = time[b[i].d[j].interval]+1;
                set_period(&hr1, p1, &hr2, p2);
                printf("%d.\t%d:00%s-%d:00%s\t\t%s\t\tRs.%.2f\n",
                        j+1, hr1, p1, hr2, p2, b[i].d[j].p.name, b[i].d[j].amt);
            }
            printf("Total amount: Rs.%.2f\n", b[i].total_amt);
        }
        else{
            printf("HOLIDAY\n");
        }
    }
}


void disp_data_all_persons(const struct bill* b, int days, struct person* p){
    printf("\nBill details of all persons\n");
    printf("\tNAME\t\t\tTOTAL AMOUNT\n");
    double total[MAX_CUST] = {0};
    for(int i=0; i<days; i++){
        for(int k=0; k<MAX_CUST; k++){
            for(int j=0; j<MAX_BILLS_PER_DAY; j++){    
                if(!(strcmp(b[i].d[j].p.name,p[k].name))){
                    total[k] += b[i].d[j].amt;
                }
            }
        }
    }
    for(int x=0; x<MAX_CUST; x++){
        printf("%d.\t%s\t\tRs.%.2f\n", x+1, p[x].name, total[x]);
    }
}

void disp_data_all_items(const struct bill* b, int days, struct item* item){

}


void disp_data_by_date(const struct bill* b, int days, struct date cur_date){
    int i=0;
    int hr1, hr2;
    char p1[3], p2[3];
    int time[MAX_INTERVALS] = {8, 9, 10, 11, 12, 16, 17, 18, 19, 20, 21};
    while(i<days){
        if(b[i].dt.dd == cur_date.dd && b[i].dt.mm == cur_date.mm && b[i].dt.yy == cur_date.yy){
            if(b[i].day == 2){
                printf("HOLIDAY\n");
            }
            else{
                for(int j=0; j<b[i].limit; j++){
                    hr1 = time[b[i].d[j].interval];
                    hr2 = time[b[i].d[j].interval]+1;
                    set_period(&hr1, p1, &hr2, p2);
                    printf("%d.\t%d:00%s-%d:00%s\t\t%s\t\tRs.%.2f\n",
                            j+1, hr1, p1, hr2, p2, b[i].d[j].p.name, b[i].d[j].amt);
                }
                printf("Total amount: Rs.%.2f\n", b[i].total_amt);
            }    
            break;
        }
        ++i;
    }
    if(i == days){
        printf("Date out of range!!!\n");
    }

}
void disp_data_by_person(const struct bill* b, int days, char* cur_name){
    double total = 0;
    int found = 0;
    for(int i=0; i<days; i++){
        for(int j=0; j<MAX_BILLS_PER_DAY; j++){ 
            if(!(strcmp(b[i].d[j].p.name,cur_name))){
                total += b[i].d[j].amt;
                found = 1;
            }
        }
    }
    if(!found){
        printf("\n%s has no billing data\n", cur_name);
    }
    else{
        printf("\nName: %s\nTotal Amount: Rs.%.2f\n", cur_name, total);
    }
}

void disp_data_all_days(const struct bill* b, int days){
    double total[7] = {0};
    char day_name[7][10] = {"Monday  ", "Tuesday  ", "Wednesday", "Thursday",
                            "Friday  ", "Saturday", "Sunday  "};
    printf("DAY\t\tTOTAL AMOUNT\n");
    for(int i=0; i<days; i++){
        total[b[i].day-1] += b[i].total_amt;
    }
    for(int x=0; x<7; x++){
        if(total[x] == 0)
            printf("%s\tNo sales\n", day_name[x]);
        else
            printf("%s\tRs.%.2f\n",day_name[x], total[x]);
    }
}

void disp_data_all_hours(const struct bill* b, int days){
    double total[MAX_INTERVALS] = {0};
    int hr1, hr2;
    char p1[3], p2[3];
    int time[MAX_INTERVALS] = {8, 9, 10, 11, 12, 16, 17, 18, 19, 20, 21};
    for(int i=0; i<days; i++){
        if(b[i].day != 2){
            for(int j=0; j<b[i].limit; j++){
                total[b[i].d[j].interval] += b[i].d[j].amt;
            }
        }
    }
    printf("TIME INTERVAL\t\tTOTAL AMOUNT\n");
    for(int x=0; x<MAX_INTERVALS; x++){
        hr1 = time[x];
        hr2 = time[x]+1;
        set_period(&hr1, p1, &hr2, p2);
        printf("%d:00%s-%d:00%s\t\tRs.%.2f\n",hr1,p1,hr2,p2, total[x]);
    }
}