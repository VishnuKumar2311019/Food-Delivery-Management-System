#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct menu{
    char id[10];
    char type[50];
    char name[100];
    float price;
    float rating;
    int calories;
    int veg;
    int n;
    int priority;
}item;

typedef struct item_associativity{
    char id[10];
    int asoc;
}item_asoc;


void AssocSort(item_asoc all_items[],int size){
    for (int i=0;i<size-1;i++){
        for (int j=0;j<size-i-1;j++){
            if (all_items[j].asoc<all_items[j+1].asoc){
                item_asoc temp=all_items[j];
                all_items[j]=all_items[j+1];
                all_items[j+1]=temp;
            }
        }
    }
}

int InArray(char foodid[10], char arr[50][10], int size) {
    for (int i = 0; i < size; i++) {
        if (strncmp(foodid,arr[i],strlen(foodid))==0) {
            return 1;
        }
    }
    return 0;
}

int NotInArray(char foodid[], char arr[][], int size) {
    for (int i = 0; i < size; i++) {
        if (strncmp(foodid,arr[i],strlen(foodid))==0) {
            return 0;
        }
    }
    return 1;
}

item FindItem(item items[25],int count,char id[10]){
    for (int i=0;i<count;i++){
        if (strcmp(items[i].id,id)==0){
            return items[i];
        }
    }
}




void main(){
    char menu_id[50];
    item items[25];

    printf("Enter menu id:");
    scanf("%s",menu_id);

    FILE *fptr;
    fptr=fopen(menu_id,"r");

    if (fptr==NULL){
        printf("File cannot be opened");
    }

    int count=0;
    fseek(fptr, 81, SEEK_SET);

    while(!feof(fptr)){

    fscanf(fptr,"%5[^,],%50[^,],%100[^,],%f,%f,%d,%d,%d,%d\n",
           items[count].id, items[count].type,
           items[count].name, &items[count].price,
           &items[count].rating, &items[count].calories,
           &items[count].veg, &items[count].n,
           &items[count].priority);
    count++;
    }

    fclose(fptr);

    int i=0;

    item recommendtions[10];
    item_asoc all_item_assoc[50];


    for (i=0;i<count;i++){
        strcpy(all_item_assoc[i].id,items[i].id);
        all_item_assoc[i].asoc=0;
        printf("%s  %d\n",all_item_assoc[i].id,all_item_assoc[i].asoc);
    }

    int num_selected=0;

    printf("Enter number of selected items: ");
    scanf("%d",&num_selected);

    char food_id[10];
    char selected_items[50][10];

    for (i=0;i<num_selected;i++){
        printf("Enter food id: ");
        scanf("%s",food_id);
        strcpy(selected_items[i],food_id);
    }

    FILE *file= fopen("Book1.csv","r");
    char line[1000];


    while(fgets(line,sizeof(line),file)){
        char *rest_id;
        char *rest_cuisine;
        char *cust_id;
        char *ordered_item;
        char *food_id;
        char prev_foods[50][10];
        int prev_food_index=0;
        int asoc_points=10;

        rest_id=strtok(line,",");
        rest_cuisine=strtok(NULL,",");
        cust_id=strtok(NULL,",");

        while ((food_id=strtok(NULL,",\n"))!=NULL){
            strcpy(prev_foods[prev_food_index],food_id);
            prev_food_index++;
        }

        for (i=0;i<num_selected;i++){
            if (InArray(selected_items[i],prev_foods,prev_food_index)){
                for (int j=0;j<prev_food_index;j++){
                    for (int k=0;k<count;k++){
                        if (strcmp(all_item_assoc[k].id,prev_foods[j])==0){
                            all_item_assoc[k].asoc+=asoc_points;
                        }
                    }
                }
            }
        }

    }
    AssocSort(all_item_assoc,count);
    int rec=0;


    for (int k=0;k<20;k++){
            if (InArray(all_item_assoc[k].id,selected_items,num_selected)){
                printf("%s     Chosen\n",all_item_assoc[k].id);
            }
            else{
                printf("%s    %d\n",all_item_assoc[k].id,all_item_assoc[k].asoc);
                rec++;
            }

            if (rec==6){
                break;
            }

    }

    fclose(file);

}

