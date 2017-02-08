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




char** dividedDataCourses(char** dataArray){
    
    //他のものと同様に読み込んで、そのあと、配列に分けて、　ストラクチャーに入れる。
    
//    printf("%s \n", dataArray);
   
    
    int j = 0, i = 0;
    int checkString = 0;
    char** array;
    char** result;
    char* dap;
    
    dap = dataArray;
    array = (char *) malloc(sizeof(char *) * N);
    size_t len = strlen(dataArray);
    
    
//    printf("%s \n", dataArray);
    int a = 0, b = 0, index = 0, count = 0, check = 0, startIndex = 0;
    while (dap[j] != '\0') { // each line
        
        
//        printf("[%c] \n", dap[j]);
        /**/
//        if(check == 1){
//            count++;
//        }
//        //二番目の"
//        if((dap[j] == '\"') && check == 1){
//            check = 0;
//        //1番目の"
//        }else if((dap[j] == '\"') && check == 0){
//            
//            array[index] = (char *) malloc(sizeof(char *) * MAXUSER);
//            strncpy( array[index], dap+(j-count-1), count-1 );
//            
//            printf("%s \n", array[index]);
//            check = 1;
//            count = 0;
//            index++;
//            
//        }
        /**/
        
        
        if(dap[j] == '\"' && check == 0){
            check = 1;
            startIndex = j;
        }else if(dap[j] == '\"' && check == 1){
            array[index] = (char *) malloc(sizeof(char *) * MAXUSER);
            strncpy( array[index], dap+(startIndex+1), count-1 );
            array[index][count+1] = '\0';
            //
//            printf("%s \n", array[index]);
            count = 0;
            check = 0;
            index++;
        }
        if(check == 1){
            count++;
        }else{
            b++;
        }
        //                coursArray[index][count+1] = '\0';
        a++;
        
        j++;
    }
    return array;
    
}






char** getData(char** dataArray, char target[]){
    
    int j = 0, i = 0;
    int checkString = 0;
    char** array;
    
    array = (char *) malloc(sizeof(char *) * N);
//    printf("%s \n", dataArray[j]);
    while (dataArray[j] != NULL) { // each line
        if((strstr(dataArray[j], target)) != NULL ){
            array[i] = (char *) malloc(sizeof(char *) * MAXUSER);
            
            checkString = 1;
            if( target == "courses"){
                array[i] = substring(dataArray[j], 1);
            }else{
                array[i] = substring(dataArray[j], 0);
            }
            i++;
//            if((strstr(dataArray[j], "courses")) != NULL ){
//                
//                char coursArray[checkWordsComma(dataArray[j])][10];
////                char **mnthp[checkWordsComma(dataArray[j])];
//                
//                int a = 0, index = 0, count = 0, check = 0;
//                while (dataArray[j][a] != '\0') {
//                    if(dataArray[j][a] == '\235'){
//                        check = 1;
//                    }else if(dataArray[j][a] == ','){
//                        count = 0;
//                        index++;
//                    }
//                    if(dataArray[j][a] == '\342'){
//                        check = 0;
//                    }
//                    if(check == 1){
//                        if(dataArray[j][a] != ',' && dataArray[j][a] != '\235'){
//                            coursArray[index][count] = dataArray[j][a];
//                            count++;
//                        }
//                    }
//                    coursArray[index][count+1] = '\0';
//                    a++;
//                    
//                }
//                
//                
//                
//            }else{
//                checkString = 1;
//                array[i] = substring(dataArray[j]);
//                i++;
//            }
        }
        j++;
    }
    if(checkString){
        array = (char *) realloc(array, sizeof(char *) * j);
    }
    
    return array;
    
}


int checkWordsComma(char* word){
    size_t len = strlen(word);
    int num = 0;
    for (int i = 0; i < len; i++) {
        if( word[i] == '\235' ){
            if(word[i+1] == ','){
                num++;
            }
        }
    }
    return num+1;
}







char* substring(char* word, int raw){
    
    char* result;
    int counter = 0;
    int count_start = 0;
    size_t len = 0;
    int checker = 0;
    if(raw == NULL){
        raw = 0;
    }
    
    char *p1, *p2;
    len = strlen(word);
    
    // get start point
    while (word[count_start] != '\"') {
        count_start++;
    }
    
    for (int i = 0; i < len; i++) {
        if(word[i] == '\"'){
            checker = 1;
        }else if (word[i] == '\"'){
            checker = 2;
        }
        if(checker == 1 || checker == 2){
            counter++;
        }
    }
    
    
    if(checker == 1){
        counter = counter - 2;
        count_start = count_start + 1;
    }else if (checker == 2){
        counter = counter - 2;
        count_start = count_start + 1;
    }
    if(raw == 1){
        counter = counter + 2;
        count_start = count_start - 1;
    }
    
    
    result = (char*) malloc(sizeof(char) * counter+1);
    strncpy( result, word+(count_start), counter );
    result[counter+1] = '\0';
    
    
    return result;
    
    
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
            i++;
        }
        
    }
    
    
    //    printf("here....%s\n", dataArray[0]);
    //    for (int a = 0; a < i; a++) {
    //        printf("[%d]%s\n",i, dataArray[a]);
    //    }
    //
    fclose( fp );
    
    return dataArray;
}





