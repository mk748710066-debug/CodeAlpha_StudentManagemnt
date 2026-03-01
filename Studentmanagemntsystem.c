#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

// ADD RECORD
void addStudent() {
    FILE *fp = fopen("student.dat", "ab");
    struct Student s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record Added Successfully!\n");
}

// DISPLAY RECORDS
void displayStudents() {
    FILE *fp = fopen("student.dat", "rb");
    struct Student s;

    printf("\n--- Student Records ---\n");

    while(fread(&s, sizeof(s), 1, fp))
        printf("ID:%d  Name:%s  Marks:%.2f\n", s.id, s.name, s.marks);

    fclose(fp);
}

// SEARCH RECORD
void searchStudent() {
    FILE *fp = fopen("student.dat", "rb");
    struct Student s;
    int id, found = 0;

    printf("Enter ID to Search: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            printf("Record Found -> ID:%d Name:%s Marks:%.2f\n",
                   s.id, s.name, s.marks);
            found = 1;
        }
    }

    if(!found)
        printf("Record Not Found!\n");

    fclose(fp);
}

// DELETE RECORD
void deleteStudent() {
    FILE *fp = fopen("student.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Student s;
    int id, found = 0;

    printf("Enter ID to Delete: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id != id)
            fwrite(&s, sizeof(s), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if(found)
        printf("Record Deleted Successfully!\n");
    else
        printf("Record Not Found!\n");
}

// UPDATE RECORD
void updateStudent() {
    FILE *fp = fopen("student.dat", "rb+");
    struct Student s;
    int id, found = 0;

    printf("Enter ID to Update: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    if(found)
        printf("Record Updated Successfully!\n");
    else
        printf("Record Not Found!\n");

    fclose(fp);
}

// MAIN MENU
int main() {
    int choice;

    do {
        printf("\n===== Student Record System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting Program...\n"); break;
            default: printf("Invalid Choice!\n");
        }

    } while(choice != 6);

    return 0;
}