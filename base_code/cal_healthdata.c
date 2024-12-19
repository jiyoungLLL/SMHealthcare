//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

// health_data은 exercise와 diet에 모두 저장하는 과정 추가함
// void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
// 	int i;
//     FILE* file = fopen(HEALTHFILEPATH, "w");
//     if (file == NULL) {
//         printf("There is no file for health data.\n");
//         return;
//     }

//     // ToCode: to save the chosen exercise and total calories burned 
//     fprintf(file, "[Exercises] \n");
    
    
//     // ToCode: to save the chosen diet and total calories intake 
//     fprintf(file, "\n[Diets] \n");



//     // ToCode: to save the total remaining calrories
//     fprintf(file, "\n[Total] \n");
    
    
// }

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
    int i;
    
    // ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
    // health_data의 운동 데이터 출력
    for (i = 0; i < health_data->exercise_count; i++) {
        printf("Exercise: %s, Calories burned: %d kcal\n",
            health_data->exercises[i].exercise_name,
            health_data->exercises[i].calories_burned_per_minute);
    }
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    // health_data의 식단 데이터 출력
    for (i = 0; i < health_data->diet_count; i++) {
        printf("Food: %s, Calories intake: %d kcal\n",
            health_data->diet[i].food_name,
            health_data->diet[i].calories_intake);
    }

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
    printf("Basal metabolic rate: %d kcal\n", BASAL_METABOLIC_RATE);
    printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
    printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
    int remaingCal = health_data->total_calories_intake - BASAL_METABOLIC_RATE - health_data->total_calories_burned;
    printf("The remaining calories: %d kcal\n", remaingCal);
 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    if (remaingCal ==  0) {
        printf("You have consumed all your calories for today! \n");
    } else if (remaingCal < 0) {
        printf("[Warning] Too few calories! \n");
        // 남은 칼로리가 0보다 작을 때 섭취칼로리 별 문구 추가
        if (health_data->total_calories_intake == DAILY_CALORIE_GOAL) {
            printf("Your total calories intake for today has reached your goal! \n");
        } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {
            printf("Your total calories intake for today has not reached your goal, remember to eat more!! \n");
        } else {
            printf("You have eaten more calories than planned today, but you have exercised too much! \n");
        }
    } else {
        printf("Please exercise for your health! \n");
        // 남은 칼로리가 0보다 클 때 섭취칼로리 별 문구 추가
        if (health_data->total_calories_intake == DAILY_CALORIE_GOAL) {
            printf("Your total calories intake for today has reached your goal! \n");
        } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {
            printf("Your total calories intake for today has not reached your goal, remember to eat more!! \n");
        } 
    }
    
	 printf("=======================================================================\n");
}
