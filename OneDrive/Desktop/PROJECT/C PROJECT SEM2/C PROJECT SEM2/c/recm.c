#include<stdio.h>
#include<string.h>

#define MAX_ITEMS 10

typedef struct {
    char name[50];
    int price;
    int is_available;
} FoodItem;

typedef struct {
    char preference[50];
    int budget;
} UserPreference;

void recommend_food_items(FoodItem *food_items, int num_food_items, UserPreference user_preference) {
    int i, j;
    int num_recommended_items = 0;
    FoodItem recommended_items[MAX_ITEMS];

    for (i = 0; i < num_food_items; i++) {
        if (strcmp(food_items[i].name, user_preference.preference) == 0 && food_items[i].is_available == 1) {
            recommended_items[num_recommended_items] = food_items[i];
            num_recommended_items++;
        }
    }

    if (num_recommended_items == 0) {
        printf("No food items match your preference. Please try again.\n");
        return;
    }

    printf("Recommended food items:\n");
    for (j = 0; j < num_recommended_items; j++) {
        printf("%s - %d\n", recommended_items[j].name, recommended_items[j].price);
    }

    if (user_preference.budget < recommended_items[0].price) {
        printf("The recommended food items are out of your budget. Please try again.\n");
    }
}

int main() {
    FoodItem food_items[] = {
        {"Pizza", 10, 1},
        {"Burger", 8, 1},
        {"Salad", 5, 1},
        {"Sandwich", 7, 0}
    };

    UserPreference user_preference = {"Pizza", 15};

    recommend_food_items(food_items, 4, user_preference);

    return 0;
}