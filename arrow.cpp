#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
static GLfloat spin = 0.0;
static GLint ball_radius = 20, arrow_x=70,baloon_x=600,baloon_y=0,fire_arrow=0,arrow_y=350, score = 0, baloons[6], count = 0;
int i;
char string [100];
void reset_ballons() {
    for(i=0;i<6;i++)
    baloons[i] = 1;
}
 

void init(void)
{
 glClearColor (0.0, 0.0, 0.0, 0.0);
 glShadeModel (GL_FLAT);
 reset_ballons();
 
}
void drawText(char*string,int x,int y)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y,0);
	  glScalef(0.1,0.1,1);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();

}
void baloon(int x, int y){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere (ball_radius, 20, 16);

    glPopMatrix();
}
void man(){
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(100,400,0);
    glutSolidSphere (20, 20, 16);
    glBegin(GL_LINES);
	glVertex2i(0,-20);
	glVertex2i(0,-90);
	glEnd();
	glFlush();
    glBegin(GL_LINES);
	glVertex2i(0,-40);
	glVertex2i(30,-50);
	glEnd();
    glFlush();
    glBegin(GL_LINES);
	glVertex2i(0,-40);
	glVertex2i(-30,-50);
	glEnd();
    glFlush();
    glBegin(GL_LINES);
	glVertex2i(0,-90);
	glVertex2i(30,-130);
	glEnd();
    glFlush();
    glBegin(GL_LINES);
	glVertex2i(0,-90);
	glVertex2i(-30,-130);
	glEnd();
    glFlush();
    
    //glVertex2f(2 , -390);
    //glVertex2f(-2 , -390);
    glEnd();
    glPopMatrix();
}
void arrow(int x, int y){
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(x,y,0);
    glBegin(GL_LINES);
	glVertex2i(0,0);
	glVertex2i(150,0);
	glEnd();
    glFlush();
    glBegin(GL_LINES);
	glVertex2i(150,0);
	glVertex2i(130,-10);
	glEnd();
    glFlush();
    glBegin(GL_LINES);
	glVertex2i(150,0);
	glVertex2i(130,10);
	glEnd();
    glFlush();
    glPopMatrix();
}
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 //glPushMatrix();
 //glRotatef(spin, 0.0, 0.0, 1.0);
 //glColor3f(1.0, 1.0, 1.0);
 //glRectf(-25.0, -25.0, 25.0, 25.0);
  glColor3f(1,1,1);
	sprintf(string,"Score : %d ",score); 
	drawText(string,10,600); 
 //glPopMatrix();
 man();
 arrow(arrow_x,arrow_y);
 for(i=0;i<6;i++) {
    if (baloons[i])
        baloon(baloon_x+(i*100),baloon_y);
 }
 glutSwapBuffers();
}
void spinDisplay(void)
{
 spin = spin + 2.0;
 if (spin > 360.0)
 spin = spin - 360.0;
 baloon_y = baloon_y + 1;
 if(baloon_y>800){
     baloon_y=0;
}
if(fire_arrow){
arrow_x = arrow_x +10;
   if(arrow_x>1200){
    arrow_x=70;
    fire_arrow=0;
    }
}
for(i=0;i<6;i++){
    if (baloons[i])
        if(arrow_x+150 > (baloon_x + i*100) - ball_radius && arrow_x < (baloon_x + i*100) + ball_radius){
            if((arrow_y > (baloon_y - ball_radius)) && (arrow_y < (baloon_y + ball_radius))) {
                score++;
                //printf("%d\n", score);
                baloons[i] = 0;
                count++;
            }
            }
}

if (count == 6) {
    count = 0;
    reset_ballons();
    baloon_y = 0;
}


 glutPostRedisplay();
}

void reshape(int w, int h)
{
 glViewport (0, 0, (GLsizei) w, (GLsizei) h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0, 1200, 0, 800, 0, 100);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}
/*void keyboard (unsigned char key, int x, int y)
{
 switch (key) {
 case 'q':
     x=1;
    glutIdleFunc(display);
    
 glutPostRedisplay();
 break;
 
 default:
 break;
 
}*/
void mouse(int button, int state, int x, int y)
{
 switch (button) {
 case GLUT_LEFT_BUTTON:
 if (state == GLUT_DOWN)//{
    //fire_arrow=1;
    //}
 glutIdleFunc(spinDisplay);
 break;
 case GLUT_RIGHT_BUTTON:
 if (state == GLUT_DOWN){
     fire_arrow=1;
    glutIdleFunc(spinDisplay);}
    break;
 case GLUT_MIDDLE_BUTTON:
 if (state == GLUT_DOWN)
 glutIdleFunc(NULL);
 break;
 default:
 break;
 }
}
/*
 * Request double buffer display mode.
 * Register mouse input callback functions
 */
int main(int argc, char** argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize (800, 1200);
 glutInitWindowPosition (0, 0);
 glutCreateWindow (argv[0]);
 init ();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutMouseFunc(mouse);
 //glutKeyboardFunc(keyboard);
 glutMainLoop();
 return 0;
}
