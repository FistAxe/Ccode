#include <stdio.h>

#define REAL float
//#define REAL double
//#define Narray 100

int stradd(char *dest, char *src);
int stringcsvadder(char *string);
char* SetTableName(char REALtype, int Narray_table);
int SolveDE(char REALtype, int arraysize);

char* SetTableName(char REALtype, int Narray_table){
    static char tablename[50] = "homework1/SolveDE_";   //initialization, enable using stradd() from the beginning

    if(REALtype == 'f'){    //start file name with type.
        stradd(tablename, "float_");
    }
    else if(REALtype == 'd'){
        stradd(tablename, "double_");
    }
    
    char Narray_name[10];   //add used Narray.
    sprintf(Narray_name, "%d", Narray_table);
    stradd(tablename, Narray_name);

    stradd(tablename, ".csv");  //add '.csv' at the end of the file name.

    return tablename;
}

int SolveDE(char REALtype, int arraysize)
{
    if(REALtype == 'f'){
        #undef REAL
        #define REAL float
    }

    else if(REALtype == 'd'){
        #undef REAL
        #define REAL double
    }
    
    int Narray = arraysize;

    REAL zeta[Narray];
    REAL tauM = 3.0;
    REAL dtau = tauM/(Narray - 1);

    zeta[0] = 0.9;
    zeta[1] = 0.9;
    
    for(int i=0;i<(Narray-2);i++){
        REAL fzeta = (1/zeta[i+1]/zeta[i+1]/zeta[i+1] - 1/zeta[i+1]/zeta[i+1]);
        zeta[i+2] = 2*zeta[i+1] - zeta[i] + (dtau)*(dtau)*fzeta;
    }
    
    printf("%16s %16s %16s \n","index","tau","zeta");
    for(int i=0;i<Narray;i++){
        printf("%16d %16f %16f\n", i, dtau*i, (float)zeta[i]);
    }

    char save = '0';    //File exporting part
    getchar();
    printf("\nSave as a .csv file?\nPress Y to save.\n");
    scanf("%c", &save);
    printf("%c\n", save);
    
    if(save == 'Y'){
        FILE *table = fopen(SetTableName(REALtype, Narray), "w");
        if (table == NULL){
            printf("file open error!\n");
        }

        for(int i=0;i<Narray;i++){
            fprintf(table,"%d,%f,%f\n", i, dtau*i, (float)zeta[i]);
        }
        fclose(table);
    }

    return 0;
}

int stradd(char *dest, char *src){

    while(*dest){
        *dest++;
    }

    while(*src){
        *dest = *src;
        *dest++;
        *src++;
    }
    return 0;
}

int main(void){
    
    int arraysize = 0;
    char REALtype = '0';

    printf("put REAL type.\n");
    while(REALtype != 'f' && REALtype != 'd'){
        printf("press \'f\' for float, \'d\' for double.\n");
        scanf("%c", &REALtype);
    }
        printf("put array size.\n");
        scanf("%d", &arraysize);
    
    SolveDE(REALtype, arraysize);
    return 0;
}