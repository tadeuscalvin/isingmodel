#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 100   //side of the lattice
#define N (L*L) //num of spins

int net[N];     //vector that forms the lattice
//spin neighborhood
int right[N], left[N], up[N], down[N], upright[N], upleft[N], downright[N], downleft[N];
double H=0;     // External Magnetic Field
//interation strenght of the spins, if>0 is ferromagnetic (the spins tend to stand all 
//in the same direction), otherwise half of them stand +1 and half -1
double J1=1,J2=-0.6;
double beta=2;  //inverse of the temperature

//function that inicializes the lattice with random spins
void init() {
    int i;
    for(i=0; i<N; i++) {
        net[i]=1;
        if((double) rand() > RAND_MAX/2) {
            net[i]=-1;
        }
        right[i]=i+1; left[i]=i-1; up[i]=i-L; down[i]=i+L;
        upright[i]=up[i]+1, upleft[i]=up[i]-1, downright[i]=down[i]+1, downleft[i]=down[i]-1;
        //periodic boundary conditions
        if((i+1)%L==0) {    //last row
            right[i]=i+1-L, upright[i]=i-2*L+1, downright[i]=i+1;
        }
        if(i%L==0) {        //first row
            left[i]=i-1+L, upleft[i]=i-1, downleft[i]=i+2*L-1;
        }
        if(i>=N-L) {        //last line
            down[i]=i-N+L, downleft[i]=i-L*(L-1)-1, downright[i]=i-L*(L-1)+1;
        }
        if(i<L) {          //first line
            up[i]=i+N-L, upleft[i]=i+L*(L-1)-1, upright[i]=i+L*(L-1)+1;
        }
        if(i==0) {
            upleft[i]=N-1;
        }
        if(i==L-1) {
            upright[i]=N-L;
        }
        if(i==N-L) {
            downleft[i]=L-1;
        }
        if(i==N-1) {
            downright[i]=0;
        }
    }
}

//function that update the value of the spins
void update() {
    int i, j;
    double E1, E2;
    for(j=0; j<N; j++) {
        i=(int) ((double) rand()/RAND_MAX *N);
        //energy of the spin i in your state
        E1=-J1*net[i]*(net[right[i]]+net[left[i]]+net[up[i]]+net[down[i]])-J2*net[i]*(net[upleft[i]]+net[upright[i]]+net[downleft[i]]+net[downright[i]])-H*net[i];
        E2=-E1; //energy of the spin i in the other state
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
void graph(double mc_max) {
    int j,mc;
    init();
    for(mc=0; mc<mc_max; mc++) {
        update();
        //if(mc%1==0) {
            for(j=0; j<N; j++) {
                printf("%d ",net[j]);
            }
        //}
    }
}

int main() {
    int mc_max=10000;
    graph(mc_max);
    return 0;
}
