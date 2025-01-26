#include <stdio.h>
#include <stdlib.h>

typedef struct user{
    char name[100];
    char username[100];
    char password[100];
    int balance;
}user;

// ADMIN OR EVALUATOR
void signin_admin();
void menu_admin();

//USER
void signup_signin_user();


int main(){
    printf("hello world");
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

void signup(){
    FILE* data;

    data = fopen("data_user.dat", "ab");

    user signup_user;
    printf("================= SIGN UP MENU ====================\n");
    printf("Hello, guest! Before we start, let's sign you up!\n");
    printf("Insert few data to get going : ");
    printf("Name      : "); gets(signup_user.name);
    printf("Username  : "); gets(signup_user.username);
    printf("Password  : "); gets(signup_user.password);
    signup_user.balance = 0;

    size_t check = fwrite(&signup_user, sizeof(signup_user), 1, data);

    if(check != 0){
        printf("data saved successfully!\n");
    }else{
        printf("data failed to saved! try again or contact the administrator\n");
    }
    printf("press any key to continue...\n");
    getchar();
    main_menu();
}

void signin_admin(){
    user data;

    for(int trial = 3; trial > 0; trial--){
        if(trial > 0){
            printf("================ ADMIN LOGIN ================\n");
            printf("Before login, please input few informations to begin\n");
            printf("Username : "); gets(data.username);
            printf("Password : "); gets(data.password);

                if(strcmp(data.username, "admin")== 0 && strcmp(data.password, "admin") == 0){
                    printf("login success! press any key to continue..."); getchar();
                    menu_admin();
                }else{
                    printf("wrong username or password! try again!");
                }
        }else{
            printf("login failed! press any key to continue..."); getchar();
            main_menu();
        }
    }

}