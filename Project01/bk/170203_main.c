//
//  main.c
//  Project01
//
//  Created by sin on 2017/02/02.
//  Copyright © 2017年 shinji. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct account{
    char* user;
    char* pass;
};

void readStudent(void);
void showMenuOptions(void);
void showLoginView(void);
char** readFile( char file_name[], char target[], struct account* accountList);
void trim( char *s );

#define MAXUSER 1000
#define MAXTEXT 50
#define N 256

int main(int argc, const char * argv[]) {
    char file_name[] = "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Accounts.txt";
    
    char **usernameArray;
    char **userpassArray;
    char s_user[] = "User:";
    char s_pass[] = "Pass:";
    size_t userdataLen = 0;
    size_t userpassLen = 0;
    struct account* accountList;
    
//    accountList = (struct account*) malloc(sizeof(struct account) * MAXUSER);

    
    
    usernameArray = readFile(file_name, s_user, accountList);
    
    
    
    
    
//    userdataLen = strlen( *usernameArray );

//    for (int a = 0; a <= userdataLen; a++) {
////       printf( "%s\n", usernameArray[a] );
//    }
    
//    userpassArray = readFile(file_name, s_pass);
//    
//    userpassLen = strlen( *userpassArray );
//    for (int a = 0; a <= userpassLen; a++) {
//        printf( "%s\n", userpassArray[a] );
//    }
    
    //    readStudent();
    //    showLoginView();
    //    showMenuOptions();
    
    return 0;
}


void showLoginView(void){
    char* username = malloc(sizeof(char *) * MAXTEXT);
    char* password = malloc(sizeof(char *) * MAXTEXT);
    printf("************************************************************\n");
    printf("Please enter your account to login:\n");
    printf("************************************************************\n");
    printf("Username:\n");
    scanf("%s", username);
    printf("Password:\n");
    scanf("%s", password);
    if(username == "" && password == ""){
        //gotomenu
    }
    
}

char** readFile(char file_name[], char target[], struct account* accountList){
    char s_pass[] = "Pass:";
    FILE *fp;
    char s[100];
    char *p;
    
    char **usernameArray;
    char **passArray;
    
    char str[N] = "";
    char *p1, *p2;
    size_t len = 0, userdataLen = 0;
    int i = 0;
    
    fp = fopen( file_name, "r" );
    if( fp == NULL ){
        printf( "%s cannot be opened file!\n", file_name );
        exit(1);
    }
    
    usernameArray = malloc(MAXUSER); //最初の配列のメモリを確保
    accountList = (struct account*) malloc(sizeof(struct account) * MAXUSER);
    
    while( fgets( s, N, fp ) != NULL ){ // get a each line, loop until null
        p = strstr(s, target); //seach "target"
        if(p != NULL){
            p1 = s;
            len = strlen(target);
            while((p2 = strstr(p1, target)) != NULL) { // loop until no target
                strncat(str,p1,p2 - p1); // combine without deleted strings
                p1 = p2 + len; // update a pointer
            }
            usernameArray[i] = (char *) malloc(sizeof(char *) * len);
            accountList[i] = *(struct account*) malloc(sizeof(struct account) * len);
            trim(p1);
            size_t p1_len = strlen( p1 );
            
            strncpy( usernameArray[i], p1+1, p1_len-2 );//p1の先頭+1の位置から7文字をusenumにコピー
            /* このusernameArrayは将来消す */
            accountList[i].user = usernameArray[i];
            accountList[i].user[p1_len-2] = '\0'; //でも文字数指定って..だめなきがする
            
            i++;
        }
    }
    
    fclose( fp );
    
//    userdataLen = strlen(*usernameArray);
//    for (int a = 0; a <= userdataLen; a++) {
//        printf( "%s\n", usernameArray[a] );
//    }
    
    return usernameArray;
}


void trim( char *s ) {
    int i, j;
    for( i = strlen(s)-1; i >= 0 && isspace( s[i] ); i-- ) ;
    s[i+1] = '\0';
    for( i = 0; isspace( s[i] ); i++ ) ;
    if( i > 0 ) {
        j = 0;
        while( s[i] ) s[j++] = s[i++];
        s[j] = '\0';
    }
}

















void readStudent(void){
    char file_name[] = "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Accounts.txt";
    
    FILE *fp;
    char s[100];
    char s_user[] = "User:";
    char s_pass[] = "Pass:";
    char *p;
    
    char **usernameArray;
    
    char str[N] = "";
    char *p1, *p2;
    size_t len = 0,userdataLen = 0;
    int i = 0;
    
    fp = fopen( file_name, "r" );
    if( fp == NULL ){
        printf( "%s cannot be opened file!\n", file_name );
        exit(1);
    }
    
    usernameArray = malloc(MAXUSER); //最初の配列のメモリを確保
    while( fgets( s, N, fp ) != NULL ){ // get a each line, loop until null
        p = strstr(s, s_user); //seach "User:"
        if(p != NULL){
            p1 = s;
            len = strlen(s_user);
            while((p2 = strstr(p1, s_user)) != NULL) { // loop until no target
                strncat(str,p1,p2 - p1); // combine without deleted strings
                p1 = p2 + len; // update a pointer
            }
            usernameArray[i] = (char *) malloc(sizeof(char *) * len);
            strncpy( usernameArray[i], p1+1, 7 ); //p1の先頭+3の位置から5文字をusenumにコピー
            usernameArray[i][7] = '\0'; //でも文字数指定って..だめなきがする
            i++;
        }
    }
    
    fclose( fp );
    
    //just chcking
    userdataLen = strlen(*usernameArray);
    for (int a = 0; a <= userdataLen; a++) {
        printf( "%s\n", usernameArray[a] );
    }
    
};
