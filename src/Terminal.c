#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Database.h"

#define MAX_NAME_LENGTH 50
#define MAX_GRADES 10
#define MAX_TELEPHONE_LENGTH 11

//Const For Main Menu
#define Insert 1
#define Delete 2
#define Edit 3
#define Search 4
#define Top10 5
#define UnderperformedStudents 6
#define Average 7
#define Export 8
#define Exit 9

//Const For Edit Menu
#define EDIT_FIRST_NAME 1
#define EDIT_LAST_NAME 2
#define EDIT_STUDENT_TELEPHONE 3
#define EDIT_CLASS_NUMBER 4
#define EDIT_LAYER_NUMBER 5
#define EDIT_GRADES 6
#define MAIN_MENU 7

void clearInputBuffer() {
    while (getchar() != '\n');
}

//Check input
int getValidInteger() {
    int input;
    while (scanf("%d", &input) != 1) {
        printf("Invalid input. Please enter an integer: ");
        clearInputBuffer();
    }
    clearInputBuffer(); // Clear any remaining input
    return input;
}
char getValidChar() {
    char input;
    scanf(" %c", &input); // Read character input
    input = tolower(input); // Convert to lowercase for consistency
    clearInputBuffer(); // Clear any remaining input
    return input;
}
char* getValidTelephone() {
    static char input[12]; // Buffer for 10 digits plus newline and null terminator
    while (1) {
        printf("Enter Telephone Number (10 digits): ");
        fgets(input, sizeof(input), stdin); // Read input including newline

        // Remove newline character from input if present
        input[strcspn(input, "\n")] = '\0';

        // Check if the length is exactly 10 characters and all are digits
        if (strlen(input) == 10 && strspn(input, "0123456789") == 10) {
            return input; // Return the valid telephone number
        }
        printf("Invalid input. Telephone number must be exactly 10 digits.\n");
    }
}
int getValidGrade(int courseNumber) {
    int grade;
    while (1) {
        printf("Enter Grade for Course %d (0-100): ", courseNumber);
        if (scanf("%d", &grade) == 1 && grade >= 0 && grade <= 100) {
            return grade; // Valid grade, return it
        } else {
            printf("Invalid input. Grade must be a number between 0 and 100.\n");
            clearInputBuffer();
        }
    }
}

//User Display Menus
void displayMenu()
{
    printf("\nSchool Management System Menu:\n");
    printf("1. Add a New Student - Assign to Class and Layer, Enroll in Courses\n");
    printf("2. Remove a Student\n");
    printf("3. Edit Student Information (e.g., Update Grades)\n");
    printf("4. Search for Student by First and Last Name and Display All Information (Layer, Class, Grades)\n");
    printf("5. Query Top 10 Outstanding Students by Layer and Specific Subject\n");
    printf("6. List Students Eligible for Departure Based on Custom Parameters\n");
    printf("7. Calculate Average Grade per Course per Layer\n");
    printf("8. Export Entire Database to File\n");
    printf("9. Exit\n");
    printf("Please select an option (1-9): ");
}
void displayEditingMenu()
{
    printf("\nEditing Menu:\n");
    printf("1. Edit First Name\n");
    printf("2. Edit Last Name\n");
    printf("3. Edit Student ID\n");
    printf("4. Edit Class Number\n");
    printf("5. Edit Layer Number\n");
    printf("6. Edit Grades\n");
    printf("7. Return to Main Menu\n");
    printf("Please select an option (1-6): ");
}

void insertStudent()
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char* telephone;
    int studentClass = -1;
    int studentLayer = -1;
    int grades[MAX_GRADES] ={0};

    // Take required arguments from user
    printf("Enter First Name (max %d characters): ", MAX_NAME_LENGTH);
    scanf("%s" , firstName);

    printf("Enter Last Name (max %d characters): ", MAX_NAME_LENGTH);
    scanf("%s" , lastName);

    clearInputBuffer();
    telephone = getValidTelephone();

    printf("Enter Class Number: ");
    studentClass = getValidInteger();

    printf("Enter Layer Number: ");
    studentLayer = getValidInteger();

    // Optional: Take grades input

    printf("Do you want to add grades? (y/n): ");
    char addGrades = getValidChar();

    if (addGrades == 'y') {
        for (int i = 0; i < MAX_GRADES; i++) {
            grades[i] = getValidGrade(i + 1);
        }
    } else {
        // Initialize grades to 0 if not provided
        for (int i = 0; i < MAX_GRADES; i++) {
            grades[i] = 0;
        }
    }
    add_student(firstName , lastName , telephone , studentLayer , studentClass , grades);
}

void removeStudent()
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];

    // Input student first and last name to identify
    printf("Enter First Name of the Student to Remove: ");
    scanf("%s" , firstName);

    printf("Enter Last Name of the Student to Remove: ");
    scanf("%s" , lastName);

    remove_student(firstName , lastName);
}

void editStudent()
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int userInput;

    // Input student first and last name to identify
    printf("Enter First Name of the Student to Edit: ");
    scanf("%s" , firstName);

    printf("Enter Last Name of the Student to Edit: ");
    scanf("%s" , lastName);

    Student* currentStudent = get_student(firstName , lastName);
    char newFirstName[MAX_NAME_LENGTH];
    strcpy(newFirstName ,currentStudent->first_name);
    char newLastName[MAX_NAME_LENGTH];
    strcpy(newLastName ,currentStudent->last_name);
    char newTelephone[12];
    strcpy(newTelephone,currentStudent->telephone);
    int newClassNumber = currentStudent->class_id;
    int newLayerNumber = currentStudent->layer;
    int newGrades[MAX_GRADES];
    memcpy(newGrades, currentStudent->grades, MAX_GRADES * sizeof(int));

    int continueEditing = 1;
    while (continueEditing) {
        displayEditingMenu();
        userInput = getValidInteger();

        switch (userInput) {
            case EDIT_FIRST_NAME:
                printf("Enter new first name: ");
                scanf("%s", newFirstName);
                clearInputBuffer();
                break;
            case EDIT_LAST_NAME:
                printf("Enter new last name: ");
                scanf("%s", newLastName);
                clearInputBuffer();
                break;
            case EDIT_STUDENT_TELEPHONE:
                //newTelephone = getValidTelephone();
                break;
            case EDIT_CLASS_NUMBER:
                printf("Enter New Class Number: ");
                newClassNumber = getValidInteger();
                break;
            case EDIT_LAYER_NUMBER:
                printf("Enter New Layer Number: ");
                newLayerNumber = getValidInteger();
                break;
            case EDIT_GRADES:
                for (int j = 0; j < MAX_GRADES; j++) {
                    newGrades[j] = getValidGrade(j + 1);
                }
                break;
            case MAIN_MENU:
                printf("Returning to Main Menu...\n");
                return; // Exit the editing menu
            default:
                printf("Invalid choice. Please select an option between 1 and 6.\n");
                break;
        }

        printf("Do you want to continue editing? (y/n): ");
        char continueChoice = getValidChar();

        if (continueChoice != 'y') {
            continueEditing = 0; // Exit the loop if user chooses not to continue
        }
    }
    set_student(firstName , lastName , newFirstName , newLastName , newTelephone ,  newLayerNumber ,newClassNumber ,newGrades);
    printf("Exiting editing mode...\n");
}

void searchStudent()
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];

    // Input student first and last name to identify
    printf("Enter First Name of the Student to Search: ");
    scanf("%s" , firstName);

    printf("Enter Last Name of the Student to Search: ");
    scanf("%s" , lastName);

    print_student(firstName , lastName);
}

void topTenStudent()
{
    int course;
    printf("Enter course No. : ");
    course = getValidInteger();
    find_top_students(course);
}

void averagePerCourse()
{
    int course , layer;
    printf("Enter Layer and course No. : ");
    while (scanf("%d %d", &course, &layer) != 2) {
        printf("Invalid input. Please enter two integers for Layer and Course No.: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    calculate_and_print_average_per_layer(course , layer);
}
void export()
{
    const char* fileName[256];
    printf("Enter file Path to Export: ");
    scanf("%s" , fileName);
    export_data_to_file(fileName);
}

int main() {
    const char* fileName = "students_with_class.txt";
    load_data_from_file(fileName);

    int userInput;

    while (1) {
        displayMenu();
        userInput = getValidInteger();

        switch (userInput) {
            case Insert:
                printf("Option 1 selected: Add a New Student.\n");
                insertStudent();
                break;
            case Delete:
                printf("Option 2 selected: Remove a Student.\n");
                removeStudent();
                break;
            case Edit:
                printf("Option 3 selected: Edit Student Information.\n");
                editStudent();
                break;
            case Search:
                printf("Option 4 selected: Search for Student.\n");
                searchStudent();
                break;
            case Top10:
                printf("Option 5 selected: Query Top 10 Outstanding Students.\n");
                topTenStudent();
                break;
            case UnderperformedStudents:
                printf("Option 6 selected: List Students Eligible for Departure.\n");
                break;
            case Average:
                printf("Option 7 selected: Calculate Average Grade per Course per Layer.\n");
                averagePerCourse();
                break;
            case Export:
                printf("Option 8 selected: Export Entire Database to File.\n");
                export();
                break;
            case Exit:
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please select an option between 1 and 9.\n");
                break;
        }
    }
}
