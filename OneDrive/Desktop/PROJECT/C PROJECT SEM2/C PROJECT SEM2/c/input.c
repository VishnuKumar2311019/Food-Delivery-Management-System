#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10 // Maximum number of each food item

struct distance {
    float latitude;
    float longitude;
};

struct starters {
    char str_name[50];
    int price;
};

struct main_c {
    char main_name[50];
    int price;
};

struct desert {
    char desert_name[50];
    int price;
};

struct beverage {
    char bvg_name[50];
    int price;
};

struct food {
    struct starters stt[MAX_ITEMS];
    int num_starters;
    struct main_c mn[MAX_ITEMS];
    int num_main_courses;
    struct desert dt[MAX_ITEMS];
    int num_deserts;
    struct beverage bvg[MAX_ITEMS];
    int num_beverages;
};

struct hotel {
    char hotel_name[100];
    struct distance dist;
    float rating;
    struct food fd;
    int discount;
    char v_n[20];
};

int main() {
    FILE *file;
    struct hotel var1;
    int num_hotels, i, j;

    printf("Enter the number of hotels: ");
    scanf("%d", &num_hotels);

    
    file = fopen("var1.dat", "ab");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (i = 0; i < num_hotels; i++) {
        printf("\nEnter details for Hotel %d:\n", i + 1);

        printf("Hotel Name: ");
        scanf(" %[^\n]s", var1.hotel_name);

        printf("Latitude: ");
        scanf("%f", &var1.dist.latitude);

        printf("Longitude: ");
        scanf("%f", &var1.dist.longitude);

        printf("Rating: ");
        scanf("%f", &var1.rating);

        printf("Discount (%%): ");
        scanf("%d", &var1.discount);

        printf("Veg/Non-Veg (Veg/Non-Veg): ");
        scanf(" %[^\n]s", var1.v_n);

        printf("Number of Starters: ");
        scanf("%d", &var1.fd.num_starters);

        for (j = 0; j < var1.fd.num_starters; j++) {
            printf("Starter %d Name: ", j + 1);
            scanf(" %[^\n]s", var1.fd.stt[j].str_name);

            printf("Starter %d Price: ", j + 1);
            scanf("%d", &var1.fd.stt[j].price);
        }

        printf("Number of Main Courses: ");
        scanf("%d", &var1.fd.num_main_courses);

        for (j = 0; j < var1.fd.num_main_courses; j++) {
            printf("Main Course %d Name: ", j + 1);
            scanf(" %[^\n]s", var1.fd.mn[j].main_name);

            printf("Main Course %d Price: ", j + 1);
            scanf("%d", &var1.fd.mn[j].price);
        }

        printf("Number of Deserts: ");
        scanf("%d", &var1.fd.num_deserts);

        for (j = 0; j < var1.fd.num_deserts; j++) {
            printf("Desert %d Name: ", j + 1);
            scanf(" %[^\n]s", var1.fd.dt[j].desert_name);

            printf("Desert %d Price: ", j + 1);
            scanf("%d", &var1.fd.dt[j].price);
        }

        printf("Number of Beverages: ");
        scanf("%d", &var1.fd.num_beverages);

        for (j = 0; j < var1.fd.num_beverages; j++) {
            printf("Beverage %d Name: ", j + 1);
            scanf(" %[^\n]s", var1.fd.bvg[j].bvg_name);

            printf("Beverage %d Price: ", j + 1);
            scanf("%d", &var1.fd.bvg[j].price);
        }

        fwrite(&var1, sizeof(struct hotel), 1, file);
    }

    
    fclose(file);

    printf("\nHotel details written to var1.dat successfully.\n");

    return 0;
}