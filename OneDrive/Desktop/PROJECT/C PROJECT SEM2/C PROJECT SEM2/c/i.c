#include <stdio.h>
#include <string.h>

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
    struct starters stt;
    struct main_c mn;
    struct desert dt;
    struct beverage bvg;
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
    struct hotel var1;
    FILE *file;

    // Open the file in binary read mode
    file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read and print all structures from the file
    while (fread(&var1, sizeof(struct hotel), 1, file) == 1) {
        printf("Hotel Name: %s\n", var1.hotel_name);
        printf("Latitude: %.2f\n", var1.dist.latitude);
        printf("Longitude: %.2f\n", var1.dist.longitude);
        printf("Rating: %.2f\n", var1.rating);
        printf("Discount: %d\n", var1.discount);
        printf("Veg/Non-Veg: %s\n", var1.v_n);

        printf("\nStarter:\n");
        printf("Name: %s\n", var1.fd.stt.str_name);
        printf("Price: %d\n", var1.fd.stt.price);

        printf("\nMain Course:\n");
        printf("Name: %s\n", var1.fd.mn.main_name);
        printf("Price: %d\n", var1.fd.mn.price);

        printf("\nDesert:\n");
        printf("Name: %s\n", var1.fd.dt.desert_name);
        printf("Price: %d\n", var1.fd.dt.price);

        printf("\nBeverage:\n");
        printf("Name: %s\n", var1.fd.bvg.bvg_name);
        printf("Price: %d\n", var1.fd.bvg.price);

        printf("\n---------------------\n");
    }

    // Close the file
    fclose(file);

    return 0;
}
