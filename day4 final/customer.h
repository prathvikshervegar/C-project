#ifndef CUSTOMER_H
#define CUSTOMER_H
#define MAX_CUST 50

struct person{
    char name[30];
    double total_per_person;
};

void read_cust_data(FILE* fp, struct person* p);
void disp_data_all_persons(const struct person* p);

#endif