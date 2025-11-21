#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<ctype.h>



// #define MAX_USERS 100

typedef struct {
    char first_name[50];
    char last_name[50];
    char username[20];
    char password[20];
    char phone[20];
    char email[50];
    char security_one[20];
    char security_two[20];
    int wrong_pass_count;
    int wrong_security_count;
    
} User;

int verify_password(User users[], int *numUsers)
{
    char given_password[50];
    int len_pass=0,upper=0,lower=0,spec=0,digit=0;
    strcpy(given_password,users[*numUsers].password);
    for (int i=0;i<strlen(given_password);i++)
    {
        if (isupper(given_password[i]))
        {
            upper=1;
        }
        else if (islower(given_password[i]))
        {
            lower=1;
        }
        else if (isdigit(given_password[i]))
        {
            digit=1;
        }
        else
        {
            spec=1;
        }
    }
    if (strlen(given_password)>=8)
    {
        len_pass=1;
    }
    int total=len_pass+upper+lower+digit+spec;
    if (total==5)
    {
        return 1;
    }
    return 0;
}

int name_create(User users[], int *numUsers)
{
    printf("Enter your First Name : ");
    scanf("%s",users[*numUsers].first_name);
    printf("Enter your Last Name : ");
    scanf("%s",users[*numUsers].last_name);
    return 0;
}



int username_create(User users[], int *numUsers)
{
    printf("Enter username: ");
    scanf("%s", users[*numUsers].username);
    for (int i=0;i< *numUsers;i++)
    {
        if (strcmp(users[*numUsers].username, users[i].username)==0)
        {
            printf(" !!! %s is already exist.check and enter username \n",users[*numUsers].username);
            return username_create(users,numUsers);
        }
    }
    return 1;
}


int password_create(User users[], int *numUsers)
{
    //static try=1;
    printf("Enter password: ");
    scanf("%s", users[*numUsers].password);
    
    if (verify_password(users,numUsers))
    {
        char confirmPass[20];
        printf("Confirm password: ");
        scanf("%s", confirmPass);
    
        if(strcmp(users[*numUsers].password, confirmPass) == 0)
        {
            return 1;
        }
        else
        {
            printf("\n !!! Password mismatch Re-create\n");
            return password_create(users,numUsers);
            
        }
    }
    else
    {
        printf("Password doesn't match with our password criteria\nRe-");
        return password_create(users,numUsers);
    }
}


int phone_create(User users[], int *numUsers)
{
    printf("Enter phone number: ");
    scanf("%s", users[*numUsers].phone);
    if (strlen(users[*numUsers].phone)!=10)
    {
        printf("!!! Enter correct number,Phone number length is must be 10\n");
        return phone_create(users,numUsers);
    }
    for (int i=0;i< *numUsers;i++)
    {
        if (strcmp(users[*numUsers].phone,users[i].phone)==0)
        {
            printf(" !!! %d is already registered with other account \n",users[*numUsers].phone);
            return phone_create(users,numUsers);
        }
    }
    return 1;
}

int email_create(User users[], int *numUsers)
{
    printf("Enter email ID: ");
    scanf("%s", users[*numUsers].email);
    for (int i=0;i< *numUsers;i++)
    {
        if (strcmp(users[*numUsers].email, users[i].email)==0)
        {
            printf(" !!! %s is already exist.check and enter username \n",users[*numUsers].email);
            return email_create(users,numUsers);
        }
    }
    return 1;
}

int security_create(User users[],int *numUsers)
{
    printf("1.) What is your hobby ?\nAnswer : ");
    scanf("%s",users[*numUsers].security_one);
    printf("2.) Who Is Your inspiration ?\nAnswer : ");
    scanf("%s",users[*numUsers].security_two);
    
}


void signUp(User users[], int *numUsers) {
    
    name_create(users,numUsers);
    username_create(users,numUsers);
    email_create(users,numUsers);
    phone_create(users,numUsers);
    
    printf("\nNOTE :  \nOur Password Criteria \n\n 1.) Password Must Have One UpperCase.\n 2.) Password Must Have One LowerCase.\n 3.) Password Must Have One Numerical Digit.\n 4.) Password Must Have One Special Character\n 5.) Password Must Be Atleat 8 Characters.\n");
    
    if (password_create(users,numUsers))
    {
        printf("Password Created Successfully\n");
    }
    printf("\nPlease Answer The Following Security Question ,It Will Help You To Recover Password When You Forget It\n");
    security_create(users,numUsers);
    
    users[*numUsers].wrong_pass_count=0;
    users[*numUsers].wrong_security_count=0;

    (*numUsers)++;
    printf("Account created successfully!\nNow you can Login\n");
    //login()
}

int main() {
    User users[1000];
    int numUsers = 3;
    
    strcpy(users[0].first_name,"VINAY");
    strcpy(users[0].last_name,"G");
    strcpy(users[0].username,"VINAY656");
    strcpy(users[0].password,"VINAY@234");
    strcpy(users[0].phone,"9865");
    strcpy(users[0].email,"VINAY@gmail.com");
    strcpy(users[0].security_one,"dance");
    strcpy(users[0].security_two,"vijay");
    users[0].wrong_pass_count=0;
    users[0].wrong_security_count=0;
    
    
    strcpy(users[1].first_name,"SERAN");
    strcpy(users[1].last_name,"P");
    strcpy(users[1].username,"seran126");
    strcpy(users[1].password,"seran3@234");
    strcpy(users[1].phone,"9123");
    strcpy(users[1].email,"seran@gmail.com");
    strcpy(users[1].security_one,"sing");
    strcpy(users[1].security_two,"tesla");
    users[0].wrong_pass_count=0;
    users[0].wrong_security_count=0;
    
    strcpy(users[2].first_name,"PARITHI");
    strcpy(users[2].last_name,"A");
    strcpy(users[2].username,"parithi123");
    strcpy(users[2].password,"parotji@234");
    strcpy(users[2].phone,"6754");
    strcpy(users[2].email,"parithi@gmail.com");
    strcpy(users[2].security_one,"chess");
    strcpy(users[2].security_two,"musk");
    users[0].wrong_pass_count=0;
    users[0].wrong_security_count=0;

    printf("=== Signup Page ===\n\n\n");

    signUp(users, &numUsers);
    // printf("%s\n",users[3].username);
    // printf("%s\n",users[3].email);
    // printf("%s"\n,users[3].phone);
    // printf("%s"\n,users[3].password);
    // printf("%s"\n,users[3].security_one);
    // printf("%s"\n,users[3].security_two);

    return 0;
}