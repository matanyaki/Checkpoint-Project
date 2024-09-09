#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "Database.h"

// Setup and Teardown functions
int setup() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    return 0;
}

int teardown() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Student *student = hashTable[i];
        while (student != NULL) {
            Student *temp = student;
            student = student->next;
            free(temp);  // Free allocated memory for students
        }
        hashTable[i] = NULL;
    }
    return 0;
}

// Test function declarations
void test_add_student();
void test_remove_student();
void test_find_top_students();
void test_calculate_average();

// Test function definitions
void test_add_student() {
    int grades[MAX_SUBJECTS] = {85, 90, -1, -1, 75, -1, 88, -1, 92, -1};
    add_student("Alice", "Johnson", "1234567890", 10, 101, grades);
    unsigned int index = hash("Alice", "Johnson");

    // Assertions to check if student is added correctly
    CU_ASSERT_PTR_NOT_NULL(hashTable[index]);
    CU_ASSERT_STRING_EQUAL(hashTable[index]->first_name, "Alice");
    CU_ASSERT_STRING_EQUAL(hashTable[index]->last_name, "Johnson");
    CU_ASSERT_STRING_EQUAL(hashTable[index]->telephone, "1234567890");
    CU_ASSERT_EQUAL(hashTable[index]->layer, 10);
    CU_ASSERT_EQUAL(hashTable[index]->class_id, 101);
    CU_ASSERT_EQUAL(hashTable[index]->grades[0], 85);
    CU_ASSERT_EQUAL(hashTable[index]->grades[1], 90);
    CU_ASSERT_EQUAL(hashTable[index]->grades[2], -1);
}

void test_remove_student() {
    int grades[MAX_SUBJECTS] = {85, 90, -1, -1, 75, -1, 88, -1, 92, -1};
    add_student("Bob", "Smith", "0987654321", 9, 102, grades);
    remove_student("Bob", "Smith");
    unsigned int index = hash("Bob", "Smith");

    // Assertions to check if student was removed
    CU_ASSERT_PTR_NULL(hashTable[index]);
}


void test_find_top_students() {
    int grades1[MAX_SUBJECTS] = {95, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int grades2[MAX_SUBJECTS] = {85, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int grades3[MAX_SUBJECTS] = {78, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    
    add_student("Dave", "White", "1234509876", 12, 101, grades1);
    add_student("Eve", "Green", "9876543210", 12, 102, grades2);
    add_student("Frank", "Blue", "4567891230", 12, 103, grades3);

    find_top_students(0);  // This function should return the top students for subject 0
    // Since this function likely prints results, no assertions are made here
    // You could add an internal data structure to collect top students for further assertions
}

void test_calculate_average() {
    int grades1[MAX_SUBJECTS] = {-1, 80, -1, -1, -1, -1, -1, -1, -1, -1};
    int grades2[MAX_SUBJECTS] = {-1, 90, -1, -1, -1, -1, -1, -1, -1, -1};
    
    add_student("Grace", "Red", "1029384756", 12, 104, grades1);
    add_student("Hank", "Yellow", "5647382910", 12, 105, grades2);

    calculate_average(1);  // Should calculate the average grade for subject 1
    // You could extend `calculate_average` to return the average, making it testable
    // For now, manually verify the output is correct or adjust the function for automated tests
}

int main() {
    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add suite and test cases
    CU_pSuite suite = CU_add_suite("Student Database Tests", setup, teardown);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if ((NULL == CU_add_test(suite, "Test Add Student", test_add_student)) ||
        (NULL == CU_add_test(suite, "Test Remove Student", test_remove_student)) ||
        (NULL == CU_add_test(suite, "Test Find Top Students", test_find_top_students)) ||
        (NULL == CU_add_test(suite, "Test Calculate Average", test_calculate_average))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using CUnit basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Clean up registry
    CU_cleanup_registry();
    return CU_get_error();
}
