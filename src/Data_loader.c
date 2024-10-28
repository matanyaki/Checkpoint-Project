#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Database.h"

#define MAX_LINE_LENGTH 256
#define PHONE_NUM_LENGTH 11

// Function to load data from the file and insert it into the student database
void load_data_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        // Variables to store parsed data
        char first_name[50], last_name[50], telephone[PHONE_NUM_LENGTH];
        int layer, class_id, grades[MAX_SUBJECTS];

        // Parse the line into the respective fields
        int parsed = sscanf(line, "%s %s %s %d %d %d %d %d %d %d %d %d %d %d %d",
                            first_name, last_name, telephone, &layer, &class_id,
                            &grades[0], &grades[1], &grades[2], &grades[3],
                            &grades[4], &grades[5], &grades[6], &grades[7], &grades[8], &grades[9]);

        // Check if the line was parsed correctly (15 items)
        if (parsed == 15) {
            // Insert the student data into the database using the new add_student function
            add_student(first_name, last_name, telephone, layer, class_id, grades);

        } else {
            fprintf(stderr, "Failed to parse line: %s", line);
        }
    }

    fclose(file);
}


// Function to export data from the database to a file
void export_data_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Iterate through the hash table
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Student *student = hashTable[i];
        while (student != NULL) {
            // Export each student's data in the same format as the input
            fprintf(file, "%s %s %s %d %d",
                    student->first_name, student->last_name, student->telephone,
                    student->layer, student->class_id);
            for (int j = 0; j < MAX_SUBJECTS; j++) {
                fprintf(file, " %d", student->grades[j]);
            }
            fprintf(file, "\n");
            student = student->next;
        }
    }

    fclose(file);
}
