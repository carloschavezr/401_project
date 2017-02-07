//
//  load.h
//  Project01
//
//  Created by sin on 2017/02/04.
//  Copyright © 2017年 shinji. All rights reserved.
//

#ifndef load_h
#define load_h


void readStudent( void );
void showMenuOptions( void );
void showLoginView( void );
char** readFile( char file_name[], char target[]);
void trim( char *s );
//void substring( char* word, int startIndex, int endIndex );

char* substring(char* word);
char** loadFile( char file_name[] );
char** getData(char** dataArray, char target[]);

#endif /* load_h */
