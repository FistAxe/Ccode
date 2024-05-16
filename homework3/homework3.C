#include <iostream>
#include <string>
#include "do_TSomething.h"
using namespace std;

Route readFile(char* filename){
    try{
        FILE *fp = fopen(filename, "r");
        if (fp == NULL){
            throw string "No File!\n";
        
    }
}






int main(void){
    Route route[ROUTE_NUM];
    char filename[20];

    for(int index=0;index<ROUTE_NUM;index++){
        cout << "asdf" <<endl;
        cin >> filename;
        route[index] = readFile(filename);
    }

    return 0;
}