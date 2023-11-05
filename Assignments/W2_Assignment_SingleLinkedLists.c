#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to hold student information
struct Student {
    int number;
    char name[100];
    int age;
};

// Node structure for linked list
struct Node {
    struct Student data;
    struct Node* next;
};

// Q1. Write a function that adds all odd numbers to the beginning and even
// numbers to the end of the list until -1 is entered from the keyboard.
void addNumbersToList(struct Node** head) {
    int num;
    struct Node* current = *head;
    struct Node* newNode;

    printf("Enter numbers. Enter -1 to stop.\n");
    while (1) {
        scanf("%d", &num);
        if (num == -1) {
            break;
        }

        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data.number = num;
        newNode->next = NULL;

        if (num % 2 == 1) {
            newNode->next = *head;
            *head = newNode;
        } else {
            if (current == NULL) {
                *head = newNode;
            } else {
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }
}

// Q2. Add 100 randomly generated numbers to the list, write the C code that
// sorts all the numbers entered from largest to smallest and prints them on the screen.
void addAndSortRandomNumbers(struct Node** head) {
    // Add 100 random numbers
    for (int i = 0; i < 100; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data.number = rand() % 1000;
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
        } else {
            struct Node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Sort the list in descending order
    struct Node* sortedList = NULL;
    struct Node* current = *head;
    while (current != NULL) {
        struct Node* next = current->next;
        struct Node* sortedCurrent = sortedList;
        struct Node* sortedPrev = NULL;

        while (sortedCurrent != NULL && sortedCurrent->data.number > current->data.number) {
            sortedPrev = sortedCurrent;
            sortedCurrent = sortedCurrent->next;
        }

        if (sortedPrev == NULL) {
            current->next = sortedList;
            sortedList = current;
        } else {
            sortedPrev->next = current;
            current->next = sortedCurrent;
        }

        current = next;
    }

    *head = sortedList;
}

// Q3.  Function to print the list of numbers
void printNumbers(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data.number);
        if (current->next != NULL) {
            printf("->");
        }
        current = current->next;
    }
    printf("\n");
}

// Q4. Write a function that stores the student number, name and age, traverses all the nodes in
// the list, writes all the student information on the screen and counts it.

void addStudent(struct Node** head, int number, const char* name, int age) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data.number = number;
    strncpy(newNode->data.name, name, sizeof(newNode->data.name));
    newNode->data.age = age;
    newNode->next = *head;
    *head = newNode;
}

void printStudents(struct Node* head) {
    struct Node* current = head;
    int count = 0;
    while (current != NULL) {
        printf("%d) %s %d %d\n", count + 1, current->data.name, current->data.age, current->data.number);
        current = current->next;
        count++;
    }
    printf("Total students: %d\n", count);
}

// Q5. Write the function that searches records by student name in the list.
void searchStudentByName(struct Node* head, const char* name) {
    struct Node* current = head;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            printf("Student found: %d) %s %d %d\n", current->data.number, current->data.name, current->data.age, current->data.number);
            return;
        }
        current = current->next;
    }
    printf("Student not found with name: %s\n", name);
}

// Q6. Write the function that deletes the next node from the node with the searched student name in the list.
void deleteNextNodeByName(struct Node** head, const char* name) {
    struct Node* current = *head;
    while (current != NULL) {
        if (current->next != NULL && strcmp(current->next->data.name, name) == 0) {
            struct Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            printf("Next node after %s deleted.\n", name);
            return;
        }
        current = current->next;
    }
    printf("No matching student found for deletion after %s.\n", name);
}

// Q7. Write the function that prints the record with the longest name in the list.
void printLongestName(struct Node* head) {
    int maxLength = 0;
    const char* longestName = NULL;

    struct Node* current = head;
    while (current != NULL) {
        int nameLength = strlen(current->data.name);
        if (nameLength > maxLength) {
            maxLength = nameLength;
            longestName = current->data.name;
        }
        current = current->next;
    }

    if (longestName != NULL) {
        printf("The longest name in the list: %s\nLength: %d\n", longestName, maxLength);
    } else {
        printf("No names found in the list.\n");
    }
}

int main() {
    struct Node* head = NULL;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add odd numbers to the beginning and even numbers to the end of the list\n");
        printf("2. Add 100 random numbers and sort them\n");
        printf("3. Print the list of numbers\n");
        printf("4. Add a student record to the list\n");
        printf("5. Print all student records and count them\n");
        printf("6. Search for a student by name\n");
        printf("7. Delete the next node after a student by name\n");
        printf("8. Print the record with the longest name\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNumbersToList(&head);
                break;
            case 2:
                addAndSortRandomNumbers(&head);
                break;
            case 3:
                printNumbers(head);
                break;
            case 4:
                {
                    int number, age;
                    char name[100];
                    printf("Enter student number, name, and age: ");
                    scanf("%d %s %d", &number, name, &age);
                    addStudent(&head, number, name, age);
                }
                break;
            case 5:
                printStudents(head);
                break;
            case 6:
                {
                    char name[100];
                    printf("Enter the name to search: ");
                    scanf("%s", name);
                    searchStudentByName(head, name);
                }
                break;
            case 7:
                {
                    char name[100];
                    printf("Enter the name to delete the next node after: ");
                    scanf("%s", name);
                    deleteNextNodeByName(&head, name);
                }
                break;
            case 8:
                printLongestName(head);
                break;
            case 9:
                // Free memory and exit
                while (head != NULL) {
                    struct Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


