#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee
{
    int id;
    char fullname[100];
    char gender;
    char designation[100];
    float salary;
    char mobile[15];
    char address[100];
};

void addEmployee(struct Employee employees[], int *count);
void deleteEmployee(struct Employee employees[], int *count);
void editEmployee(struct Employee employees[], int count);
void displaySpecificEmployee(struct Employee employees[], int count);
void displayAllEmployees(struct Employee employees[], int count);
void deleteAllEmployees(int *count);
void showOnlyMaleEmployees(struct Employee employees[], int count);
void showOnlyFemaleEmployees(struct Employee employees[], int count);
void saveEmployeesToFile(struct Employee employees[], int count);
void loadEmployeesFromFile(struct Employee employees[], int *count);

int main()
{
    struct Employee employees[100];
    int count = 0;
    int choice;

    loadEmployeesFromFile(employees, &count);

    printf("\n\t\t\tEMPLOYEE MANAGEMENT SYSTEM\t\t\t\n");
    printf("\n\t\t\t  NAHID HASAN CHOWDHURY\t\t\t\n");
    printf("\n\t\t\t       212-15-4125\t\t\t\n");
    printf("\n\t\t\t           59_A\t\t\t\n");
    printf("\n\t\t\t   COMPILER DESIGN LAB\t\t\t\n");

    while (1)
    {
        printf("\n\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Delete Specific Employee\n");
        printf("3. Edit Specific Employee\n");
        printf("4. Display Specific Employee\n");
        printf("5. Display All Employee\n");
        printf("6. Delete All Employee\n");
        printf("7. Show Only Male Employees\n");
        printf("8. Show Only Female Employees\n");
        printf("9. Save Employees to File\n");
        printf("10. Load Employees from File\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addEmployee(employees, &count);
            break;
        case 2:
            deleteEmployee(employees, &count);
            break;
        case 3:
            editEmployee(employees, count);
            break;
        case 4:
            displaySpecificEmployee(employees, count);
            break;
        case 5:
            displayAllEmployees(employees, count);
            break;
        case 6:
            deleteAllEmployees(&count);
            break;
        case 7:
            showOnlyMaleEmployees(employees, count);
            break;
        case 8:
            showOnlyFemaleEmployees(employees, count);
            break;
        case 9:
            saveEmployeesToFile(employees, count);
            break;
        case 10:
            loadEmployeesFromFile(employees, &count);
            break;
        case 11:
            printf("\nExiting program...\n");
            saveEmployeesToFile(employees, count);
            return 0;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addEmployee(struct Employee employees[], int *count)
{

    if (*count >= 100)
    {
        printf("\nMaximum employees limit reached.\n");
        return;
    }

    struct Employee emp;
    int validInput = 0;

add:
    while (!validInput)
    {
        printf("Enter employee ID: ");
        if (scanf("%d", &emp.id) != 1)
        {
            printf("\nWrong format. Please enter a valid integer ID.\n");

            while (getchar() != '\n')
                ;
        }
        else
        {
            validInput = 1;

            for (int i = 0; i < *count; i++)
            {
                if (employees[i].id == emp.id)
                {
                    printf("\nEmployee with this ID already exists. Enter Again\n");
                    validInput = 0;
                    goto add;
                }
            }
        }
    }

    printf("Enter full name: ");
    getchar();
    fgets(emp.fullname, sizeof(emp.fullname), stdin);
    emp.fullname[strcspn(emp.fullname, "\n")] = 0;

    validInput = 0;
    while (!validInput)
    {
        printf("Enter gender (M/F): ");
        scanf(" %c", &emp.gender);
        if (emp.gender == 'M' || emp.gender == 'F')
        {
            validInput = 1;
        }
        else
        {
            printf("\nInvalid input. Please enter 'M' for Male or 'F' for Female.\n");

            while (getchar() != '\n')
                ;
        }
    }

    printf("Enter designation: ");
    getchar();
    fgets(emp.designation, sizeof(emp.designation), stdin);
    emp.designation[strcspn(emp.designation, "\n")] = 0;

    printf("Enter salary: ");
    scanf("%f", &emp.salary);

    printf("Enter mobile number: ");
    scanf("%s", emp.mobile);

    printf("Enter address: ");
    getchar();
    fgets(emp.address, sizeof(emp.address), stdin);
    emp.address[strcspn(emp.address, "\n")] = 0;

    employees[*count] = emp;
    (*count)++;

    printf("\nEmployee added successfully.\n");
}

void deleteEmployee(struct Employee employees[], int *count)
{

    int id;
del:
    printf("Enter ID of employee to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < *count; i++)
    {
        if (employees[i].id == id)
        {
            found = 1;
            for (int j = i; j < *count - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            (*count)--;
            printf("\nEmployee deleted successfully.\n");
            break;
        }
    }

    if (!found)
        printf("\nEmployee with ID %d not found. Enter Again\n", id);
}

void editEmployee(struct Employee employees[], int count)
{
    int id;
edit:
    printf("Enter ID of employee to edit: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input. Please enter a valid integer ID.\n");
        while (getchar() != '\n')
            ;
        goto edit;
    }

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (employees[i].id == id)
        {
            found = 1;
            printf("Enter new full name: ");
            getchar();
            fgets(employees[i].fullname, sizeof(employees[i].fullname), stdin);
            employees[i].fullname[strcspn(employees[i].fullname, "\n")] = 0;

            int validInput = 0;
            while (!validInput)
            {
                printf("Enter new gender (M/F): ");
                scanf(" %c", &employees[i].gender);
                if (employees[i].gender == 'M' || employees[i].gender == 'F')
                {
                    validInput = 1;
                }
                else
                {
                    printf("Invalid input. Please enter 'M' for Male or 'F' for Female.\n");

                    while (getchar() != '\n')
                        ;
                }
            }

            printf("Enter new designation: ");
            getchar();
            fgets(employees[i].designation, sizeof(employees[i].designation), stdin);
            employees[i].designation[strcspn(employees[i].designation, "\n")] = 0;

            printf("Enter new salary: ");
            scanf("%f", &employees[i].salary);

            printf("Enter new mobile number: ");
            scanf("%s", employees[i].mobile);

            printf("Enter new address: ");
            getchar();
            fgets(employees[i].address, sizeof(employees[i].address), stdin);
            employees[i].address[strcspn(employees[i].address, "\n")] = 0;

            printf("Employee details updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Employee with ID %d not found.\n", id);
        goto edit;
    }
}

void displaySpecificEmployee(struct Employee employees[], int count)
{
    int id;
    printf("\nEnter ID of employee to display: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (employees[i].id == id)
        {
            found = 1;
            printf("\nEmployee Details\n");
            printf("ID:  %d\n", employees[i].id);
            printf("Full Name: %s\n", employees[i].fullname);
            printf("Gender: %c\n", employees[i].gender);
            printf("Designation: %s\n", employees[i].designation);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("Mobile: %s\n", employees[i].mobile);
            printf("Address:%s\n", employees[i].address);
            break;
        }
    }

    if (!found)
        printf("\nEmployee with ID %d not found.\n", id);
}

void displayAllEmployees(struct Employee employees[], int count)
{
    printf("\nAll Employees\n");
    printf("ID\tFull Name\tGender\tDesignation\tSalary\tMobile\tAddress\n");
    for (int i = 0; i < count; i++)
    {
        printf(" %d\t %s\t\t%c\t%s\t\t%.2f\t%s\t%s\n", employees[i].id, employees[i].fullname, employees[i].gender, employees[i].designation, employees[i].salary, employees[i].mobile, employees[i].address);
    }
}

void deleteAllEmployees(int *count)
{
    *count = 0;
    printf("\nAll employees deleted successfully.\n");
}

void showOnlyMaleEmployees(struct Employee employees[], int count)
{
    printf("\nMale Employees\n");
    printf("ID\tFull Name\tGender\tDesignation\tSalary\tMobile\tAddress\n");
    for (int i = 0; i < count; i++)
    {
        if (employees[i].gender == 'M')
        {
            printf("%d\t%s\t%c\t%s\t%.2f\t%s\t%s\n", employees[i].id, employees[i].fullname, employees[i].gender, employees[i].designation, employees[i].salary, employees[i].mobile, employees[i].address);
        }
    }
}

void showOnlyFemaleEmployees(struct Employee employees[], int count)
{
    printf("\nFemale Employees\n");
    printf("ID\tFull Name\tGender\tDesignation\tSalary\tMobile\tAddress\n");
    for (int i = 0; i < count; i++)
    {
        if (employees[i].gender == 'F')
        {
            printf("%d\t%s\t%c\t%s\t%.2f\t%s\t%s\n", employees[i].id, employees[i].fullname, employees[i].gender, employees[i].designation, employees[i].salary, employees[i].mobile, employees[i].address);
        }
    }
}

void saveEmployeesToFile(struct Employee employees[], int count)
{
    FILE *file = fopen("employees.txt", "w");
    if (file == NULL)
    {
        printf("\nError opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%c,%s,%.2f,%s,%s\n", employees[i].id, employees[i].fullname, employees[i].gender, employees[i].designation, employees[i].salary, employees[i].mobile, employees[i].address);
    }

    fclose(file);
    printf("\nEmployee data saved to file successfully.\n");
}

void loadEmployeesFromFile(struct Employee employees[], int *count)
{
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL)
    {
        printf("\nError opening file for reading.\n");
        return;
    }

    *count = 0;
    while (!feof(file) && *count < 100)
    {
        fscanf(file, "%d,%[^,],%c,%[^,],%f,%[^,],%[^\n]\n", &employees[*count].id, employees[*count].fullname, &employees[*count].gender, employees[*count].designation, &employees[*count].salary, employees[*count].mobile, employees[*count].address);
        (*count)++;
    }

    fclose(file);
    printf("\nEmployee data loaded from file successfully.\n");
}
