#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define ESPRESSO_BEANS_Minimum 8
#define ESPRESSO_WATER_Minimum 30


#define CAPPUCCINO_BEANS_Minimum 8
#define CAPPUCCINO_WATER_Minimum 30
#define CAPPUCCINO_MILK_Minimum 70


#define MOCHA_BEANS_Minimum 8
#define MOCHA_WATER_Minimum 39
#define MOCHA_MILK_Minimum 160
#define MOCHA_SYRUP_Minimum 30

//-------------------------------------prices of drinks---------------------------
double CAPPUCCINO_PRICE = 4.5;
double Mocha_PRICE = 5.5;
double Espresso_PRICE = 3.5;
//----------------------------------------admin password--------------
#define ADMIN_PASSWORD 123
//--------------------------------------espresso ingredients-----------------------------------------
int esp_beans = 80;
//------------------------------------mocha ingredients-------------------------
int moc_beans = 0;
int moc_syrup = 0;
//--------------------------------------cappucino ingredients------------
int Cap_beans = 80;
//---------------------------------general ingredients--------------------------
int water_available = 0;
int milk_available= 0;
//----------------------------total money from sale---------------------------
float total_amount = 0;



//----------------------Admin Control-----------------------------

int Admin_access(){
    bool loop_end = true;
do{
    int Admin_access_choice;
    printf("\nDisplay Quantities remaining : 1\n ");
    printf("Replenish stock : 2\n ");
    printf("Change coffee price : 3\n ");
    printf("Exit admin mode : 4\n");
    scanf("%d", &Admin_access_choice);
    if (Admin_access_choice==1)
   {
     printf("espresso beans remaining : %d \n",esp_beans);
    printf("Cappucino beans remaining : %d \n", Cap_beans);
    printf("mocha beans remaining : %d \n",moc_beans);
    printf("chocolate syrup remaining : %d \n",moc_syrup);
    printf("Milk remaining : %d \n",milk_available);
    printf("Water remaining : %d \n",water_available);
    printf("Total sale : \n",total_amount);
   }
   else if (Admin_access_choice==2)
   {
     int replenish_choice;
    printf("espresso beans : 1 \n");
    printf("Cappucino beans : 2  \n");
    printf("mocha beans : 3  \n");
    printf("chocolate  : 4 \n");
    printf("Milk  : 5\n");
    printf("Water  : 6\n");
    printf("Enter ur choice to replenish");
    scanf("%d",&replenish_choice);
   if (replenish_choice==1)
   {esp_beans = 80;
    printf("espresso beans replenished to %d \n",esp_beans);
   }
   else if (replenish_choice==2)
   {Cap_beans = 80;
    printf("cappuchino beans replenished to %d \n",Cap_beans);
   }
    else if (replenish_choice==3)
   {moc_beans = 80;
    printf("mocha beans replenished to %d \n",moc_beans);
   }
 else if (replenish_choice==4)
   {moc_syrup = 300;
    printf("mocha syrup replenished to 300 ml %d \n",moc_syrup);
   }
 else if (replenish_choice==5)
   {milk_available = 2000;
    printf("milk replenished to %d \n",milk_available);
   }
 else if (replenish_choice==6)
   {water_available = 3000;
    printf("water replenished to %d \n",water_available);
   }
   }
   else if (Admin_access_choice==3)
   {
    double price_set;
   int choose_coffee_price_change;
   printf("Choose which price to change : \n");
   printf("Espresso : 1 \n");
   printf("Cappuchino : 2 \n");
   printf("mocha : 3 \n");
   scanf("%d",&choose_coffee_price_change);
   printf("What price to set : \n");
   scanf("%f",&price_set);
   if (choose_coffee_price_change == 1)
   {Espresso_PRICE=price_set;
    printf("chenged price of espresso to : %f",price_set);
   }
   else if (choose_coffee_price_change == 2)
   {CAPPUCCINO_PRICE = price_set;
    printf("chenged price of cappuchino to : %f",price_set);
   }
    else if (choose_coffee_price_change == 3)
   {Mocha_PRICE=price_set;
    printf("changed price of mocha to : %f",price_set);
   }}
   else if(Admin_access_choice==4){
    loop_end = false;
    
   }
}while (loop_end);
}



//----------------------check ingredients-------------------
int check_ingredients_cap(){
   int status_cap;
   if (Cap_beans>=CAPPUCCINO_BEANS_Minimum&&milk_available>=CAPPUCCINO_MILK_Minimum&&water_available>=CAPPUCCINO_WATER_Minimum)
   {
    status_cap = 1;
   }
   else{
    status_cap = 0;
   }
return status_cap;
}
int check_ingredients_esp(){
     int status_esp;
   if (esp_beans>=ESPRESSO_BEANS_Minimum&&water_available>=ESPRESSO_WATER_Minimum)
   {
    status_esp = 1;
   }
   else{
    status_esp = 0;
   }
return status_esp;
}
int check_ingredients_moc(){
int status_moc;
   if (moc_beans>=MOCHA_BEANS_Minimum&&moc_syrup>=MOCHA_SYRUP_Minimum&&
   milk_available>=MOCHA_MILK_Minimum&&water_available>=MOCHA_WATER_Minimum)
   {
    status_moc = 1;
   }
   else{
    status_moc = 0;
   }
return status_moc;

}

