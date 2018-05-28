#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 100   //side of the lattice
#define N (L*L) //num of spins

int net[N];     //vector that forms the lattice
int right[N], left[N], up[N], down[N];  //spin neighborhood
double H=0;     // External Magnetic Field
double J=1;     /*interation strenght of the spins, if>0 is ferromagnetic (the spins tend to 
                stand all in the same direction), otherwise half of them stand +1 and half -1 */
double beta=1;  //inverse of the temperature

//function that inicializes the lattice with random spins
void init() {
    int i;
    for(i=0; i<N; i++) {
        net[i]=1;
        if((double) rand() > RAND_MAX/2) {
            net[i]=-1;
        }
        right[i]=i+1; left[i]=i-1; up[i]=i-L; down[i]=i+L;
        //periodic boundary conditions
        if((i+1)%L==0) {    //last row
            right[i]=i+1-L;
        }
        if(i%L==0) {        //first row
            left[i]=i-1+L;
        }
        if(i>=N-L) {        //last line
            down[i]=i-N+L;
        }
        if(i<L) {          //first line
            up[i]=i+N-L;
        }
    }
}

//function that update the value of the spins
void update() {
    int j, i;
    double E1, E2;
    for(j=0; j<N; j++) {
        i=(int) ((double) rand()/RAND_MAX *N);  
        E1=-J*net[i]*(net[right[i]]+net[left[i]]+net[up[i]]+net[down[i]])-H*net[i]; //energy of the spin i in your state
        E2=-E1;                                                 //energy of the spin i in the other state
        //if the energy of the other state is smaller than his, he changes his state
        if(E2-E1<=0) {
            net[i]=-net[i];
        }
        //probability of the temperature changes the state of the spins
        else if((double) rand()/RAND_MAX < exp(-beta*(E2-E1))) {
            net[i]=-net[i];
        }
    }
}

//animation of the lattice
void graph(int mc_max) {
    int j,mc;
    init();
    for(mc=0; mc<mc_max; mc++) {
        update();
        if(mc%10==0) {
            for(j=0; j<N; j++) {
                printf("%d\n",net[j]);
            }
        }
    }
}

int main() {
    int mc_max=10000;
    graph(mc_max);
    return 0;
}
