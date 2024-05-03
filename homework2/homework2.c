#include <stdio.h>
#include <stdlib.h>

#define length 25
#define txtlength 20
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

int lineCleaner(char *str, char dest[]){     //leaves only IsValue() characters in the string 
    int i = 0;
    
    while (*str != '\0'){
        if (IsValue(*str)){
            dest[i] = *str;
            str++;
            i++;
        }
        else {
            str++;
        }
    }
    
    printf("debug: dest[3]: %c\n", dest[3]);

    return 0;
}

int strInverter(char *str, Table *table){  //gets numerical string, divides into 3 parts, and conveys it to Table
    char strtau[20];
    char strzeta[20];
    char strtheta[20];

    int i = 0;

    while (*str != ','){
        strtau[i] = *str;
        
        str++;
        i++;
    }

    strtau[i] = '\0';
    str++;
    i = 0;
    
    while (*str != ','){
        strzeta[i] = *str;

        str++;
        i++;
    }
    
    strzeta[i] = '\0';
    str++;
    i = 0;

    while (*str != '\0'){
        strtheta[i] = *str;
        str++;
        i++;
    }

    strtheta[i] = '\0';

    printf("debug: strtau: %s", strtau);

    sscanf(strtau, "%lf", table->tau);
    sscanf(strzeta, "%lf", table->zeta);
    sscanf(strtheta, "%lf", table->theta);

    return 0;
}


int readFile(char filename[20], Table table[]){   //get file from filename, and generate info from it
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("file error\n");
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
            printf("%dth line done!\n",i);
            printf("%dth tau: %lf\n", i, table[i].tau);
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
    double dtau = tau - prev_tau;
    double dzeta = zeta - prev_zeta;
    double dtheta = theta - prev_theta;

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

void fileNameTrimmer(char filename[]){
    for (int i=0;i<30;i++){
        if (filename[i] == '\n'){
            filename[i] = '\0';
            break;
        }
    }
}

int main(void){
    char filename[txtlength];  //max filename legnth: txtlength
    Table route[length];    //max number of points: length
    //debug: route[0].tau = 0.0123f;

    printf("Homework 2: Action Calculator\n");
    printf("Type the name of a route txt file placed in the same folder: ");
    fgets(filename, txtlength, stdin);
    fileNameTrimmer(filename);
    readFile(filename, route);

    for (int i=0;i<length;i++){
        printf("tau[%d]: %lf\n", i, route[i].tau);
    }

    return 0;
}