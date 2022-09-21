#ifndef LIST_H
#define LIST_H
#define MAX_CUST 50
#define MAX_ITEM 50
#define MAX_MONTH 12
#define MIN_YEAR 1600
#define MAX_YEAR 2999
#define MIN_BILLS_PER_DAY 20
#define MAX_BILLS_PER_DAY 40
#define MIN_BILL_AMT 100
#define MAX_BILL_AMT 5000
#define MAX_INTERVALS 11


struct date{
    int dd;
    int mm;
    int yy;
};

struct person{
    char name[30];
};

struct item{
    char item_name[30];
    double price;
    int quantity;
};

struct details{
    struct person p;
    double amt;
    int interval;
    struct item item[5];
};


struct bill{    
    struct details d[MAX_BILLS_PER_DAY];
    int limit;
    struct date dt;
    double total_amt;
    int day;
};

void read_cust_data(FILE* fp, struct person* p);
void read_item_data(FILE* fp, struct item* item);

int is_valid_date(const struct date* cur_date);
int is_valid_range(const struct date* start_date, const struct date* end_date);
int date_diff(const struct date* start_date,const  struct date* end_date);
void generate_bill(struct bill* b, const struct date* start_date, int bill_day, int days, struct person* p, struct item* item);
void disp_data_all_dates(const struct bill* b, int days);
void disp_data_all_persons(const struct bill* b, int days, struct person* p);
void disp_data_by_date(const struct bill* b, int days, struct date cur_date);
void disp_data_by_person(const struct bill* b, int days, char* cur_name);

void disp_data_all_days(const struct bill* b, int days);
void disp_data_all_hours(const struct bill* b, int days);

void disp_data_all_items(const struct bill* b, int days, struct item* item);

#endif