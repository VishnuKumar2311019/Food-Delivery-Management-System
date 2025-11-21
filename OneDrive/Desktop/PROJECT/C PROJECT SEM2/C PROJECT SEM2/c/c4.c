#include <stdio.h>
#include <string.h>
#include <math.h> // For math functions like sin, cos, sqrt

#define MAX_ITEMS 10 // Maximum number of each food item
#define MAX_CART_ITEMS 50 // Maximum number of items in the cart
#define EARTH_RADIUS 6371.0 // Radius of the Earth in kilometers

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
    int quantity, price, found = 0;

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
            break;
        }
    }

    if (!found) {
        printf("Hotel not found.\n");
        fclose(file);
        return;
    }

    // Close the file
    fclose(file);

    printf("Enter the food item name:\n");
    fgets(food_item, sizeof(food_item), stdin);
    food_item[strcspn(food_item, "\n")] = '\0';

    printf("Enter the quantity:\n");
    scanf("%d", &quantity);
    getchar(); // Clear the newline character from the input buffer

    found = 0;

    // Search for the food item in the hotel's food list
    for (int i = 0; i < var1.fd.num_starters; i++) {
        if (strcmp(var1.fd.stt[i].str_name, food_item) == 0) {
            found = 1;
            price = var1.fd.stt[i].price * quantity;
            break;
        }
    }
    for (int i = 0; i < var1.fd.num_main_courses; i++) {
        if (strcmp(var1.fd.mn[i].main_name, food_item) == 0) {
            found = 1;
            price = var1.fd.mn[i].price * quantity;
            break;
        }
    }
    for (int i = 0; i < var1.fd.num_deserts; i++) {
        if (strcmp(var1.fd.dt[i].desert_name, food_item) == 0) {
            found = 1;
            price = var1.fd.dt[i].price * quantity;
            break;
        }
    }
    for (int i = 0; i < var1.fd.num_beverages; i++) {
        if (strcmp(var1.fd.bvg[i].bvg_name, food_item) == 0) {
            found = 1;
            price = var1.fd.bvg[i].price * quantity;
            break;
        }
    }

    if (!found) {
        printf("Food item not found in the selected hotel.\n");
        return;
    }

    // Add the food item to the cart
    if (user_cart->num_items < MAX_CART_ITEMS) {
        strcpy(user_cart->items[user_cart->num_items].item_name, food_item);
        user_cart->items[user_cart->num_items].price = price;
        strcpy(user_cart->items[user_cart->num_items].hotel_name, hotel_name);
        user_cart->num_items++;
        printf("Item added to the cart.\n");
    } else {
        printf("Cart is full. Cannot add more items.\n");
    }
}

// Function to calculate the total cost of items in the cart
void calculate_total_cost(struct cart *user_cart) {
    int total_cost = 0;
    for (int i = 0; i < user_cart->num_items; i++) {
        total_cost += user_cart->items[i].price;
    }
    printf("Total cost of items in the cart: %d\n", total_cost);
}

// Function to print cart items
void print_cart_items(struct cart *user_cart) {
    printf("Cart items:\n");
    for (int i = 0; i < user_cart->num_items; i++) {
        printf("Item Name: %s, Price: %d, Hotel Name: %s\n",
               user_cart->items[i].item_name, user_cart->items[i].price, user_cart->items[i].hotel_name);
    }
}

// Function to clear the cart
void clear_cart(struct cart *user_cart) {
    user_cart->num_items = 0;
    printf("Cart cleared.\n");
}

// Function to display the grid map indicating different types of restaurants
void display_map() {
    char map[10][10];

    // Initialize the map with empty spaces
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            map[i][j] = ' ';
        }
    }

    // Randomly place different types of restaurants on the map
    // V - Vegetarian, N - Non-vegetarian, B - Both
    map[2][3] = 'V';
    map[5][5] = 'N';
    map[8][1] = 'B';
    map[1][7] = 'V';
    map[4][4] = 'N';
    map[6][8] = 'B';

    // Display the map
    printf("Grid map indicating different types of restaurants:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

// Function to implement the NotOnRestaurant functionality
void NotOnRestaurant() {
    struct cart user_cart;
    user_cart.num_items = 0;

    while (1) {
        int choice;
        printf("\nMenu:\n");
        printf("1. Show hotel names by veg/non-veg preference\n");
        printf("2. Sort hotels by distance\n");
        printf("3. Sort hotels by discount\n");
        printf("4. Show food items by hotel name\n");
        printf("5. Add food items to cart\n");
        printf("6. Calculate total cost of items in the cart\n");
        printf("7. Print cart items\n");
        printf("8. Clear cart\n");
        printf("9. Display map\n");
        printf("10. Exit\n");
        printf("Enter your choice:\n");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                show_hotel_names_by_preference();
                break;
            case 2: {
                float user_latitude, user_longitude;
                printf("Enter your latitude:\n");
                scanf("%f", &user_latitude);
                printf("Enter your longitude:\n");
                scanf("%f", &user_longitude);
                getchar(); // Clear the newline character from the input buffer
                sort_hotels_by_distance(user_latitude, user_longitude);
                break;
            }
            case 3:
                sort_hotels_by_discount();
                break;
            case 4:
                show_food_items_by_hotel_name();
                break;
            case 5:
                add_food_items_to_cart(&user_cart);
                break;
            case 6:
                calculate_total_cost(&user_cart);
                break;
            case 7:
                print_cart_items(&user_cart);
                break;
            case 8:
                clear_cart(&user_cart);
                break;
            case 9:
                display_map();
                break;
            case 10:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

int main() {
    NotOnRestaurant();
    return 0;
}
