//
//  cal_diets.c
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

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    char diet[100]; // diets.txt 내용 담을 배열 

    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

    // 식단 list 출력
    printf("The list of diets: \n");
    int diet_num = 1; // 식단 번호 매기기
    // ToCode: to read a list of the diets from the given file
    while (fgets(diet, MAX_DIETS, file) != NULL) {
        printf("%d. %s", diet_num, diet); // 내용 출력
        if (diet_list_size >= MAX_DIETS) {
            break;
        }
        diet_num++;
    }
    fclose(file);

}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, calories;    
    int dietIndex = 99999999;  // 기존 식단 index를 저장할 변수
    
    // 하루에 3끼 까지
    // 입력 받을 수 있는 음식의 개수 3개로 제한
    if (diet_list_size < 3) {
        // ToCode: to enter the diet to be chosen with exit option
        printf("\nEnter the choice of the food(if you want to exit, plz enter a number other than 1-6 to exit): ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 6) {
            return;
        }
    } else {
        // 이미 3끼 입력됐으면 입력을 받지 않음 (<-건강한 칼로리 섭취를 위해, 하루에 3끼를 먹음)
        printf("You have already had 3 meals today! \n");
        return;
    }

    // ToCode: to enter the total calories intake in the health data
    switch (choice) {
        case 1:
            strcpy(diet_list[diet_list_size].food_name, "rice");
            diet_list[diet_list_size].calories_intake = 600;
            calories = 600;
            break;
        
        case 2:
            strcpy(diet_list[diet_list_size].food_name, "bread");
            diet_list[diet_list_size].calories_intake = 680;
            calories = 680;
            break;
        
        case 3:
            strcpy(diet_list[diet_list_size].food_name, "chicken");
            diet_list[diet_list_size].calories_intake = 925;
            calories = 925;
            break;

        case 4:
            strcpy(diet_list[diet_list_size].food_name, "salad");
            diet_list[diet_list_size].calories_intake = 70;
            calories = 70;
            break;

        case 5:
            strcpy(diet_list[diet_list_size].food_name, "pizza");
            diet_list[diet_list_size].calories_intake = 900;
            calories = 900;
            break;

        case 6:
            strcpy(diet_list[diet_list_size].food_name, "tteokbokki");
            diet_list[diet_list_size].calories_intake = 615;
            calories = 615;
            break;

        default:
            return;
    }

    // 기존 배열에 같은 이름의 식단이 있는지 확인
    for (int i = 0; i < diet_list_size; i++) {
        if (strstr(diet_list[i].food_name, diet_list[diet_list_size].food_name) != NULL) {
            // 이미 운동이 있을 때, 해당 운동의 index -> dietIndex
            dietIndex = i;
            break;
        }
    }

    if (dietIndex != 99999999) {
        // 이미 식단이 있으면 칼로리만 업데이트
        diet_list[dietIndex].calories_intake += calories;
        // health_data diet 칼로리 업데이트
        health_data->diet[dietIndex].calories_intake += calories;
    } else {
        // new 식단 !
        strcpy(diet_list[diet_list_size].food_name, diet_list[diet_list_size].food_name);
        diet_list[diet_list_size].calories_intake = calories;
        
        // health_data diet 추가
        strcpy(health_data->diet[diet_list_size].food_name, diet_list[diet_list_size].food_name);
        health_data->diet[diet_list_size].calories_intake = calories;

        // 식단 개수 증가
        health_data->diet_count++;
        // diet_list_size 인덱스 1+
        diet_list_size++;
    }

    // 먹은 칼로리 업데이트
    health_data->total_calories_intake += calories;

    // saveData로 health_data.txt 업데이트
    saveData("health_data.txt", health_data);
}

