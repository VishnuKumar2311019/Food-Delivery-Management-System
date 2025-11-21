#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100

struct starter {
    char str_name[50];
    int price;
};

struct main_course {
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

struct food_items {
    struct starter stt[MAX_ITEMS];
    int num_starters;
    struct main_course mn[MAX_ITEMS];
    int num_main_courses;
    struct desert dt[MAX_ITEMS];
    int num_deserts;
    struct beverage bvg[MAX_ITEMS];
    int num_beverages;
};

struct hotel {
    char hotel_name[50];
    char v_n[20]; // veg or non-veg
    float rating;
    int discount;
    struct food_items fd;
};

void show_hotels_by_preference() {
    struct hotel var1;
    FILE *file;
    char preference[20];

    printf("Enter your preference (veg/non-veg):\n");
    fgets(preference, sizeof(preference), stdin);
    preference[strcspn(preference, "\n")] = '\0';

    // Open the file in binary read mode
    file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Hotels with %s preference:\n", preference);
    while (fread(&var1, sizeof(struct hotel), 1, file)) {
        if (strcmp(var1.v_n, preference) == 0) {
            printf("\nHotel Name: %s\n", var1.hotel_name);
            printf("Rating: %.2f\n", var1.rating);
            printf("Discount: %d%%\n", var1.discount);
            printf("Food Items:\n");
            for (int i = 0; i < var1.fd.num_starters; i++) {
                printf("  Starter: %s, Price: %d\n", var1.fd.stt[i].str_name, var1.fd.stt[i].price);
            }
            for (int i = 0; i < var1.fd.num_main_courses; i++) {
                printf("  Main Course: %s, Price: %d\n", var1.fd.mn[i].main_name, var1.fd.mn[i].price);
            }
            for (int i = 0; i < var1.fd.num_deserts; i++) {
                printf("  Desert: %s, Price: %d\n", var1.fd.dt[i].desert_name, var1.fd.dt[i].price);
            }
            for (int i = 0; i < var1.fd.num_beverages; i++) {
                printf("  Beverage: %s, Price: %d\n", var1.fd.bvg[i].bvg_name, var1.fd.bvg[i].price);
            }
        }
    }

    // Close the file
    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("Enter 2 to view hotels by veg/non-veg preference\n");
        printf("Enter 3 to exit\n");
        scanf("%d", &choice);

        // Handle trailing newline character left by scanf
        while ((getchar()) != '\n');

        if (choice == 2) {
            show_hotels_by_preference();
        } else if (choice == 3) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}






