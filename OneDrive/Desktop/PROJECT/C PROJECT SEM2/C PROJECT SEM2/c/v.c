#include <stdio.h>
struct distance{
   float latitude;
   float longitude;
}var2;
struct starters{
   char str_name[50];
   int price;
}stt;

struct main_c{
   char main_name[50];
   int price;
}mn;

struct desert{
   char desert_name[50];
   int price;
}dt;

struct beverage{
   char bvg_name[50];
   int price;
}bvg;
struct food{
   struct starters;
   struct main_c;
   struct desert;
   struct beverage;
}var3;
struct hotel{
   char hotel_name[100];
   struct distance;
   float rating;
   struct food;
   int dicount;
   char v_n[20];
}var1;


int main(){
   int choice;
    FILE *file;
    printf("Enter  hotel name:\n ");
    fgets(var1.hotel_name, sizeof(var1.hotel_name), stdin);
    // Remove newline character from the string
    var1.hotel_name[strcspn(var1.hotel_name, "\n")] = 0;

    printf("Enter latitude:\n ");
    scanf("%f", &var2.var1.latitude);

    printf("Enter longitude:\n ");
    scanf("%f", &var2.var1.longitude);

   printf("Enter  hotel rating:\n ");
   scanf("%f", &var1.rating);

   printf("Enter 1.to add starter\n 2.to add main course\n 3.to add desert \n 4.to add beverages\n ");
   sacnf("%s",choice);
   if (choice==1){
      printf("Enter  starter name:\n ");
      fgets(stt.var1.str_name, sizeof(stt.var1.str_name), stdin);
    
      stt.var1.str_name[strcspn(stt.var1.str_name, "\n")] = 0;

      printf("Enter starter price:\n ");
      scanf("%d", &stt.var1.price);
   }
   else if (choice==2){
      printf("Enter main course name:\n ");
      fgets(mn.var1.main_name, sizeof(mn.var1.main_name), stdin);
    
      mn.var1.main_name[strcspn(mn.var1.main_name, "\n")] = 0;

      printf("Enter main course price:\n ");
      scanf("%d", &mn.var1.price);
   }
   else if (choice==3){
      printf("Enter desert name:\n ");
      fgets(dt.var1.desert_name, sizeof(dt.var1.desert_name), stdin);
    
      dt.var1.desert_name[strcspn(dt.var1.desert_name, "\n")] = 0;

      printf("Enter desert price:\n ");
      scanf("%d", &dt.var1.price);
   }

   else if (choice==4){
      printf("Enter beverage name:\n ");
      fgets(bvg.var1.bvg_name, sizeof(bvg.var1.bvg_name), stdin);
    
      bvg.var1.bvg_name[strcspn(bvg.var1.bvg_name, "\n")] = 0;

      printf("Enter beverage price:\n ");
      scanf("%d", &bvg.var1.price);
   }
   printf("Enter the discount:\n ");
   scanf("%f", &var1.discount);

   printf("Enter veg/non-veg:\n ");
   fgets(var1.v_n, sizeof(var1.v_n), stdin);
    // Remove newline character from the string
    var1.v_n[strcspn(var1.v_n, "\n")] = 0;
    // Open the file in binary write mode
    file = fopen("var1.dat", "wb");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write the structure to the file
    fwrite(&var1, sizeof(struct var1), 1, file);

    // Close the file
    fclose(file);

    printf("Data has been written to the file.\n");



   return 0;
}