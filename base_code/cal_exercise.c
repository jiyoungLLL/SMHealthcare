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

/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/
void inputExercise(HealthData* health_data) {
    int choice, duration, calories;
    int existing_exercise_index = -1;  // 기존 운동 인덱스를 저장할 변수

    // ToCode: to enter the exercise to be chosen with exit option
    printf("\nEnter the choice of the exercise(if you want to exit, plz enter a number other than 1-6 to exit): ");
    scanf("%d", &choice);
    if(choice < 1 || choice > 6) {
        return;
    }

    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);

    // 운동 이름 저장 배열
    char exercise_name[MAX_EXERCISE_NAME_LEN];
    
    // 운동 이름 & 칼로리 저장
    switch(choice) {
        case 1: 
            strcpy(exercise_name, "walking"); 
            calories = 4 * duration; 
            break;
        case 2: 
            strcpy(exercise_name, "running"); 
            calories = 11 * duration; 
            break;
        case 3: 
            strcpy(exercise_name, "riding"); 
            calories = 5 * duration; 
            break;
        case 4: 
            strcpy(exercise_name, "swimming"); 
            calories = 12 * duration; 
            break;
        case 5: 
            strcpy(exercise_name, "pilates"); 
            calories = 4 * duration; 
            break;
        case 6: 
            strcpy(exercise_name, "yoga"); 
            calories = 2 * duration; 
            break;
        default: 
            return;
    }

    // 기존 배열에 같은 이름의 운동이 있는지 확인
    for (int i = 0; i < exercise_list_size; i++) {
        if (strcmp(exercise_list[i].exercise_name, exercise_name) == 0) {
            existing_exercise_index = i;
            break;
        }
    }

    if (existing_exercise_index != -1) {
        // 이미 운동이 있을 때 -> 칼로리 업데이트
        exercise_list[existing_exercise_index].calories_burned_per_minute += calories;
        health_data->exercises[existing_exercise_index].calories_burned_per_minute += calories;
    } else {
        // new 운동 !
        strcpy(exercise_list[exercise_list_size].exercise_name, exercise_name);
        exercise_list[exercise_list_size].calories_burned_per_minute = calories;
        
        strcpy(health_data->exercises[exercise_list_size].exercise_name, exercise_name);
        health_data->exercises[exercise_list_size].calories_burned_per_minute = calories;
        
        health_data->exercise_count++;
        exercise_list_size++;
    }

    // health_data에 총 소모된 칼로리 업데이트
    health_data->total_calories_burned += calories;

    // saveData로 health_data.txt 업데이트
    saveData("health_data.txt", health_data);
}

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
        printf("%d. %s", exercise_num, exercise);
        if (exercise_list_size >= MAX_EXERCISES) {
            break;
        }
        exercise_num++;
    }
    
    fclose(file);

}
