#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_ITEMS 10
#define MAX_CART_ITEMS 50
#define EARTH_RADIUS 6371.0

#define max_u_lg 20
#define max_p_lg 20


GtkWidget *hotel_name_entry;
GtkWidget *food_items_view;
GtkWidget *food_item_entry;
GtkWidget *cart_view;
GtkWidget *total_bill_label;

struct User {
    char username[max_u_lg];
    char password[max_p_lg];
};


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

struct freq_item {
    char item_name[50];
};
struct freq_item frequency_items[MAX_ITEMS];
int next_item = 0;



int login() {
    char username[max_u_lg];
    char password[max_p_lg];
    struct User user;

    printf("Login\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);
    char c;
    int i = 0;
    while ((c = getchar()) != '\n') {
        if (i < max_p_lg - 1) {
            password[i++] = c;
        }
    }
    password[i] = '\0';

    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        printf("Error opening users.dat file.\n");
        return 0;
    }

    int found = 0;
    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            printf("Login successful!\n");
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("User not found. Creating new account...\n");
        file = fopen("users.dat", "ab");
        if (file == NULL) {
            printf("Error opening file.\n");
            return 0;
        }

        struct User n_user;
        strcpy(n_user.username, username);
        strcpy(n_user.password, password);
        fwrite(&n_user, sizeof(struct User), 1, file);
        fclose(file);
        printf("New account created successfully!\n");
        return 1; // New line added
    }

    return found;
}

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


GtkWidget *preference_entry;
GtkWidget *hotel_list;
GtkWidget *latitude_entry;
GtkWidget *longitude_entry;
GtkWidget *distance_list;
GtkWidget *discount_list;
GtkWidget *cart_view;
GtkWidget *total_bill_label;
GtkWidget *recommendation_view;
struct cart user_cart;


int item_in_cart(struct cart_item *items, int num_items, const char *item_name) {
    for (int i = 0; i < num_items; i++) {
        if (strcmp(items[i].item_name, item_name) == 0) {
            return 1;
        }
    }
    return 0;
}

void pref(GtkButton *button, gpointer user_data) {
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

void sort_dist(GtkButton *button, gpointer user_data) {
    float user_latitude = atof(gtk_entry_get_text(GTK_ENTRY(latitude_entry)));
    float user_longitude = atof(gtk_entry_get_text(GTK_ENTRY(longitude_entry)));

    struct hotel hotels[100]; 
    int num_hotels = 0;
    FILE *file = fopen("var1.dat", "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&hotels[num_hotels], sizeof(struct hotel), 1, file)) {
        double distance = calculate_distance(user_latitude, user_longitude, hotels[num_hotels].dist.latitude, hotels[num_hotels].dist.longitude);
        hotels[num_hotels].dist.latitude = distance; 
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

void sort_disc(GtkButton *button, gpointer user_data) {
    struct hotel hotels[100]; 
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

void view_cart(GtkButton *button, gpointer user_data) {
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(cart_view)), "", -1);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cart_view));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    for (int i = 0; i < user_cart.num_items; i++) {
        char item_info[200];
        sprintf(item_info, "Item    :   %s       Price   :   %d\n", 
                 
                user_cart.items[i].item_name, 
                user_cart.items[i].price);
        gtk_text_buffer_insert(buffer, &iter, item_info, -1);
    }
}

void show_food(GtkButton *button, gpointer user_data) {
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
            
            char food_info[200];
            sprintf(food_info, "Starters:\n");
            gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            for (int i = 0; i < var1.fd.num_starters; i++) {
                sprintf(food_info, "%s - %d\n", var1.fd.stt[i].str_name, var1.fd.stt[i].price);
                gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            }

            sprintf(food_info, "\nMain Courses:\n");
            gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            for (int i = 0; i < var1.fd.num_main_courses; i++) {
                sprintf(food_info, "%s - %d\n", var1.fd.mn[i].main_name, var1.fd.mn[i].price);
                gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            }

            sprintf(food_info, "\nDeserts:\n");
            gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            for (int i = 0; i < var1.fd.num_deserts; i++) {
                sprintf(food_info, "%s - %d\n", var1.fd.dt[i].desert_name, var1.fd.dt[i].price);
                gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            }

            sprintf(food_info, "\nBeverages:\n");
            gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            for (int i = 0; i < var1.fd.num_beverages; i++) {
                sprintf(food_info, "%s - %d\n", var1.fd.bvg[i].bvg_name, var1.fd.bvg[i].price);
                gtk_text_buffer_insert(buffer, &iter, food_info, -1);
            }
            break;
        }
    }

    fclose(file);
}

void add_cart(GtkButton *button, gpointer user_data) {
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
            for (int i = 0; i < var1.fd.num_starters; i++) {
                if (strcmp(var1.fd.stt[i].str_name, food_item) == 0) {
                    struct cart_item new_item;
                    strcpy(new_item.hotel_name, hotel_name);
                    strcpy(new_item.item_name, food_item);
                    new_item.price = var1.fd.stt[i].price;
                    user_cart.items[user_cart.num_items] = new_item;
                    user_cart.num_items++;
                    break;
                }
            }

            for (int i = 0; i < var1.fd.num_main_courses; i++) {
                if (strcmp(var1.fd.mn[i].main_name, food_item) == 0) {
                    struct cart_item new_item;
                    strcpy(new_item.hotel_name, hotel_name);
                    strcpy(new_item.item_name, food_item);
                    new_item.price = var1.fd.mn[i].price;
                    user_cart.items[user_cart.num_items] = new_item;
                    user_cart.num_items++;
                    break;
                }
            }

            for (int i = 0; i < var1.fd.num_deserts; i++) {
                if (strcmp(var1.fd.dt[i].desert_name, food_item) == 0) {
                    struct cart_item new_item;
                    strcpy(new_item.hotel_name, hotel_name);
                    strcpy(new_item.item_name, food_item);
                    new_item.price = var1.fd.dt[i].price;
                    user_cart.items[user_cart.num_items] = new_item;
                    user_cart.num_items++;
                    break;
                }
            }

            for (int i = 0; i < var1.fd.num_beverages; i++) {
                if (strcmp(var1.fd.bvg[i].bvg_name, food_item) == 0) {
                    struct cart_item new_item;
                    strcpy(new_item.hotel_name, hotel_name);
                    strcpy(new_item.item_name, food_item);
                    new_item.price = var1.fd.bvg[i].price;
                    user_cart.items[user_cart.num_items] = new_item;
                    user_cart.num_items++;
                    break;
                }
            }
            break;
        }
    }

    fclose(file);
}

void remove_from_cart(GtkButton *button, gpointer user_data) {
    const gchar *item_name = gtk_entry_get_text(GTK_ENTRY(food_item_entry));

    for (int i = 0; i < user_cart.num_items; i++) {
        if (strcmp(user_cart.items[i].item_name, item_name) == 0) {
            // Remove the item from the cart
            for (int j = i; j < user_cart.num_items - 1; j++) {
                user_cart.items[j] = user_cart.items[j + 1];
            }
            user_cart.num_items--;
            break;
        }
    }

    // Refresh the cart view
    view_cart(NULL, NULL);
}

void calc_bill(GtkButton *button, gpointer user_data) {
    int total = 0;
    FILE *sold_file = fopen("sold.csv", "a"); 

    if (sold_file == NULL) {
        printf("Error opening sold.csv file.\n");
        return;
    }

    for (int i = 0; i < user_cart.num_items; i++) {
        total += user_cart.items[i].price;
        fprintf(sold_file, "%s,", user_cart.items[i].item_name);
    }
    fprintf(sold_file,"\n");
    fclose(sold_file);

    char total_str[50];
    sprintf(total_str, "Total Bill: %d", total);
    gtk_label_set_text(GTK_LABEL(total_bill_label), total_str);
}

void recommend(GtkButton *button, gpointer user_data) {
    char line[200];
    int frequency[MAX_ITEMS] = {0};
    int next_item = 0;

    FILE *file = fopen("sold.csv", "r");
    if (file == NULL) {
        printf("Error opening sold.csv file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            // Remove leading/trailing whitespace from the token
            char *trimmed_token = g_strstrip(token);

            // Skip empty tokens
            if (trimmed_token[0] == '\0') {
                token = strtok(NULL, ",");
                continue;
            }

            int found = 0;
            for (int i = 0; i < next_item; i++) {
                if (strcmp(frequency_items[i].item_name, trimmed_token) == 0) {
                    frequency[i]++;
                    found = 1;
                    break;
                }
            }
            if (!found && next_item < MAX_ITEMS) {
                strcpy(frequency_items[next_item].item_name, trimmed_token);
                frequency[next_item]++;
                next_item++;
            }
            token = strtok(NULL, ",");
        }
    }
    fclose(file);

    for (int i = 0; i < next_item - 1; i++) {
        for (int j = 0; j < next_item - i - 1; j++) {
            if (frequency[j] < frequency[j + 1]) {
                int temp_freq = frequency[j];
                frequency[j] = frequency[j + 1];
                frequency[j + 1] = temp_freq;
                struct freq_item temp = frequency_items[j];
                frequency_items[j] = frequency_items[j + 1];
                frequency_items[j + 1] = temp;
            }
        }
    }

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(recommendation_view)), "", -1);
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(recommendation_view));
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);

    char recommendation_info[200];
    sprintf(recommendation_info, "Top 5 Recommended Items:\n");
    gtk_text_buffer_insert(buffer, &iter, recommendation_info, -1);

    for (int i = 0; i < 5 && i < next_item; i++) {
        if (frequency_items[i].item_name[0] != '\0') {
            sprintf(recommendation_info, "%d. %s  (%d sold)\n", i + 1, frequency_items[i].item_name, frequency[i]);
            gtk_text_buffer_insert(buffer, &iter, recommendation_info, -1);
        }
    }
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Food Ordering System");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);

    GtkWidget *preference_page = gtk_vbox_new(FALSE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), preference_page, gtk_label_new("Preferences"));

    GtkWidget *preference_label = gtk_label_new("Preference:");
    gtk_box_pack_start(GTK_BOX(preference_page), preference_label, FALSE, FALSE, 0);
    preference_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(preference_page), preference_entry, FALSE, FALSE, 0);
    GdkColor c1;
    gdk_color_parse ("#FFD700", &c1);
    gtk_widget_modify_bg (GTK_WIDGET(preference_page), GTK_STATE_NORMAL, &c1);
    GdkColor c2;
    gdk_color_parse ("#50C878", &c2);
    gtk_widget_modify_bg (GTK_WIDGET(preference_entry), GTK_STATE_NORMAL, &c2);
    
    GtkWidget *show_preference_button = gtk_button_new_with_label("Show Hotels");
    gtk_box_pack_start(GTK_BOX(preference_page), show_preference_button, FALSE, FALSE, 0);
    g_signal_connect(show_preference_button, "clicked", G_CALLBACK(pref), NULL);

    hotel_list = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(preference_page), hotel_list, TRUE, TRUE, 0);
    gtk_widget_modify_bg (GTK_WIDGET(hotel_list), GTK_STATE_NORMAL, &c2);
    GtkWidget *distance_page = gtk_vbox_new(FALSE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), distance_page, gtk_label_new("Distance"));

    GtkWidget *latitude_label = gtk_label_new("Latitude:");
    gtk_box_pack_start(GTK_BOX(distance_page), latitude_label, FALSE, FALSE, 0);
    latitude_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(distance_page), latitude_entry, FALSE, FALSE, 0);

    GtkWidget *longitude_label = gtk_label_new("Longitude:");
    gtk_box_pack_start(GTK_BOX(distance_page), longitude_label, FALSE, FALSE, 0);
    longitude_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(distance_page), longitude_entry, FALSE, FALSE, 0);

    GtkWidget *sort_by_distance_button = gtk_button_new_with_label("Sort by Distance");
    gtk_box_pack_start(GTK_BOX(distance_page), sort_by_distance_button, FALSE, FALSE, 0);
    g_signal_connect(sort_by_distance_button, "clicked", G_CALLBACK(sort_dist), NULL);

    distance_list = gtk_text_view_new();
   
    gtk_box_pack_start(GTK_BOX(distance_page), distance_list, TRUE, TRUE, 0);

    GtkWidget *discount_page = gtk_vbox_new(FALSE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), discount_page, gtk_label_new("Discount"));

    GtkWidget *sort_by_discount_button = gtk_button_new_with_label("Sort by Discount");
    gtk_box_pack_start(GTK_BOX(discount_page), sort_by_discount_button, FALSE, FALSE, 0);
    g_signal_connect(sort_by_discount_button, "clicked", G_CALLBACK(sort_disc), NULL);

    discount_list = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(discount_page), discount_list, TRUE, TRUE, 0);


    gtk_widget_modify_bg (GTK_WIDGET(longitude_label), GTK_STATE_NORMAL, &c2);
    gtk_widget_modify_bg (GTK_WIDGET(latitude_label), GTK_STATE_NORMAL, &c2);
    gtk_widget_modify_bg (GTK_WIDGET(sort_by_distance_button), GTK_STATE_NORMAL, &c1);
    gtk_widget_modify_bg (GTK_WIDGET(discount_page), GTK_STATE_NORMAL, &c1);
    gtk_widget_modify_bg (GTK_WIDGET(distance_list), GTK_STATE_NORMAL, &c2);
    gtk_widget_modify_bg (GTK_WIDGET(discount_list), GTK_STATE_NORMAL, &c2);



    GtkWidget *cart_page = gtk_vbox_new(FALSE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), cart_page, gtk_label_new("Cart"));


    gtk_widget_modify_bg (GTK_WIDGET(cart_page), GTK_STATE_NORMAL, &c1);
    
    


    GtkWidget *view_cart_button = gtk_button_new_with_label("View Cart");
    gtk_box_pack_start(GTK_BOX(cart_page), view_cart_button, FALSE, FALSE, 0);
    g_signal_connect(view_cart_button, "clicked", G_CALLBACK(view_cart), NULL);
    GtkWidget *remove_from_cart_button = gtk_button_new_with_label("Remove from Cart");
    gtk_box_pack_start(GTK_BOX(food_page), remove_from_cart_button, FALSE, FALSE, 0);
    g_signal_connect(remove_from_cart_button, "clicked", G_CALLBACK(remove_from_cart), NULL);
    cart_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(cart_page), cart_view, TRUE, TRUE, 0);
    
 


    gtk_widget_modify_bg (GTK_WIDGET(cart_view), GTK_STATE_NORMAL, &c2);



    GtkWidget *food_page = gtk_vbox_new(FALSE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), food_page, gtk_label_new("Food Items"));

    GtkWidget *hotel_name_label = gtk_label_new("Hotel Name:");
    gtk_box_pack_start(GTK_BOX(food_page), hotel_name_label, FALSE, FALSE, 0);
    hotel_name_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(food_page), hotel_name_entry, FALSE, FALSE, 0);

    GtkWidget *show_food_items_button = gtk_button_new_with_label("Show Food Items");
    gtk_box_pack_start(GTK_BOX(food_page), show_food_items_button, FALSE, FALSE, 0);
    g_signal_connect(show_food_items_button, "clicked", G_CALLBACK(show_food), NULL);

    food_items_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(food_page), food_items_view, TRUE, TRUE, 0);


    gtk_widget_modify_bg (GTK_WIDGET(food_items_view), GTK_STATE_NORMAL, &c1);


    GtkWidget *food_item_label = gtk_label_new("Food Item:");
    gtk_box_pack_start(GTK_BOX(food_page), food_item_label, FALSE, FALSE, 0);
    food_item_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(food_page), food_item_entry, FALSE, FALSE, 0);

    GtkWidget *add_to_cart_button = gtk_button_new_with_label("Add to Cart");
    gtk_box_pack_start(GTK_BOX(food_page), add_to_cart_button, FALSE, FALSE, 0);
    g_signal_connect(add_to_cart_button, "clicked", G_CALLBACK(add_cart), NULL);
    
    GtkWidget *total_bill_button = gtk_button_new_with_label("Calculate Total Bill");
    gtk_box_pack_start(GTK_BOX(food_page), total_bill_button, FALSE, FALSE, 0);
    g_signal_connect(total_bill_button, "clicked", G_CALLBACK(calc_bill), NULL);

    total_bill_label = gtk_label_new("Total Bill: 0");
    gtk_box_pack_start(GTK_BOX(food_page), total_bill_label, FALSE, FALSE, 0);


    gtk_widget_modify_bg (GTK_WIDGET(food_item_entry), GTK_STATE_NORMAL, &c1);
    gtk_widget_modify_bg (GTK_WIDGET(hotel_name_entry), GTK_STATE_NORMAL, &c1);
    gtk_widget_modify_bg (GTK_WIDGET(hotel_name_label), GTK_STATE_NORMAL, &c2);
    gtk_widget_modify_bg (GTK_WIDGET(food_item_label), GTK_STATE_NORMAL, &c2);
    gtk_widget_modify_bg (GTK_WIDGET(total_bill_label), GTK_STATE_NORMAL, &c2);
    gtk_widget_modify_bg (GTK_WIDGET(latitude_entry), GTK_STATE_NORMAL, &c1);
    gtk_widget_modify_bg (GTK_WIDGET(longitude_entry), GTK_STATE_NORMAL, &c1);

    

    recommendation_view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(food_page), recommendation_view, TRUE, TRUE, 0); 
    GtkWidget *recommendation_button = gtk_button_new_with_label("Show Recommendations");
    gtk_box_pack_start(GTK_BOX(food_page), recommendation_button, FALSE, FALSE, 0);
    g_signal_connect(recommendation_button, "clicked", G_CALLBACK(recommend), NULL);
    for (int i = 0; i < MAX_ITEMS; i++) {
        frequency_items[i].item_name[0] = '\0';
    }

    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
