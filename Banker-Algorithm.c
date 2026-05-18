#include "stdio.h"

int main(){
    
    int available[3] = {3, 3, 2};
    int max[5][3] = { {7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3} };
    int allocated[5][3] = { {0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2} };
    
    int need[5][3];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            need[i][j] = max[i][j] - available[i][j];
        }
    }
    
    int safe = 0;
    int finish[5] = {0,0,0,0,0};
    
    for(int k = 0; k < 5; k++){
        for(int j = 0; j < 5; j++){
            if(finish[j] = 0){
                
                if(available[j][0] >= need[j][0] && available[j][1] >= need[j][1] && available[j][2] >= need[j][2]){
                    
                    available[j][0] += allocated[j][0];
                    available[j][1] += allocated[j][1];
                    available[j][2] += allocated[j][2];
                    
                    finish[j] = 1;
                    safe++;
                    
                }
            }
        }
    }
    
    if(safe == 5){
        printf("safe sequence");
        return 0;
    }
    printf("unsafe sequence");
    return 0;
}
