#ifndef ITEM_H
#define ITEM_H
#define MAX_ITEM 50

struct item{
    char item_name[30];
    double price;
    int initial_quantity;
    int quantity_sold;
};

void read_item_data(FILE* fp, struct item* item);
void disp_data_all_items(const struct item* item);

#endif