#ifndef DO_TSOMETHING_H
#define DO_TSOMETHING_H

#define TXT_LENGTH 25

typedef struct {
    char route_name[TXT_LENGTH];
    double total_action;
} Route;

#ifdef __cplusplus
extern "C"{
#endif
    
void do_TSomething_C(char* filename, int total_route, Route route[]);

#ifdef __cplusplus
}
#endif

#endif  //DO_TSOMETHING_H