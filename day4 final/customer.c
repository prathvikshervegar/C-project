#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

void read_cust_data(FILE* fp, struct person* p){
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    int i=0;
    while(i<MAX_CUST && !feof(fp)){
        fgets(p[i].name, 29, fp);
        p[i].name[strcspn(p[i].name, "\n")] = 0;
        p[i].total_per_person = 0;
        ++i;
    }
    fclose(fp);
}

void disp_data_all_persons(const struct person* p){
    printf("\nBill details of all persons\n");
    printf("\tNAME\t\t\tTOTAL AMOUNT\n");
    for(int i=0; i<MAX_CUST; i++){
        printf("%d.\t%s\t\tRs.%.2f\n", i+1, p[i].name, p[i].total_per_person);
    }
}