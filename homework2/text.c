#include <stdio.h>

typedef struct {
    char route_name[16];
    double total_action;
} Route;

void addRoute(Route *route, char *filename){
    sscanf(filename, "%s", route->route_name);
}

int main(){
    char filename[30] = "Hello";
    Route route[3];
    printf("your input was: %s\n", filename);
    addRoute(&route[0], filename);
    printf("%s", route[0].route_name);
    
    return 0;
}