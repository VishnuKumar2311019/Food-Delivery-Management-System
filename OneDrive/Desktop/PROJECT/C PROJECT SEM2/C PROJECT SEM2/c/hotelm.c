#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_ITEMS 10
#define MAX_CART_ITEMS 50
#define EARTH_RADIUS 6371.0


GtkWidget *hotel_name_entry;
GtkWidget *food_items_view;
GtkWidget *food_item_entry;
GtkWidget *cart_view;

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
    double lat1_rad = lat1 * M_PI / 180.0;
    double lon1_rad = lon1 * M_PI / 180.0;
    double lat2_rad = lat2 * M_PI / 180.0;
    double lon2_rad = lon2 * M_PI / 180.0;
    double delta_lat = lat2_rad - lat1_rad;
    double delta_lon = lon2_rad - lon1_rad;
    double a = sin(delta_lat / 2) * sin(delta_lat / 2) +
               cos(lat1_rad) * cos(lat2_rad) *
               sin(delta_lon / 2) * sin(delta_lon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = EARTH_RADIUS * c;
    return distance;
}

// Define global variables for GTK+ components and user cart
GtkWidget *preference_entry;
GtkWidget *hotel_list;
GtkWidget *latitude_entry;
GtkWidget *longitude_entry;
GtkWidget *distance_list;
GtkWidget *discount_list;
GtkWidget *cart_view;
struct cart user_cart;

// Callback functions
void on_show_preference_clicked(GtkButton *button, gpointer user_data) {
    const gchar *preference = gtk_entry_get_text(GTK_ENTRY(preference_entry));
    struct hotel var1;
    FILE *file = fopen("var1.dat", "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(hotel_list)), "", -1);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(hotel_list));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    while (fread(&var1, sizeof(struct hotel), 1, file)) {
        if (strcmp(var1.v_n, preference) == 0) {
            gtk_text_buffer_insert(buffer, &iter, var1.hotel_name, -1);
            gtk_text_buffer_insert(buffer, &iter, "\n", -1);
        }
    }

    fclose(file);
}

void on_sort_by_distance_clicked(GtkButton *button, gpointer user_data) {
    float user_latitude = atof(gtk_entry_get_text(GTK_ENTRY(latitude_entry)));
    float user_longitude = atof(gtk_entry_get_text(GTK_ENTRY(longitude_entry)));

    struct hotel hotels[100]; // Assuming a maximum of 100 hotels
    int num_hotels = 0;
    FILE *file = fopen("var1.dat", "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&hotels[num_hotels], sizeof(struct hotel), 1, file)) {
        double distance = calculate_distance(user_latitude, user_longitude, hotels[num_hotels].dist.latitude, hotels[num_hotels].dist.longitude);
        hotels[num_hotels].dist.latitude = distance; // Store the distance in the latitude field temporarily
        num_hotels++;
    }

    fclose(file);

    for (int i = 0; i < num_hotels - 1; i++) {
        for (int j = 0; j < num_hotels - i - 1; j++) {
            if (hotels[j].dist.latitude > hotels[j + 1].dist.latitude) {
                struct hotel temp = hotels[j];
                hotels[j] = hotels[j + 1];
                hotels[j + 1] = temp;
            }
        }
    }

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(distance_list)), "", -1);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(distance_list));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    for (int i = 0; i < num_hotels; i++) {
        char hotel_info[200];
        sprintf(hotel_info, "Hotel Name: %s, Distance: %.2f km\n", hotels[i].hotel_name, hotels[i].dist.latitude);
        gtk_text_buffer_insert(buffer, &iter, hotel_info, -1);
    }
}

void on_sort_by_discount_clicked(GtkButton *button, gpointer user_data) {
    struct hotel hotels[100]; // Assuming a maximum of 100 hotels
    int num_hotels = 0;
    FILE *file = fopen("var1.dat", "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&hotels[num_hotels], sizeof(struct hotel), 1, file)) {
        num_hotels++;
    }

    fclose(file);

    for (int i = 0; i < num_hotels - 1; i++) {
        for (int j = 0; j < num_hotels - i - 1; j++) {
            if (hotels[j].discount < hotels[j + 1].discount) {
                struct hotel temp = hotels[j];
                hotels[j] = hotels[j + 1];
                hotels[j + 1] = temp;
            }
        }
    }

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(discount_list)), "", -1);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(discount_list));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    for (int i = 0; i < num_hotels; i++) {
        char hotel_info[200];
        sprintf(hotel_info, "Hotel Name: %s, Discount: %d%%\n", hotels[i].hotel_name, hotels[i].discount);
        gtk_text_buffer_insert(buffer, &iter, hotel_info, -1);
    }
}





void on_view_cart_clicked(GtkButton *button, gpointer user_data) {
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(cart_view)), "", -1);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cart_view));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    for (int i = 0; i < user_cart.num_items; i++) {
        char item_info[200];
        sprintf(item_info, "Hotel: %s, Item: %s, Price: %d\n", 
                user_cart.items[i].hotel_name, 
                user_cart.items[i].item_name, 
                user_cart.items[i].price);
        gtk_text_buffer_insert(buffer, &iter, item_info, -1);
    }
}

void on_show_food_items_clicked(GtkButton *button, gpointer user_data) {
    const gchar *hotel_name = gtk_entry_get_text(GTK_ENTRY(hotel_name_entry));
    struct hotel var1;
    FILE *file = fopen("var1.dat", "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(food_items_view)), "", -1);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(food_items_view));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    while (fread(&var1, sizeof(struct hotel), 1, file)) {
        if (strcmp(var1.hotel_name, hotel_name) == 0) {
            // Display food items for the selected hotel
            char food_info[200];
            sprintf(food_info, "Hotel Name: %s\n", var1.hotel_name);
            gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            for (int i = 0; i < var1.fd.num_starters; i++) {
                sprintf(food_info, "Starter: %s, Price: %d\n", var1.fd.stt[i].str_name, var1.fd.stt[i].price);
                gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            }
            // Similar loops for main courses, desserts, and beverages
            break;
        }
    }

    fclose(file);
}

void on_add_to_cart_clicked(GtkButton *button, gpointer user_data) {
    const gchar *hotel_name = gtk_entry_get_text(GTK_ENTRY(hotel_name_entry));
    const gchar *food_item = gtk_entry_get_text(GTK_ENTRY(food_item_entry));
    struct hotel var1;
    FILE *file = fopen("var1.dat", "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&var1, sizeof(struct hotel), 1, file)) {
        if (strcmp(var1.hotel_name, hotel_name) == 0) {
            // Check if the selected food item exists in the hotel's menu
            int item_found = 0;
            for (int i = 0; i < var1.fd.num_starters; i++) {
                if (strcmp(var1.fd.stt[i].str_name, food_item) == 0) {
                    // Add the item to the cart
                    strcpy(user_cart.items[user_cart.num_items].item_name, var1.fd.stt[i].str_name);
                    user_cart.items[user_cart.num_items].price = var1.fd.stt[i].price;
                    strcpy(user_cart.items[user_cart.num_items].hotel_name, var1.hotel_name);
                    user_cart.num_items++;
                    item_found = 1;
                    break;
                }
            }
            // Similar checks for main courses, desserts, and beverages
            if (item_found) {
                printf("Added to cart: %s, %s\n", hotel_name, food_item);
            } else {
                printf("Food item not found in the menu.\n");
            }
            break;
        }
    }

    fclose(file);
}



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Initialize cart
    user_cart.num_items = 0;

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Food Ordering System");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a notebook to switch between different functionalities
    GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);

    // Create a page for hotel preference
    GtkWidget *pref_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *pref_label = gtk_label_new("Enter your preference (veg/non-veg):");
    preference_entry = gtk_entry_new();
    GtkWidget *pref_button = gtk_button_new_with_label("Show Hotels");
    hotel_list = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(hotel_list), FALSE);
    gtk_box_pack_start(GTK_BOX(pref_page), pref_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(pref_page), preference_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(pref_page), pref_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(pref_page), hotel_list, TRUE, TRUE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), pref_page, gtk_label_new("Preference"));

    g_signal_connect(pref_button, "clicked", G_CALLBACK(on_show_preference_clicked), NULL);

    // Create a page for sorting by distance
    GtkWidget *distance_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *lat_label = gtk_label_new("Enter your latitude:");
    latitude_entry = gtk_entry_new();
    GtkWidget *lon_label = gtk_label_new("Enter your longitude:");
    longitude_entry = gtk_entry_new();
    GtkWidget *distance_button = gtk_button_new_with_label("Sort Hotels by Distance");
    distance_list = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(distance_list), FALSE);
    gtk_box_pack_start(GTK_BOX(distance_page), lat_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(distance_page), latitude_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(distance_page), lon_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(distance_page), longitude_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(distance_page), distance_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(distance_page), distance_list, TRUE, TRUE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), distance_page, gtk_label_new("Sort by Distance"));

    g_signal_connect(distance_button, "clicked", G_CALLBACK(on_sort_by_distance_clicked), NULL);

    // Create a page for sorting by discount
    GtkWidget *discount_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *discount_button = gtk_button_new_with_label("Sort Hotels by Discount");
    discount_list = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(discount_list), FALSE);
    gtk_box_pack_start(GTK_BOX(discount_page), discount_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(discount_page), discount_list, TRUE, TRUE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), discount_page, gtk_label_new("Sort by Discount"));
    GdkColor red;
    gdk_color_parse ("#50C878", &red);
    gtk_widget_modify_bg (GTK_WIDGET(discount_page), GTK_STATE_NORMAL, &red);
    
    GdkColor blue;
    gdk_color_parse ("#FFD700", &blue);
    gtk_widget_modify_bg (GTK_WIDGET(discount_list), GTK_STATE_NORMAL, &blue);
    
    g_signal_connect(discount_button, "clicked", G_CALLBACK(on_sort_by_discount_clicked), NULL);

    GtkWidget *food_items_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *hotel_name_label = gtk_label_new("Enter the hotel name:");
    hotel_name_entry = gtk_entry_new(); // Assign to the global variable
    GtkWidget *show_food_items_button = gtk_button_new_with_label("Show Food Items");
    food_items_view = gtk_text_view_new(); // Assign to the global variable
    gtk_text_view_set_editable(GTK_TEXT_VIEW(food_items_view), FALSE);
    gtk_box_pack_start(GTK_BOX(food_items_page), hotel_name_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(food_items_page), hotel_name_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(food_items_page), show_food_items_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(food_items_page), food_items_view, TRUE, TRUE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), food_items_page, gtk_label_new("View Food Items"));

    g_signal_connect(show_food_items_button, "clicked", G_CALLBACK(on_show_food_items_clicked), NULL);

    // Create a page for adding to cart
    GtkWidget *add_to_cart_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *food_item_label = gtk_label_new("Enter the food item:");
    food_item_entry = gtk_entry_new(); // Assign to the global variable
    GtkWidget *add_to_cart_button = gtk_button_new_with_label("Add to Cart");
    gtk_box_pack_start(GTK_BOX(add_to_cart_page), food_item_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(add_to_cart_page), food_item_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(add_to_cart_page), add_to_cart_button, FALSE, FALSE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), add_to_cart_page, gtk_label_new("Add to Cart"));

    g_signal_connect(add_to_cart_button, "clicked", G_CALLBACK(on_add_to_cart_clicked), NULL);

    // Create a page for viewing the cart
    GtkWidget *view_cart_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *view_cart_button = gtk_button_new_with_label("View Cart");
    cart_view = gtk_text_view_new(); // Assign to the global variable
    gtk_text_view_set_editable(GTK_TEXT_VIEW(cart_view), FALSE);
    gtk_box_pack_start(GTK_BOX(view_cart_page), view_cart_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(view_cart_page), cart_view, TRUE, TRUE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), view_cart_page, gtk_label_new("View Cart"));

    g_signal_connect(view_cart_button, "clicked", G_CALLBACK(on_view_cart_clicked), NULL);


    // Show all components
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
