#include <stdio.h>
#include <stdlib.h>

#define length 25
typedef struct {
    double tau;
    double zeta;
    double theta;
} Table;

int IsValue(char *value){    //return 1 if value is number of ','
    if (*value = '0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' || ',') 
        //defines meaningful char only
        return 1;
    else
        return 0;
}

int lineCleaner(char *str, char *dest){
    int i = 0;

    while (*str != '\0'){
        if (*str == IsValue(str)){
            dest[i] = *str;
            str++;
        }
        else {
            str++;
        }
    }
    
    return 0;
}

int strInverter(char *str, Table *table){    
    char strtau[20];
    char strzeta[20];
    char strtheta[20];

    int i = 0;

    while (*str == ','){
        strtau[i] = *str;
        
        str++;
        i++;
    }

    str++;
    i = 0;
    
    while (*str == ','){
        strzeta[i] = *str;

        str++;
        i++;
    }
    
    str++;
    i = 0;

    while (*str == '\0'){
        strtheta[i] = *str;
        str++;
        i++;
    }

    sscanf(strtau, "%lf", &table->tau);
    sscanf(strzeta, "%lf", &table->zeta);
    sscanf(strtheta, "lf", &table->theta);

    return 0;
}


int readFile(char filename[20], Table table[20]){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        return 0;
    }
    
    char line[50];
    for (int i=0;i<20;i++){
        
        fgets(line, 50, fp);
        if (line[0] == '\0'){
            break;
        }
        else{
            char buf[50];
            lineCleaner(line, buf);
            strInverter(buf, &table[i]);
        }
    }

    fclose(fp);
    return 0;
}


double setDelta(double value, double prev_value){
    double delta_value = value - prev_value;
    return delta_value;
}

double getdAction(double tau, double prev_tau, double zeta, double prev_zeta, double theta, double prev_theta){
    double dtau = setDelta(tau, prev_tau);
    double dzeta = setDelta(zeta, prev_zeta);
    double dtheta = setDelta(theta, prev_theta);

    double action = ((1/2*( (dzeta/dtau)*(dzeta/dtau) + zeta*zeta*(dtheta/dtau)*(dtheta/dtau) )) + 1/zeta)*dtau;
    return action;
}

double getSumAction(double action[length]){
    double action_sum;
    for (int i=0;i<length;i++){
        action_sum += action[i];
    }
    return action_sum;
};

int main(void){
    char filename[20];  //max filename legnth: 20
    Table route[20];

    printf("Homework 2: Action Calculator\n");
    printf("Type the name of a route txt file placed in the same folder: ");
    scanf("%s", &filename);
    readFile(filename, route);

    for (int i=0;i<20;i++){
        printf("tau: %lf\n", route[i].tau);
    }

    return 0;
}