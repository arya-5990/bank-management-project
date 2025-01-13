#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include<conio.h>
int response, age;
float zero_balance = 0;
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
void create_account(FILE *fileptr) {
    char name[20];
    printf("Enter your full name: ");
    getchar(); 
    fgets(name, sizeof(name), stdin);
    size_t len = strlen(name);
    if (len > 0 && name[len - 1] == '\n') {
        name[len - 1] = '\0';
    }
    printf("Enter your age: ");
    scanf("%d", &age);
    if (age < 18 || age > 70) {
        printf("Sorry, you are not eligible to create a bank account.\n");
    } else {
        fprintf(fileptr, "%s %.2f\n", name, zero_balance); 
        printf("Account created successfully for %s with balance: %.2f\n", name, zero_balance);
    }
}
void login_account(FILE *fileptr) {
    char entered_name[20];
    int name_found = 0;
    float user_balance = 0.0;
    printf("Enter your name: ");
    getchar(); 
    fgets(entered_name, sizeof(entered_name), stdin);
    size_t len = strlen(entered_name);
    if (len > 0 && entered_name[len - 1] == '\n') {
        entered_name[len - 1] = '\0';
    }
    to_lowercase(entered_name); 
    rewind(fileptr); 
    char line[50];
    while (fgets(line, sizeof(line), fileptr)) {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        char stored_name[20];
        float balance;
        sscanf(line, "%[^0-9] %f", stored_name, &balance); 
        len = strlen(stored_name);
        while (len > 0 && isspace(stored_name[len - 1])) {
            stored_name[len - 1] = '\0';
            len--;
        }
        to_lowercase(stored_name); 
        if (strcmp(entered_name, stored_name) == 0) {
            name_found = 1;
            user_balance = balance;
            break;
        }
    }
    if (name_found) {
        printf("Welcome back, %s! Your current balance is: %.2f\n", entered_name, user_balance);
        login:
        printf("(1) Add Money From Credit Card\n(2) Make a Transaction\n(3) Exit Portal\n");
        int action;
        scanf("%d", &action);
        if (action == 1) {
    float add_amount;
    printf("Enter amount to add: ");
    scanf("%f", &add_amount);
    user_balance += add_amount;
    printf("New balance: %.2f\n", user_balance);

    // Update the file with the new balance
    FILE *tempfile = fopen("temp.txt", "w");
    rewind(fileptr);
    while (fgets(line, sizeof(line), fileptr)) {
        char stored_name[20];
        float balance;
        sscanf(line, "%[^0-9] %f", stored_name, &balance);
        len = strlen(stored_name);
        while (len > 0 && isspace(stored_name[len - 1])) {
            stored_name[len - 1] = '\0';
            len--;
        }
        to_lowercase(stored_name);
        if (strcmp(entered_name, stored_name) == 0) {
            fprintf(tempfile, "%s %.2f\n", stored_name, user_balance);
        } else {
            fprintf(tempfile, "%s %.2f\n", stored_name, balance);
        }
    }
    fclose(tempfile);
    fclose(fileptr);
    remove("names.txt");
    rename("temp.txt", "names.txt");
    goto login;
    return; // Exit after successfully updating the file
}
    else if (action == 2) {
            char recipient_name[20];
            printf("Enter the name of the user to transfer money to: ");
            getchar(); 
            fgets(recipient_name, sizeof(recipient_name), stdin);
            len = strlen(recipient_name);
            if (len > 0 && recipient_name[len - 1] == '\n') {
                recipient_name[len - 1] = '\0';
            }
            to_lowercase(recipient_name);
            rewind(fileptr);
            int recipient_found = 0;
            float recipient_balance = 0.0;
            while (fgets(line, sizeof(line), fileptr)) {
                char stored_name[20];
                float balance;
                sscanf(line, "%[^0-9] %f", stored_name, &balance);
                len = strlen(stored_name);
                while (len > 0 && isspace(stored_name[len - 1])) {
                    stored_name[len - 1] = '\0';
                    len--;
                }
                to_lowercase(stored_name);
                if (strcmp(recipient_name, stored_name) == 0) {
                    recipient_found = 1;
                    recipient_balance = balance;
                    break;
                }
            }
            if (!recipient_found) {
                printf("User '%s' is not registered.\n", recipient_name);
                
            } else {
                float transaction_amount;
                printf("Enter transaction amount: ");
                scanf("%f", &transaction_amount);
                if (transaction_amount > user_balance) {
                    printf("Insufficient funds!\n");
                } else {
                    user_balance -= transaction_amount;
                    recipient_balance += transaction_amount;
                    printf("Transaction successful. Your new balance: %.2f\n", user_balance);
                    FILE *tempfile = fopen("temp.txt", "w");
                    rewind(fileptr);
                    while (fgets(line, sizeof(line), fileptr)) {
                        char stored_name[20];
                        float balance;
                        sscanf(line, "%[^0-9] %f", stored_name, &balance);
                        len = strlen(stored_name);
                        while (len > 0 && isspace(stored_name[len - 1])) {
                            stored_name[len - 1] = '\0';
                            len--;
                        }
                        to_lowercase(stored_name);
                        if (strcmp(entered_name, stored_name) == 0) {
                            fprintf(tempfile, "%s %.2f\n", stored_name, user_balance);
                        } else if (strcmp(recipient_name, stored_name) == 0) {
                            fprintf(tempfile, "%s %.2f\n", stored_name, recipient_balance);
                        } else {
                            fprintf(tempfile, "%s %.2f\n", stored_name, balance);
                        }
                    }
                    fclose(tempfile);
                    fclose(fileptr);
                    remove("names.txt");
                    rename("temp.txt", "names.txt");
                    // goto login;
                    return; // Exit after successful transaction
                }
            }
        }
        fclose(fileptr);
    } else {
        printf("Name not found. Please check your details or create a new account.\n");
        // goto exit;
    }
}

int main() {
    int existing_user;
    FILE *fileptr;
    while (1) {
        fileptr = fopen("names.txt", "a+");
        if (fileptr == NULL) {
            printf("Error opening the file. Please ensure 'names.txt' exists and has the correct permissions.\n");
            return 1; 
        }
        printf("Are you an existing user?\n1: Yes 0: No\n");
        if (scanf("%d", &existing_user) != 1) {
            printf("Invalid input. Please enter 1 or 0.\n");
            while (getchar() != '\n');   
            continue;
        }
        if (existing_user == 0) {
            printf("Do you want to create an account?\n1: Yes 0: No\n");
            if (scanf("%d", &response) != 1) {
                printf("Invalid input. Please enter 1 or 0.\n");
                while (getchar() != '\n'); 
                continue;
            }
            if (response == 1) {
                create_account(fileptr);
            }
            fclose(fileptr);
        } else if (existing_user == 1) {
            printf("Select action:\n1. Login to account\n2. Exit portal\n");
            int login_action;
            if (scanf("%d", &login_action) != 1) {
                printf("Invalid input. Please enter 1 or 2.\n");
                while (getchar() != '\n'); 
                continue;
            }
            if (login_action == 1) {
                login_account(fileptr);
            } else if (login_action == 2) {
                exit:
                fclose(fileptr);
                printf("Exiting the portal. Goodbye!\n");
                break; 
            } else {
                printf("Invalid option. Please try again.\n");
            }
        } else {
            printf("Invalid option. Please enter 1 or 0.\n");
        }
    }
    getch();
    return 0;
}