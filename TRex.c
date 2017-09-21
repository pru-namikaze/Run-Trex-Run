


/*
*
*
*
*
*			             Computer Graphics Mini-Project using OpenGL in C Language
*
*
*	Aim:Program to play "the T-Rex Game" which can be played in Google Chrome when user's Computer is not connected to the Internet
*
*	Developer:	Pranshu Raj Goel
*	Tools:		OpenGL
*	Language:	C Language
*
*
*
*
*/


							//header Files
#include<stdio.h>					//Standard Input-Output Library
#include<stdlib.h>					//Standard Function Library
#include<GL/glut.h> 					//OpenGL Library
#include<string.h>					//String Library


#define collisioncheck 1				//to turn collision detection on->1, and off->0  


							//menu id's for the menu
int texchangeid,terchangeid,speedchangeid,sunshowid,sunsizeid,sunspinid,settimeid,daylenid;

							//flags declaration
int COLLISIONCHECKTIME=1;				//check for collision ever millisecond

int JUMPSPEED=8;					//speed of jump: 125 pixel/sec, jump time: 2.4sec
int MAX_HEIGHT=150;					//max height that can be reached by T_Rex: 150

int NUM_CACT=25;					//number of cactus position stored: 25
int DASH_CACT_SAND=3;					//speed of cactus: 333.33 pixels/sec, Time to attack: 6 sec

int SCREEN_CENTERX=1000;				//center X coordinate for the screen: 1000
int SCREEN_CENTERY=250;					//center Y coordinate for the screen: 250
int ANGULAR_SPEED=5;					//angular speed: 142.86 degree/sec, time to complete a full rotation: 2.52 sec
int ZOOMING=1;						//rate at which rectangle expands: 166.67 pixles/sec

float SUN_SCALE=0.5;					//sun's approximate radius: 100*SUN_SCALE= 100*0.5= 50pixel
int SUN_EDGE=10;					//number of edge in sun: decagon, i.e- 10
int SUN_X=1900;						//X coordinate of sun: 1900
int SUN_Y=400;						//Y coordinate of sun: 400
int SUN_ASPEED=1;					//angular speed of sun:1000 deg/sec, time to complete a rotation 0.36 sec
int SPINSUN=1;

int NUM_SAND_GRANULE=40;				//number of sand granule in the desert Land

int NUM_STAR=63;					//number of position for star stored
int NUM_SKY_COLOR=1000;					//Maximum day time in the game,i.e-  0-Max and Max-0
int day=1;						//Day or Not
int skyindex=1000;					//Current time
int DAYCYCLE=10;					//how fast does the time updates
float STAR_SHOW=0.4;					//show star at RGB value<(RGB(sky blue)*SHOW_STAR)/NUM_SKY_COLOR


//T_Rex Coordinates
GLdouble dinox[]={
20.0,40.0,40.0,20.0,
70.0,90.0,90.0,70.0,
10.0,100.0,100.0,10.0,
10.0,20.0,20.0,10.0,
20.0,30.0,30.0,20.0,
30.0,65.0,65.0,30.0,
52.5,56.25,56.25,52.5
};
							//28 Entries
GLdouble dinoy[]={
200.0,200.0,210.0,210.0,
200.0,200.0,210.0,210.0,
210.0,210.0,250.0,250.0,
250.0,250.0,300.0,300.0,
290.0,290.0,300.0,300.0,
265.0,265.0,300.0,300.0,
273.75,273.75,277.5,277.5
};
							//28 Entries
//T-Rex Color vector array
GLfloat dinomorfer[][3]={{0.0,0.0,0.0},{0.491176,0.275098,0.1058824},{1.0,0.0,0.0}};
int trexcolor=2;					//color select option for T-Rex Body


//Desert Coordinates
GLfloat desertx[]={0.0,1999.0,1999.0,0.0};		//4 Entries
GLfloat deserty[]={0.0,0.0,200.0,200.0};		//4 Entries
//land Color
GLfloat landmorfer[]={
0.639216,0.431373,0.250980,0.121,0.267,0.251,
0.168627,0.219608,0.137255,-0.035294,+0.325490,-0.003922
};
int landcolor=0;


//Cactus Coordinates
GLfloat cactusx[]={
320.0,340.0,340.0,337.5,335.0,325.0,322.5,320.0,
340.0,350.0,360.0,340.0,
350.0,360.0,360.0,358.75,357.5,352.5,351.25,350.0,
300.0,310.0,320.0,320.0,
300.0,310.0,310.0,308.75,307.5,302.5,301.25,300.0
};
							//32 Entries
GLfloat cactusy[]={
185.0,185.0,280.0,283.5,285.0,285.0,283.5,280.0,
230.0,230.0,240.0,240.0,
240.0,240.0,280.0,281.66,282.5,282.5,281.66,280.0,
240.0,230.0,230.0,240.0,
240.0,240.0,280.0,281.66,282.5,282.5,281.66,280.0
};
							//32 Entries


//the cactus is 320 unit unit from the left side of the screen,but during plotting of cactus we took care of the is extra
//distance by subtracting the excess from the the position
GLfloat cactposmsg[]={2000.0,2830.0,3600.0,4450.0,5320.0,6210.0,6980.0,7790.0,8630.0,9500.0,10300.0,11180.0,12070.0,12880.0,13750.0,14580.0,15430.0,16200.0,
16990.0,17880.0,18680.0,19550.0,20450.0,21200.0,22000.0};
							//Starting position of cactus
GLfloat cactpos[]={2000.0,2830.0,3600.0,4450.0,5320.0,6210.0,6980.0,7790.0,8630.0,9500.0,10300.0,11180.0,12070.0,12880.0,13750.0,14580.0,15430.0,16200.0,
16990.0,17880.0,18680.0,19550.0,20450.0,21200.0,22000.0};
							//Dynamic position of cactus


//position of Stone Granules
GLfloat sandx[]={1620.000000,267.000000,45.000000,387.000000,1236.000000,52.000000,468.000000,179.000000,998.000000,61.000000,1935.000000,920.000000,
1305.000000,1253.000000,1584.000000,1142.000000,1459.000000,1328.000000,801.000000,1912.000000,1198.000000,1302.000000,1977.000000,
557.000000,1562.000000,1697.000000,257.000000,427.000000,1832.000000,1784.000000,1305.000000,1453.000000,125.000000,1423.000000,
1913.000000,1362.000000,1548.000000,382.000000,1614.000000,620.000000};
GLfloat sandy[]={116.000000,9.000000,45.000000,166.000000,92.000000,60.000000,26.000000,19.000000,143.000000,120.000000,89.000000,54.000000,171.000000,
59.000000,150.000000,73.000000,149.000000,60.000000,107.000000,92.000000,134.000000,73.000000,83.000000,126.000000,27.000000,
176.000000,84.000000,181.000000,32.000000,16.000000,143.000000,100.000000,177.000000,188.000000,18.000000,69.000000,0.000000,
44.000000,41.000000,144.000000};


//Sun Vertices
							//starting position of the sun
GLdouble sunxmsg[]={2000.000000,1980.901733,1930.901733,1869.098267,1819.098267,1800.000000,1819.098267,1869.098267,1930.901611,1980.901611};
GLdouble sunymsg[]={400.000000,458.778534,495.105652,495.105652,458.778534,400.000000,341.221466,304.894348,304.894348,341.221436};
							//dynamic position of sun
GLdouble sunx[]={2000.000000,1980.901733,1930.901733,1869.098267,1819.098267,1800.000000,1819.098267,1869.098267,1930.901611,1980.901611};
GLdouble suny[]={400.000000,458.778534,495.105652,495.105652,458.778534,400.000000,341.221466,304.894348,304.894348,341.221436};
int SHOWSUN=1;						//show the shun or not
int showsunmenu=1;					//show sun using menu
GLdouble sunangle=0;					//sun angle rotation


//Position of Stars in Night Sky
GLfloat starx[]={85.0,44.0,110.0,1482.0,1579.0,146.0,716.0,125.0,793.0,801.0,1524.0,1706.0,1432.0,1992.0,700.0,1038.0,1889.0,858.0,1845.0,666.0,748.0,1403.0,
236.0,208.0,1904.0,1507.0,1589.0,1319.0,760.0,1475.0,915.0,265.0,1324.0,1921.0,1647.0,903.0,1967.0,363.0,928.0,1613.0,1917.0,
1304.0,271.0,301.0,249.0,871.0,1240.0,138.0,582.0,1937.0,1556.0,182.0,292.0,645.0,290.0,197.0,1004.0,731.0,1416.0,1664.0,207.0,1183.0,1829.0};
GLfloat stary[]={469.0,458.0,300.0,383.0,205.0,228.0,286.0,224.0,444.0,467.0,237.0,361.0,223.0,461.0,262.0,472.0,284.0,454.0,263.0,466.0,343.0,371.0,
248.0,436.0,468.0,390.0,333.0,373.0,422.0,401.0,489.0,329.0,384.0,419.0,212.0,389.0,499.0,350.0,466.0,443.0,369.0,255.0,356.0,393.0,
216.0,471.0,417.0,301.0,477.0,232.0,319.0,321.0,404.0,368.0,309.0,372.0,310.0,494.0,245.0,232.0,395.0,235.0,413.0};


//vertices for the kill screen sqaure
GLfloat killscrnxmsg[]={-3,3,3,-3};
GLfloat killscrnymsg[]={-3,-3,3,3};
							//Starting vertices of killscrnsquare
GLfloat killscrnx[]={-3,3,3,-3};
GLfloat killscrny[]={-3,-3,3,3};
							//Dynamic vertices of killscrnsquare

GLfloat killscrnangle=0;
GLint killscrnover=0;

GLfloat height=0.0;					//height in the air
GLint jflag=0;						//Jump Flag;
GLint jcount=0;						//jump Count;

int gameover=0;						//flag for game is over or not
int score=0;						//variable to count score


//Text to diaplay on cover screen
char texta[]={"Bangalore Institut Of Technology"};
char textb[]={"Department of Computer Science and Engineering"};
char textc[]={"OpenGL Mini Project"};
char textd[]={"Run T-Rex Run !!!"};
char texte[]={"<<---------------------- INSTRUCTIONS ---------------------->>"};
char textf[]={"Press 'w' or 'W' or <Spacebar Key> to make T-Rex Jump"};
char textg[]={"Press 'r' or 'R' to Restart the game"};
char texth[]={"Press 's' or 'S' to start the game"};
char texti[]={"Press the right mouse button to access Menu"};
char textj[]={"Press <ESC Key> to quit the game"};
char textk[]={"Teacher Incharges: "};
char textl[]={"  Prof. BHANUSHREE K J"};
char textm[]={"  Prof. BHAVANA K V"};
char textn[]={"Submited By: "};
char texto[]={"  PRANSHU RAJ GOEL"};
char textp[]={"  1BI14CS119"};


GLint gameStart=0;					//Game has started or not


GLuint displayID1,displayID2;				//declaration for displaylist


void drawText(GLint x,GLint y,char* str)		//to draw a string of character(One character at a time) at position x,y
{
	int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(str);i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}


void drawSun()						//draw decagon for sun
{
	int i;
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,0.0);
	for(i=0;i<SUN_EDGE;i++)
		glVertex2f(sunx[i]-SUN_X,suny[i]-SUN_Y);
	glEnd();
}
void drawStars()					//draw stars
{
	int i;
	glPushMatrix();
	glLoadIdentity();
	glPointSize(3.0);
	glBegin(GL_POINTS);
	glColor3f(0.5294,0.8078,0.9216);		//sky blue
	for(i=0;i<NUM_STAR;i++)
		glVertex2f(starx[i],stary[i]);
	glEnd();
	glPopMatrix();
}
void drawTRex()						//Drawing R_Rex
{	int i;
	glBegin(GL_POLYGON);				//left leg
	glColor3fv(dinomorfer[trexcolor]);
	for(i=0;i<4;i++)
		glVertex2d(dinox[i],dinoy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//right leg
	glColor3fv(dinomorfer[trexcolor]);
	for(i=4;i<8;i++)
		glVertex2d(dinox[i],dinoy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//torso
	glColor3fv(dinomorfer[trexcolor]);
	for(i=8;i<12;i++)
		glVertex2d(dinox[i],dinoy[i]);
	glEnd();
	glBegin(GL_POLYGON);				// |-neck
	glColor3fv(dinomorfer[trexcolor]);
	for(i=12;i<16;i++)
		glVertex2d(dinox[i],dinoy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//_ -neck
	glColor3fv(dinomorfer[trexcolor]);
	for(i=16;i<20;i++)
		glVertex2d(dinox[i],dinoy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//head
	glColor3fv(dinomorfer[trexcolor]);
	for(i=20;i<24;i++)
		glVertex2d(dinox[i],dinoy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//eye
	glColor3f(1.0,1.0,1.0);
	for(i=24;i<28;i++)
		glVertex2d(dinox[i],dinoy[i]);
	glEnd();

}
void drawSand()						//Draw Stones/Granules
{
	int i;
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glColor3f(0.9569,0.5725,0.3765);
	for(i=0;i<NUM_SAND_GRANULE;i++)
		glVertex2f(sandx[i],sandy[i]);
	glEnd();

}
void drawDesert()					//Drawing Desert
{
	int i;
	glBegin(GL_POLYGON);				//land
	glColor3f(landmorfer[landcolor+0]+((landmorfer[landcolor+3])*skyindex/NUM_SKY_COLOR),landmorfer[landcolor+1]+((landmorfer[landcolor+4])*skyindex/NUM_SKY_COLOR),landmorfer[landcolor+2]+((landmorfer[landcolor+5])*skyindex/NUM_SKY_COLOR));
	for(i=0;i<4;i++)
		glVertex2f(desertx[i],deserty[i]);
	glEnd();
	drawSand();
}
void drawCactus()					//drawing cactus template
{
	int i;
	glBegin(GL_POLYGON);				//middle cactus shoot |
	glColor3f(0.5412,0.6039,0.0404);
	for(i=0;i<8;i++)
		glVertex2f(cactusx[i],cactusy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//right cactus branch _
	glColor3f(0.5412,0.6039,0.0404);
	for(i=8;i<12;i++)
		glVertex2f(cactusx[i],cactusy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//right cactus shoot |
	glColor3f(0.5412,0.6039,0.0404);
	for(i=12;i<20;i++)
		glVertex2f(cactusx[i],cactusy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//left cactus branch _
	glColor3f(0.5412,0.6039,0.0404);
	for(i=20;i<24;i++)
		glVertex2f(cactusx[i],cactusy[i]);
	glEnd();
	glBegin(GL_POLYGON);				//left cactus shoot |
	glColor3f(0.5412,0.6039,0.0404);
	for(i=24;i<32;i++)
		glVertex2f(cactusx[i],cactusy[i]);
	glEnd();
}
void drawkillscrnsquare()				//draw kill screen square
{
	int i;
	glBegin(GL_POLYGON);
	glColor3f(0.109375,0.222656,0.730468);		//Persian Blue
	for(i=0;i<4;i++)
		glVertex2f(killscrnx[i],killscrny[i]);
	glEnd();

}
void drawCoverPage()					//drawing the cover page
{
        	glClearColor(0.0,0.52,0.79,1.0);	
       	 	glColor3f(1.0,1.0,1.0);			
        	drawText(0757.142857,450.0,texta);	//draw texta
        	drawText(0642.857143,400.0,textb);	//draw textb
        	drawText(0842.857143,350.0,textc);	//draw textc
        	drawText(0857.142857,300.0,textd);	//draw textd
        	drawText(0385.714286,250.0,texte);	//draw texte
        	drawText(0585.714286,225.0,textf);	//draw textf
        	drawText(0748.571429,200.0,textg);	//draw textg
        	drawText(0771.428571,175.0,texth);	//draw texth
         	drawText(0677.142857,150.0,texti);	//draw texti
        	drawText(0748.571429,125.0,textj);	//draw textj
        	drawText(0100.000000,075.0,textk);	//draw textk
        	drawText(0100.000000,050.0,textl);	//draw textl
        	drawText(0100.000000,025.0,textm);	//draw textm
        	drawText(1557.142857,075.0,textn);	//draw textn
        	drawText(1557.142857,050.0,texto);	//draw texto
        	drawText(1557.142857,025.0,textp);	//draw textp
        	
}
void drawScnFreez()					//displaying the scoreand GAME OVER
{
	char result[10];
	sprintf(result,"SCORE: %d",score);		//store score in result
	glClearColor(0.109375,0.222656,0.730468,1.0);	//Persian blue
	glColor3f(1.0,0.0,0.0);				//red
	drawText(800,350,"GAME OVER");			//display GAME OVER message
	drawText(700,250,"T_Rex is hurt ");		//display trex is hurt
	drawText(750,150,result);			//display the result
}


void plotCactus(GLfloat pos)				//plotting cactus in right positionwithrespect to left side of the screen
{
	glPushMatrix();
 	glTranslatef((pos-320.0),0.0,0.0);		//now the distance of the posis from the right
 	glCallList(displayID1);				//now draw the cactus with respect to left side of the screen
   	glPopMatrix();
}


void animateSky(int value)
{
	if(gameStart!=0)				//if the game has begin
	{
		if(day==1&&skyindex<NUM_SKY_COLOR)	//and it is day time
			skyindex++;			//time will increase
		if(day==1 && skyindex==NUM_SKY_COLOR)	//if day is over
		{
			day=0;				//day is over
			skyindex--;			//time will decreament by one as it is one more than maximum time
		}
		else if(day==0&&skyindex>0)		//if it is night
			skyindex--;			//time will decrease
		else if(day==0 && skyindex==0)		//if night is over
		{
			day=1;				//day has begin
			skyindex++;			//time will increment as it is one less than the minimum value
		}
		glutPostRedisplay();			//change has happen so redisplay
	}
	glutTimerFunc(DAYCYCLE,animateSky,0);		//call animateSky back after DAYCYCLE millisec

}
void flying()						//Jumping of T_Rex
{
	if(jflag==1 && height<MAX_HEIGHT)		//if jumping and below max height
		height++;				//increase height
	else if(jflag==1 && height==MAX_HEIGHT)		//if reached max height
		jflag=-1;				//start falling
}
void falling()						//falling of T_Rex
{
	if(jflag==-1 && height>0)			//if falling and didn't reach groumd
		height--;				//decrease height
	else if(jflag==-1 && height==0)			//if reached ground
	{
		jflag=0;				//be in a state to be ready to jump
		jcount--;				//release the jump lock
	}
}
void animateTRex(int value)				//animation for T_Rex's jumping;
{
	if(gameStart!=0)
	{
		flying();				//upward movement of T_Rex
		falling();				//downward movement of T_Rex
		glutPostRedisplay(); 			//Inform GLUT that the display has changed;
    	}
    	glutTimerFunc(JUMPSPEED,animateTRex,0);		//Call animateTRex after each 8 millisecond;

}
void animateCactus(int value)				//animation,reset and check collision for cactus;
{
	int i;
	if(gameStart!=0)
	{
		for(i=0;i<NUM_CACT;i++)			//for ever cactus object
		{
			if(cactpos[i]==-40)		//to reset the position of cactus once the pass T_Rex
			       cactpos[i]=(cactposmsg[i]+cactposmsg[NUM_CACT-1]);//reset
			cactpos[i]--;			//left movement of cactus
		}
		glutPostRedisplay(); 			// Inform GLUT that the display has changed;
    	}
    	glutTimerFunc(DASH_CACT_SAND,animateCactus,0);	//Call animateCactus after each 3 millisecond;
}
void animateSand(int value)				//animation,reset and check collision for cactus;
{
	int i;
	if(gameStart!=0)
	{
		for(i=0;i<NUM_SAND_GRANULE;i++)		//for ever cactus object
		{
			if(sandx[i]==0)			//if sand granule reaches the end
				sandx[i]=2000;		//reset its position
			sandx[i]--;			//till then move the sand
		}
		glutPostRedisplay(); 			// Inform GLUT that the display has changed;
    	}
    	glutTimerFunc(DASH_CACT_SAND,animateSand,0);	//Call animateCactus after each 3 millisecond;
}
void killSrcnSquareRotation(int value)			//angle updater for kill screen square
{
	killscrnangle++;				//increase angle
	if(killscrnangle>360.0)				//if angle is more than 360 degree
		killscrnangle-=360.0;			//recalculate the angle
	glutPostRedisplay(); 				// Inform GLUT that the display has changed;
	glutTimerFunc(ANGULAR_SPEED,killSrcnSquareRotation,0);//call killSrcnSquareRotation after each 14 milliseconds
}
void killSrcnSquareScaling(int value)			//scaling the kill screen square
{

	if(gameover && !killscrnover)			//if game is over and kill screen is not covered
	{						//scale the coordinated of the kill screen square
		killscrnx[0]-=0.5;			//		A
		killscrnx[1]+=0.5;			//		|
		killscrnx[2]+=0.5;			//		|
		killscrnx[3]-=0.5;			//		|
		killscrny[0]-=0.5;			//		|
		killscrny[1]-=0.5;			//		|
		killscrny[2]+=0.5;			//		|
		killscrny[3]+=0.5;			//		|
   	}						//		V
   	if(killscrnx[0]==-1050)				//if kill screen is fully covered
   		killscrnover=1;				//tell that kill screen is fully covered
	glutPostRedisplay(); 				// Inform GLUT that the display has changed;
	glutTimerFunc(ZOOMING,killSrcnSquareScaling,0);	//call killSrcnSquareScaling after each 14 milliseconds
}
void endScreen()					//animation in the end screen
{
	glPushMatrix();
	glTranslatef(SCREEN_CENTERX,SCREEN_CENTERY,0.0);//transfer the kill screen square to the middle of the screen
	glRotatef(killscrnangle,0.0,0.0,1.0);		//rotate the kill screen square
	drawkillscrnsquare();				//draw the kill screen square
   	glPopMatrix();
}
void sunRotation(int value)				//angle updater for sun square
{
	sunangle++;					//increase angle
	if(sunangle>360.0)				//if angle is more than 360 degree
		sunangle-=360.0;			//recalculate the angle
	glutPostRedisplay(); 				// Inform GLUT that the display has changed;
	glutTimerFunc(SUN_ASPEED,sunRotation,0);	//call sunSquareRotation after each 14 milliseconds

}
void sunShine()						//animation for Sun
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(SUN_X,SUN_Y,0.0);			//transfer the sun square1 to the sun position
	if(SPINSUN)					//if the sun has to spin
		glRotatef(sunangle,0.0,0.0,1.0);	//rotate the sun polygon
	glScalef(SUN_SCALE,SUN_SCALE,1.0);		//scale the sun
	glCallList(displayID2);				//Draw the sun
	glPopMatrix();
}


void checkCollision(int value)				//check if game is over or not and update scoreboard
{
	int i;
	if(collisioncheck)
	{
		for(i=0;i<NUM_CACT;i++)			//for ever cactus object
		{
			if(cactpos[i]>=110 && cactpos[i]<=120)//if cactus is in range,be careful and so check if you hit a cactus and hurt T_Rex
				if(height<85 && !gameover)//if the jump is low, T_Rex is hurt; check if the cactus is touching the body or 	not
				{			//because in this case the body will be directly above the cactus
				     printf("T_Rex is hurt\n");//T_Rex got hit
				     printf("Score:%d\n",score);//display score
				     gameover=1;	//Game Over
				}
			if(cactpos[i]>-10 && cactpos[i]<110)//if cactus is in range,be careful and so check if you hit a cactus and hurt T_Rex
				if(height<100 && !gameover)//if the jump is low, T_Rex is hurt
				{
				     printf("T_Rex is hurt\n"); //T_Rex got hit
				     printf("Score:%d\n",score);//display score
				     gameover=1;	//Game Over
				}
			if(cactpos[i]>=-30 && cactpos[i]<=-10)//if cactus is in range,be careful and so check if you hit a cactus and hurt T_Rex
				if(height<85 && !gameover)//if the jump is low, T_Rex is hurt; check if the cactus is touching the body or 	not
				{			//because in this case the body will be directly above the cactus
				     printf("T_Rex is hurt\n"); //T_Rex got hit
				     printf("Score:%d\n",score);//display score
				     gameover=1;	//Game Over
				}
			if(cactpos[i]==-40)		//to reset the position of cactus once the pass T_Rex
			       if(!gameover)		//if game is not over
			       		score+=100;	//add 100 points to be able to jump above the cactus
		}
	}
	glutPostRedisplay(); 				// Inform GLUT that the display has changed;
	glutTimerFunc(COLLISIONCHECKTIME,checkCollision,0);//Call animateCactus after each 33 millisecond;
}


void display()
{
	int i;
	char temp;
	glClear(GL_COLOR_BUFFER_BIT);			//Clear Color buffer bit
	if(gameStart==1)				//if the game has started
	{
		if(!gameover)				//if game is not over, play the game
		{
			glClearColor((0.5294117647*skyindex)/NUM_SKY_COLOR,(0.8078431373*skyindex)/NUM_SKY_COLOR,(0.921568275*skyindex)/NUM_SKY_COLOR,1.0);					//dynamic background Color change
			if(jflag!=0)			//if T_Rex is not on ground
			{
				glPushMatrix();
 				glTranslatef(0.0,height,0.0);//Translate T_Rex to his height
 				drawTRex();		//draw T_Rex
   				glPopMatrix();
			}
			else if(jflag==0)		//if T_Rex is ready to jump
				drawTRex();		//draw T_rex on the Ground
				drawDesert();		//draw Desert sand
			if(skyindex<(STAR_SHOW*NUM_SKY_COLOR))//if light level is low enough for star to shine
			{
				drawStars();		//star will shine
				SHOWSUN=0;		// sun will go down
			}
			else
				SHOWSUN=1;		//if light level are high then sun will shine
			if(SHOWSUN && showsunmenu)	//if sun has to shine
				sunShine();		//then the sun will shine
			for(i=0;i<NUM_CACT;i++)		//for every cactus plant
				plotCactus(cactpos[i]);	//plot the cactus in their position
		}
		else					//if game is over
		{
			glClearColor(0.0,0.0,0.0,1.0);	//black
			if(!killscrnover)		//if the kill screen is not covered
				endScreen();		//if the game is over, show the GAME OVER screen
		}
		if(killscrnover)			//if screen is completely covered
			drawScnFreez();			//display the GAME OVER message

	}
    	else if(gameStart==0)				//cover Page of the Game
    	{
        	drawCoverPage();
        	glutPostRedisplay();			//changle has been made to the display so re display it
       	}
	glFlush();					//flush the output to the screen
	glutPostRedisplay();				//show any change if any
}


void reset()						//initilize or reset the value of constants to start a new game
{
	int i;
	day=1;						//reset all the constants
	NUM_SKY_COLOR=1000;				//		A
	skyindex=NUM_SKY_COLOR;				//		|
	SHOWSUN=1;					//		|
	sunangle=0;					//		|
	killscrnangle=0;				//		|
	killscrnover=0;					//		|
	height=0.0;					//		|
	jflag=0;					//		|
	jcount=0;					//		|
	gameover=0;					//		|
	DASH_CACT_SAND=3;				//		|
	DAYCYCLE=10;					//		|
	SPINSUN=1;					//		|
	SUN_SCALE=0.5;					//		|
	showsunmenu=1;					//		|
	score=0;					//		|
	trexcolor=2;					//		|
	landcolor=0;					//		V
	for(i=0;i<NUM_CACT;i++)				//reset the position of cactus
		cactpos[i]=cactposmsg[i];
	for(i=0;i<4;i++)				//reset the value of the kill screen square
	{
		killscrnx[i]=killscrnxmsg[i];
		killscrny[i]=killscrnymsg[i];
	}
	for(i=0;i<SUN_EDGE;i++)				//reset the value of the kill screen square
	{
		sunx[i]=sunxmsg[i];
		suny[i]=sunymsg[i];
	}
}


void keyboardEvent(unsigned char key,int x,int y)
{
	if(key==' '||key=='w'||key=='W') 		//if w or W or " " is pressed make T_rex jump once
		if(jcount==0)				//apply jumplock
		{
			jflag=1;			//jumping
			jcount++;			//number of jumps active,either 0 or 1
		}
	if(key==27)					//if c or C is pressed
		exit(0);				//Close
	if(key=='r'||key=='R')				//if r or R is pressed
		reset();				//Restart
	if(key=='s'||key=='S')				//if s or S is pressed
		gameStart=1;				//Start the Game
	display();					//call the display
}


void menu(int key1 )					//menu menu
{   
	switch(key1)
	{
		case 1:	reset();
			gameStart=(gameStart+1)%2;
			break;
		case 2: exit(0);
		  	break;
	}
}
void texchange(int key2)				//submenu to change TRex color
{
	switch(key2)
	{
		case 1:	trexcolor=0;
			break;
		case 2:	trexcolor=1;
			break;
		case 3:	trexcolor=2;
			break;
	}
}
void terchange(int key3)				//submenu to change the terrain
{
	switch(key3)
	{
		case 1:	landcolor=0;
			break;
		case 2:	landcolor=6;
			break;
	}
}
void speedchange(int key4)				//submenu to change the travelling speed
{
	switch(key4)
	{
		case 1:	DASH_CACT_SAND=3;
			break;
		case 2:	DASH_CACT_SAND=6;
			break;
		case 3:	DASH_CACT_SAND=9;
			break;
	}
}
void sunshow(int key5)					//submenu to control displaying of sun
{
	switch(key5)
	{
		case 1:	showsunmenu=1;
			break;
		case 2:	showsunmenu=0;
			break;
	}
}
void sunspin(int key6)					//submenu for spinning of the sun
{
	switch(key6)
	{
		case 1:	SPINSUN=1;
			break;
		case 2:	SPINSUN=0;
			break;
	}
}
void sunsize(int key7)					//submenu to control the sun size
{
	switch(key7)
	{
		case 1:	SUN_SCALE=0.3;
			break;
		case 2:	SUN_SCALE=0.5;
			break;
		case 3:	SUN_SCALE=0.7;
			break;
	}
}
void settime(int key8)					//submenu to set time
{
	switch(key8)
	{
		case 1:	day=1;
			skyindex=NUM_SKY_COLOR/10;
			break;
		case 2:	day=1;
			skyindex=NUM_SKY_COLOR;
			break;
		case 3:	day=0;
			skyindex=NUM_SKY_COLOR/10;
			break;
		case 4:	day=1;
			skyindex=0;
			break;
	}
}
void daylen(int key9)					//submenu to set day-night cycle length
{
	switch(key9)
	{
		case 1:	NUM_SKY_COLOR=2;
			skyindex=0;
			DAYCYCLE=1000;
			break;
		case 2:	NUM_SKY_COLOR=10;
			skyindex=0;
			DAYCYCLE=100;
			break;
		case 3:	NUM_SKY_COLOR=100;
			skyindex=0;
			DAYCYCLE=100;
			break;
		case 4:	NUM_SKY_COLOR=1000;
			skyindex=0;
			DAYCYCLE=10;
			break;
	}
}

void menusystem()					//main menu description function
{
	texchangeid = glutCreateMenu(texchange);		
	glutAddMenuEntry("Black",1);
	glutAddMenuEntry("Brown",2);
	glutAddMenuEntry("Red",3);

	terchangeid = glutCreateMenu(terchange);
	glutAddMenuEntry("Dessert",1);
	glutAddMenuEntry("Arid",2);

	speedchangeid = glutCreateMenu(speedchange);
	glutAddMenuEntry("Normal",1);
	glutAddMenuEntry("Slow",2);
	glutAddMenuEntry("Slowest",3);

	sunshowid = glutCreateMenu(sunshow);
	glutAddMenuEntry("on",1);
	glutAddMenuEntry("off",2);

	sunsizeid = glutCreateMenu(sunsize);
	glutAddMenuEntry("smaller",1);
	glutAddMenuEntry("normal",2);
	glutAddMenuEntry("large",3);

	sunspinid = glutCreateMenu(sunspin);
	glutAddMenuEntry("on",1);
	glutAddMenuEntry("off",2);

	settimeid = glutCreateMenu(settime);
	glutAddMenuEntry("Morning",1);
	glutAddMenuEntry("Noon",2);
	glutAddMenuEntry("Afternoon",3);
	glutAddMenuEntry("Night",4);

	daylenid = glutCreateMenu(daylen); 
	glutAddMenuEntry("length: 2",1);
	glutAddMenuEntry("length:10",2);
	glutAddMenuEntry("length:100",3);
	glutAddMenuEntry("default",4);

	glutCreateMenu(menu);
	glutAddMenuEntry("Re/Start Game",1);
	glutAddSubMenu("T-rex color",texchangeid);
	glutAddSubMenu("Terrain",terchangeid);
	glutAddSubMenu("Travelling speed",speedchangeid);
	glutAddSubMenu("Toggle Show Sun",sunshowid);
	glutAddSubMenu("Change sun size",sunsizeid);
	glutAddSubMenu("Toggle sun spin",sunspinid);
	glutAddSubMenu("Day-Night Cycle lenght",daylenid);
	glutAddSubMenu("Set time",settimeid);
	glutAddMenuEntry("Quit",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


void myinit()						//initilization function
{ 	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,1999.0,0.0,499.0);
	glMatrixMode(GL_MODELVIEW);
	displayID1 = glGenLists(1);			//Display List for drawing Cactus
	glNewList(displayID1,GL_COMPILE);
		drawCactus();
	glEndList();
	displayID2 = glGenLists(1);			//Display List for drawing sun
	glNewList(displayID2,GL_COMPILE);
		drawSun();
	glEndList();
}


int main(int argc,char** argv)				//MAIN FUNCION
{
	reset();					//start or restart the game
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(2000,500);			//window size
	glutInitWindowPosition(200,0);			//window position
	glutCreateWindow("Run T-REX Run");		//window tital name
	glutDisplayFunc(display);			
	glutKeyboardFunc(keyboardEvent);
	myinit();					//initilization function
	menusystem();					//menu system
	glutTimerFunc(JUMPSPEED,animateTRex,0);		//timer to animate jumping of TRex
	glutTimerFunc(DASH_CACT_SAND,animateCactus,0);	//timer to animate movement of cactus
	glutTimerFunc(DASH_CACT_SAND,animateSand,0);	//timer to animate movement of sand Granules
	glutTimerFunc(COLLISIONCHECKTIME,checkCollision,0);//timer to check collision between TRex and Cactus 
	glutTimerFunc(ANGULAR_SPEED,killSrcnSquareRotation,0);//timer to animate rotation of kill screen square
	glutTimerFunc(ZOOMING,killSrcnSquareScaling,0);	//timer to animate scaling of the kill screen square
	glutTimerFunc(SUN_ASPEED,sunRotation,0);	//timer to animate rotation of sun
	glutTimerFunc(DAYCYCLE,animateSky,0);		//time to animate passing of time
	glutMainLoop();
	return 0;
}
