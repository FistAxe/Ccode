#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ROUTENAME_LENGTH 15
#define POINT_NUM 16    //point contains (0, 0) to (15, 15)
#define ROUTE_NUM 9
#define CURVE_NUM 10

#define INIT_TAU 0
#define MAX_TAU 3.20065
#define INIT_ZETA 0.9
#define MAX_ZETA 1.125
#define INIT_THETA 0
#define MAX_THETA 3.14159
#define PI 3.14159

#define RANDOM_RANGE 0.01
#define RANDOM_DECREASE 0.2


typedef struct {    //struct Point with tau, zeta, theta
    double tau;
    double zeta;
    double theta;
} Point;

typedef struct {    //struct Route with route_name, total_action, and 'Point' array whose size is POINT_NUM.
    char route_name[ROUTENAME_LENGTH];
    double total_action;
    Point point[POINT_NUM];
} Route;

void func(){
    printf("func\n");
}

double randomAmpGen(int attempt){
    int ran = rand();
    double max_amplitude = RANDOM_RANGE*pow(RANDOM_DECREASE, attempt - 1);
    double amplitude = max_amplitude * ((ran- 16384) / 16384);
    return amplitude;
}

double getdAction(double tau, double prev_tau, double zeta, double prev_zeta, double theta, double prev_theta){ //calculates
    double dtau = tau - prev_tau;
    double dzeta = zeta - prev_zeta;
    double dtheta = theta - prev_theta;

    double daction = ((0.5*( (dzeta/dtau)*(dzeta/dtau) + zeta*zeta*(dtheta/dtau)*(dtheta/dtau) )) + 1.0/zeta)*dtau;
    //printf("debug: daction = %f\n", daction);
    return daction;
}

void calculateAction(Point point[], double *action){    //get sum of dActions from point[], save at *action
    double sum_action = 0;

    //Starts from (0,1) interval 
    for (int i=1; i<POINT_NUM;i++){
        sum_action += getdAction(
                                 point[i].tau, point[i-1].tau,
                                 point[i].zeta, point[i-1].zeta,
                                 point[i].theta, point[i-1].theta
                                );
        //printf("debug: sum_action: %f\n", sum_action);
    }
    *action = sum_action;
    //printf("debug: *action : %f\n", *action);
}

void straight_route(
    Route* route,
    double init_tau,
    double max_tau,
    double init_zeta,
    double max_zeta,
    double init_theta,
    double max_theta)
{
    strcpy(route[0].route_name, "straight");
    printf("straight route\n");
    double slope_zeta = (max_zeta - init_zeta) / (max_tau - init_tau);
    double slope_theta = (max_theta - init_theta) / (max_tau - init_tau);
    //len(interval) = len(point) - 1
    double dtau = (max_tau - init_tau) / (POINT_NUM - 1);
    for (int index=0;index<POINT_NUM;index++){
        route[0].point[index].tau = init_tau + index*dtau;
        route[0].point[index].zeta = init_zeta + index*dtau*slope_zeta;
        route[0].point[index].theta = init_theta + index*dtau*slope_theta;
        printf("test\n");
        printf("%f, %f, %f\n", route[0].point[index].tau, route[0].point[index].zeta, route[0].point[index].theta);
    }
    calculateAction(route[0].point, &(route[0].total_action));
    for (int rou = 1; rou<ROUTE_NUM; rou++){
        route[rou].total_action = route[0].total_action;
    }
}

void calculateRoute(Route *route, int attempt, int iter){
    strcpy(route[attempt].route_name, "%sth attempt");
    Route sample_route;
    sample_route.total_action = route[attempt - 1].total_action;

    sample_route.point[0].tau = route[attempt].point[0].tau = route[attempt - 1].point[0].tau;
    sample_route.point[0].zeta = route[attempt].point[0].zeta = route[attempt - 1].point[0].zeta;
    sample_route.point[0].theta = route[attempt].point[0].theta = route[attempt - 1].point[0].theta;
    for (int i=1; i<POINT_NUM;i++){
        sample_route.point[i].tau = route[attempt].point[i].tau = route[0].point[i].tau;
        sample_route.point[i].zeta = route[attempt - 1].point[i].zeta;
        sample_route.point[i].theta = route[attempt - 1].point[i].theta;
    }
    for (int repeat=0; repeat<iter; repeat++)
        for (int curve=1; curve<=CURVE_NUM; curve++){
            double amp_zeta = randomAmpGen(attempt);
            double amp_theta = randomAmpGen(attempt);
            for (int i=1; i<POINT_NUM;i++){
                double dzeta = sin(i / (POINT_NUM - 1) * PI * curve) * amp_zeta;
                double dtheta = sin(i / (POINT_NUM - 1) * PI * curve) * amp_theta;

                sample_route.point[i].zeta += dzeta;
                sample_route.point[i].theta += dtheta;
                }
            }
        calculateAction(sample_route.point, &(sample_route.total_action));
        if (sample_route.total_action < route[attempt].total_action){
            route[attempt] = sample_route;
            printf("less Action of : %f", sample_route.total_action);
        }
}

int homework3(Route* route, int iter){
    func();
    straight_route(route, INIT_TAU, MAX_TAU, INIT_ZETA, MAX_ZETA, INIT_THETA, MAX_THETA);
    char key = '0';
    printf("%dth Iterantion, Action: %f\n", 0, route[0].total_action);

    for (int i=1; i<ROUTE_NUM; i++){
        getchar();
        calculateRoute(route, i, iter);

        printf("%dth Iterantion, Action: %f\n", i, route[i].total_action);
        printf("To repeat, press 'r'. To proceed to next step, press 'p'.\n");
        while (1){
            scanf("%c", &key);
            if (key == 'r'){
                i -= 1;
                break;
            }
            else if (key == 'p'){
                break;
            }
            else {
                printf("Wrong key!\n");
            }
        }
    }

    printf("Program ended. Last Action was: %f\n", route[ROUTE_NUM - 1].total_action);
    return 0;
}




int main(void){
    Route route[ROUTE_NUM];
    int iter = 0;
    printf("Please enter the number of iteration: ");
    scanf("%d", &iter);
    homework3(route, iter);

    return 0;
}