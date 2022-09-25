#include <stdio.h>
#include "date.h"

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