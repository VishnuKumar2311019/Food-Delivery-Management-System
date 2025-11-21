#include <stdio.h>
#include <string.h>

#define max_u_lg 20
#define max_p_lg 20

struct User {
    char username[max_u_lg];
    char password[max_p_lg];
};

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

int main() {
    if (login()) {
        
        printf("Welcome to the food ordering system application!\n");

        
    } else {
        
        printf("Failed to log in.\n");
    }

    return 0;
}