#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_ITEMS 100
#define NUM_RECOMMENDATIONS 3

typedef struct {
    char item[50];
    int count;
} ItemCount;

void sortItemCounts(ItemCount *items, int numItems) {
    for (int i = 0; i < numItems - 1; i++) {
        for (int j = 0; j < numItems - i - 1; j++) {
            if (items[j].count < items[j + 1].count) {
                ItemCount temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

int main() {
    FILE *file = fopen("sold.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char userInput[50];
    ItemCount itemCounts[MAX_ITEMS] = {0};
    int numItems = 0;

    printf("Enter a food item: ");
    fgets(userInput, sizeof(userInput), stdin);
    userInput[strcspn(userInput, "\n")] = '\0';  // Remove newline character

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char *token = strtok(line, ",");
        int tokenCount = 0;
        char currentItem[50];
        strcpy(currentItem, "");

        while (token != NULL) {
            if (tokenCount == 1) {
                strcpy(currentItem, token);
            }
            if (tokenCount == 1 && strcmp(token, userInput) != 0) {
                int found = 0;
                for (int i = 0; i < numItems; i++) {
                    if (strcmp(itemCounts[i].item, currentItem) == 0) {
                        itemCounts[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found && numItems < MAX_ITEMS) {
                    strcpy(itemCounts[numItems].item, currentItem);
                    itemCounts[numItems].count = 1;
                    numItems++;
                }
            }
            token = strtok(NULL, ",");
            tokenCount++;
        }
    }

    sortItemCounts(itemCounts, numItems);

    printf("Recommended items to buy with '%s':\n", userInput);
    for (int i = 0; i < NUM_RECOMMENDATIONS && i < numItems; i++) {
        printf("%s\n", itemCounts[i].item);
    }

    fclose(file);
    return 0;
}