#ifndef BILL_GENERATE_H
#include "read.h"
#include "date.h"
#define BILL_GENERATE_H
#define MIN_BILLS_PER_DAY 20
#define MAX_BILLS_PER_DAY 40
#define MIN_BILL_AMT 100
#define MAX_BILL_AMT 5000
#define MAX_INTERVALS 11

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

void generate_bill(struct bill* b, const struct date* start_date, int bill_day, 
                    int days, struct person* p, struct item* item);

#endif