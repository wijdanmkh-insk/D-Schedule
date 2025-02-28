#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user{
    char name[100];
    char username[100];
    char password[100];
    char date[20];
    int attendance;
    int charge;
    int balance;
}user;

//UNIVERSAL FUNCTION
void main_menu();
void sort(user *users, int max);


// ADMIN OR EVALUATOR
void signin_admin(); //
void menu_admin(); //
void attendance_check();
void give_charge();
void see_users();
void delete_users();

//USER
void signup_signin_user();
void menu_user(char *username, char *name);
void change_password(char *username, char *name);
void check_balance(char *username, char *name);
void seek_charges(char *username, char *name);
void delete_charges(char *username, char *name);

//FILE HANDLING
FILE* data_file;
FILE *attendance_file;
FILE* charge_file;

int main(){
    main_menu();
}
//UNIVERSAL FUNCTIONS
void main_menu(){
    printf("================ MAIN MENU ===================\n");
    printf("Hello! Choose the role to use the app :\n");
    printf("1. Admin\n");
    printf("2. Employees\n");
    printf("choose : "); int choose; scanf("%d", &choose); getchar();

    if(choose == 1){
        signin_admin();
    }else{
        if(choose == 2){
            signup_signin_user();
        }else{
            printf("wrong menu!");
            main_menu();
        }
    }

}

//================================================================================
//USER MENU
void signup_signin_user() {
    user data;
    user find;
    FILE *data_file;

    printf("=========== MENU USER ============\n");
    printf("1. Sign Up\n2. Sign In\nChoose menu : ");
    int choose;
    scanf("%d", &choose);
    getchar();

    if (choose == 1) {  // Sign Up
        data_file = fopen("data_user.dat", "ab");
        if (data_file == NULL) {
            printf("Error: Unable to open file for saving user data.\n");
            return;
        }

        user signup_user;

        printf("================= SIGN UP MENU ====================\n");
        printf("Hello, guest! Before we start, let's sign you up!\n");
        printf("Insert a few details to get going:\n");
        printf("Name      : "); gets(signup_user.name);
        printf("Username  : "); gets(signup_user.username);
        printf("Password  : "); gets(signup_user.password);
        signup_user.balance = 0;
        signup_user.charge = 0;

        if (fwrite(&signup_user, sizeof(signup_user), 1, data_file) != 0) {
            printf("Data saved successfully!\n");
        } else {
            printf("Failed to save data! Try again or contact the administrator.\n");
        }

        fclose(data_file);

        printf("Press any key to continue...\n");
        getchar();
        main_menu();

    } else if (choose == 2) {  // Sign In
        data_file = fopen("data_user.dat", "rb");
        if (data_file == NULL) {
            printf("No user data found! Please sign up first.\n");
            printf("Press any key to return to the main menu...\n");
            getchar();
            main_menu();
            return;
        }

        int found = 0;

        for (int trial = 3; trial > 0; --trial) {
            printf("================ USER LOGIN ================\n");
            printf("Before login, please input a few details to begin:\n");
            printf("Username : "); gets(data.username);
            printf("Password : "); gets(data.password);

            rewind(data_file);  // Reset file pointer to the start
            while (fread(&find, sizeof(find), 1, data_file) == 1) {  
                if (strcmp(data.username, find.username) == 0 && strcmp(data.password, find.password) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                fclose(data_file);  // Close only after checking all users
                printf("Login successful! Press any key to continue...\n");
                getchar();
                menu_user(find.username, find.name);
                return;
            } else {
                printf("Wrong username or password! Remaining attempts: %d\n", trial - 1);
            }

            if (trial == 1) {
                printf("Login failed! Press any key to return to the main menu...\n");
                getchar();
                main_menu();
            }
        }

        fclose(data_file);
    }
}


void menu_user(char *username, char *name){
    printf("============== USER MENU =============\n");
    printf("1. Check for balance\n2. Change Password\n3. See Charges\n4. Leaderboards\n5. Pay Charge\n6. Log Out\n7. Exit\nChoose : "); int choose; scanf("%d", &choose); getchar();

    switch(choose){
        case 1:
            check_balance(username, name);
            break;
        case 2:
            change_password(username, name);
            break;
        case 3:
            seek_charges(username, name);
            break;
        case 4:
            see_users(username, name);
            break;
        case 5: 
            delete_charges(username, name);
            break;
        case 6:
            main_menu();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Wrong choice! Try again!");
            menu_user(username, name);
    }
}

void check_balance(char *username, char *name){
    user check;
    
    FILE *user_data;
    user_data = fopen("data_user.dat", "rb");

    printf("============== BALANCE CHECK =============\n");
    printf("Hello, %s! Here's your balance/salary you get this month :\n", name);
    
    while(fread(&check, sizeof(check), 1, user_data) != 0){
        if(strcmp(check.username, username)==0){
            printf("Name     : %s\n", check.name);
            printf("Balance  : Rp%d", check.balance);
        }
    }

    fclose(user_data);
    printf("\nPress any key to continue...");
    getchar();

    menu_user(username, name);
}

void change_password(char *username, char *name){
   user change, find;
   int found;
   char password[100];

   FILE* user_data;
   user_data = fopen("data_user.dat", "rb+");

   printf("============= CHANGE PASSWORD ===========\n");
   printf("Enter your password : "); gets(password);

   while(fread(&find, sizeof(find), 1, user_data)!= 0){
       if(strcmp(find.username, username) == 0){
           strcpy(find.password, password);
           fseek(user_data, -sizeof(find), SEEK_CUR);
           if(fwrite(&find, sizeof(find), 1, user_data) == 1){
               found = 1;
               printf("Password has successfully changed!\n");
               break;
           }
       }
   }

   fclose(user_data);

   if(!found){
       printf("Failed to change password\n");
   }

   printf("Press any key to continue..."); getchar();
   menu_user(username, name);
}

void delete_charges(char *username, char *name) {
    FILE *user_data, *temp_data;
    user read;
    int found = 0;

    printf("============= DELETE CHARGE =============\n");

    user_data = fopen("data_user.dat", "rb");
    if (user_data == NULL) {
        printf("Error: User data file not found.\n");
        return;
    }

    temp_data = fopen("temp.dat", "wb");
    if (temp_data == NULL) {
        printf("Error: Unable to create temp file.\n");
        fclose(user_data);
        return;
    }

    while (fread(&read, sizeof(read), 1, user_data)) {
        if (strcmp(read.username, username) == 0) {
            found = 1;
            printf("Current Balance: Rp%d\n", read.balance);
            printf("Current Charge: Rp%d\n", read.charge);

            if (read.charge > 0) {
                read.balance -= read.charge; // Deduct charge from balance
                if (read.balance < 0) read.balance = 0; // Prevent negative balance
                read.charge = 0; // Reset charge

                printf("Charge deleted. Updated Balance: Rp%d\n", read.balance);
            } else {
                printf("No charge to delete.\n");
            }
        }
        fwrite(&read, sizeof(read), 1, temp_data);
    }

    fclose(user_data);
    fclose(temp_data);

    if (found) {
        remove("data_user.dat");
        rename("temp.dat", "data_user.dat");
        printf("Charge deletion successful!\n");
    } else {
        remove("temp.dat");
        printf("User not found.\n");
    }

    printf("Press any key to continue...");
    getchar();
    menu_user(username, name);
}

void seek_charges(char *username, char *name) {
    FILE *user_data;
    user check;
    int found = 0, choice;

    printf("============= SEEK CHARGES =============\n");

    user_data = fopen("data_user.dat", "rb");
    if (user_data == NULL) {
        printf("Error: User data file not found.\n");
        return;
    }

    while (fread(&check, sizeof(check), 1, user_data)) {
        if (strcmp(check.username, username) == 0) {
            found = 1;
            printf("Hello, %s!\n", name);
            printf("Current Charge: Rp%d\n", check.charge);
            printf("Current Balance: Rp%d\n", check.balance);
            break;
        }
    }

    fclose(user_data);

    if (!found) {
        printf("User not found.\n");
    } else {
        printf("Do you want to delete the charge?\n1. Yes\n2. No\nChoose: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 1) {
            delete_charges(username, name);
        } else {
            printf("Charge not deleted.\n");
        }
    }

    printf("Press any key to continue...");
    getchar();
}


//ADMIN MENU
void signin_admin(){
    user data;

    for(int trial = 3; trial > 0; --trial){
        if(trial > 0){
            printf("================ ADMIN LOGIN ================\n");
            printf("Before login, please input few informations to begin\n");
            printf("Username : "); gets(data.username);
            printf("Password : "); gets(data.password);

                if(strcmp(data.username, "admin")== 0 && strcmp(data.password, "admin") == 0){
                    printf("login success! press any key to continue..."); getchar();
                    system("cls");
                    menu_admin();
                }else{
                    printf("Remaining account input : %d\n", trial-1);
                    printf("wrong username or password! try again!\n");
                }
        }else{
            printf("login failed! press any key to continue..."); getchar();
            main_menu();
        }
    }
}

void menu_admin(){
    printf("============== ADMIN MENU =============\n");
    printf("1. Check Attendance\n2. Give Charge\n3. See User Lists\n4. Log Out\n5. Exit\nChoose : "); int choose; scanf("%d", &choose); getchar();

    switch(choose){
        case 1:
            attendance_check();
            break;
        case 2:
            give_charge();
            break;
        case 3:
            see_users();
            break;
        case 4:
            main_menu();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Wrong choice! Try again!");
            menu_admin();
    }
}

void attendance_check() {
    char search[100], date[20];
    struct user find;
    int found = 0, attendance_status;

    printf("================= ATTENDANCE CHECK =================\n");
    printf("Input the current date: "); gets(date);
    printf("Input the employee's name to check attendance: "); gets(search);

    attendance_file = fopen("user_attendance.dat", "rb+");
    if (attendance_file == NULL) {
        attendance_file = fopen("user_attendance.dat", "ab+");
    }

    while (fread(&find, sizeof(find), 1, attendance_file)) {
        if (strcmp(search, find.name) == 0 && strcmp(date, find.date) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Attendance for %s on %s is currently: %s\n", find.name, find.date, 
               find.attendance ? "Present" : "Absent");
        printf("Update attendance? Present (1) / Absent (0): ");
        scanf("%d", &attendance_status);
        getchar(); // Consume newline to avoid issues with gets()

        find.attendance = attendance_status;
        
        // Move file pointer back to overwrite the correct record
        fseek(attendance_file, -sizeof(find), SEEK_CUR);
        
        if (fwrite(&find, sizeof(find), 1, attendance_file) == 1) {
            printf("Data updated successfully!\n");
        } else {
            printf("Error updating data.\n");
        }
    } else {
        printf("User not found for the given date...\n");
    }

    printf("Press any key to continue..."); getchar();
    fclose(attendance_file);
    menu_admin();
}

void give_charge() {
    char search[100], date[20];
    struct user find;
    int found = 0, new_charge;

    printf("================= GIVE CHARGE =================\n");
    printf("Input the current date: "); gets(date);
    printf("Input the employee's name to update charge: "); gets(search);

    charge_file = fopen("user_charge.dat", "rb+");
    if (charge_file == NULL) {
        charge_file = fopen("user_charge.dat", "ab+");
    }

    while (fread(&find, sizeof(find), 1, charge_file)) {
        if (strcmp(search, find.name) == 0 && strcmp(date, find.date) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Current charge for %s on %s: %d\n", find.name, find.date, find.charge);
        printf("Enter new charge: ");
        scanf("%d", &new_charge);
        getchar(); // Consume newline to avoid issues with gets()

        find.charge = new_charge;

        // Move file pointer back to overwrite the correct record
        fseek(charge_file, -sizeof(find), SEEK_CUR);
        
        if (fwrite(&find, sizeof(find), 1, charge_file) == 1) {
            printf("Charge updated successfully!\n");
        } else {
            printf("Error updating charge.\n");
        }
    } else {
        printf("User not found for the given date...\n");
    }

    printf("Press any key to continue..."); getchar();
    fclose(charge_file);
    menu_admin();
}

void see_users(){
    FILE *user_data;

    user store[300];
    user read;
    int save_state = 0;
    user_data = fopen("data_user.dat", "rb");

    printf("================== CHECK USER DATA ================\n");
    printf("You can use this menu to check user data based on lowest\n");
    printf("and highest data so far to evaluate each employees that needs\n");
    printf("to get checked.\n\n");

    while(fread(&read, sizeof(read), 1, user_data) != 0){
        store[save_state] = read;
        save_state++;
    }

    sort(store, save_state);
    
    int choose;
    while(choose < 1 || choose > 2){
        printf("choose assorted data from :\n1. Lowest - highest\n2. Highest - Lowest\n Choose : "); scanf("%d", &choose); getchar();
        switch (choose) {
            case 1:
                printf("\nDisplaying data (Lowest to Highest):\n");
                for (int i = 0; i < save_state; i++) {
                    printf("ID: %d, Name: %s, Balance: %.2f\n",
                            i+1, store[i].name, store[i].balance);
                }
                break;

            case 2:
                printf("\nDisplaying data (Highest to Lowest):\n");
                for (int i = save_state - 1; i >= 0; i--) {
                    printf("ID: %d, Name: %s, Balance: %.2f\n",
                            i+1, store[i].name, store[i].balance);
                }
                break;

            default:
                printf("Invalid choice. Please choose 1 or 2.\n");
                break;
        }
    }

    fclose(user_data);
    printf("press any key to continue..."); getchar();
    menu_admin();
}

void delete_users() {
    FILE *user_data, *temp_data;
    user read;
    char target_name[100];
    int found = 0;

    printf("================= DELETE USER =================\n");
    printf("Enter the name of the user to delete: "); gets(target_name);

    user_data = fopen("data_user.dat", "rb");
    if (user_data == NULL) {
        printf("Error: User data file not found.\n");
        return;
    }

    temp_data = fopen("temp.dat", "wb");
    if (temp_data == NULL) {
        printf("Error: Unable to create temp file.\n");
        fclose(user_data);
        return;
    }

    while (fread(&read, sizeof(read), 1, user_data)) {
        if (strcmp(read.name, target_name) == 0) {
            found = 1; // Mark as found but don't write to temp file
        } else {
            fwrite(&read, sizeof(read), 1, temp_data);
        }
    }

    fclose(user_data);
    fclose(temp_data);

    if (found) {
        remove("data_user.dat");     // Delete original file
        rename("temp.dat", "data_user.dat"); // Rename temp file
        printf("User '%s' deleted successfully!\n", target_name);
    } else {
        remove("temp.dat"); // No need to keep temp file if no changes were made
        printf("User '%s' not found.\n", target_name);
    }

    printf("Press any key to continue..."); getchar();
    menu_admin();
}


void sort(struct user *users, int max) {
    struct user temp;
    for (int i = 0; i < max - 1; i++) {
        for (int j = 0; j < max - i - 1; j++) {
            if (users[j].balance > users[j + 1].balance){
                temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
}
