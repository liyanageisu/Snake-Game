//8888888888888888888888888888888888888
#include <GL/gl.h>   
#include <GL/glut.h>
#include <ctime>								
#include <iostream>
#include <cstdlib>							// for srand and rand
#include <math.h>

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#define MAX 100								// max length that snake can grow

//levels change from this values(if change these values, change main.cpp's values also )
#define Level1 15
#define Level2 30

extern int score;							// to access the score variable from main.cpp
extern bool GameOver;						// to access the variable GameOve from main.cpp
int snakedirec = RIGHT; 						
bool food = true;							// when the game starts food has been drawn so default value should set true

int snakelength=2;
int gdX,gdY; 
int foodX,foodY;
int positionX[MAX]={20,20}, positionY[MAX]={20,19}; 			// default squire will be made vertex(20,20) on the grid. 

void random(int&,int&);
void square(int,int);


void initializebord(int x,int y){	
	gdX=x;
	gdY=y;
}

void drawbord(){	
	// draw square sheet
	for(int x=0; x<gdX; x++){
		for(int y=0; y<gdY; y++){
			square(x,y);
		}
	}
}

// make small square border and grid 

void square(int x,int y){
	
	if(x==0 || y==0 || x==gdX-1 || y==gdY-5){
		
	glLineWidth(1.0); 									// thiknness of the line
	glColor3f(0.5019607843137255,0.0,0.0);			    // maroon - set border color
	glBegin(GL_POLYGON); 
		glVertex2f(x,y);
		glVertex2f(x+1,y);
		glVertex2f(x+1,y+1);
		glVertex2f(x,y+1);
	glEnd();
	}else if(y==gdY-4 || y==gdY-3 || y==gdY-2 || y==gdY-1){  // TOP Score bar 
		glColor3f(0.1490196078431373,0.1490196078431373,0.1490196078431373);	//color dark gray
		glBegin(GL_POLYGON); 
		glVertex2f(x,y);
		glVertex2f(x+1,y);
		glVertex2f(x+1,y+1);
		glVertex2f(x,y+1);
	glEnd();	
	}else{
		glColor3f(1.0,1.0,0.9019607843137255);			    // light yellow 
		glBegin(GL_POLYGON); 
		glVertex2f(x,y);
		glVertex2f(x+1,y);
		glVertex2f(x+1,y+1);
		glVertex2f(x,y+1);
		glEnd();
	}
}

void makefood(){
	
	if(food){
		random(foodX,foodY);
	}
	food=false;
	
	// food color change after compleating level
	if(score<Level1){
		glColor3f(1.0,0.6,0.4);		//light orange											
	}else if(score<Level2){
		glColor3f(0.8,0.0,0.8);		//orange											
	}else{
		glColor3f(1.0,0.0,0.0);		//red
	}
	glRectf(foodX,foodY,foodX+1,foodY+1); 
		
}
 
void makesnake(){
	
	for(int i=snakelength-1; i>0; i--){
		
		positionX[i]=positionX[i-1];
		positionY[i]=positionY[i-1];
	}
	if(snakedirec==UP){
		positionY[0]++;
	}else if(snakedirec==DOWN){
		positionY[0]--;
	}else if(snakedirec==LEFT){
		positionX[0]--;
	}else if(snakedirec==RIGHT){
		positionX[0]++;
	}
	for(int i=0;i<snakelength;i++){
		if(i==0){
			glColor3f(0.0,0.0,0.803921568627451);					//snake head color
		}else{
			glColor3f(0.4823529411764706,0.407843137254902,0.9333333333333333);			//snake body color
		} 			
			glRectd(positionX[i],positionY[i],positionX[i]+1,positionY[i]+1);
	}
	
	if(positionX[0]==1 || positionX[0]==gdX-2 || positionY[0]==1 || positionY[0]==gdY-6){
		GameOver=true;
	}
	
	if(positionX[0]==foodX && positionY[0]==foodY){
		score++;
		snakelength++;
		if(snakelength>MAX){
			snakelength=MAX;
		}
		food=true; 
	} 
		   
}

// genarate random values for x and y 

void random(int &x,int &y){

	int maxX=gdX-3;
	int min=2;
	int maxY=gdY-6; 
	srand(time(NULL));   
	x=min+rand()%(maxX-min); 
	y=min+rand()%(maxY-min);
}

//njdkfdbfidgibgldbdkgj


