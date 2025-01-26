#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user{
    char name[100];
    char username[100];
    char password[100];
    int balance;
}user;

//UNIVERSAL FUNCTION
void main_menu();

// ADMIN OR EVALUATOR
void signin_admin();
void menu_admin();

//USER
void signup_signin_user();
void menu_user();


int main(){
    main_menu();
}

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

void signup_signin_user(){
    FILE* data_file;
    user data;
    user find;

    printf("=========== MENU USER ============\n");
    printf("1. Sign Up\n2. Sign In\nChoose menu : "); int choose; scanf("%d", &choose); getchar();

    if(choose == 1){
        data_file = fopen("data_user.dat", "ab");

        user signup_user;
        printf("================= SIGN UP MENU ====================\n");
        printf("Hello, guest! Before we start, let's sign you up!\n");
        printf("Insert few data to get going : ");
        printf("Name      : "); gets(signup_user.name);
        printf("Username  : "); gets(signup_user.username);
        printf("Password  : "); gets(signup_user.password);
        signup_user.balance = 0;

        size_t check = fwrite(&signup_user, sizeof(signup_user), 1, data_file);

        if(check != 0){
            printf("data saved successfully!\n");
        }else{
            printf("data failed to saved! try again or contact the administrator\n");
        }
        printf("press any key to continue...\n");
        getchar();
        main_menu();
    }else if(choose == 2){
        data_file = fopen("data_user.dat", "rb");
        for(int trial = 3; trial > 0; --trial){
            if(trial > 0){
                printf("================ USER LOGIN ================\n");
                printf("Before login, please input few informations to begin\n");
                printf("Username : "); gets(data.username);
                printf("Password : "); gets(data.password);

                while(fread(&find, sizeof(find), 1, data_file)!=0){
                    if(strcmp(data.username, find.username)== 0 && strcmp(data.password, find.password) == 0){
                        fclose(data_file);
                        printf("login success! press any key to continue..."); getchar();
                        menu_user();
                    }else{
                        printf("Remaining account input : %d\n", trial-1);
                        printf("wrong username or password! try again!\n");
                    }
                }
            }else{
                fclose(data_file);
                printf("login failed! press any key to back to main menu"); getchar();
                main_menu();
            }
        }
    }
}

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

void menu_user(){
    printf("============== USER MENU =============\n");
    printf("1. Check for balance\n2. Change Password\n4. Log Out\5. Exit\nChoose : "); int choose; scanf("%d", &choose); getchar();

    switch(choose){
        case 1:
            printf("Dummy");
            break;
        case 2:
            printf("Dummy");
            break;
        case 3:
            printf("Dummy");
            break;
        case 4:
            main_menu();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Wrong choice! Try again!");
            menu_user();
    }
}

void menu_admin(){
    printf("============== ADMIN MENU =============\n");
    printf("1. Give Charge\n2. Change User Password\n3. See User Lists\n4. Log Out\n5. Exit\nChoose : "); int choose; scanf("%d", &choose); getchar();

    switch(choose){
        case 1:
            printf("Dummy");
            break;
        case 2:
            printf("Dummy");
            break;
        case 3:
            printf("Dummy");
            break;
        case 4:
            main_menu();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Wrong choice! Try again!");
            menu_user();
    }
}