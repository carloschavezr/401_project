//
//  load.c
//  Project01
//
//  Created by sin on 2017/02/04.
//  Copyright © 2017年 shinji. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "load.h"

#define MAXUSER 1000
#define MAXTEXT 50
#define N 256

char** getData(char** dataArray, char target[]){
    int j = 0, i = 0;
    char** array;
    
    array = (char *) malloc(sizeof(char *) * N);
//    printf("%s \n", dataArray[j]);
    while (dataArray[j] != NULL) {
        if((strstr(dataArray[j], target)) != NULL ){
            array[i] = (char *) malloc(sizeof(char *) * MAXUSER);
            array[i] = substring(dataArray[j]);
            i++;
//          printf("%s\n", array[i]);
//          printf("%d\n", i);
//          printf("%s", substring(dataArray[j]));
            }
        j++;
    }
    array = (char *) realloc(array, sizeof(char *) * j);
    
    return array;
}



char** loadFile( char file_name[] ){
    FILE *fp;
    char s[100];
    char *p;
    
    char **dataArray;
    char **passArray;
    
    char str[N] = "";
    char *p1, *p2;
    size_t len = 0, userdataLen = 0;
    int i = 0;
    
    
    
    //    char target[] = "User";
    
    fp = fopen( file_name, "r" );
    if( fp == NULL ){
        printf( "%s cannot be opened file!\n", file_name );
        exit(1);
    }
    dataArray = malloc(MAXUSER); //最初の配列のメモリを確保
    
    while( fgets( s, N, fp ) != NULL ){ // get a each line, loop until null
        
        
        if(*s != '\n'){ // no need space
            trim(s); //trim empty space
            dataArray[i] = (char *) malloc(sizeof(char *) * MAXUSER);
            strcpy(dataArray[i], s); // assign to
            //                  dataArray[i] = substring(s);
            //                  printf("%s\n", dataArray[i]);
            //                  dataArray[i][] = '\0'; //でも文字数指定って..だめなきがする
            i++;
        }
        
        //        len = strlen(target);
        //        for (int i = 0; i < len; i++) {
        //            if((strstr(s, target[i])) != NULL){
        //            }
        //        }
        
    }
    
    
    //    printf("here....%s\n", dataArray[0]);
    //    for (int a = 0; a < i; a++) {
    //        printf("[%d]%s\n",i, dataArray[a]);
    //    }
    //
    fclose( fp );
    
    return dataArray;
}


char* substring(char* word){
    int counter = 0;
    int count_start = 0;
    size_t len = 0;
    int checker = 0;
    char* result;
    
    char *p1, *p2;
    len = strlen(word);
    
    // get start point
    while (word[count_start] != '\342') {
        count_start++;
    }
    
    for (int i = 0; i < len; i++) {
        if(word[i] == '\342'){
            checker = 1;
        }else if (word[i] == '\"'){
            checker = 2;
        }
        if(checker == 1 || checker == 2){
            counter++;
        }
    }
    if(checker == 1){
        counter = counter - 6;
        count_start = count_start + 3;
    }else if (checker == 2){
        counter = counter - 2;
        count_start = count_start + 1;
    }
    
    result = (char*) malloc(sizeof(char) * counter+1);
    strncpy( result, word+(count_start), counter );//p1の先頭+1の位置から7文字をusenumにコピー
    result[counter+1] = '\0';
    
    return result;
    //    printf("%s \n", result);
    //    printf("******char : %s \n", word);
    //    printf("total char : %zu \n", len);
    //    printf("necee char : %d \n\n", counter);
    
    
    
}


char** readFile(char file_name[], char target[]){
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
    //    Account = (struct account*) malloc(sizeof(struct account) * MAXUSER);
    
    while( fgets( s, N, fp ) != NULL ){ // get a each line, loop until null
        p = strstr(s, target); //seach "target"
        if(p != NULL){
            p1 = s;
            len = strlen(target); //length
            while((p2 = strstr(p1, target)) != NULL) { // search and loop until no target
                strncat(str,p1,p2 - p1); // combine without deleted strings
                p1 = p2 + len; // update a pointer
            }
            usernameArray[i] = (char *) malloc(sizeof(char *) * len);
            trim(p1);
            size_t p1_len = strlen( p1 );
            
            strncpy( usernameArray[i], p1+1, p1_len-2 );//p1の先頭+1の位置から7文字をusenumにコピー
            usernameArray[i][p1_len-2] = '\0'; //でも文字数指定って..だめなきがする
            
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



