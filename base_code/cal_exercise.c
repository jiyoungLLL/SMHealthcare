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
    int choice, duration, calories;

    // ToCode: to enter the exercise to be chosen with exit option
    printf("\nEnter the choice of the exercise(if you want to exit, plz enter a number other than 1-6 to exit): ");
    scanf("%d", &choice);
    if(choice < 1 || choice > 6) {
        return;
    }

    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);


    // ToCode: to enter the selected exercise and total calcories burned in the health data
    switch (choice)
    {
        case 1:
            // 이름 저장
            strcpy(exercise_list[exercise_list_size].exercise_name, "walking");
            // 분당 소모 칼로리 저장
            exercise_list->calories_burned_per_minute = 4;
            // 사용자한테 입력받은 시간 * 분당 소모 칼로리 = 총 소모 칼로리 계산
            calories = 4 * duration;
            break;

        case 2:
            strcpy(exercise_list[exercise_list_size].exercise_name, "running");
            exercise_list->calories_burned_per_minute = 11;
            calories = 11 * duration;
            break;

        case 3:
            strcpy(exercise_list[exercise_list_size].exercise_name, "riding");
            exercise_list->calories_burned_per_minute = 5;
            calories = 5 * duration;
            break;

        case 4:
            strcpy(exercise_list[exercise_list_size].exercise_name, "swimming");
            exercise_list->calories_burned_per_minute = 12;
            calories = 12 * duration;
            break;

        case 5:
            strcpy(exercise_list[exercise_list_size].exercise_name, "pilates");
            exercise_list->calories_burned_per_minute = 4;
            calories = 4 * duration;
            break;

        case 6:
            strcpy(exercise_list[exercise_list_size].exercise_name, "yoga");
            exercise_list->calories_burned_per_minute = 2;
            calories = 2 * duration;
            break;

        default:
            break;
    }


    // 운동 내용 출력 (확인용)
    printf("Exercise: %s\n", exercise_list[exercise_list_size].exercise_name);
    printf("Calories burned per minute: %d\n", exercise_list[exercise_list_size].calories_burned_per_minute);
    printf("Total calories burned: %d\n", calories);

    // health_data에 소모된 칼로리 업데이트
    health_data->total_calories_burned += calories;
    // health_data exercises 업데이트
    health_data->exercises[exercise_list_size].exercise_name[exercise_list_size] = exercise_list->exercise_name[exercise_list_size];
    health_data->exercises[exercise_list_size].calories_burned_per_minute = exercise_list[exercise_list_size].calories_burned_per_minute;
    // 운동 개수 증가
    health_data->exercise_count++;
    // 배열 주소 up
    exercise_list_size++;

    // 기존 health_data.txt 파일
    FILE *health = fopen("health_data.txt", "r");
    if (health == NULL) {
        printf("파일이 없습니다.\n");
        return;
    }

    // 임시 파일
    FILE *newHealth = fopen("new_health_data.txt", "w");
    char healthArr[200];  
    int isThereExercise = 0;  // 운동이 이미 있는지
    int inExercise = 0;  // [Exercises] 안에 내용이 있는지
    
    while (fgets(healthArr, sizeof(healthArr), health)) {
        // 줄바꿈 문자 제거
        int len = 0;
        while (healthArr[len] != '\n' && healthArr[len] != '\0') len++;
        healthArr[len] = '\0';
        
        // 대괄호 시작?
        if (healthArr[0] == '[') {
            // [Exercises]인지 
            int isExercises = 1;
            char exercise_str[] = "[Exercises]";
            for(int i = 0; exercise_str[i] != '\0'; i++) {
                if(healthArr[i] != exercise_str[i]) {
                    isExercises = 0;
                    break;
                }
            }
            // [Exercises]이면 inExercise = 1
            if(isExercises) inExercise = 1;
            else inExercise = 0;
            
            // 운동 추가하기
            if (!isThereExercise && inExercise == 0) {
                fprintf(newHealth, "%s - %d kcal\n", 
                    exercise_list[exercise_list_size-1].exercise_name, calories);
                isThereExercise = 1;
            }
        }
        
        // [Exercises] 
        if (inExercise) {
            char name[50];  // 운동 이름 배열
            int cal;        // 기존 칼로리 변수
            int i = 0, j = 0;
            
            // 운동 이름 가져오기
            while (healthArr[i] != '-' && healthArr[i] != '\0') {
                if (healthArr[i] != ' ') name[j++] = healthArr[i];
                i++;
            }
            name[j] = '\0';
            
            // 운동 이름 비교
            int nameMatching = 1;
            for(int k = 0; name[k] != '\0' || exercise_list[exercise_list_size-1].exercise_name[k] != '\0'; k++) {
                if(name[k] != exercise_list[exercise_list_size-1].exercise_name[k]) {
                    nameMatching = 0;
                    break;
                }
            }
            
            // 같은 이름이면 칼로리 더하기
            if (nameMatching) {
                // 기존 칼로리 
                while (healthArr[i] != '\0' && !(healthArr[i] >= '0' && healthArr[i] <= '9')) i++;
                cal = 0;
                while (healthArr[i] >= '0' && healthArr[i] <= '9') {
                    cal = cal * 10 + (healthArr[i] - '0');
                    i++;
                }
                // 더하기
                fprintf(newHealth, "%s - %d kcal\n", name, cal + calories);
                isThereExercise = 1;
                continue;
            }
        }
        
        // 나머지 줄은 그대로 
        fprintf(newHealth, "%s\n", healthArr);
    }

    fclose(health);
    fclose(newHealth);
    
    remove("health_data.txt"); // 이전 파일 지우기
    rename("new_health_data.txt", "health_data.txt"); // 임시파일 이름 변경
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
