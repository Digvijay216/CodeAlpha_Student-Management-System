#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student
{
    int iRollNo;
    char szName[50];
    float fMarks;
} STUDENT;

void AddStudent(void);
void DisplayStudents(void);
void SearchStudent(void);
void UpdateStudent(void);
void DeleteStudent(void);

int main(void)
{
    int iChoice = 0;

    do
    {
        printf("\n====================================");
        printf("\n     STUDENT MANAGEMENT SYSTEM");
        printf("\n====================================");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");

        printf("\n\nEnter Your Choice : ");
        scanf("%d", &iChoice);

        switch(iChoice)
        {
            case 1:
                AddStudent();
                break;

            case 2:
                DisplayStudents();
                break;

            case 3:
                SearchStudent();
                break;

            case 4:
                UpdateStudent();
                break;

            case 5:
                DeleteStudent();
                break;

            case 6:
                printf("\nThank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(iChoice != 6);

    return 0;
}

void AddStudent(void)
{
    FILE *pFile = NULL;
    STUDENT stStudent;

    pFile = fopen("Student.dat", "ab");

    if(pFile == NULL)
    {
        printf("\nUnable to Open File!\n");
        return;
    }

    printf("\nEnter Roll Number : ");
    scanf("%d", &stStudent.iRollNo);

    printf("Enter Name : ");
    scanf(" %[^\n]", stStudent.szName);

    printf("Enter Marks : ");
    scanf("%f", &stStudent.fMarks);

    fwrite(&stStudent, sizeof(STUDENT), 1, pFile);

    fclose(pFile);

    printf("\nStudent Added Successfully!\n");
}

void DisplayStudents(void)
{
    FILE *pFile = NULL;
    STUDENT stStudent;

    pFile = fopen("Student.dat", "rb");

    if(pFile == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n=================================================");
    printf("\nRoll No\t\tName\t\t\tMarks");
    printf("\n=================================================\n");

    while(fread(&stStudent, sizeof(STUDENT), 1, pFile))
    {
        printf("%d\t\t%-20s\t%.2f\n",
               stStudent.iRollNo,
               stStudent.szName,
               stStudent.fMarks);
    }

    fclose(pFile);
}

void SearchStudent(void)
{
    FILE *pFile = NULL;
    STUDENT stStudent;

    int iRollNo = 0;
    int bFound = 0;

    pFile = fopen("Student.dat", "rb");

    if(pFile == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search : ");
    scanf("%d", &iRollNo);

    while(fread(&stStudent, sizeof(STUDENT), 1, pFile))
    {
        if(stStudent.iRollNo == iRollNo)
        {
            printf("\nStudent Found");
            printf("\n------------------------");
            printf("\nRoll Number : %d", stStudent.iRollNo);
            printf("\nName        : %s", stStudent.szName);
            printf("\nMarks       : %.2f\n", stStudent.fMarks);

            bFound = 1;
            break;
        }
    }

    if(bFound == 0)
    {
        printf("\nStudent Not Found!\n");
    }

    fclose(pFile);
}

void UpdateStudent(void)
{
    FILE *pFile = NULL;
    STUDENT stStudent;

    int iRollNo = 0;
    int bFound = 0;

    pFile = fopen("Student.dat", "rb+");

    if(pFile == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update : ");
    scanf("%d", &iRollNo);

    while(fread(&stStudent, sizeof(STUDENT), 1, pFile))
    {
        if(stStudent.iRollNo == iRollNo)
        {
            printf("\nEnter New Name : ");
            scanf(" %[^\n]", stStudent.szName);

            printf("Enter New Marks : ");
            scanf("%f", &stStudent.fMarks);

            fseek(pFile, -sizeof(STUDENT), SEEK_CUR);

            fwrite(&stStudent, sizeof(STUDENT), 1, pFile);

            bFound = 1;

            printf("\nRecord Updated Successfully!\n");
            break;
        }
    }

    if(bFound == 0)
    {
        printf("\nStudent Not Found!\n");
    }

    fclose(pFile);
}

void DeleteStudent(void)
{
    FILE *pFile = NULL;
    FILE *pTempFile = NULL;

    STUDENT stStudent;

    int iRollNo = 0;
    int bFound = 0;

    pFile = fopen("Student.dat", "rb");

    if(pFile == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    pTempFile = fopen("Temp.dat", "wb");

    if(pTempFile == NULL)
    {
        printf("\nUnable to Create Temporary File!\n");
        fclose(pFile);
        return;
    }

    printf("\nEnter Roll Number to Delete : ");
    scanf("%d", &iRollNo);

    while(fread(&stStudent, sizeof(STUDENT), 1, pFile))
    {
        if(stStudent.iRollNo == iRollNo)
        {
            bFound = 1;
        }
        else
        {
            fwrite(&stStudent, sizeof(STUDENT), 1, pTempFile);
        }
    }

    fclose(pFile);
    fclose(pTempFile);

    remove("Student.dat");
    rename("Temp.dat", "Student.dat");

    if(bFound)
    {
        printf("\nRecord Deleted Successfully!\n");
    }
    else
    {
        printf("\nStudent Not Found!\n");
    }
}