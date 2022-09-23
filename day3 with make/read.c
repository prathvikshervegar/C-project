#include <stdio.h>
#include "read.h"
#include "date.h"

void read_cust_data(FILE* fp, struct person* p){
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    int i=0;
    while(fgets(p[i].name, sizeof(p[i].name), fp) != NULL){
        p[i].name[strcspn(p[i].name, "\n")] = 0;
        //printf("%d %s\n", i+1, p[i].name);
        ++i;
    }
    fclose(fp);
}

void read_item_data(FILE* fp, struct item* item){ 
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    char line[1024];
    char *token;
    int i = 0;
    fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line), fp) != NULL){
        token = strtok(line, ",");
        strcpy(item[i].item_name, token);
        token = strtok(NULL, ",");
        item[i].price = atof(token);
        ++i;
    }

    //for(int j=0; j<MAX_ITEM; j++){
    //    printf("%d.\t%s\t\t%.2f\n", j+1, item[j].item_name, item[j].price);
    //}
    fclose(fp);
}

void read_dates(int* start_day, struct date* start_date, struct date* end_date){
    printf("Enter billing start day(Mon-1/Tue-2/Wed-3/Thur-4/Fri-5/Sat-6/Sun-7): ");
    scanf("%d", start_day);
    if(! is_valid_day(*start_day)){
        printf("Invalid day provided!!!\n");
        exit(1);
    }
    printf("Enter billing start date(dd mm yyyy): ");
    scanf("%d %d %d", &start_date->dd, &start_date->mm, &start_date->yy);
    if(! is_valid_date(&start_date)){
        printf("Invalid date provided!!!\n");
        exit(1);
    }
    printf("Enter billing end date(dd mm yyyy): ");
    scanf("%d %d %d", &end_date->dd, &end_date->mm, &end_date->yy);
    if(! is_valid_date(&end_date)){
        printf("Invalid date provided!!!\n");
        exit(1);
    }
}