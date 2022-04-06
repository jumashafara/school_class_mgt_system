#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    char first_name[20];
    char last_name[20];
    char student_number[20];
    char registration_number[20];
    char course[20];
    int year_of_study;
    int marks[2];
};

#define MAXIMUM 2000

FILE *student_file_pointer;

void enterStudents(struct student student_list[MAXIMUM]);
void printStudents(struct student student_list[MAXIMUM]);
void storeStudentsDetails(struct student student_list[MAXIMUM]);
void getGrade(int marks);
float getMean(int count_of_unit);
int getMarksColumn(int count_of_unit,int list_of_marks[MAXIMUM]);
int getArraySize(int array[MAXIMUM]);
int getMax(int count_of_unit);
int getMin(int count_of_unit);


int main(){

    struct student student_list[MAXIMUM];
    int choice, count_of_unit, marks;

    Menu:system("cls");

    printf("\t\tMenu\n"
            "\t1. To enter student info\n"
            "\t2. To print student info\n"
            "\t3. To get grade of a mark\n"
            "\t4. To get mean mark of a unit\n"
            "\t5. To get min mark of a unit\n"
            "\t6. To get max mark of a unit\n"
            "\t7. To print student info to excel\n"
            "\t0. To exit the system"
            "\nNote:"
            "\tGaps in the excel file are automatically given a value of zero(0).\n"
            "\tStatiscal calculations start from the second row of the excel file.\n"
            "\tShould the excel file be missing, a new one will be created on printing a new student, the above notes will still hold\n\n"
            );
    printf("Please enter choice: ");
    scanf("%d", &choice);

    system("cls");

    switch (choice)
    {
    	
    case 0:
    	break;
    case 1:
        enterStudents(student_list);
        goto Menu;

    case 2:
        printStudents(student_list);
        printf("\nPress Enter to continue...");
        getch();
        goto Menu;

    case 3:
        printf("Enter your mark: ");
        scanf("%d", &marks);
        getGrade(marks);
        printf("\nPress Enter to continue...");
        getch();
        goto Menu;

    case 4: 
        printf("Enter count of unit to get Mean: ");
        scanf("%d", &count_of_unit);
        printf("The mean mark of course unit %d is %.2f\n",count_of_unit, getMean(count_of_unit));
        printf("Press Enter to continue...");
        getch();
        goto Menu;

    case 5: 
        printf("Enter count of unit to get Min: ");
        scanf("%d", &count_of_unit);
        printf("The Min mark of unit %d is %d\n", count_of_unit, getMin(count_of_unit));
        printf("Press Enter to continue...");
        getch();
        goto Menu;

    case 6: 
        printf("Enter count of unit to get Max: ");
        scanf("%d", &count_of_unit);
        printf("The Min mark of unit %d is %d\n", count_of_unit, getMax(count_of_unit));
        printf("Press Enter to continue...");
        getch();
        goto Menu;

    case 7:
        storeStudentsDetails(student_list);
        printf("Student information file updated.");
        printf("Press Enter to continue...");
        getch();
        goto Menu;
    
    default:
        printf("Invalid Entry! Press Enter to try again...");
        goto Menu;
    }        

}

void enterStudents(struct student student_list[MAXIMUM]){

    int number, number_of_students;

    printf("How many students do you want to enter: ");
    scanf("%d", &number_of_students);

    for(number = 0; number < number_of_students; number++){

        printf("For student %d: \n", (number + 1));

        printf("Enter student first name: ");
        scanf("%s", &student_list[number].first_name);

        printf("Enter student last name: ");
        scanf("%s", &student_list[number].last_name);

        printf("Enter student number: ");
        scanf("%s", &student_list[number].student_number);

        printf("Enter student registration: ");
        scanf("%s", &student_list[number].registration_number);

        printf("Enter student course: ");
        scanf("%s", &student_list[number].course);

        printf("Enter student year of study: ");
        scanf("%d", &student_list[number].year_of_study);

        printf("Enter student marks for first course unit: ");
        scanf("%d", &student_list[number].marks[0]);

        printf("Enter student marks for second course unit: ");
        scanf("%d", &student_list[number].marks[1]);

        }
}

void printStudents(struct student student_list[MAXIMUM]){

    char buffer[1024];
    int row = 1;

    student_file_pointer = fopen("student_info.csv", "r");

    while(fgets(buffer, 1024, student_file_pointer)){
        printf("Row %d: %s",row, buffer);
        row++;
    }

    fclose(student_file_pointer);
}


void storeStudentsDetails(struct student student_list[MAXIMUM]){
   
    int number, size;
    FILE *student_file_pointer;

    student_file_pointer = fopen("student_info.csv", "a");

    if(NULL != student_file_pointer){
        fseek (student_file_pointer, 0, SEEK_END);
        size = ftell(student_file_pointer);
        
        if(0 == size){
            fprintf(student_file_pointer, "%s, %s, %s, %s, %s, %s, %s, %s\n",
            "First_Name", "Last_Name", "Student_Number", "Registration_Number", "Course", "Year_of_Study", "Unit 1", "Unit 2");
        }
    }

    for(number = 0; number < 10; number ++){

        if(student_list[number].year_of_study && student_list[number].marks[0] && student_list[number].marks[1]){
            
            fprintf(student_file_pointer, "%s, %s, %s, %s, %s, %d, %d, %d\n", 
                student_list[number].first_name,
                student_list[number].last_name,
                student_list[number].student_number,
                student_list[number].registration_number,
                student_list[number].course,
                student_list[number].year_of_study,
                student_list[number].marks[0],
                student_list[number].marks[1]
             );

        }
    }

    fclose(student_file_pointer);

}

void getGrade(int marks){

    if(marks > 79){
        printf("Grade A");
    }else if(marks > 74){
        printf("Grade B+");
    }else if(marks > 69){
        printf("Grade B");
    }else if(marks > 64){
        printf("Grade C+");
    }else if(marks > 59){
        printf("Grade C");
    }else if(marks > 54){
        printf("Grade D+");
    }else if(marks > 49){
        printf("Grade D");
    }else{
        printf("Grade F");
    }

}

int collectMarks(char str[1024], int count, int marks_col[10], int count_of_unit){
    
    char cpy[1024];
    int marks[100];
    char *token;
    int tok_to_num, counter = 0, pass_point = (5 + count_of_unit);

    strcpy(cpy, str);
   
   token = strtok(cpy, ",");
   
   while( token != NULL ) {

    if(counter == pass_point){

        tok_to_num = atoi(token);

        marks_col[count] = tok_to_num;

    }

 token = strtok(NULL, ",");

 counter ++ ;

   }
}


int getMarksColumn(int count_of_unit, int list_of_marks[MAXIMUM]){

    char buffer[1024];

    int row = 0, count = 0;

    student_file_pointer = fopen("student_info.csv", "r");

    while(fgets(buffer, 1024, student_file_pointer)){
        if(row == 0){
            //Do nothing for first row
        }else{
            collectMarks(buffer, count, list_of_marks, count_of_unit);
            count++;
        }
        row++; 
    }

    fclose(student_file_pointer);

    return count;

}

float getMean(int count_of_unit){
    int list_of_marks[MAXIMUM], list_size, sum = 0, counter;
    float mean;

    list_size = getMarksColumn(count_of_unit, list_of_marks);

    for (counter = 0; counter < list_size; counter++){
        sum += list_of_marks[counter];
    }

   return (sum/list_size); 
    
}

int getMax(int count_of_unit){

   int max, list_of_marks[MAXIMUM], list_size, counter;

    list_size = getMarksColumn(count_of_unit, list_of_marks);

    max = list_of_marks[0];
    
   for(counter = 0; counter < list_size; counter ++){

       if(list_of_marks[counter] > max){
           max = list_of_marks[counter];
       }

   }

   return max;
}

int getMin(int count_of_unit){

    int min, list_of_marks[MAXIMUM], list_size, counter;

    list_size = getMarksColumn(count_of_unit, list_of_marks);

    min = list_of_marks[0];
    
    for(counter = 0; counter < list_size; counter ++){
     
       if(list_of_marks[counter] < min){
           min = list_of_marks[counter];
       }

   }

   return min;
}
