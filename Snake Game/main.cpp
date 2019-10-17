#include <GL/gl.h>
#include <GL/glut.h>
#include "snake.cpp"
#include <windows.h>
#include <stdlib.h>									//pop up window for windows OS
#define cols 40
#define rows 40

//levels change from this values(if change these values, change snake.cpp's values also )
#define Level1 25									
#define Level2 50

extern int snakedirec;								// to access the snakedirec key word from snake.cpp
bool GameOver=false;								// set default as false
int score=0;
int Ltime=250;
void display();
void resize(int,int);  
void timer(int); 
void keybord(int,int,int);

// --------------------------------------------- main function -----------------------------------------
int main(int argc,char **argv){
	
	glutInit(&argc,argv); 		   												// initializes GLUT 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 								// set RGB color mode and use two buffers
	glutInitWindowSize(600,600);												// size of the window
	glutCreateWindow("SNAKE"); 
	glutDisplayFunc(display); 													// callback function
	glutReshapeFunc(resize); 													// window maximize,minimize,resize or move 
	glutTimerFunc(Ltime,timer,0); 												// number of milisecond, hen it sets 0, it will be display as soon as starts,callback function, finction passed int value  
	glutSpecialFunc(keybord);													// Keybord callback function - similer as glutKeybordFunc()
	
	glClearColor(0.8627450980392157,0.8627450980392157,0.8627450980392157,1.0);	// change background color (red,green,blue,alpha)
	initializebord(cols,rows); 
	glutMainLoop(); 															// call again and again, the functions specified before
	return 0;
}
//------------------------------------Top bar texts-------------------------------------------
void drawtext(const char *text, int length, int x,int y){
	
	glMatrixMode(GL_PROJECTION);
	double *matrix=new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0.0,600,0.0,600,-5,5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x,y);
	
	for(int i=0; i<length;i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,(int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

// --------------------------------------------- display function ----------------------------------------
void display(){
	
	glClear(GL_COLOR_BUFFER_BIT); 								// clear color buffer 
	drawbord(); 
	makesnake();
	makefood();
	
	std::string text;
	std::string text2;
	std::string text3;
	std::string text4;
	
	char scr[10];
	glColor3f(1.0,1.0,1.0);											//text color
	text = itoa(score,scr,10);										// get score and convert to string
	drawtext(text.data(),text.size(),170,550);
	text2 = "Score : ";
	drawtext(text2.data(),text2.size(),100,550);
	text3 = "Level : ";
	drawtext(text3.data(),text3.size(),400,550);
		if(score<Level1){
			text4="1";
			drawtext(text4.data(),text4.size(),470,550);  		
															
		}else if(score<Level2){
			text4="2";
			drawtext(text4.data(),text4.size(),470,550);
															
		}else{
			text4="3";
			drawtext(text4.data(),text4.size(),470,550);;
		}
	
	glutSwapBuffers();											// swap the buffer and next frame will be display on the screen
	
	if(score==Level1){										
		Ltime=100;											// level 2
	}else if(score==Level2){
		Ltime=50;														// level 3
	}
	
	if(GameOver){
		char scr[10];
		itoa(score,scr,10);
		char msg[100]="Your score : ";
		strcat(msg,scr);
		MessageBox(NULL,msg,"GAME OVER",0);			//pop up window
		exit(0);
	}
}

// --------------------------------------------- resize function ------------------------------------------
void resize(int w,int h){ 
	glutReshapeWindow(600,600); 								// fixed size window
	glViewport(0,0,(GLsizei)w,(GLsizei)h);						// sets viwe port of the window // GLsizei-A non-negative binary integer, for sizes.
	glMatrixMode(GL_PROJECTION); 								// specify which matrix is the current matrix, GL_PROJECTION - Applies subsequent matrix operations to the projection matrix stack.
	glLoadIdentity(); 											// replace the current matrix with the identity matrix
	gluOrtho2D(0.0,cols,0.0,rows); 								// (left-x,right-x,bottom-y,top-y)means representing two dimensional objects  
	glMatrixMode(GL_MODELVIEW); 								// Applies subsequent matrix operations to the modelview matrix stack.
}

// --------------------------------------------- timer funcion ---------------------------------------------
void timer(int){ 							// not use any variable so dont pass variable
	glutPostRedisplay();					// call display function --new frame will be display each time timer function calls, display function aslo call
	glutTimerFunc(Ltime,timer,0);				// this is used to  get continous loop for frames display -- want 10 frames in 1 seconds, 1 second has 1000 miliseconds.
	
}

// --------------------------------------------- keyboard input funcion ---------------------------------------------
void keybord(int key,int,int){					    
	switch(key){
		
		case GLUT_KEY_UP:					// turn up
			if(snakedirec!=DOWN){			// when the snake is going up its direction mustn't change 180 degrees.. can change left and right
				snakedirec=UP;	
				break;  
			}
		case GLUT_KEY_DOWN:					// turn down
			if(snakedirec!=UP){			
				snakedirec=DOWN;	
				break;   
			}
		case GLUT_KEY_RIGHT:				// turn right
			if(snakedirec!=LEFT){			
				snakedirec=RIGHT;	
				break;  
			}
		case GLUT_KEY_LEFT:					// turn left
			if(snakedirec!=RIGHT){			
				snakedirec=LEFT;	
				break;  
			}
	
	}
}

