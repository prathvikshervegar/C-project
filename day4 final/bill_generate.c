#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "customer.h"
#include "item.h"
#include "date.h"
#include "bill_generate.h"


static int get_random_val(int min, int max, int day){
    if(day == 6 || day == 7)
        min = MAX_BILLS_PER_DAY - 5;
    else
        max = MAX_BILLS_PER_DAY - 5;
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

void disp_detailed_bill(const struct bill* b, int days){
    for(int i=0; i<days; i++){
        printf("\nBill details of %d-%d-%d\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        if(b[i].day != 2){
            for(int j=0; j<b[i].limit; j++){
                printf("\nBILL NO.: B-%06d\nTIME: %d:%02d\n"
                        "NAME: %s\nITEMS:\n",
                        b[i].d[j].bill_no, b[i].d[j].hr, b[i].d[j].min, b[i].d[j].p.name);
                printf("\tSL NO.\tITEM NAME\t\tAMOUNT\n");
                for(int k=0; k<b[i].d[j].no_of_items; k++){
                    printf("\t%d.\t%-20sRs.%9.2f\n", k+1, b[i].d[j].item[k].item_name, 
                            b[i].d[j].item[k].price);
                }
                printf("TOTAL AMOUNT: Rs.%.2f\n", b[i].d[j].amt);
            }
            printf("\nTOTAL OF THE DAY: Rs.%.2f\n\n", b[i].total_per_day);
        }
        else{
            printf("HOLIDAY\n\n");
        }
    }
}

void disp_data_all_dates(const struct bill* b, int days){
    for(int i=0; i<days; i++){
        printf("\nBill details of %d-%d-%d\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        if(b[i].day != 2){
            printf("BILL NO.\tTIME\t\tNAME\t\t\tAMOUNT\n");
            for(int j=0; j<b[i].limit; j++){
                printf("B-%06d\t%02d:%02d\t\t%-24sRs.%10.2f\n",
                       b[i].d[j].bill_no, b[i].d[j].hr, b[i].d[j].min, b[i].d[j].p.name, b[i].d[j].amt);
            }
            printf("TOTAL OF THE DAY: Rs.%.2f\n", b[i].total_per_day);
        }
        else{
            printf("HOLIDAY\n");
        }
    }
}

void disp_data_by_date(const struct bill* b, int days, struct date cur_date){
    int i = 0;
    //int bill_no = 0;
    while(i<days){
        if(b[i].dt.dd == cur_date.dd && b[i].dt.mm == cur_date.mm && b[i].dt.yy == cur_date.yy){
            printf("\nBill details of %d-%d-%d\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
            if(b[i].day == 2){
                printf("HOLIDAY\n");
            }
            else{
                printf("BILL NO.\tTIME\t\tNAME\t\t\tAMOUNT\n");
                for(int j=0; j<b[i].limit; j++){
                    printf("B-%06d\t%02d:%02d\t\t%-24sRs.%10.2f\n",
                            b[i].d[j].bill_no, b[i].d[j].hr, b[i].d[j].min, b[i].d[j].p.name, 
                            b[i].d[j].amt);
                }
                printf("Total amount: Rs.%.2f\n", b[i].total_per_day);
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
    char day_name[7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday",
                            "Friday", "Saturday", "Sunday"};
    printf("DAY\t\tTOTAL AMOUNT\n");
    for(int i=0; i<days; i++){
        total[b[i].day-1] += b[i].total_per_day;
    }
    for(int x=0; x<7; x++){
        if(total[x] == 0)
            printf("%-8s\tNo sales\n", day_name[x]);
        else
            printf("%-8s\tRs.%10.2f\n",day_name[x], total[x]);
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
                for(int k=0; k<MAX_INTERVALS; k++){
                    if(b[i].d[j].hr == time[k]){
                        total[k] += b[i].d[j].amt;
                    }
                }
            }
        }
    }
    printf("   TIME INTERVAL\tTOTAL AMOUNT\n");
    for(int x=0; x<MAX_INTERVALS; x++){
        hr1 = time[x];
        hr2 = time[x]+1;
        set_period(&hr1, p1, &hr2, p2);
        printf("%02d:00%s - %02d:00%s\tRs.%10.2f\n",hr1,p1,hr2,p2, total[x]);
    }
}

void disp_data_by_dates_and_items(const struct bill* b, int start, int end, const struct item* item){
    for(int i=start; i<=end; i++){
        int quantity[50] = {0};
        printf("\nBill details of %d-%d-%d\n\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        if(b[i].day != 2){
            printf("\tITEM NAME\tQUANTITY\tTOTAL AMOUNT\n");
            for(int j=0; j<b[i].limit; j++){
                for(int k=0; k<b[i].d[j].no_of_items; k++){
                    for(int l=0; l<MAX_ITEM; l++){
                        if(! strcmp(b[i].d[j].item[k].item_name, item[l].item_name)){
                            ++quantity[l];
                        }
                    }
                }
            }
            for(int m=0; m<MAX_ITEM; m++){
                printf("%d.\t%-20s%d\t\t%10.2f\n", m+1, item[m].item_name, quantity[m], 
                        quantity[m] * item[m].price);
            }
            printf("\nTOTAL OF THE DAY: Rs.%.2f\n\n", b[i].total_per_day);
        }
        else{
            printf("HOLIDAY\n");
        }
    }
}

static void generate_bill_time(int* time){
    int random = 10 + rand()% 13;
    if((time[1] + random) >= 60){
        ++time[0];
        if(time[0] == 13){
            time[0] = 16;
        }
        time[1] += random - 60;
    }
    else{
        time[1] += random;
    }
}

void generate_bill(struct bill* b, const struct date* start_date, int bill_day, 
                    int days, struct person* p, struct item* item){
    struct date bill_date = *start_date;
    int bill_no = 0;
    for(int i=0; i<days; i++){
        b[i].dt = bill_date;
        b[i].day = bill_day;
        b[i].total_per_day = 0;
        if(bill_day != 2){
            b[i].limit = get_random_val(MIN_BILLS_PER_DAY, MAX_BILLS_PER_DAY, bill_day);
            int temp[b[i].limit];
            generate_array_of_unique_indices(temp, b[i].limit);
            int time[2] = {8,0}; // stores values of hours and minutes 
            for(int j=0; j<b[i].limit; j++){
                generate_bill_time(time);
                b[i].d[j].hr = time[0];
                b[i].d[j].min = time[1];
                //b[i].d[j].interval = rand()%MAX_INTERVALS;
                strcpy(b[i].d[j].p.name, p[temp[j]].name);
                // b[i].d[j].amt = (MIN_BILL_AMT+ rand()%(MAX_BILL_AMT-MIN_BILL_AMT)) 
                //                 + (double)rand()/100;
                b[i].d[j].no_of_items = 1 + rand()%5;
                b[i].d[j].amt = 0;
                int select[b[i].d[j].no_of_items];
                generate_array_of_unique_indices(select, b[i].d[j].no_of_items);
                int k = 0;
                while(k < b[i].d[j].no_of_items){
                    int available = item[select[k]].initial_quantity - item[select[k]].quantity_sold;
                    if(available > 0){
                        b[i].d[j].item[k] = item[select[k]];
                        b[i].d[j].amt += b[i].d[j].item[k].price;
                        ++b[i].d[j].item[k].quantity_sold;
                        ++item[select[k]].quantity_sold;
                        ++k;
                    }
                    else{
                        --b[i].d[j].no_of_items;
                    }
                }
                if(b[i].d[j].amt != 0){
                    ++bill_no;
                    b[i].d[j].bill_no = bill_no;
                    p[temp[j]].total_per_person += b[i].d[j].amt;
                    b[i].total_per_day += b[i].d[j].amt;
                }
                else{
                    --j;
                }
            }
        }
        next_date(&bill_date);
        bill_day = bill_day % 7 + 1;
    }
}

