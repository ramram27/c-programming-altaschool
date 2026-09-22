#include <stdio.h>

int main() {

    float balance=5000;
    float amount;
    int chioce;

    do{
        printf("1. Check Balance \n");
        printf("2. Deposit");
        printf("3. Withdraw");
        printf("4. Exit")

        printf("Enter your choice");
        scanf("%d",&chioce);
        switch (chioce)
        {
        case 1:
             printf("%.2f",balance);
            break;
        case 2:
             printf("Enter a Deposit amount");
             scanf("%f",&amount);
             if(amount > 0){
                balance = amount + balance;
                printf("%.2f",balance);
             }else{
                printf("invalid amount %.2f",amount)
             }
             break;
        case 3:
               printf("Enter a Withdraw amount\n");
               scanf("%f",&amount);
               if(amount > 0 && amount < balance) {
                balance = balance - amount;
                printf("%.2f\n", balance);
               }else{
                printf("invalid amount %.2f",amount)
               }
               break;
        case 4: 
              printf("Thank you for using ATM\n");
        default:
          printf("Invalid choice");
            break;
        }
    }while(chioce != 4)
    return 0;
}