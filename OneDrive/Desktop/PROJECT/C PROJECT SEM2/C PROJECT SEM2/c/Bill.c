#include <stdio.h>
#include <string.h>

// Define the structure for a food item
typedef struct {
    char name[50];
    float price;
    float discount; // Discount as a percentage (e.g., 10 for 10%)
} FoodItem;

// Define the structure to hold the total discount sum
typedef struct {
    float totalDiscountSum;
} DiscountSum;

// Function to calculate the total discount sum for a list of food items
DiscountSum calculateTotalDiscount(FoodItem foodList[], int size) {
    DiscountSum discountSum;
    discountSum.totalDiscountSum = 0.0;
    
    for (int i = 0; i < size; i++) {
        float discountAmount = (foodList[i].price * foodList[i].discount) / 100;
        discountSum.totalDiscountSum += discountAmount;
    }
    
    return discountSum;
}

int main() {
    // Create a list of food items
    FoodItem foodList[3];
    
    strcpy(foodList[0].name, "Burger");
    foodList[0].price = 5.99;
    foodList[0].discount = 10.0; // 10% discount
    
    strcpy(foodList[1].name, "Pizza");
    foodList[1].price = 8.99;
    foodList[1].discount = 15.0; // 15% discount
    
    strcpy(foodList[2].name, "Salad");
    foodList[2].price = 4.99;
    foodList[2].discount = 5.0; // 5% discount
    
    // Calculate the total discount sum
    DiscountSum totalDiscount = calculateTotalDiscount(foodList, 3);
    
    // Print the total discount sum
    printf("Total Discount Sum: $%.2f\n", totalDiscount.totalDiscountSum);
    
    return 0;
}