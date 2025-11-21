#include <stdio.h>
#include <string.h>
#include <math.h> // For math functions like sin, cos, sqrt

#define MAX_ITEMS 10 // Maximum number of each food item
#define MAX_CART_ITEMS 50 // Maximum number of items in the cart
#define EARTH_RADIUS 6371.0 // Radius of the Earth in kilometers

GtkWidget *quantity_entry;
GtkWidget *total_label;

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

struct cart_item {
    char item_name[50];
    int price;
    char hotel_name[100];
};

struct cart {
    struct cart_item items[MAX_CART_ITEMS];
    int num_items;
};

// Function to calculate the distance between two points using latitude and longitude
double calculate_distance(float lat1, float lon1, float lat2, float lon2) {
    // Convert latitude and longitude from degrees to radians
    double lat1_rad = lat1 * M_PI / 180.0;
    double lon1_rad = lon1 * M_PI / 180.0;
    double lat2_rad = lat2 * M_PI / 180.0;
    double lon2_rad = lon2 * M_PI / 180.0;

    // Calculate differences between latitudes and longitudes
    double delta_lat = lat2_rad - lat1_rad;
    double delta_lon = lon2_rad - lon1_rad;

    // Calculate distance using Haversine formula
    double a = sin(delta_lat / 2) * sin(delta_lat / 2) +
               cos(lat1_rad) * cos(lat2_rad) *
               sin(delta_lon / 2) * sin(delta_lon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = EARTH_RADIUS * c;

    return distance;
}

// Function to show hotel names based on veg/non-veg preference
void show_hotel_names_by_preference() {
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
            printf("Hotel Name: %s\n", var1.hotel_name);
        }
    }

    // Close the file
    fclose(file);
}

// Function to calculate distance between user and hotels, and sort based on distance
void sort_hotels_by_distance(float user_latitude, float user_longitude) {
    struct hotel hotels[100]; // Assuming a maximum of 100 hotels
    int num_hotels = 0;

    // Open the file in binary read mode
    FILE *file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read hotel data and calculate distance from user's location
    while (fread(&hotels[num_hotels], sizeof(struct hotel), 1, file)) {
        double distance = calculate_distance(user_latitude, user_longitude, hotels[num_hotels].dist.latitude, hotels[num_hotels].dist.longitude);
        hotels[num_hotels].dist.latitude = distance; // Store the distance in the latitude field temporarily
        num_hotels++;
    }

    // Close the file
    fclose(file);

    // Sort hotels by distance
    for (int i = 0; i < num_hotels - 1; i++) {
        for (int j = 0; j < num_hotels - i - 1; j++) {
            if (hotels[j].dist.latitude > hotels[j + 1].dist.latitude) {
                struct hotel temp = hotels[j];
                hotels[j] = hotels[j + 1];
                hotels[j + 1] = temp;
            }
        }
    }

    // Print sorted hotel names and distances
    printf("Hotels sorted by distance:\n");
    for (int i = 0; i < num_hotels; i++) {
        printf("Hotel Name: %s, Distance: %.2f km\n", hotels[i].hotel_name, hotels[i].dist.latitude);
    }
}

// Function to sort hotels by discount
void sort_hotels_by_discount() {
    struct hotel hotels[100]; // Assuming a maximum of 100 hotels
    int num_hotels = 0;

    // Open the file in binary read mode
    FILE *file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read hotel data
    while (fread(&hotels[num_hotels], sizeof(struct hotel), 1, file)) {
        num_hotels++;
    }

    // Close the file
    fclose(file);

    // Sort hotels by discount
    for (int i = 0; i < num_hotels - 1; i++) {
        for (int j = 0; j < num_hotels - i - 1; j++) {
            if (hotels[j].discount < hotels[j + 1].discount) {
                struct hotel temp = hotels[j];
                hotels[j] = hotels[j + 1];
                hotels[j + 1] = temp;
            }
        }
    }

    // Print sorted hotel names and discounts
    printf("Hotels sorted by discount:\n");
    for (int i = 0; i < num_hotels; i++) {
        printf("Hotel Name: %s, Discount: %d%%\n", hotels[i].hotel_name, hotels[i].discount);
    }
}

// Function to show food items of a specific hotel
void show_food_items_by_hotel_name() {
    struct hotel var1;
    FILE *file;
    char hotel_name[100];
    int found = 0;

    printf("Enter the hotel name:\n");
    fgets(hotel_name, sizeof(hotel_name), stdin);
    hotel_name[strcspn(hotel_name, "\n")] = '\0';

    // Open the file in binary read mode
    file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Search for the hotel by name and display its food items
    while (fread(&var1, sizeof(struct hotel), 1, file)) {
        if (strcmp(var1.hotel_name, hotel_name) == 0) {
            found = 1;
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
            break;
        }
    }

    if (!found) {
        printf("Hotel not found.\n");
    }

    // Close the file
    fclose(file);
}

// Function to add food items to cart
void add_food_items_to_cart(struct cart *user_cart) {
    struct hotel var1;
    FILE *file;
    char hotel_name[100];
    char food_item[50];
    int found = 0;

    printf("Enter the hotel name:\n");
    fgets(hotel_name, sizeof(hotel_name), stdin);
    hotel_name[strcspn(hotel_name, "\n")] = '\0';

    // Open the file in binary read mode
    file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Search for the hotel by name
    while (fread(&var1, sizeof(struct hotel), 1, file)) {
        if (strcmp(var1.hotel_name, hotel_name) == 0) {
            found = 1;
            while (1) {
                printf("Enter the food item name (or type 'done' to finish):\n");
                fgets(food_item, sizeof(food_item), stdin);
                food_item[strcspn(food_item, "\n")] = '\0';

                if (strcmp(food_item, "done") == 0) {
                    break;
                }

                // Check if the food item exists in the hotel's menu and add to the cart
                int item_found = 0;
                for (int i = 0; i < var1.fd.num_starters; i++) {
                    if (strcmp(var1.fd.stt[i].str_name, food_item) == 0) {
                        strcpy(user_cart->items[user_cart->num_items].item_name, var1.fd.stt[i].str_name);
                        user_cart->items[user_cart->num_items].price = var1.fd.stt[i].price;
                        strcpy(user_cart->items[user_cart->num_items].hotel_name, var1.hotel_name);
                        user_cart->num_items++;
                        item_found = 1;
                        printf("Added starter: %s, Price: %d\n", var1.fd.stt[i].str_name, var1.fd.stt[i].price);
                    }
                }
                for (int i = 0; i < var1.fd.num_main_courses; i++) {
                    if (strcmp(var1.fd.mn[i].main_name, food_item) == 0) {
                        strcpy(user_cart->items[user_cart->num_items].item_name, var1.fd.mn[i].main_name);
                        user_cart->items[user_cart->num_items].price = var1.fd.mn[i].price;
                        strcpy(user_cart->items[user_cart->num_items].hotel_name, var1.hotel_name);
                        user_cart->num_items++;
                        item_found = 1;
                        printf("Added main course: %s, Price: %d\n", var1.fd.mn[i].main_name, var1.fd.mn[i].price);
                    }
                }
                for (int i = 0; i < var1.fd.num_deserts; i++) {
                    if (strcmp(var1.fd.dt[i].desert_name, food_item) == 0) {
                        strcpy(user_cart->items[user_cart->num_items].item_name, var1.fd.dt[i].desert_name);
                        user_cart->items[user_cart->num_items].price = var1.fd.dt[i].price;
                        strcpy(user_cart->items[user_cart->num_items].hotel_name, var1.hotel_name);
                        user_cart->num_items++;
                        item_found = 1;
                        printf("Added desert: %s, Price: %d\n", var1.fd.dt[i].desert_name, var1.fd.dt[i].price);
                    }
                }
                for (int i = 0; i < var1.fd.num_beverages; i++) {
                    if (strcmp(var1.fd.bvg[i].bvg_name, food_item) == 0) {
                        strcpy(user_cart->items[user_cart->num_items].item_name, var1.fd.bvg[i].bvg_name);
                        user_cart->items[user_cart->num_items].price = var1.fd.bvg[i].price;
                        strcpy(user_cart->items[user_cart->num_items].hotel_name, var1.hotel_name);
                        user_cart->num_items++;
                        item_found = 1;
                        printf("Added beverage: %s, Price: %d\n", var1.fd.bvg[i].bvg_name, var1.fd.bvg[i].price);
                    }
                }

                if (!item_found) {
                    printf("Food item not found in the menu.\n");
                }
            }
            break;
        }
    }

    if (!found) {
        printf("Hotel not found.\n");
    }

    // Close the file
    fclose(file);
}

// Function to display the items in the cart
void display_cart(struct cart *user_cart) {
    printf("\nItems in your cart:\n");
    for (int i = 0; i < user_cart->num_items; i++) {
        printf("Hotel: %s, Item: %s, Price: %d\n", user_cart->items[i].hotel_name, user_cart->items[i].item_name, user_cart->items[i].price);
    }
}

// Function to calculate and display the total bill
// Function to calculate and display the total bill
void calculate_total_bill(struct cart *user_cart) {
    int base_price = 0;
    int total_discount = 0;
    FILE *file;
    struct hotel var1;

    // Calculate the base price of all items in the cart
    for (int i = 0; i < user_cart->num_items; i++) {
        base_price += user_cart->items[i].price;
    }

    // Open the file in binary read mode to get the hotel discounts
    file = fopen("var1.dat", "rb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Calculate the total discount based on the hotel-specific discounts
    for (int i = 0; i < user_cart->num_items; i++) {
        // Search for the hotel to get the discount
        rewind(file); // Reset file pointer to start
        while (fread(&var1, sizeof(struct hotel), 1, file)) {
            if (strcmp(user_cart->items[i].hotel_name, var1.hotel_name) == 0) {
                total_discount += user_cart->items[i].price * var1.discount / 100;
                break;
            }
        }
    }

    // Close the file
    fclose(file);

    int final_price = base_price - total_discount;
    printf("\nTotal Bill:\n");
    printf("Base Price: %d\n", base_price);
    printf("Total Discount: %d\n", total_discount);
    printf("Final Price: %d\n", final_price);
}

int main() {
    int choice;
    float user_latitude, user_longitude;
    struct cart user_cart;
    user_cart.num_items = 0;

    while (1) {
        printf("\nEnter 1 to view hotel names by veg/non-veg preference\n");
        printf("Enter 2 to sort hotels by distance\n");
        printf("Enter 3 to view food items by hotel name\n");
        printf("Enter 4 to add food items to cart\n");
        printf("Enter 5 to view cart\n");
        printf("Enter 6 to view total bill\n");
        printf("Enter 7 to exit\n");
        printf("Enter 8 to sort by discount\n");
        scanf("%d", &choice);

        
        while ((getchar()) != '\n');

        if (choice == 1) {
            show_hotel_names_by_preference();
        } else if (choice == 2) {
            printf("Enter your latitude:\n");
            scanf("%f", &user_latitude);
            printf("Enter your longitude:\n");
            scanf("%f", &user_longitude);
            while ((getchar()) != '\n'); 
            sort_hotels_by_distance(user_latitude, user_longitude);
        } else if (choice == 3) {
            show_food_items_by_hotel_name();
        } else if (choice == 4) {
            add_food_items_to_cart(&user_cart);
        } else if (choice == 5) {
            display_cart(&user_cart);
        } else if (choice == 6) {
            calculate_total_bill(&user_cart);
        } else if (choice == 7) {
            printf("Exiting the program.\n");
            break;
        } 
        else if (choice == 8) {
            sort_hotels_by_discount();
        }
        else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
