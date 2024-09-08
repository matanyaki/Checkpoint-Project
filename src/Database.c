#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Database.h"

// Initialize the hash table with NULL values
Student* hashTable[HASH_TABLE_SIZE] = {NULL};

// Hash function to calculate index for student name
unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str)
        hash = (hash << 5) + *str++;
    return hash % HASH_TABLE_SIZE;
}

// Add a new student
void add_student(const char* name) {
    unsigned int index = hash(name);
    Student* new_student = (Student*)malloc(sizeof(Student));
    strcpy(new_student->name, name);
    for (int i = 0; i < MAX_SUBJECTS; i++) new_student->grades[i] = -1;  // Initialize with no grades
    new_student->next = hashTable[index];
    hashTable[index] = new_student;
}

// Remove a student
void remove_student(const char* name) {
    unsigned int index = hash(name);
    Student* student = hashTable[index];
    Student* prev = NULL;

    while (student != NULL && strcmp(student->name, name) != 0) {
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

// Update a student's grade
void update_grade(const char* name, int subject_id, int grade) {
    unsigned int index = hash(name);
    Student* student = hashTable[index];

    while (student != NULL && strcmp(student->name, name) != 0) {
        student = student->next;
    }

    if (student == NULL) {
        printf("Student not found!\n");
        return;
    }

    student->grades[subject_id] = grade;
}

// Print details of a student
void print_student(const char* name) {
    unsigned int index = hash(name);
    Student* student = hashTable[index];

    while (student != NULL && strcmp(student->name, name) != 0) {
        student = student->next;
    }

    if (student == NULL) {
        printf("Student not found!\n");
        return;
    }

    printf("Student: %s\n", student->name);
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
    char top_names[10][50] = {0};

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        student = hashTable[i];
        while (student != NULL) {
            if (student->grades[subject_id] != -1) {
                for (int j = 0; j < 10; j++) {
                    if (student->grades[subject_id] > top_students[j]) {
                        for (int k = 9; k > j; k--) {
                            top_students[k] = top_students[k - 1];
                            strcpy(top_names[k], top_names[k - 1]);
                        }
                        top_students[j] = student->grades[subject_id];
                        strcpy(top_names[j], student->name);
                        break;
                    }
                }
            }
            student = student->next;
        }
    }

    printf("Top 10 students in subject %d:\n", subject_id);
    for (int i = 0; i < 10; i++) {
        if (top_students[i] != 0) {
            printf("Student: %s, Grade: %d\n", top_names[i], top_students[i]);
        }
    }
}

// Calculate average grade for a subject
void calculate_average(int subject_id) {
    Student* student;
    int sum = 0, count = 0;

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        student = hashTable[i];
        while (student != NULL) {
            if (student->grades[subject_id] != -1) {
                sum += student->grades[subject_id];
                count++;
            }
            student = student->next;
        }
    }

    if (count == 0) {
        printf("No grades available for subject %d.\n", subject_id);
        return;
    }

    printf("Average grade for subject %d: %.2f\n", subject_id, (float)sum / count);
}
