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
        int layer, class_id, grades[10];

        // Parse the line into the respective fields
        int parsed = sscanf(line, "%s %s %s %d %d %d %d %d %d %d %d %d %d %d %d",
                            first_name, last_name, telephone, &layer, &class_id,
                            &grades[0], &grades[1], &grades[2], &grades[3],
                            &grades[4], &grades[5], &grades[6], &grades[7], &grades[8], &grades[9]);

        // Check if the line was parsed correctly (15 items)
        if (parsed == 15) {
            // Insert the student data into the database
            add_student(first_name, last_name , telephone , layer ,class_id , grades);

            // Update other information
            unsigned int index = hash(first_name, last_name);
            Student *student = hashTable[index];
            student->layer = layer;      // Store the layer
            student->class_id = class_id;   // Store the class
            strcpy(student->telephone, telephone);  // Store the telephone number
            for (int i = 0; i < 10; i++) {
                student->grades[i] = grades[i];  // Store grades in the grades array
            }
        } else {
            fprintf(stderr, "Failed to parse line: %s", line);
        }
    }

    fclose(file);
}
