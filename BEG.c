#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 100     //side of the lattice
#define N L*L     //num of spins

int lat[N]; //vector that forms the lattice
double D=0.02;
double H=0; // Campo externo
double J=1; /*interation strenght of the spins, if>0 is ferromagnetic (the spins tend to stand all in the same direction),
	      otherwise half of them stand +1 and half -1 */

//function that inicializes the lattice with random spins
int init() {
  int i;
  for(i=0; i<N; i++) {
    lat[i]=1;
    if((double) rand() > RAND_MAX/2) {
      lat[i]=-1;
    }
    if((double) rand()/RAND_MAX < D){
      lat[i]=0;
    }
  }
}

//function that update the value of the spins
int update(double beta) {
  int j, i, r, l, d, u;
  double E1, E2;
  for(j=0; j<N; j++) {
    i=(int) ((double) rand()/RAND_MAX *N);
    r=i+1; l=i-1; u=i-L; d=i+L;
    if((i+1)%L==0){ r=i+1-L; } //periodic boundary conditions
    if(i%L==0)	  { l=i-1+L; }
    if(i>=N-L)	  { d=i-N+L; }
    if(i<L)	  { u=i+N-L; }
    E1=-J*lat[i]*(lat[r]+lat[l]+lat[u]+lat[d])-H*lat[i];            //energy of the spin i in your state
    E2= J*lat[i]*(lat[r]+lat[l]+lat[u]+lat[d])+H*lat[i];            //energy of the spin i in the other state
    if(E2-E1<=0) { 			//if the energy of the other state is smaller than his, he changes his state
      lat[i]=-lat[i];
    }
    //probability of the temperature changes the state of the spins
    else if((double) rand()/RAND_MAX < exp(-beta*(E2-E1))) { 
      lat[i]=-lat[i];
    }
  }
}

//animation of the lattice
int graph(double mc_max) {
  int j,mc;
  double beta=5;
  init();
  for(mc=0; mc<mc_max; mc++) {
    update(beta);
    if(mc%1==0) {
      for(j=0; j<N; j++) {
	printf("%d\n",lat[j]);
      }
    }
  }
}

//behavior of lattices with temperature variation
int history(int mc_max) {
  FILE*f1=fopen("N100.dat","w");
  int j,mc,anthony,m=0;
  double ma=0,beta;
  for(beta=0.2; beta<0.8; beta+=0.01) {
    for(anthony=0; anthony<50; anthony++) {
      init();
      for(mc=0; mc<mc_max; mc++) {
	update(beta);
      }
      for(j=0; j<N; j++) {
	m+=lat[j];
      }
      ma+=fabs(m);
      m=0;
    }
    fprintf(f1,"%f %f\n",beta,ma/50);
    ma=0;
  }
}

int main() {
  int mc_max=10000;
  graph(mc_max);
}
