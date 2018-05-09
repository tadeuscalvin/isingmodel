#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//Standard Libraries
#define _USE_MATH_DEFINES // M_PI constant

int L=TAM;

const int WINDOWS_WIDTH = 850;
const int WINDOWS_HEIGHT = 650;

typedef struct
{
  GLfloat x, y, z;
  GLfloat r, g, b, a;
} Vertex;

typedef struct
{
  GLfloat x, y, z;
} Data;

void drawPoint(Vertex v1, GLfloat size);
void drawPointsDemo(int width, int height);
void drawLineSegment(Vertex v1, Vertex v2, GLfloat width);
void drawGrid(GLfloat width, GLfloat height, GLfloat grid_width);
void DrawFrame();
void gridMode(int tempo, double GRID[600][800]);
void particleMode(int tempo);
void grid2dMode();
void particle2dMode();
void DrawCircle(double x0, double y0, double r);
void SpectreMode();
int main(void)
{
  GLFWwindow* window;
  if (!glfwInit())
    exit(EXIT_FAILURE);
  window = glfwCreateWindow(WINDOWS_WIDTH, WINDOWS_HEIGHT,
			    "Chapter 2: Primitive drawings", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  // glfwSwapInterval(5);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  double GRID[600][800] = {0.0};
  int tempo = 0;
  while (!glfwWindowShouldClose(window))
    {
      tempo++;
      float ratio;
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      ratio = (float) width / (float)height;
      glViewport(0, 0, width, height);
      //glClear(GL_COLOR_BUFFER_BIT);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      //Orthographic Projection
      // glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // drawGrid(5.0f, 1.0f, 0.1f);
      DrawFrame();

      if(mo==0){
	gridMode(tempo,GRID);
      }
      else if(mo==1){
	particleMode(tempo);
      }
      else if(mo==2){
	grid2dMode(tempo);
      }
      else if(mo==3){
	particle2dMode(tempo);
      }
      else if(mo==4){
  SpectreMode(tempo);
      }
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void drawPoint(Vertex v1, GLfloat size){
  glPointSize(size);
  glBegin(GL_POINTS);
  glColor4f(v1.r, v1.g, v1.b, v1.a);
  glVertex3f(v1.x, v1.y, v1.z);
  glEnd();
}

void DrawCircle(double x0, double y0, double r){
  int i;

  glBegin(GL_POLYGON);
  for(i=0; i <= 300; i++){
    double angle = 2 * M_PI * i / 300;
    double x = r/880*cos(angle)-x0;
    double y = r/660*sin(angle)-y0;
    glVertex2d(x,y);
  }
  glEnd();
}

void drawPointsDemo(int width, int height){
  GLfloat size=5.0f;
  for(GLfloat x = 0.0f; x<=1.0f; x+=0.2f, size+=5)
    {
      Vertex v1 = {x, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
      drawPoint(v1, size);
    }
}

void drawLineSegment(Vertex v1, Vertex v2, GLfloat width) {
  glLineWidth(width);
  glBegin(GL_LINES);
  glVertex3f(v1.x, v1.y, v1.z);
  glColor4f(v2.r, v2.g, v2.b, v2.a);
  glVertex3f(v2.x, v2.y, v2.z);
  glEnd();
}

void drawGrid(GLfloat width, GLfloat height, GLfloat grid_width){
  //horizontal lines
  for(float i=-height; i<height; i+=grid_width){
    Vertex v1 = {-width, i, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f};
    Vertex v2 = {width, i, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f};
    drawLineSegment(v1, v2,grid_width);
  }
  //vertical lines
  for(float i=-width; i<width; i+=grid_width){
    Vertex v1 = {i, -height, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f};
    Vertex v2 = {i, height, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f};
    drawLineSegment(v1, v2,grid_width);
  }
}

void DrawFrame(){
  Vertex v1 = {-0.95f, -0.95f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
  Vertex v2 = {0.95f, -0.95f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
  Vertex v3 = {0.95f, 0.95f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
  Vertex v4 = {-0.95f, 0.95f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};
  // drawLineSegment(v1, v2,3.0f);
  // drawLineSegment(v2, v3,3.0f);
  // drawLineSegment(v3, v4,3.0f);
  // drawLineSegment(v4, v1,3.0f);
}

void gridMode(int tempo,double GRID[600][800]){
  int i,j;
  float cor;
  float yy;
  Vertex v;

  for(i=0; i<L; i++){
    scanf("%f\n", &cor);
    cor = (cor+1)/2.0;
    GRID[tempo%600][i] = cor;
  }
  glClear(GL_COLOR_BUFFER_BIT);
  for(j=0;j < 600; j++){
    for(i=0; i<L; i++){
      v.x = (i - L/2)/440.0;
      v.y = (float) (-j+300.0f)/330.0f;
      v.z = 0.0f;
      v.r = GRID[j][i];
      v.g = GRID[j][i];
      v.b = GRID[j][i];
      v.a = 1.0f;
      drawPoint(v,1.0f);
    }
  }
}

void particleMode(int tempo){
  int i;
  float cor;
  float yy, xx;
  Vertex v;

  glBegin(GL_QUADS); //Begin quadrilateral coordinates
  //Trapezoid
  glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
  glVertex3f(-1.0f, -(2.*(tempo%600)-600.)/660.-0.01f, 0.0f);
  glVertex3f(1.0f,  -(2.*(tempo%600)-600.)/660.-0.01f, 0.0f);
  glVertex3f(1.0f,  -(2.*(tempo%600)-600.)/660., 0.0f);
  glVertex3f(-1.0f, -(2.*(tempo%600)-600.)/660., 0.0f);
  glEnd(); //End quadrilateral coordinates

  yy = (float) (-(tempo%600)+300.0f)/330.0f;
  for(i=0; i<L; i++){
    scanf("%f\n", &xx);
    cor = 1.0f;
    v.x = (2*xx-1)/1.15;
    v.y = yy;
    v.z = 0.0f;
    v.r = cor;
    v.g = cor;
    v.b = cor;
    v.a = 1.0f;
    drawPoint(v,1.1f);
  }
}

void grid2dMode(int tempo){
  int i,j;
  double cor;
  Vertex v;

  for(j=0; j<L; j++){
    for(i=0; i<L; i++){
      scanf("%lf\n", &cor);
      cor = (cor+1.0)/2.0;
      //cor = 1.0f;
      v.x = (i*(2./L)-1)*660/880;
      v.y = (j*(2./L)-1);
      v.z = 0.0f;
      v.r = cor;
      v.g = cor;
      v.b = cor;
      v.a = 1.0f;
      drawPoint(v,1000/L);
    }
  }
}

void particle2dMode(){
  int i;
  double cor, xx, yy, r;
  Vertex v;

  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0; i<L; i++){
    scanf("%lf %lf %lf\n", &xx, &yy, &r);
    cor = 1.0;
    //cor = 1.0f;
    v.x = (2*xx-1)/1.15*660/880;
    v.y = (2*yy-1)/1.15;
    v.z = 0.0f;
    v.r = cor;
    v.g = cor;
    v.b = cor;
    v.a = 1.0f;
    //drawPoint(v,r);
    DrawCircle(v.x, v.y, r+3);
  }
}

void SpectreMode(){
  int pos,t;
  float value;
  double cor = 1.0;
  Vertex v1,v2;
  int Lk = (800/2+1);
  scanf("%d\t%f",&pos,&value);
  v1.x = (2.0*pos/Lk) -1.0f;
  v1.y = (value);
  v1.z = 0.0f;
  v1.r = cor;
  v1.g = cor;
  v1.b = cor;
  v1.a = 1.0f;
  glClear(GL_COLOR_BUFFER_BIT);

  for(t = 1; t < Lk;t++){
    scanf("%d",&pos);
    scanf("%f",&value);
    v2.x = (2.0f*pos/Lk) -1.0f;
    // v2.y = 2.0f*rand()/RAND_MAX - 1.0f;
    v2.y = 2.0f*value - 1.0f;
    v2.z = 0.0f;
    v2.r = cor;
    v2.g = cor;
    v2.b = cor;
    v2.a = 1.0f;
    drawLineSegment(v1,v2,3.0f);
    v1.x = v2.x;
    v1.y = v2.y;
    v1.z = v2.z;
    v1.r = cor;
    v1.g = cor;
    v1.b = cor;
    v1.a = 1.0f;
  }
}
