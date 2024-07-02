#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct employee {
    int id;
    char name[50];
    float salary;
} e;
FILE *file;
int choicefunction_part_1(int n);
int choicefunction_part_2(int m);
void addEmployee();
void removeEmployee();
void printEmployees();
void sortEmployee();
int countEmployee();
int comparingfunction(const void *a, const void *b);
void searchEmployee();
int main() {
    int choice;
    printf("EMPLOYEE MANAGEMENT SYSTEM\n");
    printf("Please enter the choice or Press '0' to close :\n");
    printf("1. Add Employee\n");
    printf("2. Remove Employee\n");
    printf("3. Sort Employee List\n");
    printf("4. Search Employee\n");
    printf("Please enter choice: ");
    scanf("%d", &choice);
    choicefunction_part_1(choice);
    return 0;
}
void addEmployee() {
    file = fopen("EmployeeList.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Please enter ID: ");
    scanf("%d", &e.id);
    getchar(); 
    printf("Please enter Name of the Employee: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0'; 

    printf("Please enter salary in per month: ");
    scanf("%f", &e.salary);
    fprintf(file, "%d,%s,%.2f\n", e.id, e.name, e.salary);

    fclose(file);

    printf("Employee added successfully!\n");
}
void removeEmployee() {
   printEmployees();
   int ref;
   int flag = 0;
   FILE *temporaryfile;
   printf("Please enter the ID of Employee you want to fire :\n");
   scanf("%d", &ref);
   file = fopen("EmployeeList.txt", "r");
   temporaryfile = fopen("TemporaryFile.txt", "w");
   while(fscanf(file, "%d, %[^,],%f\n", &e.id, e.name, &e.salary) != EOF) {
       if (ref == e.id) {
           flag = 1;
       }
       else {
            fprintf(temporaryfile, "%d,%s,%.2f\n", e.id, e.name, e.salary);
       }
   }
   if (flag == 1) {
       printf("Employee Fired\n");
   }
   else {
       printf("No Record Found\n");
   }
   fclose(file);
   fclose(temporaryfile);
   remove("EmployeeList.txt");
   rename("TemporaryFile.txt", "EmployeeList.txt");
}
void printEmployees() {
    file = fopen("EmployeeList.txt", "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }


    printf("Employee List:\n");
    while (fscanf(file, "%d,%[^,],%f\n", &e.id, e.name, &e.salary) != EOF) {
        printf("ID: %d\n", e.id);
        printf("Name: %s\n", e.name);
        printf("Salary: %.2f\n", e.salary);
        printf("\n");
    }

    fclose(file);
}
void sortEmployee() {
    int size = countEmployee();
    struct employee employee_array[size];

    file = fopen("EmployeeList.txt", "r");
    int i = 0;
    while (fscanf(file, "%d,%[^,],%f\n", &employee_array[i].id, employee_array[i].name, &employee_array[i].salary) == 3) {
        i++;
    }
    fclose(file);
    qsort(employee_array, size, sizeof(struct employee), comparingfunction);
    file = fopen("EmployeeList.txt", "w");
    int j = 0;
    while(j != size) {
        fprintf(file, "%d,%s,%.2f\n", employee_array[j].id, employee_array[j].name, employee_array[j].salary);
        j++;
    }
    fclose(file);
    printf("Employee List Sorted\n");
}

int comparingfunction(const void *a, const void *b) {
    const struct employee *x = (const struct employee *)a;
    const struct employee *y = (const struct employee *)b;
    return x->id - y->id;
}
int countEmployee() {
    file = fopen("EmployeeList.txt", "r+");
    char ch;
    int num_employee = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            num_employee++;
        }
    }
    fclose(file);
    num_employee++;
    return num_employee;    
}
int choicefunction_part_1(int n) {
    if (n == 0) {
        printf("THANK YOU");
    }
    else {
        int temp = n;
        choicefunction_part_2(temp);
    }
}
int choicefunction_part_2(int m) {
    switch (m) {
        case 1:
            addEmployee();
            break;
        case 2:
            removeEmployee();
            break;
        case 3 :
            sortEmployee();
            break;
        case 4 :
            searchEmployee();
            break;
    }
    int a;
    printf("Please enter choice or press '0' to stop the programme :\n");
    printf("1. Add Employee\n");
    printf("2. Remove Employee\n");
    printf("3. Sort Employee List\n");
    printf("4. Search Employee\n");
    scanf("%d", &a);
    return choicefunction_part_1(a);
}
void searchEmployee() {
    char target[100];
    printf("Please enter the name :\n");
    getchar();
    fgets(target, 100, stdin);
    target[strcspn(target, "\n")] = '\0';
    file = fopen("EmployeeList.txt", "r");
    int found = 0;
    while(fscanf(file,"%d,%[^,],%f\n", &e.id, e.name, &e.salary) != EOF) {
        if (strcmp(e.name, target) == 0) {
            printf("Employee Found\n");
            printf("ID = %d\n", e.id);
            printf("Name = %s\n", e.name);
            printf("Salary = %.2f\n", e.salary);
            found++;
        }
    }
    if (found == 0) {
        printf("No employee Found\n");
    }
    else {
        printf("No of employees found = %d\n", found);
    }
}
