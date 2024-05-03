#include <stdio.h>

int main(){
    char filename[30];
    fgets(filename, 30, stdin);
    for (int i=0;i<30;i++){
        if (filename[i] == '\n'){
            filename[i] = '\0';
            break;
        }
    }
    printf("your input was: %s\n", filename);
    
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("file error!\n");
        return 0;
    }
    
    return 0;
}