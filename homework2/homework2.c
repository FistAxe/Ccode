#include <stdio.h>
#include <stdlib.h>

#define POINT_NUM 16
#define TXT_LENGTH 25
#define ROUTE_NUM 9
typedef struct {
    double tau;
    double zeta;
    double theta;
} Point;

typedef struct {
    char route_name[TXT_LENGTH];
    double total_action;
} Route;

int IsValue(char value){    //return 1 if value is number of ','
    char valueset[12] = {'0','1','2','3','4','5','6','7','8','9',',','.'}; //defines meaningful char only

    for (int i=0;i<12;i++){
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

int strInverter(char *str, Point *point){  //gets numerical string, divides into 3 parts, and conveys it to Table
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

    //printf("debug: strtau: %s", strtau);

    sscanf(strtau, "%lf", &(point->tau));
    sscanf(strzeta, "%lf", &(point->zeta));
    sscanf(strtheta, "%lf", &(point->theta));

    return 0;
}


int readFile(char filename[20], Point point[]){   //get file from filename, and generate info from it
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("file error\n");
        return 0;
    }
    
    char line[50];
    for (int i=0;i<POINT_NUM;i++){
        
        fgets(line, 50, fp);
        if (line[0] == '\0'){
            break;
        }
        else{
            char buf[50];
            lineCleaner(line, buf);
            //printf("debug: cleaned line: %s", buf);
            strInverter(buf, &point[i]);
            //printf("%dth line done!\n",i);
            //printf("%dth tau: %lf\n", i, table[i].tau);
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

void fileNameTrimmer(char filename[]){
    for (int i=0;i<TXT_LENGTH;i++){
        if (filename[i] == '\n'){
            filename[i] = '\0';
            break;
        }
    }
}

void calculateAction(Point point[], double *action){
    for (int i=1; i<POINT_NUM;i++){     //Starts from (0,1) interval
        double sum_action = 0;
        sum_action += getdAction(
                                 point[i].tau, point[i-1].tau,
                                 point[i].zeta, point[i-1].zeta,
                                 point[i].theta, point[i-1].theta
                                );
        *action = sum_action;
    }
}

int main(void){
    char filename[TXT_LENGTH];  //max filename legnth: TXT_LENGTH
    Point point[POINT_NUM];    //max number of points: POINT_NUM
    Route route[ROUTE_NUM];
    //debug: route[0].tau = 0.0123f;

    printf("Homework 2: Action Calculator\n");
    while (1)
    {
        printf("Type the name of a route txt file placed in the same folder.\n");
        printf("Number of points must be 16, and name of the txt file must be shorter than 20.\n");
        printf("Press q to exit: ");
        fgets(filename, TXT_LENGTH, stdin);
        if (filename[0] == 'q')
            break;
        else {
            addRoute(route);
        }
        fileNameTrimmer(filename);
        readFile(filename, point);

        //for (int i=0;i<POINT_NUM;i++){
        //   printf("tau[%d]: %lf\n", i, route[i].tau);
        //}

        for (int i=0;i<POINT_NUM;i++){
            calculateAction(point, &(route[dynamic].total_action));
        }
    }
    return 0;
}