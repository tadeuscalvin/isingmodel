#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L 100     //side of the lattice
#define N L*L     //num of spins

int lat[L][L]; //vector that forms the lattice
double J=1; /*interation strenght of the spins, if>0 is ferromagnetic (the spins tend to stand all in the same direction),
	      otherwise half of them stand +1 and half -1 */

//function that inicializes the lattice with random spins
void init() {
  int i,j;
  for(i=0; i<L; i++) {
    for(j=0; j<L; j++) {
      lat[i][j]=1;
      if((double) rand() > RAND_MAX/2) {
	lat[i][j]=-1;
      }
    }
  }
}

//function that update the value of the spins
void update(double beta) {
  int j, i, k, l;
  double E1, E2;
  for(k=0; k<L; k++) {
    for(l=0; l<L; l++) {
      i=(int)((double)rand()/RAND_MAX*L);
      j=(int)((double)rand()/RAND_MAX*L);

      E1=-J*lat[i][j]*(lat[((i+1)%L)][j]+lat[i][((j+1)%L)]+lat[((i-1+L)%L)][j]+lat[i][((j-1+L)%L)]);            //energy of the spin i in your state
      E2= J*lat[i][j]*(lat[((i+1)%L)][j]+lat[i][((j+1)%L)]+lat[((i-1+L)%L)][j]+lat[i][((j-1+L)%L)]);            //energy of the spin i in the other state

      if(E2-E1<=0) { 			//if the energy of the other state is smaller than his, he changes his state
	lat[i][j]=-lat[i][j];
      }
      //probability of the temperature changes the state of the spins
      else if((double) rand()/RAND_MAX < exp(-beta*(E2-E1))) { 
	lat[i][j]=-lat[i][j];
      }
    }
  }
}

//animation of the lattice
void graph(double mc_max) {
  int i,j,mc;
  double beta=10;
  init();
  for(mc=0; mc<mc_max; mc++) {
    update(beta);
    if(mc%1==0) {
      for(i=0; i<L; i++) {
	for(j=0; j<L; j++) {
	  printf("%d\n",lat[i][j]);
	}
      }
    }
  }
}

//behavior of lattices with temperature variation
void history(int mc_max) {
  FILE*f1=fopen("N100.dat","w");
  int i,j,mc,anthony,m=0;
  double ma=0,beta;
  for(beta=0.2; beta<0.8; beta+=0.01) {
    for(anthony=0; anthony<50; anthony++) {
      init();
      for(mc=0; mc<mc_max; mc++) {
	update(beta);
      }
      for(i=0; i<L; i++) {      
	for(j=0; j<L; j++) {
	  m+=lat[i][j];
	}
      }
      ma+=fabs(m);
      m=0;
    }
    fprintf(f1,"%f %f\n",beta,ma/50);
    ma=0;
  }
}

int main() {
  int mc_max=100;
  graph(mc_max);

  return 0;
}
