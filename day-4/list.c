#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"


void read_cust_data(FILE* fp, struct person* p){
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    int i=0;
    while(i<MAX_CUST && !feof(fp)){
        fgets(p[i].name, 29, fp);
        p[i].name[strcspn(p[i].name, "\n")] = 0;
        p[i].total_per_person = 0;
        ++i;
    }
    fclose(fp);
}

void read_item_data(FILE* fp, struct item* item){ 
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    char line[1024];
    char *token;
    int i = 0;
    fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        token = strtok(line, ",");
        strcpy(item[i].item_name, token);
        token = strtok(NULL, ",");
        item[i].price = atof(token);
        token = strtok(NULL, ",");
        item[i].initial_quantity = atoi(token);
        item[i].quantity_sold = 0;
        ++i;
    }
    fclose(fp);
}

int is_valid_date(const struct date* cur_date){
    int month[MAX_MONTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((cur_date->yy%4 ==0 && cur_date->yy%100 != 0) || (cur_date->yy%400 == 0)){
        month[1]=29;
    }
    if(cur_date->dd < 1 || cur_date->dd > month[cur_date->mm-1])
        return 0;
    if(cur_date->mm < 1 || cur_date->mm > MAX_MONTH)
        return 0;
    if(cur_date->yy < MIN_YEAR || cur_date->yy > MAX_YEAR)
        return 0;
    return 1;
}

int is_valid_day(int day){
    if(day<1 || day >7){
        return 0;
    }
    return 1;
}

int is_valid_range(const struct date* start_date, const struct date* end_date){
    if(start_date->yy > end_date->yy)
        return 0;
    if(start_date->yy == end_date->yy && start_date->mm > end_date->mm)
        return 0;
    if(start_date->yy == end_date->yy && start_date->mm == end_date->mm && start_date->dd > end_date->dd)
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
    for(int i=start_date->mm; i<end_date->mm-1; i++){
        res = res + month[i];
    }
    res = res + end_date->dd;
    return res;
}

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
    int hr1, hr2;
    char p1[3], p2[3];
    int bill_no = 0;
    for(int i=0; i<days; i++){
        printf("\nBill details of %d-%d-%d\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        if(b[i].day != 2){
            for(int j=0; j<b[i].limit; j++){
                hr1 = b[i].d[j].hr;
                hr2 = b[i].d[j].hr+1;
                set_period(&hr1, p1, &hr2, p2);
                ++bill_no;
                printf("\nBILL NO.: B-%05d\nTIME INTERVAL: %d:00%s-%d:00%s\n"
                        "NAME: %s\nITEMS:\n",
                        bill_no, hr1, p1, hr2, p2, b[i].d[j].p.name);
                printf("\tSL NO.\tITEM NAME\t\tAMOUNT\n");
                for(int k=0; k<b[i].d[j].no_of_items; k++){
                    printf("\t%d.\t%s\t\tRs.%.2f\n", k+1, b[i].d[j].item[k].item_name, 
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
    int bill_no = 0;
    for(int i=0; i<days; i++){
        printf("\nBill details of %d-%d-%d\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        if(b[i].day != 2){
            printf("BILL NO.\tTIME\t\t\tNAME\t\t\tAMOUNT\n");
            for(int j=0; j<b[i].limit; j++){ 
                ++bill_no;
                if(b[i].d[j].min < 10){
                    printf("B-%05d\t\t%d:%02d\t\t%s\t\tRs.%.2f\n",
                        bill_no, b[i].d[j].hr, b[i].d[j].min, b[i].d[j].p.name, b[i].d[j].amt);
                }
                else{
                    printf("B-%05d\t\t%d:%d\t\t%s\t\tRs.%.2f\n",
                        bill_no, b[i].d[j].hr, b[i].d[j].min, b[i].d[j].p.name, b[i].d[j].amt);
                }
            }
            printf("TOTAL OF THE DAY: Rs.%.2f\n", b[i].total_per_day);
        }
        else{
            printf("HOLIDAY\n");
        }
    }
}


void disp_data_all_persons(const struct person* p){
    printf("\nBill details of all persons\n");
    printf("\tNAME\t\t\tTOTAL AMOUNT\n");
    for(int i=0; i<MAX_CUST; i++){
        printf("%d.\t%s\t\tRs.%.2f\n", i+1, p[i].name, p[i].total_per_person);
    }
}

void disp_data_all_items(const struct item* item){
    printf("\nBill details of all items\n");
    printf("  ITEM NAME\t\tRATE\t\tAVAILABLE QUANTITY\t\tQUANTITY SOLD\t\tSALES AMOUNT\t\t\n");
    for(int i=0; i<MAX_ITEM; i++){
        printf("%d. %s\tRs.%.2f\t\t%d\t\t\t%d\t\tRs.%.2f\n", i+1, item[i].item_name, item[i].price,
                item[i].initial_quantity - item[i].quantity_sold ,item[i].quantity_sold, 
                item[i].quantity_sold * item[i].price);
    }
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
                    hr1 = b[i].d[j].hr;
                    hr2 = b[i].d[j].hr+1;
                    set_period(&hr1, p1, &hr2, p2);
                    printf("%d.\t%d:00%s-%d:00%s\t\t%s\t\tRs.%.2f\n",
                            j+1, hr1, p1, hr2, p2, b[i].d[j].p.name, b[i].d[j].amt);
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
    char day_name[7][10] = {"Monday  ", "Tuesday  ", "Wednesday", "Thursday",
                            "Friday  ", "Saturday", "Sunday  "};
    printf("DAY\t\tTOTAL AMOUNT\n");
    for(int i=0; i<days; i++){
        total[b[i].day-1] += b[i].total_per_day;
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
                for(int k=0; k<MAX_INTERVALS; k++){
                    if(b[i].d[j].hr == time[k]){
                        total[k] += b[i].d[j].amt;
                    }
                }
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

void disp_data_by_dates_and_items(const struct bill* b, int start, int end, const struct item* item){
    for(int i=start; i<=end; i++){
        int quantity[50] = {0};
        printf("\nBill details of %d-%d-%d\n\n", b[i].dt.dd, b[i].dt.mm, b[i].dt.yy);
        printf("\tITEM NAME\tQUANTITY\tTOTAL AMOUNT\n");
        if(b[i].day != 2){
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
                printf("%d.\t%s\t\t%d\t\t%.2f\n", m+1, item[m].item_name, quantity[m], quantity[m] * item[m].price);
            }
            printf("\nTOTAL OF THE DAY: Rs.%.2f\n\n", b[i].total_per_day);
        }
        else{
            printf("HOLIDAY\n");
        }
    }
}

static void next_date(struct date* bill_date){
    int month[MAX_MONTH] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((bill_date->yy%4 ==0 && bill_date->yy%100 != 0) || (bill_date->yy%400 == 0) ){
        month[1]=29;
    }
    if(bill_date->dd == month[bill_date->mm-1]){
        if(bill_date->mm == MAX_MONTH){
            bill_date->mm = 1;
            ++bill_date->yy;
        }
        else
            ++bill_date->mm;
        bill_date->dd = 1;
    }
    else{
        ++bill_date->dd;
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
                //for(int k=0; k<b[i].d[j].no_of_items; k++){
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

