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
#include "load.h"

struct account{
    int user;
    char* pass;
};
struct course{
    char* courseID;
    char* name;
};
struct student{
    char* studentID;
    char* name;
    char* gender;
    short grade;
    char* address;
    short admission_year;
    char* courses;
};
struct studentcourse{
    int studentID;
    char* courseID;
    short mark;
};
void enterLogin( void );
void showMenuOptions( void );
void showLoginView( void );
void makeAccountStructure( char file_name[] );
void makeCourseStructure( char file_name[] );
void makeStudentStructure( char file_name[] );
void makeStuCourseStructure( char file_name[] );
int getArrayLength(char** dataArray);

#define MAXUSER 1000
#define MAXTEXT 50
#define N 256

struct account*       Account;
struct course*        Course;
struct student*       Student;
struct studentcourse* StudentCourse;

int myStudentID = 0;
int accountMaxNum = 0;
int courseMaxNum = 0;
int studentMaxNum = 0;
int stuCourseMaxNum = 0;

int main(int argc, const char * argv[]) {
    char file_account[] = "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Accounts.txt";
    char file_course[] = "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Courses.txt";
    char file_student[] = "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Students.txt";
    char file_studentscourses[] = "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/StudentsCourses.txt";
    
    Account       = (struct account*) malloc(sizeof(struct account) * MAXUSER);
    Course        = (struct course*) malloc(sizeof(struct course) * MAXUSER);
    Student       = (struct student*) malloc(sizeof(struct student) * MAXUSER);
    StudentCourse = (struct studentcourse*) malloc(sizeof(struct studentcourse) * MAXUSER);
    
    
    // 構造体の配列の変数を入れた配列を渡して、その関数内で代入したかったな。
    //    char* strctArray[4] = { &Account, &Course, &Student, &StudentCourse};
    //    Course[0].studentID = "12345";
    //    printf("%s \n", Course[0].studentID );
    //    printf("%s \n", *(strctArray[1])[0].studentID );
    
    makeAccountStructure(file_account);
    makeCourseStructure(file_course);
    makeStudentStructure(file_student);
    makeStuCourseStructure(file_studentscourses);
    
    Account = (struct account*) realloc(Account, sizeof(struct account ) * accountMaxNum);
    Course  = (struct course*) realloc(Course, sizeof(struct course ) * courseMaxNum);
    Student = (struct student*) realloc(Student, sizeof(struct student ) * studentMaxNum);
    StudentCourse = (struct studentcourse*) realloc(StudentCourse, sizeof(struct studentcourse ) * stuCourseMaxNum);
    
    printf("%s \n",Student[0].courses);
    
//    for (int i = 0; i < 20; i++) {
//        printf("%d \n",Account[i].user);
//        printf("%s\n",Account[i].pass);
//    }
//    printf("%d \n",Student[0].grade);
        showLoginView();
    //    showMenuOptions();
    
    return 0;
}


// need divided
void showLoginView(void){
    printf("************************************************************\n");
    printf("Please enter your account to login:\n");
    printf("************************************************************\n");
    enterLogin();
}

void enterLogin( void ){
    int num = 0, inputUsername = 0;
    char* inputPassword = malloc(sizeof(char) * N);
    printf("Username:");
    scanf("%d", &inputUsername);
    printf("Password:");
    scanf("%s", inputPassword);
    
    //check login
    for (int i = 0; i < accountMaxNum; i++) {
        if(inputUsername == Account[i].user){
            myStudentID = inputUsername;
            num = i;
            break;
        }
    }
    
    if(strcmp(inputPassword,Account[num].pass) == 0){
        // login saccess
        printf("************************************************************\n");
        printf("Welcome to Cornerstone International College of Canada.\n");
        printf("************************************************************\n");
    }else{
        printf("************************************************************\n");
        printf("Your account does not exist. Please try again!\n");
        printf("************************************************************\n");
        enterLogin();
    }
    
}





void makeAccountStructure( char file_name[] ){
    
    char** dataArray;
    int dataLen = 0;
    
    dataArray = loadFile(file_name);
    
    char** arrayUser = getData(dataArray, "User");
    dataLen = getArrayLength(arrayUser);
    
    char** arrayPass = getData(dataArray, "Pass");
    accountMaxNum = dataLen;
    
    for (int i = 0; i < dataLen; i++) {
        Account[i].user = atoi(arrayUser[i]);
        Account[i].pass = arrayPass[i];
    }
    
}

void makeCourseStructure( char file_name[] ){
    
    char** dataArray;
    int dataLen = 0;
    
    dataArray = loadFile(file_name);
    
    char** arrayCourseID = getData(dataArray, "courseID");
    dataLen = getArrayLength(arrayCourseID);
    
    char** arrayName = getData(dataArray, "name");
    courseMaxNum = dataLen;
    
    for (int i = 0; i < dataLen; i++) {
        Course[i].courseID = arrayCourseID[i];
        Course[i].name = arrayName[i];
//        printf("%s \n", Course[i].name);
    }
    
}

void makeStudentStructure( char file_name[] ){
    
    char** dataArray;
    int dataLen = 0;
    
    dataArray = loadFile(file_name);
    char** arrayStudentID = getData(dataArray, "studentID");
    dataLen = getArrayLength(arrayStudentID);
    
    char** arrayName = getData(dataArray, "name");
    char** arrayGender = getData(dataArray, "gender");
    char** arrayGrade = getData(dataArray, "grade");
    char** arrayAddress = getData(dataArray, "address");
    char** arrayAdmis = getData(dataArray, "admission_year");
    char** arrayCourses = getData(dataArray, "courses");
    studentMaxNum = dataLen;
    
    for (int i = 0; i < dataLen; i++) {
        Student[i].studentID = arrayStudentID[i];
        Student[i].name = arrayName[i];
        Student[i].gender = arrayGender[i];
        Student[i].grade = (short)atoi(arrayGrade[i]);
        Student[i].address = arrayAddress[i];
        Student[i].admission_year = (short)atoi(arrayAdmis[i]);
        Student[i].courses = arrayCourses[i];
    }
    
}

void makeStuCourseStructure( char file_name[] ){
    
    char** dataArray;
    int dataLen = 0;
    
    dataArray = loadFile(file_name);
    
    char** arrayStudentID = getData(dataArray, "studentID");
    dataLen = getArrayLength(arrayStudentID);
    
    char** arrayCourseID = getData(dataArray, "courseID");
    
    char** arrayMark = getData(dataArray, "mark");
    stuCourseMaxNum = dataLen;
    
//    printf("StuCourse:%zu \n", dataLen);
    for (int i = 0; i < dataLen; i++) {
        StudentCourse[i].studentID = atoi(arrayStudentID[i]);
        StudentCourse[i].courseID = arrayCourseID[i];
        StudentCourse[i].mark = (short)atoi(arrayMark[i]);
    }
    
}

int getArrayLength(char** dataArray){
    int num = 0;
    while (dataArray[num] != NULL) {
        num++;
    }
    return num;
}








