#ifndef BILL_GENERATE_H
#define BILL_GENERATE_H
#define MIN_BILLS_PER_DAY 20
#define MAX_BILLS_PER_DAY 40
#define MIN_BILL_AMT 100
#define MAX_BILL_AMT 5000
#define MAX_INTERVALS 11
#define MAX_TRANSACTION 5

struct details{
    struct person p;
    double amt;
    int hr;
    int min;
    int no_of_items;
    struct item item[MAX_TRANSACTION];
};

struct bill{    
    struct details d[MAX_BILLS_PER_DAY];
    int limit;
    struct date dt;
    double total_per_day;
    int day;
};

void generate_bill(struct bill* b, const struct date* start_date, int bill_day, int days, struct person* p, struct item* item);

void disp_data_all_dates(const struct bill* b, int days);
void disp_data_all_days(const struct bill* b, int days);
void disp_data_all_hours(const struct bill* b, int days);

void disp_data_by_date(const struct bill* b, int days, struct date cur_date);
void disp_data_by_person(const struct bill* b, int days, char* cur_name);

void disp_detailed_bill(const struct bill* b, int days);
void disp_data_by_dates_and_items(const struct bill* b, int start, int end, const struct item* item);

#endif