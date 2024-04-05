#include <stdio.h>
//#define REAL float
//#define REAL double
//#define Narray 100

int SolveDE(char REALtype, int arraysize)
{
    if(REALtype == 'f'){
        #define REAL float
    }

    else if(REALtype == 'd'){
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
        printf("%16d %f %f\n", i, dtau*i, (float)zeta[i]);
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