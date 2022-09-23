#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bill_generate.h"
#include "date.h"
#include "read.h"

static int get_random_val(int min, int max, int day){
    if(day == 6 || day == 7)
        min = 35;
    else
        max = 35;
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

static void sort_By_interval(struct bill* b, int day)
{
    for(int i=0;i<b[day].limit-1;++i)
    {
        for(int j=i+1;j<b[day].limit;++j)
        {
            if(b[day].d[i].interval>b[day].d[j].interval)
            {
                struct details temp=b[day].d[i];
                b[day].d[i]=b[day].d[j];
                b[day].d[j]=temp;
            }
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

void generate_bill(struct bill* b, const struct date* start_date, int bill_day, 
                    int days, struct person* p, struct item* item){
    struct date bill_date = *start_date;
    for(int i=0; i<days; i++){
        b[i].dt = bill_date;
        b[i].day = bill_day;
        b[i].total_amt = 0;
        if(bill_day != 2){
            b[i].limit = get_random_val(MIN_BILLS_PER_DAY, MAX_BILLS_PER_DAY, bill_day);
            int temp[b[i].limit];
            generate_array_of_unique_indices(temp, b[i].limit);
            for(int j=0; j<b[i].limit; j++){
                //temp[j] = rand()%limit;
                b[i].d[j].interval = rand()%MAX_INTERVALS;
                strcpy(b[i].d[j].p.name, p[temp[j]].name);
                b[i].d[j].amt = (MIN_BILL_AMT+ rand()%(MAX_BILL_AMT-MIN_BILL_AMT)) 
                                + (double)rand()/100;
                b[i].total_amt += b[i].d[j].amt;
            }
            sort_By_interval(b, i);
        }
        next_date(&bill_date);
        if(bill_day == 7)
            bill_day = 1;
        else
            ++bill_day;
    }
}

