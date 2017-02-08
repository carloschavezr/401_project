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
    int studentID;
    char* name;
    char* gender;
    short grade;
    char* address;
    short admission_year;
    char** courses;
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
int getArrayLength( char** dataArray );
int getArrayLen(char** dataArray);
void showPrintMyCourse( int myStudentID );
char* getCourseName(char* courseID);
int strlength(char* line);

float calculateGPA(struct studentcourse* StudentCourse, int myStudentID);
int calculateRank(int myStudentID);
void printCourses();

void mainMenu();
void delay();

#define MAXUSER 1000
#define MAXTEXT 50
#define N 256

#define FILE_ACCOUNT "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Accounts.txt";;
#define FILE_COURSE "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Courses.txt"
#define FILE_STUDENT "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/Students.txt"
#define FILE_STUCOURSE "/Users/shinji/Mydata/personalmarketing/english/canada/school/CICCC/subject/401/Project01/Project01/Project01/StudentsCourses.txt"

struct account*       Account;
struct course*        Course;
struct student*       Student;
struct studentcourse* StudentCourse;

int myStudentID = 0;
int myStudentNum = 0;
int accountMaxNum = 0;
int courseMaxNum = 0;
int studentMaxNum = 0;
int stuCourseMaxNum = 0;

int indexStudentStruct = 0;
float myGpa = 0.0;
int numCourses = 0;

int stuStrIndex = 0;

int main( int argc, const char * argv[] ) {
    
    char file_account[] = FILE_ACCOUNT;
    char file_course[] = FILE_COURSE;
    char file_student[] = FILE_STUDENT;
    char file_studentscourses[] = FILE_STUCOURSE;
    
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
    
      showLoginView();
//      showMenuOptions();
    
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
            indexStudentStruct =compareIds(myStudentID);
            break;
        }
    }
    
    if(strcmp(inputPassword,Account[num].pass) == 0){
        // login saccess
        printf("************************************************************\n");
        printf("Welcome to Cornerstone International College of Canada.\n");
        printf("************************************************************\n");
        delay(3000);
        mainMenu();
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
    char** arrayCourses = getData( dataArray, "courses");
    
    studentMaxNum = dataLen;
    
    for (int i = 0; i < dataLen; i++) {
        Student[i].studentID = atoi(arrayStudentID[i]);
        Student[i].name = arrayName[i];
        Student[i].gender = arrayGender[i];
        Student[i].grade = (short)atoi(arrayGrade[i]);
        Student[i].address = arrayAddress[i];
        Student[i].admission_year = (short)atoi(arrayAdmis[i]);
    }
    for (int i = 0; i < getArrayLength(arrayCourses); i++) {
        Student[i].courses = dividedDataCourses(arrayCourses[i]);
        //        printf("%s", Student[i].courses[1]);
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




void mainMenu(){
    int repeater = 0;
    int opt;
    while(repeater==0){
    printf("******************************************\n");
    printf("Select from the options:\n");
    printf("******************************************\n");
    printf("¬[1] Print my enrollment certificate\n");
    printf("¬[2] Print my courses\n");
    printf("¬[3] Print my transcript\n");
    printf("¬[4] Print my GPA\n");
    printf("¬[5] Print my ranking among all students in the college\n");
    printf("¬[6] List of all available courses\n");
    printf("¬[7] List of all students\n");
    printf("¬[8] Logout\n");
    printf("¬[9] Exit\n");
    printf("******************************************\n");
    printf("Enter the number corresponding to each item to proceed:\n");
    

    
    showPrintMyCourse(myStudentID);
    
        scanf("%d",&opt);
        myGpa = calculateGPA(StudentCourse, myStudentID);
    switch(opt){
        case 1:
            printf("Dear Sir/Madam,\n\nThis is to certify that Mr. %s with student id %d is a student at grade %hd at CICCC. He was admited to our college in %hd and has taken %d course(s). Currently he resides at %s\n\n", Student[indexStudentStruct].name, myStudentID,Student[indexStudentStruct].grade ,Student[indexStudentStruct].admission_year, numCourses ,Student[indexStudentStruct].address);
            printf("If you have any questions, please do not hesitate to contact us.\n");
            delay(3000);
            break;
        case 2:
            printf("Hi Mr. %s  has taken the following courses:\n", Student[indexStudentStruct].name);
            

            showPrintMyCourse(myStudentID);
            break;
        case 3:
            printf("Hi Mr. %s,\n", Student[indexStudentStruct].name);
            printf("Here is your transcript:\n\n");
            break;
        case 4:
            printf("Hi Mr. %s,\n", Student[indexStudentStruct].name);
            printf("Your GPA is: %f\n\n",myGpa/numCourses);
            delay(4000);
            break;
        case 5:
            printf("Hi Mr. %s,\n", Student[indexStudentStruct].name);
            printf("Your GPA is:%f and therefore your rank is []\n\n",myGpa/numCourses);
            break;
        case 6:
            printf("The following courses are offered in CICCC:\n");
            
            break;
        case 7:
            printf("There are %d students in CICCC as following:\n", stuCourseMaxNum);
            
            break;
        case 8:
            printf("Logging out...");
            delay(4000);
            repeater=1;
            
            break;
        case 9:
            printf("Thank you for using our program!\n");
            delay(4000);
            exit(1);
            break;
        default:
            printf("Wrong Option, please try again!\n");
        }
    }
        
    if (repeater==1){
        delay(3000);
        showLoginView();
    }
}


void delay(int x){
   	int c = 1, d = 1;
    
    for ( c = 1 ; c <= x ; c++ )
        for ( d = 1 ; d <= 200000 ; d++ )
        {}
}


void showPrintMyCourse(int myStudentID){
    for (int i = 0; i < studentMaxNum; i++) {
        if(Student[i].studentID == myStudentID){
            stuStrIndex = i;
        }
    }
    
    int mnum = getArrayLen(Student[stuStrIndex].courses);
    
    for (int i = 0; i < mnum; i++) {
//        printf("%s \n",Student[stuStrIndex].courses[i]);
        char* courseName = getCourseName(Student[stuStrIndex].courses[i]);
        printf("%s\n", courseName);
    }
    
    
}

char* getCourseName(char* courseID){
    int idlen = strlength(courseID);
    char* courseName;
    char* courseNameID;
    for (int i = 0; i < courseMaxNum; i++) {
        if(strcmp(courseID, Course[i].courseID) == 0){
            courseName = Course[i].name;
            courseID = Course[i].courseID;
            strcat(courseNameID, courseName);
            break;
        }
    }
    
    return courseNameID;
}


//

int compareIds(int studentID){
    int result=0;
    for(int i=0;i<studentMaxNum;i++){
        if(Student[i].studentID==studentID){
            result = i;
        }
    }
    
    return result;
}


float calculateGPA(struct studentcourse* StudentCourse, int myStudentID){
    
    for (int i=0; i<stuCourseMaxNum; i++) {
        if (myStudentID==StudentCourse[i].studentID) {
            myGpa = myGpa + StudentCourse[i].mark;
            numCourses++;
        }
    }
    return myGpa;
}

int calculateRank(int myStudentID){
    int result = 0;
    
    return result;
}




int getArrayLength(char** dataArray){
    int num = 0;
    while (dataArray[num] != NULL) {
        num++;
    }
    return num;
}

int getArrayLen(char** dataArray){
    int size = sizeof dataArray / sizeof dataArray[0];
    return size;
}

int strlength(char* line){
    int len = strlen(line);
    return len;
}
