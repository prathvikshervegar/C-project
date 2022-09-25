#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

void read_item_data(FILE* fp, struct item* item){ 
    if(fp == NULL){
        printf("Error!!");
        exit(1);
    }
    char line[1024];
    char *token;
    int i = 0;
    fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        token = strtok(line, ",");
        strcpy(item[i].item_name, token);
        token = strtok(NULL, ",");
        item[i].price = atof(token);
        token = strtok(NULL, ",");
        item[i].initial_quantity = atoi(token);
        item[i].quantity_sold = 0;
        ++i;
    }
    fclose(fp);
}

void disp_data_all_items(const struct item* item){
    printf("\nBill details of all items\n");
    printf("\tITEM NAME\t\tRATE\t\tAVAILABLE QUANTITY\tQUANTITY SOLD\t\tSALES AMOUNT\n");
    for(int i=0; i<MAX_ITEM; i++){
        printf("%d.\t%-20sRs.%9.2f\t\t%3d\t\t%3d\t\t\tRs.%10.2f\n", i+1, item[i].item_name, item[i].price,
                item[i].initial_quantity - item[i].quantity_sold ,item[i].quantity_sold, 
                item[i].quantity_sold * item[i].price);
    }
}