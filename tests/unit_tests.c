#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>  // for free()
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
void test_update_grade();
void test_find_top_students();
void test_calculate_average();

// Test function definitions
void test_add_student() {
    add_student("Alice");
    unsigned int index = hash("Alice");
    CU_ASSERT_PTR_NOT_NULL(hashTable[index]);
    CU_ASSERT_STRING_EQUAL(hashTable[index]->name, "Alice");
}

void test_remove_student() {
    add_student("Bob");
    remove_student("Bob");
    unsigned int index = hash("Bob");
    CU_ASSERT_PTR_NULL(hashTable[index]);
}

void test_update_grade() {
    add_student("Charlie");
    update_grade("Charlie", 2, 85);
    unsigned int index = hash("Charlie");
    CU_ASSERT_EQUAL(hashTable[index]->grades[2], 85);
}

void test_find_top_students() {
    add_student("Dave");
    update_grade("Dave", 1, 95);
    add_student("Eve");
    update_grade("Eve", 1, 88);
    find_top_students(1);  // This prints results, you can manually verify
}

void test_calculate_average() {
    add_student("Frank");
    update_grade("Frank", 3, 80);
    add_student("Grace");
    update_grade("Grace", 3, 100);
    calculate_average(3);  // This also prints results, manually verify average is correct
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
        (NULL == CU_add_test(suite, "Test Update Grade", test_update_grade)) ||
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
