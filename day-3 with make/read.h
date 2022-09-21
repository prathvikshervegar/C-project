#ifndef READ_H
#define READ_H
#define MAX_CUST 50
#define MAX_ITEM 50

struct person{
    char name[30];
};

struct item{
    char item_name[30];
    double price;
    int quantity;
};

void read_cust_data(FILE* fp, struct person* p);
void read_item_data(FILE* fp, struct item* item);
void read_dates(int* start_day, struct date* start_date, struct date* end_date);

#endif