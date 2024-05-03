#include <stdio.h>

typedef struct {
    double tau;
    double zeta;
    double theta;
} Table;

int readFile(char filename[20], Table *table[20]){
    FILE *fp = fopen(filename, 'r');
    if (fp == NULL){
        return 0;
    }
    
    char line[50];
    int repeat = 1;
    while (repeat == 0){
        
        fgets(line, 50, fp);
        if (line[0] == NULL){
            repeat = 0;
        }
        else{
            char buf = line[50];
            buf = lineCleaner(line);
            strDivider(buf, *table);
        }
    }

    fclose(filename);
    return 0;
}

int main(){
    char filename[30];
    Table table[20];
    
    printf("test. type file name.txt: ");
    scanf("%s", &filename);
    readFile(filename, table);

    for (int i=0;i<20;i++){
        printf("tau: %lf\n", table[i].tau);
    }

    return 0;
}