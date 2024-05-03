#include <stdio.h>

typedef struct {
    double tau;
    double zeta;
    double theta;
} Table;

int IsValue(char value){    //return 1 if value is number of ','
    char valueset[11] = {'0','1','2','3','4','5','6','7','8','9',','}; //defines meaningful char only

    for (int i=0;i<11;i++){
        if (value == valueset[i])
            return 1;
    }
    
    return 0;
}

int main(){
    char str[] = "123ab,456";
    printf("%c", str[3]);
    for (int i=0;i<9;i++){
        printf("str[i] is %c\n", str[i]);
        printf("IsValue is %d\n", IsValue(str[i]));
        if (IsValue(str[i]) == 1){
            printf("%c!\n", str[i]); 
        }
    }
    printf("end");
    return 0;
}