#include <stdio.h>

int main() {
    int balance = 1000;
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int num_of_transactions = 7;
    int to_be_processed[100];
    int num_of_unprocessed = 0;

    printf("Starting balance: %d AED\n", balance);

    for (int i = 0; i < num_of_transactions; i++) {
        int transaction = transactions[i];
        
        
        if (transaction < 0 && balance + transaction < 0) {
            printf("Invalid transaction %d: %d current balance %d \n", i + 1, transaction, balance);
            to_be_processed[num_of_unprocessed++] = transaction;
            continue;
        }
        balance += transaction;

        if (balance == 0) {
            printf("Balance is zero after transaction %d. No further transactions will be processed. \n", i + 1);
            to_be_processed[num_of_unprocessed++] = transaction;
            break;
        }

        printf("Processed transaction %d: %d , new balance: %d AED \n", i + 1, transaction, balance);
    }

    printf("Final balance: %d \n", balance);
    
    if (num_of_unprocessed> 0) {
        printf("Unprocessed transactions: ");
        for (int i = 0; i < num_of_unprocessed; i++) {
            printf("%d ", to_be_processed[i]);
        }
    } else {
        printf("All transactions processed successfully.\n");
    }

    return 0;
}
