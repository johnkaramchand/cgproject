#include <iostream>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <cstdio>

// Apple Specific Compatibility Issues
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// Define the value of PI, upto 12 decimal places
#define PI 3.141592653589

// ID to detect which scene the story is in.
int SCENE_ID;

// Variables for Animator Faders
GLfloat title_fade,
	intro_next_text_appear,  light_r = 30, light_rs=0;

// Variables for Translation Animators
GLfloat schoolboy_x = 1150, schoolboy_y = 5220,
    schoolboy_x1 = 0, schoolboy_y1 = 5220, schoolboy_x1_h = 0, schoolboy_y1_h =5220, schoolboy_x1_v2 = 0, schoolboy_y1_v2 = 5220;

// Variables for Color Morphers
GLfloat window_top_r = 59, window_top_g = 91, window_top_b = 132,
	window_bottom_r = 97, window_bottom_g = 131, window_bottom_b = 159,
	sky_r = 12, sky_g = 172, sky_b = 232,
	grass_r = 82, grass_g =  163, grass_b = 42,
	sun_r = 251, sun_g = 255, sun_b = 163;


bool move = true ;
int speed = 2.0 ;
    char result[10]; 
    char batv[10]; 
    int num = 5; 
		float wh = 0.15 ;

// Variables for Random Star Generation
int star_alpha, no_of_stars, stars_array[40][2];

// Function to Create Delay
void delay(float secs) {
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

// Function to Print Text
void print(char *string,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a,
	GLint x, GLint y,
	GLfloat w, GLfloat h,
	GLfloat strokeSize) {
	glPushMatrix();

	glColor4f(r, g, b, a);
	glTranslatef(x, y, 0);
	glScalef(w, h, 0);

	glPointSize(strokeSize);
	glLineWidth(strokeSize);

	while (*string)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string++);

	glPopMatrix();

	glLineWidth(1);
	glPointSize(1);
}

// Function to Draw Circle
void drawCircle(GLfloat x, GLfloat y,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat sx, GLfloat sy,
	GLfloat radius) {
		glPushMatrix();

		glTranslatef(x, y, 0);
		glScalef(sx, sy, 0);

    glBegin(GL_POLYGON);
		glColor3ub(r, g, b);
    for (GLfloat i = 0; i < 360; i += 5)
        glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
    glEnd();



		glPopMatrix();

        glBegin(GL_LINES);
    glColor3f(255,255,255);
        glVertex2f(x,y+(radius-4));
        glVertex2f(x,y-(radius-4));

        glVertex2f(x-(radius-4),y);
        glVertex2f(x+(radius-4),y);
    glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

// Function to Draw Circle for numbers
void drawCircleText(GLfloat x, GLfloat y,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat sx, GLfloat sy,
	GLfloat radius,char *str) {
		glPushMatrix();

		glTranslatef(x, y, 0);
		glScalef(sx, sy, 0);

    glBegin(GL_POLYGON);
		glColor3ub(r, g, b);
    for (GLfloat i = 0; i < 360; i += 5)
        glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
    glEnd();

		glPopMatrix();

		if (num>=10)
		{
			wh = 0.1 ;
		}
		else
		{
			wh = 0.15 ;
		}

        print(str, 1,1,1, 1, x-8,y-8,wh,wh,1) ;
    }

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
        glColor4f(1, 1, 1,1);
		glVertex2f(x, y); // center of circle
        glColor4f(1, 1, 0, 0.25);
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

/*
* Scene 0 - Introduction Screen
*/
void introduction() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("ELECTRONIC CIRCUIT SIMULATION",
		1, 1, 1, title_fade, 280, 380, .3, .3, 2);

	print("by JOHN KARAMCHAND - 1AT16CS041",
		1, 1, 1, title_fade, 790, 345, .15, .15, 1);
	print("& KARTHIK GS - 1AT16CS044",
		1, 1, 1, title_fade, 840, 320, .15, .15, 1);

	print("Press N to CONTINUE...",
		1, 1, 1, intro_next_text_appear, 560, 10, .09, .09, 1);
}


/*
*	Scene OF SIMULATION
*/


void HS_drawBackground() {
	// Background


	glBegin(GL_POLYGON);
	glColor3ub(sky_r, sky_g, sky_b); // Sky Blue
	glVertex2f(1400, 800);
	glVertex2f(0, 800);
	glColor3ub(grass_r, grass_g, grass_b); // Green Grass
	glVertex2f(0, 0);
	glVertex2f(1400, 0);
	glEnd();
}



void draw_bulb(float x1, float x2, float y1) {
    glBegin(GL_LINES);
      glVertex2f(x1,y1);
      glVertex2f(x1,y1+15);
    
      glVertex2f(x2,y1);
      glVertex2f(x2,y1+15);
    glEnd();
    int v = (x2-x1)/2 + x1 ;
    glBegin(GL_LINES);
      glVertex2f(x1,y1+15);
      glVertex2f(v,y1+12);
      glVertex2f(v,y1+12);
      glVertex2f(x2,y1+15);
    glEnd();
    
    drawHollowCircle(v,y1+20,15) ;

		if(move) {
    drawFilledCircle(v,y1+18,light_r) ;
		}

}



void HS_drawBattery() {

	glBegin(GL_POLYGON);
    //glColor4f(1,1,0,0.5);

	glColor3ub(59, 91, 132);
	glVertex2f(400, 280);
	glVertex2f(450, 280);
	glVertex2f(450, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(400, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(400, 280);
	glVertex2f(450, 280);
	glVertex2f(450, 200);
	glVertex2f(400, 200);
	glEnd();

    glBegin(GL_LINES);
    glColor3ub(20,20,20);
    glVertex2f(400, 260);
    glVertex2f(450, 260);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(20,20,20);
    glVertex2f(415, 270);
    glVertex2f(435, 270);

    glVertex2f(425, 265);
    glVertex2f(425, 275);
    glLineWidth(1);

    glEnd();
    glLineWidth(1);

    if(move){
    sprintf(batv, "%dv", num);
		if (num>=10)
		{
			wh = 0.1 ;
		}
		else
		{
			wh = 0.15 ;
		}
		
		
    print(batv, 1,1,1, 1, 410,230,wh,wh,1.5) ;



    sprintf(result, "%d", num);

        drawCircleText(425,380,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15,result);  
        drawCircleText(850,380,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15,"0"); 
        drawCircleText(850,100,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15,"0"); 
        drawCircleText(425,100,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15,"0");   
		} 

		    print("Press + to increase voltage", 1,1,1, 1, 350,700,0.15,0.15,1.5) ;
				print("Press - to Decrease voltage", 1,1,1, 1, 350,650,0.15,0.15,1.5) ;
				print("Press o to open/close circuit", 1,1,1, 1, 350,600,0.15,0.15,1.5) ;

				print("Press b to go to previous screen and q to quit",	1, 1, 1, 1, 560, 10, .09, .09, 1);



}

void HS_drawCircuit() {

    glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(425, 280);
	glVertex2f(425, 380);
    glVertex2f(425, 380);
	glVertex2f(750, 380);
	glEnd();
    glLineWidth(1);

    glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(760, 380);
    glVertex2f(850, 380);

    glVertex2f(850, 380);
	glVertex2f(850, 100);

    glVertex2f(850, 100);
    glVertex2f(425, 100);

    glVertex2f(425, 100);
    glVertex2f(425, 200);
    glLineWidth(1);
	glEnd();
    glLineWidth(1);


}




void drawSchoolBoy(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	//glScalef(sx, sy, 0);
	glTranslatef(tx, ty, 0);

	// Left Bulb


    drawCircle(-345,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);
    drawCircle(-300,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-250,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-200,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-150,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-100,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  

    drawCircle(-50,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 
          
    drawCircle(0,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 

	glPopMatrix();

}

void drawSchoolBoy3(GLfloat tx_h2, GLfloat ty_h2,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	//glScalef(sx, sy, 0);
	glTranslatef(tx_h2, ty_h2, 0);

	// Left Bulb


    drawCircle(-345,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);
    drawCircle(-300,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-250,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-200,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-150,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  
    drawCircle(-100,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);  

    drawCircle(-50,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 
          
    drawCircle(0,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 

	glPopMatrix();

}

void drawSchoolBoy1(GLfloat tx_v1, GLfloat ty_v1,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	//glScalef(sx, sy, 0);
	glTranslatef(tx_v1, ty_v1, 0);

	// Left Bulb

    drawCircle(0,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 
    drawCircle(0,-50,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 
    drawCircle(0,-100,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);
    drawCircle(0,-150,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);    

    drawCircle(0,-200,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 

	glPopMatrix();

}
void drawSchoolBoy2(GLfloat tx_v2, GLfloat ty_v2,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	//glScalef(sx, sy, 0);
	glTranslatef(tx_v2, ty_v2, 0);

	// Left Bulb

    drawCircle(0,0,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 
    drawCircle(0,-50,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 
    drawCircle(0,-100,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);
    drawCircle(0,-150,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15);    

    drawCircle(0,-200,
		window_top_r, window_top_g, window_top_b,
		1, 1,
  	15); 

	glPopMatrix();

}

void highSchool() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	HS_drawBackground();

    HS_drawCircuit();
    draw_bulb(750,760,380);


	drawSchoolBoy(schoolboy_x, schoolboy_y,
		1, 1,
		255, 0, 0);

    drawSchoolBoy1(schoolboy_x1, schoolboy_y1,
		1, 1,
		255, 0, 0);

        drawSchoolBoy2(schoolboy_x1_v2 , schoolboy_y1_v2 ,
		1, 1,
		255, 0, 0);    


    drawSchoolBoy3(schoolboy_x1_h , schoolboy_y1_h ,
		1, 1,
		255, 0, 0);


	HS_drawBattery();


       

}




// Function to Render Scene
void renderScene() {
	// Switch to know which scene is playing
	switch (SCENE_ID) {
	case 0:
		introduction();
		break;
    case 7:
        highSchool();
		break;
	default:
		break;
	}

	// glFush sends it to the Display Buffer
	glFlush();
}

// Function to Handle Mouse Clicks
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		std::cout << x << "\t" << 800 - y << "\n";
}

// Animator Updation Function
void update(int) {
	// Introduction
	if (SCENE_ID == 0) {
		if (title_fade < 1)
			title_fade += .003;
		else
			intro_next_text_appear = 1;
	}


    if (SCENE_ID == 7) {
        if(move == true) {
            schoolboy_y = 100 ;
            if(schoolboy_x>=770 && schoolboy_x<=850) {
                schoolboy_x -= speed ;
            }
            else
            {
                schoolboy_x = 850 ;
            }

            //vertical one
            schoolboy_x1 = 850 ;
            if(schoolboy_y1>=300 && schoolboy_y1<=380) {
                schoolboy_y1 -= speed ;
            }
            else
            {
                schoolboy_y1 = 380 ;
            }
            //hoz top
            schoolboy_y1_h = 380 ;
            if(schoolboy_x1_h<=850 && schoolboy_x1_h>=770) {
                schoolboy_x1_h += speed ;
            }
            else
            {
                schoolboy_x1_h = 770 ;
            }
                        //vertical left
            schoolboy_x1_v2 = 425 ;
            if(schoolboy_y1_v2>=300 && schoolboy_y1_v2<=380) {
                schoolboy_y1_v2 += speed ;
            }
            else
            {
                schoolboy_y1_v2 = 300 ;
            }
                        
        }
    }

	


	// Recalls the Display Function
	glutPostRedisplay();

	// Creates a Timer of 25ms
	glutTimerFunc(25, update, 0);
}

// Keyboard Action
void keyPress(unsigned char key, int x, int y) {
	switch (key) {
	// Go to Previous Scene
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID = 0;
		break;
	// Go to Next Scene
	case 'n':
	case 'N':
		if (SCENE_ID == 7)
			break;
		SCENE_ID = 7;
		break;
    	// Go to Next Scene
	case 'o':
	case 'O':
		if (move == true) {
			move = false;
            light_rs = light_r;
            light_r = 0 ;
        }
		else
        {
            move = true ;
            light_r = light_rs ;
        }
        
		break;    
	// Quit Story
	case 'q':
	case 'Q':
		exit(0);
		break;
	case '+':
		light_r = light_r + 8 ;
        speed = speed + 1 ;
        num += 1 ;
		break;
	case '-':
		light_r = light_r - 8 ;
        speed = speed - 1 ;
        num -=1 ;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Function to Initialize Screen
void initializeScreen() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);
}

// Main Function
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("The Epilogue of Education");

	// Enables Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable Smoothening
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Display Function
	glutDisplayFunc(renderScene);

	// Input Functions
	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseClick);

	initializeScreen();

	// Timer Function
	// every 25 milliseconds, update function is called
	glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}
