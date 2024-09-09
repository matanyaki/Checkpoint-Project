#ifndef DATABASE_H
#define DATABASE_H

#define MAX_SUBJECTS 10
#define HASH_TABLE_SIZE 100003  // A prime number for better distribution

// Structure to store each student's information
typedef struct Student {
    char first_name[50];
    char last_name[50];
    char telephone[11];      // Added telephone field
    int layer;               // Layer field
    int class_id;            // Class ID field
    int grades[MAX_SUBJECTS]; // Array to store grades for different subjects
    struct Student *next;     // Pointer for chaining in hash table
} Student;

// Hash table for students
extern Student *hashTable[HASH_TABLE_SIZE];

// Function declarations
unsigned int hash(const char *first_name, const char *last_name);
void add_student(const char *first_name, const char *last_name, const char *telephone, int layer, int class_id, int grades[MAX_SUBJECTS]);
void remove_student(const char *first_name, const char *last_name);
void update_grade(const char *first_name, const char *last_name, int subject_id, int grade);
void print_student(const char *first_name, const char *last_name);
void find_top_students(int subject_id);
void calculate_average(int subject_id);
void load_data_from_file(const char *filename); // New function to load data

#endif
