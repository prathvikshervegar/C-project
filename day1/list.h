#ifndef LIST_H
#define LIST_H

struct date{
    int dd;
    int mm;
    int yy;
};

struct person{
    char name[50];
};

struct details{
    char name[50];
    double amt;
};

struct bill{    
    struct details d[40];
};

void read_cust_data(FILE* fp);
void generate_bill(const struct date* start_date, const struct date* end_date);

#endif