#include <stdio.h>

void newValue(void);

int data[10] = {0,0,0,0,0,0,0,0,0,0};
int edge = 1; //1 para subida y 2 para bajada
int count = 0;

int main(void){
    for(int i = 0; i < 1100; i++){
        printf("%d %d %d %d %d %d %d %d %d %d\n",data[0], data[1],
        data[2], data[3], data[4], data[5], data[6], data[7],
        data[8], data[9]);
        newValue();
    }
    return 0;
}

void newValue(void){
    if(edge == 1){
        count++;
        data[9]++;
        for(int i = 9; i >= 0; i--){
            if(data[i] > 1){
                data[i-1]++;
                data[i] = 0;
            }
        }
        if(count >= 1024){
            count = 0;
            edge = 2;
        }
    }
    else if(edge == 2){
        count++;
        data[9]--;
        for(int i = 9; i >= 0; i--){
            if(data[i] < 1){
                data[i-1]--;
                data[i] = 1;
            }
        }
        if(count >= 1024){
            count = 0;
            edge = 1;
        }
    }
}