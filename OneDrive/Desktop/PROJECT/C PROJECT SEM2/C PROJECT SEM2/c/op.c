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

void print_hotel_details(struct hotel var1) {
    printf("Hotel Name: %s\n", var1.hotel_name);
    printf("Latitude: %.2f\n", var1.dist.latitude);
    printf("Longitude: %.2f\n", var1.dist.longitude);
    printf("Rating: %.2f\n", var1.rating);
    printf("Discount: %d\n", var1.discount);
    printf("Veg/Non-Veg: %s\n", var1.v_n);

    printf("\nStarters:\n");
    for (int i = 0; i < var1.fd.num_starters; i++) {
        printf("Name: %s, Price: %d\n", var1.fd.stt[i].str_name, var1.fd.stt[i].price);
    }

    printf("\nMain Course:\n");
    for (int i = 0; i < var1.fd.num_main_courses; i++) {
        printf("Name: %s, Price: %d\n", var1.fd.mn[i].main_name, var1.fd.mn[i].price);
    }

    printf("\nDesert:\n");
    for (int i = 0; i < var1.fd.num_deserts; i++) {
        printf("Name: %s, Price: %d\n", var1.fd.dt[i].desert_name, var1.fd.dt[i].price);
    }

    printf("\nBeverage:\n");
    for (int i = 0; i < var1.fd.num_beverages; i++) {
        printf("Name: %s, Price: %d\n", var1.fd.bvg[i].bvg_name, var1.fd.bvg[i].price);
    }
}

int main() {
    FILE *file;
    struct hotel var1;

    // Open the file in binary read mode
    file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read and print hotel details until end of file
    while (fread(&var1, sizeof(struct hotel), 1, file)) {
        print_hotel_details(var1);
        printf("\n----------------------------------------\n");
    }

    // Close the file
    fclose(file);

    return 0;
}
