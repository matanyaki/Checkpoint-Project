#ifndef STUDENTS_DB_H
#define STUDENTS_DB_H

// Constants
#define MAX_SUBJECTS 10
#define HASH_TABLE_SIZE 100003

// Structure to store each student's information
typedef struct Student {
    char name[50];
    int grades[MAX_SUBJECTS];
    struct Student* next;  // For chaining in hash table
} Student;

// Hash table for students
extern Student* hashTable[HASH_TABLE_SIZE];

// Function declarations
unsigned int hash(const char* str);
void add_student(const char* name);
void remove_student(const char* name);
void update_grade(const char* name, int subject_id, int grade);
void print_student(const char* name);
void find_top_students(int subject_id);
void calculate_average(int subject_id);

#endif
