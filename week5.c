#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
int moc_beans = 80;
int moc_syrup = 300;
//--------------------------------------cappucino ingredients------------
int Cap_beans = 80;
//---------------------------------general ingredients--------------------------
int water_available = 2000;
int milk_available= 2000;
//----------------------------total money from sale---------------------------
double total_amount ;



//----------------------Admin Control-----------------------------

int Admin_access(){
    bool loop_end = true;
do{
    int Admin_access_choice;
    int admin_choose_money;
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
    printf("Total sale : \n %.2f",total_amount);
    printf("\n Do you want to withdraw the money and reset it to 0?? \n");
    printf(" if yes choose 1 to not reset select 0\n");
    scanf("%d",&admin_choose_money);
    if (admin_choose_money==1)
    {
      printf(" %f has been withdrawn and has been reset to 0 in the machine \n",total_amount);
      total_amount=0;
    }
    else
    {
      printf("no reset \n");
    }
    
    

   }
   else if (Admin_access_choice==2)
   {
    int replenish_choice;
    
    
    srand(time(0)); // Seed the random number generator

    printf("espresso beans : 1 \n");
    printf("Cappuccino beans : 2  \n");
    printf("mocha beans : 3  \n");
    printf("chocolate  : 4 \n");
    printf("Milk  : 5\n");
    printf("Water  : 6\n");
    printf("Enter your choice to replenish: ");
    scanf("%d", &replenish_choice);

    if (replenish_choice == 1) {
        esp_beans = 10 + rand() % 90; // Random value between 10 and 99
        printf("espresso beans replenished to %d\n", esp_beans);
    } else if (replenish_choice == 2) {
        Cap_beans = 10 + rand() % 90; // Random value between 10 and 99
        printf("cappuccino beans replenished to %d\n", Cap_beans);
    } else if (replenish_choice == 3) {
        moc_beans = 10 + rand() % 90; // Random value between 10 and 99
        printf("mocha beans replenished to %d\n", moc_beans);
    } else if (replenish_choice == 4) {
        moc_syrup = 100 + rand() % 201; // Random value between 100 and 300
        printf("mocha syrup replenished to %d ml\n", moc_syrup);
    } else if (replenish_choice == 5) {
        milk_available = 1000 + rand() % 2001; // Random value between 1000 and 3000
        printf("milk replenished to %d ml\n", milk_available);
    } else if (replenish_choice == 6) {
        water_available = 1000 + rand() % 2001; // Random value between 1000 and 3000
        printf("water replenished to %d ml\n", water_available);
    } else {
        printf("Invalid choice\n");
    }

    return 0;
}

   
   else if (Admin_access_choice==3)
   {
    float price_set;
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
    printf("changed price of espresso to : %.2f",Espresso_PRICE);
   }
   else if (choose_coffee_price_change == 2)
   {CAPPUCCINO_PRICE = price_set;
    printf("changed price of cappuchino to : %.2f",CAPPUCCINO_PRICE);
   }
    else if (choose_coffee_price_change == 3)
   {Mocha_PRICE=price_set;
    printf("changed price of mocha to : %.2f",Mocha_PRICE);
   }}
   else {
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
//----------------------Coffee Choice--------------------------
int Order_cofee(int check_ingredients_cap,int check_ingredients_esp,int check_ingredients_moc){
   int Coffee_choice;
   if(check_ingredients_cap==1&&check_ingredients_esp==1&&check_ingredients_moc==1){
   
   printf("Please choose the type of coffee\n ");
   printf("0 to exit \n");
   printf("1.Espresso  -  %.2f\n",Espresso_PRICE);
   printf("2.Cappucino  -  %.2f\n",CAPPUCCINO_PRICE);
   printf("3.Mocha  -  %.2f\n",Mocha_PRICE);
   scanf("%d",&Coffee_choice);
    return Coffee_choice ;
    
}
else if (check_ingredients_cap==0&&check_ingredients_esp==0&&check_ingredients_moc==0)
{  
   printf("Please choose the type of coffee\n ");
   printf("0 to exit ");
   printf("Unavailable\n");
   printf("Unavailable\n");
   printf("Unavailable\n");
   Coffee_choice = 0;
   return Coffee_choice;
}
else if (check_ingredients_cap==0&&check_ingredients_esp==0&&check_ingredients_moc==1)
{
   printf("Please choose the type of coffee\n ");
   printf("0 to exit ");
   printf("Unavailable\n");
   printf("Unavailable\n");
   printf("3.Mocha  -  %f\n",Mocha_PRICE);
   scanf("%d",&Coffee_choice);
    return Coffee_choice ;

}
else if (check_ingredients_cap==0&&check_ingredients_esp==1&&check_ingredients_moc==0)
{

   printf("Please choose the type of coffee\n ");
   printf("0 to exit ");
   printf("1.Espresso  -  %f\n",Espresso_PRICE);
   printf("Unavailable\n");
   printf("Unavailable\n");
   scanf("%d",&Coffee_choice);
    return Coffee_choice ;
}
else if (check_ingredients_cap==0&&check_ingredients_esp==1&&check_ingredients_moc==1)
{

    printf("Please choose the type of coffee\n ");
    printf("0 to exit ");
   printf("1.Espresso  -  %f\n",Espresso_PRICE);
   printf("Unavailable\n");
   printf("3.Mocha  -  %f\n",Mocha_PRICE);
   scanf("%d",&Coffee_choice);
    return Coffee_choice ;
}
else if (check_ingredients_cap==1&&check_ingredients_esp==0&&check_ingredients_moc==0)
{
    printf("Please choose the type of coffee\n ");
    printf("0 to exit ");
   printf("Unavailable\n");
   printf("2.Cappucino  -  %f\n",CAPPUCCINO_PRICE);
   printf("Unavailable\n");
   scanf("%d",&Coffee_choice);
    return Coffee_choice ;

}
else if (check_ingredients_cap==1&&check_ingredients_esp==0&&check_ingredients_moc==1)
{
    printf("Please choose the type of coffee\n ");
    printf("0 to exit ");
   printf("Unavailable\n");
   printf("2.Cappucino  -  %f\n",CAPPUCCINO_PRICE);
   printf("3.Mocha  -  %f\n",Mocha_PRICE);
   scanf("%d",&Coffee_choice);
    return Coffee_choice ;

}
else if (check_ingredients_cap==1&&check_ingredients_esp==1&&check_ingredients_moc==0)
{
     printf("Please choose the type of coffee\n ");
   printf("0 to exit ");
   printf("1.Espresso  -  %f\n",Espresso_PRICE);
   printf("2.Cappucino  -  %f\n",CAPPUCCINO_PRICE);
   printf("Unavailable\n");
   scanf("%d",&Coffee_choice);
    return Coffee_choice ;

}

}
//--------------order confirm-----------
int order_confrim(int order_var1_confirm ){
    float order_var2_confirm;
    float order_var3_confirm;
    if (order_var1_confirm==1)
    {
        printf("You chose espresso - %.2f\n",Espresso_PRICE);
        printf("press 1 to confirm\n");
        order_var2_confirm = Espresso_PRICE;
    }
    else if (order_var1_confirm==2)
    {
        printf("You chose Cappucino - %.2f\n",CAPPUCCINO_PRICE);
        printf("press 1 to confirm\n");
        order_var2_confirm = CAPPUCCINO_PRICE;
    }
     else if (order_var1_confirm==3)
    {
        printf("You chose Mocha  -  %.2f\n",Mocha_PRICE);
        printf("press 1 to confirm\n");
        order_var2_confirm = Mocha_PRICE;
    }
    else if (order_var1_confirm==0)
    {
        exit(0);
    }
    
    scanf("%f",&order_var3_confirm);
    if (order_var3_confirm==1)
    {
      printf("\n order confirmed pleas pay \n");
    }
    else
    {
      printf("\n cancelling order \n");
      Order_cofee(check_ingredients_cap(),check_ingredients_esp(),check_ingredients_moc());
    }
    

    return order_var2_confirm;
    
} 

//---------------------------------pay for coffee------------------------
 int pay_for_coffee(float pay_var_coffee) {
    float coin_entered;
    if (pay_var_coffee==0)
    {
      exit(0);
    }
    else{
      if (pay_var_coffee==Espresso_PRICE)
      {
        esp_beans=esp_beans-ESPRESSO_BEANS_Minimum;
        water_available=water_available-ESPRESSO_WATER_Minimum;
      }
      else if (pay_var_coffee==CAPPUCCINO_PRICE)
      {
        Cap_beans=Cap_beans-CAPPUCCINO_BEANS_Minimum;
        milk_available=milk_available-CAPPUCCINO_MILK_Minimum;
        water_available=water_available-CAPPUCCINO_WATER_Minimum;
      }
      else if (pay_var_coffee==Mocha_PRICE)
      {
        moc_beans=moc_beans-MOCHA_BEANS_Minimum;
        moc_syrup=moc_syrup-MOCHA_SYRUP_Minimum;
        water_available=water_available-MOCHA_WATER_Minimum;
        milk_available=milk_available-MOCHA_MILK_Minimum;
      }
      
      
    do {
        printf("pay using 1 or 0.5 coins \n");
        scanf("%f", &coin_entered);

        if (coin_entered == 0.5 || coin_entered == 1) {
            pay_var_coffee = pay_var_coffee - coin_entered;
            total_amount = total_amount+coin_entered;
            if (pay_var_coffee > 0) {
                printf("%.2f remaining\n", pay_var_coffee);
            } else {
                printf("Coffee fully paid. \n");
              printf(" \n\n coffee dispensed \n\n");
              
              
              }
        } else {
            printf("wrong coin, please use 1 or 0.5\n");
        }
    } while (pay_var_coffee > 0);}

    
    return 0;
}

    
//----------------------Main menu--------------------------
int menu(){
   int first_choice;
   printf("Please choose one of the following by entering 1,2 or 3 : ");
   printf("\nOrder a coffee  :  1\n");
   printf("Admin Mode  :  2 \n");
   printf("End application  :  3\n");
   scanf("%d",&first_choice);
   if (first_choice==1)
   {
    pay_for_coffee(order_confrim(Order_cofee(check_ingredients_cap(),check_ingredients_esp(),check_ingredients_moc())));
   }
   else if (first_choice==2)
   { int password_check;
      printf("enter the password : \n");
      scanf("%d",&password_check);
      if (password_check==ADMIN_PASSWORD){
    
           printf("\ncorrect password \n");
           Admin_access();
       }
       else{
        printf("wrong password \n");
       }
    }
   else if (first_choice==3)
   {
    exit(0);}
   
   
return 0;
}
  

int main()
{ 
  while (true)
  {
    menu();
  }

    
}
