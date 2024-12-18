//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;

    HealthData health_data = {0};


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to enter the exercise to be chosen with exit option
    printf("\nEnter the choice of the exercise: ");
    scanf("%d", &choice);
 
    
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);

    // ToCode: to enter the selected exercise and total calcories burned in the health data
    switch (choice)
    {
        case 1:
            i = 4 * duration;
            break;

        case 2:
            i = 11 * duration;
            break;

        case 3:
            i = 5 * duration;
            break;

        case 4:
            i = 12 * duration;
            break;

        case 5:
            i = 4 * duration;
            break;

        case 6:
            i = 2 * duration;
            break;

        default:
            break;
    }

}

/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    char exercise[100]; // exercises.txt 내용 담을 배열 

    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // 운동 list 출력
    printf("The list of exercises: \n");
    int exercise_num = 1; // 운동 번호 매기기
    // ToCode: to read a list of the exercises from the given file
    while (fgets(exercise, sizeof(exercise), file) != NULL) {
        // 줄바꿈 찾기
        int i;
        for (i = 0; exercise[i] != '\0'; i++) {
            if (exercise[i] == '\n') {
                exercise[i] = '\0';  
                break;  
            }
        }

        if (strlen(exercise) > 0) {
            printf("%d. %s\n", exercise_num, exercise);  
            exercise_num++;  
        }
    }
    

    fclose(file);

    inputExercise(&health_data);
}

