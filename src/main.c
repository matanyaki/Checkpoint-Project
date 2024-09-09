#include <stdio.h>
#include "Database.h"

// Function to print the first 5 students in the database
void print_first_five_students() {
    int printed_students = 0;
    
    for (int i = 0; i < HASH_TABLE_SIZE && printed_students < 5; i++) {
        Student *student = hashTable[i];
        while (student != NULL && printed_students < 5) {
            printf("Student #%d:\n", printed_students + 1);
            print_student(student->first_name, student->last_name);  // Use the print_student function to print details
            student = student->next;
            printed_students++;
        }
    }
}

//int main() {
//    // Load data from file
//    const char *filename = "students_with_class.txt";
//    load_data_from_file(filename);
//
//    // Print the first 5 students
//    printf("Printing the first 5 students:\n");
//    print_first_five_students();
//
//    export_data_to_file("newdbfile.txt");
//    return 0;
//}
