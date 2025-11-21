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
    struct hotel var1;
    int choice;
    FILE *file;

    // Input hotel details
    printf("Enter hotel name:\n ");
    fgets(var1.hotel_name, sizeof(var1.hotel_name), stdin);
    // Remove newline character from the string
    var1.hotel_name[strcspn(var1.hotel_name, "\n")] = '\0';

    printf("Enter latitude:\n ");
    scanf("%f", &var1.dist.latitude);

    printf("Enter longitude:\n ");
    scanf("%f", &var1.dist.longitude);

    printf("Enter hotel rating:\n ");
    scanf("%f", &var1.rating);

    // Handle trailing newline character left by scanf
    while ((getchar()) != '\n');

    // Initialize number of food items
    var1.fd.num_starters = 0;
    var1.fd.num_main_courses = 0;
    var1.fd.num_deserts = 0;
    var1.fd.num_beverages = 0;

    while(1) {
        printf("Enter 1.to add starter\n 2.to add main course\n 3.to add desert \n 4.to add beverages\n 5.To break\n ");
        scanf("%d", &choice);
        
        // Handle trailing newline character left by scanf
        while ((getchar()) != '\n');

        if (choice == 1 && var1.fd.num_starters < 10) {
            printf("Enter starter name:\n ");
            fgets(var1.fd.stt[var1.fd.num_starters].str_name, sizeof(var1.fd.stt[var1.fd.num_starters].str_name), stdin);
            var1.fd.stt[var1.fd.num_starters].str_name[strcspn(var1.fd.stt[var1.fd.num_starters].str_name, "\n")] = '\0';

            printf("Enter starter price:\n ");
            scanf("%d", &var1.fd.stt[var1.fd.num_starters].price);
            while ((getchar()) != '\n'); // Clear the newline character
            
            var1.fd.num_starters++;
        } else if (choice == 2 && var1.fd.num_main_courses < 20) {
            printf("Enter main course name:\n ");
            fgets(var1.fd.mn[var1.fd.num_main_courses].main_name, sizeof(var1.fd.mn[var1.fd.num_main_courses].main_name), stdin);
            var1.fd.mn[var1.fd.num_main_courses].main_name[strcspn(var1.fd.mn[var1.fd.num_main_courses].main_name, "\n")] = '\0';

            printf("Enter main course price:\n ");
            scanf("%d", &var1.fd.mn[var1.fd.num_main_courses].price);
            while ((getchar()) != '\n'); // Clear the newline character
            
            var1.fd.num_main_courses++;
        } else if (choice == 3 && var1.fd.num_deserts < 10) {
            printf("Enter desert name:\n ");
            fgets(var1.fd.dt[var1.fd.num_deserts].desert_name, sizeof(var1.fd.dt[var1.fd.num_deserts].desert_name), stdin);
            var1.fd.dt[var1.fd.num_deserts].desert_name[strcspn(var1.fd.dt[var1.fd.num_deserts].desert_name, "\n")] = '\0';

            printf("Enter desert price:\n ");
            scanf("%d", &var1.fd.dt[var1.fd.num_deserts].price);
            while ((getchar()) != '\n'); // Clear the newline character
            
            var1.fd.num_deserts++;
        } else if (choice == 4 && var1.fd.num_beverages < 10) {
            printf("Enter beverage name:\n ");
            fgets(var1.fd.bvg[var1.fd.num_beverages].bvg_name, sizeof(var1.fd.bvg[var1.fd.num_beverages].bvg_name), stdin);
            var1.fd.bvg[var1.fd.num_beverages].bvg_name[strcspn(var1.fd.bvg[var1.fd.num_beverages].bvg_name, "\n")] = '\0';

            printf("Enter beverage price:\n ");
            scanf("%d", &var1.fd.bvg[var1.fd.num_beverages].price);
            while ((getchar()) != '\n'); // Clear the newline character
            
            var1.fd.num_beverages++;
        } else if (choice == 5) {
            printf("Thank You\n");
            break;
        } else {
            printf("You have reached the maximum limit for this type of item.\n");
        }
    }

    printf("Enter the discount:\n ");
    scanf("%d", &var1.discount);
    while ((getchar()) != '\n'); // Clear the newline character

    printf("Enter veg/non-veg:\n ");
    fgets(var1.v_n, sizeof(var1.v_n), stdin);
    var1.v_n[strcspn(var1.v_n, "\n")] = '\0';

    // Open the file in binary write mode
    file = fopen("var1.dat", "ab");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write the structure to the file
    fwrite(&var1, sizeof(struct hotel), 1, file);

    // Close the file
    fclose(file);

    printf("Data has been written to the file.\n");

    return 0;
}
