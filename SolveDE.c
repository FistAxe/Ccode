#include <stdio.h>

#define REAL float
//#define REAL double
//#define Narray 100

int stradd(char *dest, char *src);  //Copied and Pasted from web
int stringcsvadder(char *string);   //Adds .csv at the end of the string
char* SetTableName(char REALtype, int Narray_table);    //Generates string name by args
void SolveDE();  //REAL type, arraynum selection function
int SolveDE_f(int arraysize);   //float ver
int SolveDE_d(int arraysize);   //double ver

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

int SolveDE_f(int arraysize)
{
    #undef REAL
    #define REAL float
    int Narray = arraysize;

    REAL zeta[Narray];
    REAL tauM = 3.0;
    REAL dtau = tauM/(Narray - 1);

    printf("size of REAL is %d\n", sizeof(tauM));

    zeta[0] = 0.9;
    zeta[1] = 0.9;
    
    for(int i=0;i<(Narray-2);i++){
        REAL fzeta = (1/zeta[i+1]/zeta[i+1]/zeta[i+1] - 1/zeta[i+1]/zeta[i+1]);
        zeta[i+2] = 2*zeta[i+1] - zeta[i] + (dtau)*(dtau)*fzeta;
        if (zeta[i+2] == zeta[i+1]){
            printf("Increment underflow!\n");
            //increment finding
            printf("Increment was %e", ((dtau)*(dtau)*fzeta));
            return 0;
        }
    }
    
    printf("%16s %16s %16s \n","index","tau","zeta");
    for(int i=0;i<Narray;i++){
        printf("%16d %16f %16f\n", i, dtau*i, (float)zeta[i]);
    }
    //increment finding
    printf("Min increment is: %e",(zeta[2]-zeta[1]));

    char save = '0';    //File exporting part
    getchar();
    printf("\nSave as a .csv file?\nPress Y to save.\n");
    scanf("%c", &save);
    printf("%c\n", save);
    
    if(save == 'Y'){
        FILE *table = fopen(SetTableName('f', arraysize), "w");
        if (table == NULL){
            printf("file open error!\n");
        }

        for(int i=0;i<arraysize;i++){
            fprintf(table,"%d,%f,%f\n", i, dtau*i, (float)zeta[i]);
        }
        fclose(table);
    }
    return 0;
}

int SolveDE_d(int arraysize)
{  
    #undef REAL
    #define REAL double
    
    int Narray = arraysize;

    REAL zeta[Narray];
    REAL tauM = 3.0;
    REAL dtau = tauM/(Narray - 1);

    printf("size of REAL is %d\n", sizeof(tauM));

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
        FILE *table = fopen(SetTableName('d', arraysize), "w");
        if (table == NULL){
            printf("file open error!\n");
        }

        for(int i=0;i<arraysize;i++){
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

void SolveDE(){
    
    int arraysize = 0;
    char REALtype = '0';

    printf("put REAL type.\n");
    while(REALtype != 'f' && REALtype != 'd'){
        printf("press \'f\' for float, \'d\' for double.\n");
        scanf("%c", &REALtype);
    }
        printf("put array size.\n");
        scanf("%d", &arraysize);
    
    if(REALtype == 'f'){
        SolveDE_f(arraysize);
    }

    else if(REALtype == 'd'){
        SolveDE_d(arraysize);
    }
}

int main(void){     //with restarting feature
    char repeat = 'a';
    
    do
    {
        if(repeat == 'Y'){
            getchar();
        };
        SolveDE();
        printf("Press Y to restart.\n");
        scanf(" %c", &repeat);
    } while (repeat == 'Y');

    return 0;
}