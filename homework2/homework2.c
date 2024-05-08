#include <stdio.h>
#include "do_TSomething.h"  //defines struct Route, do_TSomething_C()

#define POINT_NUM 16
#define ROUTE_NUM 9
#define SUCCESS 1
typedef struct {    //struct Point with tau, zeta, theta
    double tau;
    double zeta;
    double theta;
} Point;

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
    
    //printf("debug: dest[3]: %c\n", dest[3]);

    return 0;
}

int strConverter(char *str, Point *point){  //gets numerical string, divides into 3 parts, and conveys it to Table
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
            strConverter(buf, &point[i]);
            //printf("%dth line done!\n",i);
            //printf("debug: %dth tau: %lf\n", i, point[i].tau);
        }
    }

    fclose(fp);
    return SUCCESS;
}

double getdAction(double tau, double prev_tau, double zeta, double prev_zeta, double theta, double prev_theta){ //calculates
    double dtau = tau - prev_tau;
    double dzeta = zeta - prev_zeta;
    double dtheta = theta - prev_theta;

    double daction = ((0.5*( (dzeta/dtau)*(dzeta/dtau) + zeta*zeta*(dtheta/dtau)*(dtheta/dtau) )) + 1.0/zeta)*dtau;
    printf("debug: daction = %f\n", daction);
    return daction;
}

void fileNameTrimmer(char filename[]){  //converts string from fgets into char* string
    for (int i=0;i<TXT_LENGTH;i++){
        if (filename[i] == '\n'){
            filename[i] = '\0';
            break;
        }
    }
}

void extentionRemover(char *str){   //removes 4 characters (.xxx) from behind
    int i = 0;

    while (*str){
        i++;
        str++;
    }
    *(str-1) = *(str-2) = *(str-3) = *(str-4) = '\0';
}

void calculateAction(Point point[], double *action){    //get sum of dActions from point[], save at *action
    double sum_action = 0;
    for (int i=1; i<POINT_NUM;i++){     //Starts from (0,1) interval 
        sum_action += getdAction(
                                 point[i].tau, point[i-1].tau,
                                 point[i].zeta, point[i-1].zeta,
                                 point[i].theta, point[i-1].theta
                                );
        printf("debug: sum_action: %f\n", sum_action);
    }
    *action = sum_action;
    printf("debug: *action : %f\n", *action);
}

void addRoute(Route *route, char *filename){    //copy filename[] into route.route_name[]
    sprintf(route->route_name, "%s", filename);
}

int main(void){ 
    char filename[TXT_LENGTH];  //max filename legnth: TXT_LENGTH
    Point point[POINT_NUM];     //max number of points: POINT_NUM
    Route route[ROUTE_NUM];     //max number of routes: ROUTE_NUM
    int route_index = 0;        //number of routes = most recent route index

    printf("Homework 2: Action Calculator\n");
    while (1) {  //point[] is reused for every new route.txt. point data is not saved.
        printf("Type the name of a route txt file placed in the same folder.\n");
        printf("Number of points must be 16, and name of the txt file must be shorter than 20.\n");
        printf("Press q to end adding route: ");
        fgets(filename, TXT_LENGTH, stdin);
        if (filename[0] == 'q')
            break;
        fileNameTrimmer(filename);
        if (readFile(filename, point) == SUCCESS){  //when fopen() succeed
            extentionRemover(filename); //removes '.txt'
            addRoute(&route[route_index], filename);    //add name to struct route[i].
            printf("debug: Route %s added\n", route[route_index].route_name);

            calculateAction(point, &(route[route_index].total_action)); //calculate action from point[] and save at route[].
            route_index += 1;
        }
    }

    for (int i=0;i<route_index;i++){    //after all input
        printf("Route name: %s   ", route[i].route_name);
        printf("Total Action: %f\n", route[i].total_action);
    }

    char rootname[10] ="rootfile"; //.root file name is fixed as 'rootfile.root'
    do_TSomething_C(rootname, route_index, route);  //call external C++ fuction using ROOT lib
    return 0;
}