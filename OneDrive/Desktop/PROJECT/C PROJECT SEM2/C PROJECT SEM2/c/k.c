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

    
    while ((getchar()) != '\n');

    while(1){
        printf("Enter 1.to add starter\n 2.to add main course\n 3.to add desert \n 4.to add beverages\n 5.To break\n ");
        scanf("%d", &choice);
        
       
        while ((getchar()) != '\n');

        if (choice == 1) {
            printf("Enter starter name:\n ");
            fgets(var1.fd.stt.str_name, sizeof(var1.fd.stt.str_name), stdin);
            var1.fd.stt.str_name[strcspn(var1.fd.stt.str_name, "\n")] = '\0';

            printf("Enter starter price:\n ");
            scanf("%d", &var1.fd.stt.price);
            while ((getchar()) != '\n'); 
        } else if (choice == 2) {
            printf("Enter main course name:\n ");
            fgets(var1.fd.mn.main_name, sizeof(var1.fd.mn.main_name), stdin);
            var1.fd.mn.main_name[strcspn(var1.fd.mn.main_name, "\n")] = '\0';

            printf("Enter main course price:\n ");
            scanf("%d", &var1.fd.mn.price);
            while ((getchar()) != '\n'); 
        } else if (choice == 3) {
            printf("Enter desert name:\n ");
            fgets(var1.fd.dt.desert_name, sizeof(var1.fd.dt.desert_name), stdin);
            var1.fd.dt.desert_name[strcspn(var1.fd.dt.desert_name, "\n")] = '\0';

            printf("Enter desert price:\n ");
            scanf("%d", &var1.fd.dt.price);
            while ((getchar()) != '\n'); 
        } else if (choice == 4) {
            printf("Enter beverage name:\n ");
            fgets(var1.fd.bvg.bvg_name, sizeof(var1.fd.bvg.bvg_name), stdin);
            var1.fd.bvg.bvg_name[strcspn(var1.fd.bvg.bvg_name, "\n")] = '\0';

            printf("Enter beverage price:\n ");
            scanf("%d", &var1.fd.bvg.price);
            while ((getchar()) != '\n'); 
        } else if (choice == 5) {
            printf("Thank You\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    printf("Enter the discount:\n ");
    scanf("%d", &var1.discount);
    while ((getchar()) != '\n');

    printf("Enter veg/non-veg:\n ");
    fgets(var1.v_n, sizeof(var1.v_n), stdin);
    var1.v_n[strcspn(var1.v_n, "\n")] = '\0';

    
    file = fopen("var1.dat", "ab");

   
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    
    fwrite(&var1, sizeof(struct hotel), 1, file);

    
    fclose(file);

    printf("Data has been written to the file.\n");

    return 0;
}
