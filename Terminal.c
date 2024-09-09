#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_GRADES 10

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
#define EDIT_STUDENT_ID 3
#define EDIT_CLASS_NUMBER 4
#define EDIT_LAYER_NUMBER 5
#define EDIT_GRADES 6
#define MAIN_MENU 7

typedef struct {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int studentID;
    int layerNumber;
    int classNumber;
    float grades[MAX_GRADES];
} Student;

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
int getValidStudentID() {
    char input[12]; // Buffer for 10 digits plus newline and null terminator
    int studentID;
    while (1) {
        printf("Enter Student ID (10 digits): ");
        fgets(input, sizeof(input), stdin); // Read input including newline

        // Remove newline character from input if present
        input[strcspn(input, "\n")] = '\0';

        // Check if the length is exactly 10 characters and all are digits
        if (strlen(input) == 10 && strspn(input, "0123456789") == 10) {
            if (sscanf(input, "%d", &studentID) == 1) {
                return studentID; // Return the valid student ID
            }
        }
        printf("Invalid input. Student ID must be exactly 10 digits.\n");
    }
}
float getValidGrade(int courseNumber) {
    float grade;
    while (1) {
        printf("Enter Grade for Course %d (0-100): ", courseNumber);
        if (scanf("%f", &grade) == 1 && grade >= 0 && grade <= 100) {
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
    printf("School Management System Menu:\n");
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
    int studentID;
    int studentClass;
    int studentLayer;
    float grades[MAX_GRADES];

    // Take required arguments from user
    printf("Enter First Name (max %d characters): ", MAX_NAME_LENGTH - 1);
    scanf("%s" , firstName);
//    fgets(firstName, MAX_NAME_LENGTH, stdin);
//    firstName[strcspn(firstName, "\n")] = '\0';

    printf("Enter Last Name (max %d characters): ", MAX_NAME_LENGTH - 1);
    scanf("%s" , lastName);
//    fgets(lastName, MAX_NAME_LENGTH, stdin);
//    lastName[strcspn(lastName, "\n")] = '\0';

    clearInputBuffer();
    studentID = getValidStudentID();

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
            grades[i] = 0.0;
        }
    }

}

void removeStudent()
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];

    // Clear the input buffer to remove any leftover newline character


    // Input student first and last name to identify
    printf("Enter First Name of the Student to Remove: ");
    scanf("%s" , firstName);
//    fgets(firstName, sizeof(firstName), stdin);
//    firstName[strcspn(firstName, "\n")] = '\0'; // Remove the newline character

    printf("Enter Last Name of the Student to Remove: ");
    scanf("%s" , lastName);
//    fgets(lastName, sizeof(lastName), stdin);
//    lastName[strcspn(lastName, "\n")] = '\0';
}

void editStudent()
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char newFirstName[MAX_NAME_LENGTH], newLastName[MAX_NAME_LENGTH];
    int newStudentID;
    int newClassNumber, newLayerNumber;
    float newGrades[MAX_GRADES];
    int userInput;

//    clearInputBuffer();

    // Input student first and last name to identify
    printf("Enter First Name of the Student to Edit: ");
    scanf("%s" , firstName);
//    fgets(firstName, sizeof(firstName), stdin);
//    firstName[strcspn(firstName, "\n")] = '\0'; // Remove newline character

    printf("Enter Last Name of the Student to Edit: ");
    scanf("%s" , lastName);
//    fgets(lastName, sizeof(lastName), stdin);
//    lastName[strcspn(lastName, "\n")] = '\0';

    displayEditingMenu();
    clearInputBuffer();
    userInput = getValidInteger();

    switch (userInput) {
        case EDIT_FIRST_NAME:
            printf("Enter new first name: ");
            scanf("%s" , newFirstName);
            clearInputBuffer();
//            fgets(newFirstName, MAX_NAME_LENGTH, stdin);
//            newFirstName[strcspn(newFirstName, "\n")] = '\0';
            break;
        case EDIT_LAST_NAME:
            printf("Enter new last name: ");
            scanf("%s" , newLastName);
            clearInputBuffer();
//            fgets(newLastName, MAX_NAME_LENGTH, stdin);
//            newLastName[strcspn(newLastName, "\n")] = '\0';
            break;
        case EDIT_STUDENT_ID:
            newStudentID = getValidStudentID();
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
            for (int j = 0; j < 5; j++) {
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
}

void searchStudent()
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];

    //clearInputBuffer();

    // Input student first and last name to identify
    printf("Enter First Name of the Student to Search: ");
    scanf("%s" , firstName);
//    fgets(firstName, sizeof(firstName), stdin);
//    firstName[strcspn(firstName, "\n")] = '\0'; // Remove newline character

    printf("Enter Last Name of the Student to Search: ");
    scanf("%s" , lastName);
//    fgets(lastName, sizeof(lastName), stdin);
//    lastName[strcspn(lastName, "\n")] = '\0';
}

void topTenStudent()
{
    int course;
    printf("Enter course No. : ");
    course = getValidInteger();
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
}

int main() {
    int userInput;

    while (1) { // Loop until the user chooses to exit
        displayMenu();
        userInput = getValidInteger(); // Get user input
        // Handle the user's choice
        switch (userInput) {
            case Insert:
                printf("Option 1 selected: Add a New Student.\n");
                insertStudent();
                // Add functionality for adding a new student
                break;
            case Delete:
                printf("Option 2 selected: Remove a Student.\n");
                removeStudent();
                // Add functionality for removing a student
                break;
            case Edit:
                printf("Option 3 selected: Edit Student Information.\n");
                editStudent();
                // Add functionality for editing student information
                break;
            case Search:
                printf("Option 4 selected: Search for Student.\n");
                searchStudent();
                // Add functionality for searching for a student
                break;
            case Top10:
                printf("Option 5 selected: Query Top 10 Outstanding Students.\n");
                topTenStudent();
                // Add functionality for querying top 10 students
                break;
            case UnderperformedStudents:
                printf("Option 6 selected: List Students Eligible for Departure.\n");
                // Add functionality for listing students eligible for departure
                break;
            case Average:
                printf("Option 7 selected: Calculate Average Grade per Course per Layer.\n");
                averagePerCourse();
                // Add functionality for calculating average grade
                break;
            case Export:
                printf("Option 8 selected: Export Entire Database to File.\n");
                // Add functionality for exporting the database
                break;
            case Exit:
                printf("Exiting the program. Goodbye!\n");
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please select an option between 1 and 9.\n");
                break;
        }
    }
}
