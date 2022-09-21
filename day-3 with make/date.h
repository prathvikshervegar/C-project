#ifndef DATE_H
#define DATE_H
#define MAX_MONTH 12
#define MIN_YEAR 1600
#define MAX_YEAR 2999

struct date{
    int dd;
    int mm;
    int yy;
};


int is_valid_date(const struct date* cur_date);
int is_valid_day(int day);
int is_valid_range(const struct date* start_date, const struct date* end_date);
int date_diff(const struct date* start_date,const  struct date* end_date);

#endif