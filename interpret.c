#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "template.h"

#define MAX_LINE 2000
#define TAB_SIZE 4  

void processFile(const char *filename, Scope* currentScope) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int expectedIndent = 0; // Tracks expected indentation level
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        int indent = 0, spaceCount = 0, i=0;
        while (line[i] == ' ') {
           spaceCount++;
           if (spaceCount == TAB_SIZE) {
             indent++; 
             spaceCount = 0;
           }
           i++;
        }

        // Check indentation consistency
        if (indent > expectedIndent) {
            printf("DEBUG: indent=%d, expectedIndent=%d, line: %s\n", indent, expectedIndent, line);
            fprintf(stderr, "Error: Unexpected indentation at line: %s", line);
            fclose(file);
            return;
        }

        // Trim leading whitespace
        char *token = line + indent;
        while (*token == ' ') token++;  

        // Process command
        if (strncmp(token, "begin", 5) == 0) {
            if (indent != expectedIndent) {
                fprintf(stderr, "Error: Incorrect indentation for 'begin'\n");
                fclose(file);
                return;
            }
            createScope(&currentScope);
            expectedIndent++;  // Increase expected indentation
        } else if (strncmp(token, "end", 3) == 0) {
            if (indent != expectedIndent - 1) {
                fprintf(stderr, "Error: Incorrect indentation for 'end'\n");
                fclose(file);
                return;
            }
            
            deleteScope(&currentScope);
            expectedIndent--;  // Decrease expected indentation
            
        } else if (strncmp(token, "assign", 6) == 0) {
            char var[1000];
            int value;
            if (sscanf(token, "assign %s %d", var, &value) != 2) {
                fprintf(stderr, "Error: Invalid assignment syntax at line: %s", line);
                fclose(file);
                return;
            }
            insertVar(currentScope,var,value);
        } else if (strncmp(token, "print", 5) == 0) {
            char var[1000];
            if (sscanf(token, "print %s", var) != 1) {
                fprintf(stderr, "Error: Invalid print syntax at line: %s", line);
                fclose(file);
                return;
            }
            lookup(currentScope,var);
        } else {
            fprintf(stderr, "Error: Unknown command at line: %s", line);
            fclose(file);
            return;
        }
    }
  fclose(file);
}
