#ifndef DO_TSOMETHING_H
#define DO_TSOMETHING_H

#define TXT_LENGTH 25
#define POINT_NUM 16
#define ROUTE_NUM 9

typedef struct {    //struct Point with tau, zeta, theta
    double tau;
    double zeta;
    double theta;
} Point;

typedef struct {    //struct Route with route_name, total_action, and 'Point' array whose size is POINT_NUM.
    char route_name[TXT_LENGTH];
    double total_action;
    Point point[POINT_NUM];
} Route;

#ifdef __cplusplus
extern "C"{
#endif

//do_TSomething() caller from C main(). Call this in C program to use C++ features.
void do_TSomething_C(char* filename, int total_route, Route route[]);

#ifdef __cplusplus
}
#endif

#endif  //DO_TSOMETHING_H