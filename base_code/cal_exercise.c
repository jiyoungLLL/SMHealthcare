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
        printf("%d. %s", exercise_num, exercise);
        if (exercise_list_size >= MAX_EXERCISES) {
            break;
        }
        exercise_num++;
    }
    
    fclose(file);

}


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
    int exerciseIndex = 99999999;  // 기존 운동 index를 저장할 변수

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
        if (strstr(exercise_list[i].exercise_name, exercise_name) != NULL) {
            // 이미 운동이 있을 때, 해당 운동의 index -> exerciseIndex
            exerciseIndex = i;
            break;
        }
    }

    if (exerciseIndex != 99999999) {
        // 이미 운동이 있으면 칼로리만 업데이트
        exercise_list[exerciseIndex].calories_burned_per_minute += calories; 
        // health_data exercise 칼로리도 업데이트
        health_data->exercises[exerciseIndex].calories_burned_per_minute += calories;
    } else {
        // new 운동 !
        strcpy(exercise_list[exercise_list_size].exercise_name, exercise_name);
        exercise_list[exercise_list_size].calories_burned_per_minute = calories;
        
        // health_data exercise 추가
        strcpy(health_data->exercises[exercise_list_size].exercise_name, exercise_name);
        health_data->exercises[exercise_list_size].calories_burned_per_minute = calories;
        
        health_data->exercise_count++;  // 운동 개수 늘리기
        exercise_list_size++;  // exercise_list 인덱스 1+
    }

    // health_data에 총 소모된 칼로리 업데이트
    health_data->total_calories_burned += calories;

    // saveData로 health_data.txt 업데이트
    saveData("health_data.txt", health_data);
}
