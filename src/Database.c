#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Database.h"

// Initialize the hash table with NULL values
Student *hashTable[HASH_TABLE_SIZE] = {NULL};

// Hash function to calculate index for first and last name
unsigned int hash(const char *first_name, const char *last_name) {
    unsigned int hash = 0;
    while (*first_name)
        hash = (hash << 5) + *first_name++;
    while (*last_name)
        hash = (hash << 5) + *last_name++;
    return hash % HASH_TABLE_SIZE;
}

// Add a new student

void add_student(const char *first_name, const char *last_name, const char *telephone, int layer, int class_id, int grades[MAX_SUBJECTS])
{

    unsigned int index = hash(first_name, last_name);

    // Create a new student and allocate memory
    Student *new_student = (Student *)malloc(sizeof(Student));
    if (new_student == NULL) {
        // Handle memory allocation failure (no print but can log if needed)
        return;
    }

    // Assign first and last name
    strncpy(new_student->first_name, first_name, sizeof(new_student->first_name) - 1);
    new_student->first_name[sizeof(new_student->first_name) - 1] = '\0'; // Ensure null termination

    strncpy(new_student->last_name, last_name, sizeof(new_student->last_name) - 1);
    new_student->last_name[sizeof(new_student->last_name) - 1] = '\0'; // Ensure null termination

    // Assign telephone, layer, and class_id
    strncpy(new_student->telephone, telephone, sizeof(new_student->telephone) - 1);
    new_student->telephone[sizeof(new_student->telephone) - 1] = '\0'; // Ensure null termination
    new_student->layer = layer;
    new_student->class_id = class_id;

    // Assign grades
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        new_student->grades[i] = grades[i]; // Assign each grade directly
    }

    // Insert the new student at the head of the list for the hash index
    new_student->next = hashTable[index];
    hashTable[index]  = new_student;
}

Student* get_student(const char *first_name, const char *last_name) {
    unsigned int index = hash(first_name, last_name);
    Student *student = hashTable[index];

    // Traverse the linked list at the hash index to find the student
    while (student != NULL) {
        if (strcmp(student->first_name, first_name) == 0 && strcmp(student->last_name, last_name) == 0) {
            return student; // Student found
        }
        student = student->next;
    }
    return NULL; // Student not found
}

int set_student(const char* old_first_name, const char* old_last_name, const char* new_first_name, const char* new_last_name, const char* telephone, int layer, int class_id, int grades[MAX_SUBJECTS]) {
    Student* student = get_student(old_first_name, old_last_name);

    if (student == NULL) {
        return -1; // Student not found
    }

    remove_student(old_first_name, old_last_name); // Remove the student from the old location in the hash table
    add_student(new_first_name, new_last_name, telephone, layer, class_id, grades); // Add the student to the new location in the hash table




    return 0; // Success
}
// Remove a student
void remove_student(const char *first_name, const char *last_name) {
    unsigned int index = hash(first_name, last_name);
    Student *student = hashTable[index];
    Student *prev = NULL;

    while (student != NULL && (strcmp(student->first_name, first_name) != 0 || strcmp(student->last_name, last_name) != 0)) {
        prev = student;
        student = student->next;
    }

    if (student == NULL) {
        printf("Student not found!\n");
        return;
    }

    if (prev == NULL) {
        hashTable[index] = student->next;
    } else {
        prev->next = student->next;
    }

    free(student);
}


// Print details of a student
void print_student(const char *first_name, const char *last_name) {
    unsigned int index = hash(first_name, last_name);
    Student *student = hashTable[index];

    while (student != NULL && (strcmp(student->first_name, first_name) != 0 || strcmp(student->last_name, last_name) != 0)) {
        student = student->next;
    }

    if (student == NULL) {
        printf("Student not found!\n");
        return;
    }

    printf("Student: %s %s\n", student->first_name, student->last_name);
    printf("Telephone: %s\n", student->telephone);
    printf("Layer: %d, Class: %d\n", student->layer, student->class_id);
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        if (student->grades[i] != -1) {
            printf("Subject %d: %d\n", i, student->grades[i]);
        }
    }
}


// Find top 10 students in a subject

void find_top_students(int subject_id) {
    Student* student;
    int top_students[10] = {0};
    char top_names[10][100] = {0};  // Updated to store full names (first + last)

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        student = hashTable[i];
        while (student != NULL) {
            if (student->grades[subject_id] != -1) {
                // Build the full name from first_name and last_name
                char full_name[100];
                snprintf(full_name, sizeof(full_name), "%s %s", student->first_name, student->last_name);

                // Insert the student into the top 10 if they qualify
                for (int j = 0; j < 10; j++) {
                    if (student->grades[subject_id] > top_students[j]) {
                        // Shift the other entries down
                        for (int k = 9; k > j; k--) {
                            top_students[k] = top_students[k - 1];
                            strcpy(top_names[k], top_names[k - 1]);
                        }
                        // Insert the new top student
                        top_students[j] = student->grades[subject_id];
                        strcpy(top_names[j], full_name);
                        break;
                    }
                }
            }
            student = student->next;
        }
    }

    // Print the top 10 students
    printf("Top 10 students in subject %d:\n", subject_id);
    for (int i = 0; i < 10; i++) {
        if (top_students[i] != 0) {
            printf("Student: %s, Grade: %d\n", top_names[i], top_students[i]);
        }
    }
}

// Calculate average grade for a subject in a specific layer
void calculate_and_print_average_per_layer(int subject_id, int layer) {
    Student* student;
    int sum = 0, count = 0;

    // Loop through the entire hash table
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        student = hashTable[i];
        while (student != NULL) {
            // Check if the student is in the specified layer and has a valid grade
            if (student->layer == layer && student->grades[subject_id] != -1) {
                sum += student->grades[subject_id];
                count++;
            }
            student = student->next;
        }
    }

    // If no students found, print a message
    if (count == 0) {
        printf("No grades available for subject %d in layer %d.\n", subject_id, layer);
        return;
    }

    // Print the calculated average
    printf("Average grade for subject %d in layer %d: %.2f\n", subject_id, layer, (float)sum / count);
}
