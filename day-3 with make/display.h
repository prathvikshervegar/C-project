#ifndef DISPLAY_H
#define DISPLAY_H

void display_by_choices();

void disp_data_all_dates(const struct bill* b, int days);
void disp_data_all_persons(const struct bill* b, int days, struct person* p);
void disp_data_by_date(const struct bill* b, int days, struct date cur_date);
void disp_data_by_person(const struct bill* b, int days, char* cur_name);

void disp_data_all_days(const struct bill* b, int days);
void disp_data_all_hours(const struct bill* b, int days);

void disp_data_all_items(const struct bill* b, int days, struct item* item);

#endif