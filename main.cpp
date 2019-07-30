#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include<math.h>
#include <string.h>
#include <windows.h>
#include<mmsystem.h>
using namespace std;

float move1 = 0.0;
float move2 = 0.0;
float move3 = 0.0;
float move4 = 0.0;
float move5 = 0.0;
float move6 = 0.0;
float speed = 0.02;
int carPos = 1;
int prevcarPos = 0;
int carPos2 = 3;
int prevcarPos2 = 3;
int screen = 0;
float angle1 = 30.0f;
char start[] = "Start";
char Winner[] = "Winner";
char exitGame[] = "Exit";
char scoreText[] = "Score 1:";
char scoreText2[] = "Score 2:";
char highScore[] = "HighScore";
char instruction[] = " Control :";
char instruction2[] = "Red Car -> arrow key";
char instruction3[]= "Yellow car -> a,d ";
char Time[] = "Time Left:";
char Winner2[] = "Car 2";
char Winner1[] = "Car 1";
char Tie[] = "Tie";
char buffer[10];
int score = 0;
int score2 = 0;
int HighScore = 0;
int HighScoreGet = 0;
float objMoveRed = 0.5;
float objMoveCyan = 0.0;
float objMoveBomb = 0.5;
int timer = 30;
int counter=0;
int prob=0;
int prob2=0;
float whiteCount=0;
ofstream writef("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\ScoreHistory.txt", ofstream::app);
ofstream writef2("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\highScore.txt", ofstream::app | ofstream::trunc);
ifstream readf;//("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\highScore.txt");

void Sprint( float x, float y, char *st)
{
    int l,i;

    l=strlen( st );
    glColor3f(1.0,1.0,1.0);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
    }
}

void SprintScore(char ch[],int numtext,float x, float y)//counting the score
{
    int len;
    int k,i;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( x, y);
    for (i = 0; i <=numtext - 1; i++)
    {
        if ( i < len )
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
            k++;
        }
    }
}

void update(int value)
{
    //road white
    move4 -= speed;
    move3 -= speed;
    move2 -= speed;
    move1 -= speed;
    move5 -= speed;
    move6 -= speed;
    //whiteCount+=0.5;

    if(move4 < -.6)
        move4 = 2.2;
    else if(move3 < -1.3)
        move3 = 1.5;
    else if(move2 < -2)
        move2 = .8;
    else if(move1 < -2.7)
        move1 = .1;
    else if(move5 <= -2.0)
    {
        if(objMoveRed==-1 || objMoveRed==-1.5)
        {
            move5=0.0;
            objMoveRed=.5;

        }
        else
        {
            move5 = 0.0;
            objMoveRed-=0.5;
            objMoveCyan-=1.0;
        }
        if(objMoveCyan==-1 || objMoveCyan==-1.5)
        {
            move5=0.0;
            objMoveCyan=0.5;
        }
        else if(objMoveCyan==-.5)
        {
            move5=0.0;
            objMoveCyan=-0.5;
        }
        else
        {
            move5 = 0.0;
            objMoveCyan-=.5;
            objMoveRed-=.5;
        }
    }

    else if(move6 <= -1)
    {
        //cout<<whiteCount<<endl;

        if(objMoveBomb==-1 || objMoveBomb==-1.5)
        {
            move6=0.0;
            objMoveBomb=.5;

        }
        else if(objMoveBomb==.5)
        {
            move6=0.0;
            objMoveBomb=-0.5;
        }
        else if(objMoveBomb==-.5)
        {
            move6=0.0;
            objMoveBomb=0.0;
        }
        else
        {
            move6 = 0.0;
            objMoveBomb=-1;
            //objMoveCyan-=1.0;
        }

        /* if(whiteCount>=7.0 && whiteCount<=60.0)
         {
             move6 = .0;
             objMoveBomb=-1.0;
         }
         else if(whiteCount>=240.0 && whiteCount<=290.0)
         {
             move6 = .0;
             objMoveBomb=0.0;
         }
         else if(whiteCount>=540.0 && whiteCount<=590.0)
         {
             move6 = .0;
             objMoveBomb=0.5;
         }
         else if(whiteCount>=740.0 && whiteCount<=750.0)
         {
             move6 = .0;
             objMoveBomb=-0.5;
         }
         else if(whiteCount>=790.0)
         {
             whiteCount=0.0;
             //objMoveBomb=2.0;
             move6 = .0;
         }*/
    }

    angle1 += 2;
    if (angle1 > 130)
    {
        angle1 -= 130;
    }

    if(carPos==2 && angle1==130.0)
    {
        score+=5;
        sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\coin.wav",SND_ASYNC);
    }
    if(carPos2==2 && angle1==130.0)
    {
        score2+=5;
        sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\coin.wav",SND_ASYNC);
    }

    ///////////////ObjectRed///////////////////////
    if(move5 <= -1.97 && move5>=-1.98  && objMoveRed==0.5)
    {
        if(carPos2==3)
        {
            score2+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==3)
        {
            score+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
    }

    else if(move5 <= -1.97 && move5>=-1.98  && objMoveRed==0.0)
    {
        if(carPos2==2)
        {
            score2+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==2)
        {
            score+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
    }

    else if(move5 <= -1.97 && move5>=-1.98  && objMoveRed==-0.5)
    {
        if(carPos2==1)
        {
            score2+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==1)
        {
            score+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
    }

    else if(move5 <= -1.97 && move5>=-1.98  && objMoveRed==-1.0)
    {
        if(carPos2==0)
        {
            score2+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==0)
        {
            score+=10;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
    }


    /////////////////ObjectCyan//////////////////////
    if(move5 <= -1.97 && move5>=-1.98  && objMoveCyan==0.5)
    {
        if(carPos2==3)
        {
            score2+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==3)
        {
            score+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }

    }

    else if(move5 <= -1.97 && move5>=-1.98  && objMoveCyan==0.0)
    {
        if(carPos2==2)
        {
            score2+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==2)
        {
            score+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
    }

    else if(move5 <= -1.97 && move5>=-1.98  && objMoveCyan==-0.5)
    {
        if(carPos2==1)
        {
            score2+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==1)
        {
            score+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
    }

    else if(move5 <= -1.97 && move5>=-1.98  && objMoveCyan==-1.0)
    {
        if(carPos2==0)
        {
            score2+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
        else if(carPos==0)
        {
            score+=3;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bonus.wav",SND_ASYNC);
        }
    }


    // cout<<move6<<endl;
    /////////////////ObjectBomb//////////////////////
    if(move6 <= -0.9   && objMoveBomb==0.5)
    {
        if(carPos2==3)
        {
            carPos2=-2;
            prob2=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }

        }
        else if(carPos==3)
        {
            carPos=-2;
            prob=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }
        }
    }

    else if(move6 <= -0.9   && objMoveBomb==0.0)
    {
        if(carPos2==2)
        {
            carPos2=-2;
            prob2=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }
        }
        else if(carPos==2)
        {
            carPos=-2;
            prob=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }
        }

    }

    else if(move6 <= -0.9   && objMoveBomb==-0.5)
    {
        if(carPos2==1)
        {
            carPos2=-2;
            prob2=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }
        }
        else if(carPos==1)
        {
            carPos=-2;
            prob=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }
        }
    }

    else if(move6 <= -0.9  && objMoveBomb==-1.0)
    {
        if(carPos2==0)
        {
            carPos2=-2;
            prob2=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }
        }
        else if(carPos==0)
        {
            carPos=-2;
            prob=1;
            sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\bomb.wav",SND_ASYNC);
            if(carPos==-2 && carPos2==-2)
            {
                screen=0;
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
            }
        }
    }

    //cout<<move6<<" "<<carPos2<<" "<<move6<<endl;
    glutPostRedisplay();
    glutTimerFunc(timer,update,0);
}


void drawCar()
{
    glPushMatrix();

    if(carPos==-2)
        glTranslatef(-.64,0,0);

    if(carPos == 2)
    {
        if(carPos2==2)
        {

            if(prevcarPos2==3 )
            {
                carPos=1;
                carPos2=2;
            }
            if(prevcarPos==1)
            {
                carPos2=3;
                carPos=2;
            }
            else if(prevcarPos2==1)
            {
                carPos2=2;
                carPos=3;
            }
            else if(prevcarPos==3)
            {
                carPos=2;
                carPos2=1;
            }
        }
        else
            glTranslatef(.53,0,0);
    }

    else if(carPos == 3)
    {
        if(carPos2==3)
        {
            if(prevcarPos2==2)
            {
                carPos=0;
                carPos2=3;
            }
            else if(prevcarPos==2)
            {
                carPos=3;
                carPos2=0;
            }
        }
        else
            glTranslatef(1.05,0,0);
    }
    else if(carPos == 0)
    {
        if(carPos2==0)
        {
            if(prevcarPos2==1)
            {
                carPos=3;
                carPos2=0;
            }
            else if(prevcarPos==1)
            {
                carPos=0;
                carPos2=3;

            }
            else if(prevcarPos==2)
            {
                carPos=2;
                carPos2=1;

            }
        }
        else
            glTranslatef(-.39,0,0);
    }

    else if(carPos == 1)
    {
        if(carPos2==1)
        {
            cout<<prevcarPos<<" "<<prevcarPos2<<endl;
            if(prevcarPos==0)
            {
                carPos2=2;
                carPos=1;
            }
            else if(prevcarPos2==0)
            {
                carPos=2;
                carPos2=1;
            }
            if(prevcarPos2==2)
            {
                carPos=0;
                carPos2=1;
            }
        }
    }

    glTranslatef(-0.525f, -0.79f, 0.0f);
    glScalef(0.6f,0.5f,0.0f);
    glBegin(GL_POLYGON);
    glColor3f(214, 0, 0);
    glVertex2f(-0.05,-0.3);
    glVertex2f(0.05,-0.3);
    glVertex2f(0.09,-0.285);
    glVertex2f(0.1,-0.21);
    glVertex2f(0.1,-0.17);
    glVertex2f(0.09,-0.1);
    glVertex2f(0.09,0.1);
    glVertex2f(0.1,0.17);
    glVertex2f(0.1,0.21);
    glVertex2f(0.09,0.285);
    glVertex2f(0.05,0.3);
    glVertex2f(-0.05,0.3);
    glVertex2f(-0.09,0.285);
    glVertex2f(-0.1,0.21);
    glVertex2f(-0.1,0.17);
    glVertex2f(-0.09,0.1);
    glVertex2f(-0.09,-0.1);
    glVertex2f(-0.1,-0.17);
    glVertex2f(-0.1,-0.21);
    glVertex2f(-0.095,-0.285);
    glEnd();                        //car shape

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0.025,-0.22);
    glVertex2f(0.05,-0.17);
    glVertex2f(-0.05,-0.17);
    glVertex2f(-0.025,-0.22);
    glEnd();                       //back shape
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0.05,0.05);
    glVertex2f(0.07,0.15);
    glVertex2f(-0.07,0.15);
    glVertex2f(-0.05,0.05);
    glEnd();                        //front shape glass
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0.075,-0.18);
    glVertex2f(0.075,0.1);
    glVertex2f(0.053,0.01);
    glVertex2f(0.053,-0.13);
    glEnd();                          //right side glass
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(-0.075,-0.18);
    glVertex2f(-0.075,0.1);
    glVertex2f(-0.053,0.01);
    glVertex2f(-0.053,-0.13);
    glEnd();                          //left side glass

    glBegin(GL_POLYGON);
    glColor3f(210, 214, 0);
    glVertex2f(0.05,0.27);
    glVertex2f(0.08,0.26);
    glVertex2f(0.09,0.285);
    glVertex2f(0.05,0.3);
    glEnd();                  //head light right

    glBegin(GL_POLYGON);
    glColor3f(210, 214, 0);
    glVertex2f(-0.05,0.27);
    glVertex2f(-0.08,0.26);
    glVertex2f(-0.09,0.285);
    glVertex2f(-0.05,0.3);
    glEnd();             //head light left


}

void drawCar2()
{
    glPushMatrix();
    /*if(carPos==carPos2)
        screen=0;
    else
    {*/
    if(carPos2==-2)
        glTranslatef(90,0,0);
    if(carPos==-2)
    {
        if(carPos2==3)
            glTranslatef(1.03,0,0);
        else if(carPos2==2)
            glTranslatef(1.03,0,0);
        else if(carPos2==1)
            glTranslatef(1.03,0,0);
        else if(carPos2==0)
            glTranslatef(1.03,0,0);
    }

    if(carPos == 2)
    {
        if(carPos2==3)
            glTranslatef(-.89,0,0);
        else if(carPos2==1)
            glTranslatef(-2.5,0,0);
        else if(carPos2==2)
            glTranslatef(-1.7,0,0);
        else if(carPos2==0)
            glTranslatef(-3.25,0,0);

    }
    else if(carPos == 3)
    {
        if(carPos2==3)
            glTranslatef(-1.7,0,0);
        else if(carPos2==1)
            glTranslatef(-3.4,0,0);
        else if(carPos2==2)
            glTranslatef(-2.6,0,0);
        else if(carPos2==0)
            glTranslatef(-4.11,0,0);

    }

    else if(carPos == 3)
    {
        glTranslatef(1.05,0,0);
    }
    else if(carPos == 0)
    {
        if(carPos2==3)
            glTranslatef(.65,0,0);
        else if(carPos2==1)
            glTranslatef(-1.0,0,0);
        else if(carPos2==2)
            glTranslatef(-.2,0,0);
        else if(carPos2==0)
            glTranslatef(-2.5,0,0);
    }
    else if(carPos2 == 2)
    {
        glTranslatef(-0.83,0,0);
    }
    else if(carPos2==1)
    {
        glTranslatef(-1.70,0,0);
    }
    else if(carPos2==0)
    {
        glTranslatef(-2.30,0,0);
    }
    // }
    glTranslatef(1.7,0,0);
    glScalef(1.0f,1.0f,0.0f);
    glBegin(GL_POLYGON);
    glColor3f(214, 214, 0);
    glVertex2f(-0.05,-0.3);
    glVertex2f(0.05,-0.3);
    glVertex2f(0.09,-0.285);
    glVertex2f(0.1,-0.21);
    glVertex2f(0.1,-0.17);
    glVertex2f(0.09,-0.1);
    glVertex2f(0.09,0.1);
    glVertex2f(0.1,0.17);
    glVertex2f(0.1,0.21);
    glVertex2f(0.09,0.285);
    glVertex2f(0.05,0.3);
    glVertex2f(-0.05,0.3);
    glVertex2f(-0.09,0.285);
    glVertex2f(-0.1,0.21);
    glVertex2f(-0.1,0.17);
    glVertex2f(-0.09,0.1);
    glVertex2f(-0.09,-0.1);
    glVertex2f(-0.1,-0.17);
    glVertex2f(-0.1,-0.21);
    glVertex2f(-0.095,-0.285);
    glEnd();                        //car shape

    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0.025,-0.22);
    glVertex2f(0.05,-0.17);
    glVertex2f(-0.05,-0.17);
    glVertex2f(-0.025,-0.22);
    glEnd();                       //back shape
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0.05,0.05);
    glVertex2f(0.07,0.15);
    glVertex2f(-0.07,0.15);
    glVertex2f(-0.05,0.05);
    glEnd();                        //front shape glass
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(0.075,-0.18);
    glVertex2f(0.075,0.1);
    glVertex2f(0.053,0.01);
    glVertex2f(0.053,-0.13);
    glEnd();                          //right side glass
    glBegin(GL_POLYGON);
    glColor3f(0,0,0);
    glVertex2f(-0.075,-0.18);
    glVertex2f(-0.075,0.1);
    glVertex2f(-0.053,0.01);
    glVertex2f(-0.053,-0.13);
    glEnd();                          //left side glass

    glBegin(GL_POLYGON);
    glColor3f(255, 255, 255);
    glVertex2f(0.05,0.27);
    glVertex2f(0.08,0.26);
    glVertex2f(0.09,0.285);
    glVertex2f(0.05,0.3);
    glEnd();                  //head light right

    glBegin(GL_POLYGON);
    glColor3f(255, 255, 255);
    glVertex2f(-0.05,0.27);
    glVertex2f(-0.08,0.26);
    glVertex2f(-0.09,0.285);
    glVertex2f(-0.05,0.3);
    glEnd();//head light left

    glPopMatrix();
    glPopMatrix();
}

void drawRoad()
{
    glPushMatrix();

    glColor3f(255,255,255);
    glBegin(GL_QUADS);
    glVertex2f(-1,-1);
    glVertex2f(-1,1);
    glVertex2f(1,1);
    glVertex2f(1,-1);
    glEnd();


    //Middle Black
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0,-1);
    glVertex2f(-1.0,1);
    glVertex2f(.70,1);
    glVertex2f(.70,-1);
    glEnd();


    //left yellow
    glColor3f(1.0,1.0,0);
    glPushMatrix();
    glTranslatef(0,move1,0);
    glBegin(GL_QUADS);
    glVertex2f(-.80,1.70);
    glVertex2f(-.80,1.10);
    glVertex2f(-.70,1.10);
    glVertex2f(-.70,1.70);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move2,0);
    glBegin(GL_QUADS);
    glVertex2f(-.80,1);
    glVertex2f(-.80,.40);
    glVertex2f(-.70,.40);
    glVertex2f(-.70,1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move3,0);
    glBegin(GL_QUADS);
    glVertex2f(-.80,.30);
    glVertex2f(-.80,-.3);
    glVertex2f(-.70,-.3);
    glVertex2f(-.70,.30);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move4,0);
    glBegin(GL_QUADS);
    glVertex2f(-.80,-.40);
    glVertex2f(-.80,-1);
    glVertex2f(-.70,-1);
    glVertex2f(-.70,-.40);
    glEnd();
    glPopMatrix();

    //middle yellow
    glColor3f(1.0,1.0,0);
    glPushMatrix();
    glTranslatef(0,move1,0);
    glBegin(GL_QUADS);
    glVertex2f(-.30,1.70);
    glVertex2f(-.30,1.10);
    glVertex2f(-.20,1.10);
    glVertex2f(-.20,1.70);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move2,0);
    glBegin(GL_QUADS);
    glVertex2f(-.30,1);
    glVertex2f(-.30,.40);
    glVertex2f(-.20,.40);
    glVertex2f(-.20,1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move3,0);
    glBegin(GL_QUADS);
    glVertex2f(-.30,.30);
    glVertex2f(-.30,-.3);
    glVertex2f(-.20,-.3);
    glVertex2f(-.20,.30);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move4,0);
    glBegin(GL_QUADS);
    glVertex2f(-.30,-.40);
    glVertex2f(-.30,-1);
    glVertex2f(-.20,-1);
    glVertex2f(-.20,-.40);
    glEnd();
    glPopMatrix();

    //Right yellow
    glColor3f(1.0,1.0,0);
    glPushMatrix();
    glTranslatef(0,move1,0);
    glBegin(GL_QUADS);
    glVertex2f(.30,1.70);
    glVertex2f(.30,1.10);
    glVertex2f(.20,1.10);
    glVertex2f(.20,1.70);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move2,0);
    glBegin(GL_QUADS);
    glVertex2f(.30,1);
    glVertex2f(.30,.40);
    glVertex2f(.20,.40);
    glVertex2f(.20,1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move3,0);
    glBegin(GL_QUADS);
    glVertex2f(.30,.30);
    glVertex2f(.30,-.3);
    glVertex2f(.20,-.3);
    glVertex2f(.20,.30);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,move4,0);
    glBegin(GL_QUADS);
    glVertex2f(.30,-.40);
    glVertex2f(.30,-1);
    glVertex2f(.20,-1);
    glVertex2f(.20,-.40);
    glEnd();
    glPopMatrix();

    glPopMatrix();

}
void drawRandomBonus()
{
    glPushMatrix();
    //golden coin Object +5
    glPushMatrix();
    glRotatef(angle1, 1.0, 0.0, 0.0);
    glTranslatef(0.05, .98, 0.0);
    glColor3f(1,0.843,0.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50 ;
        float r=0.1;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();

    //RedObject +10
    glPushMatrix();
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    glTranslatef(objMoveRed,move5,0);
    glBegin(GL_QUADS);
    glVertex2f(0.1,1.70);
    glVertex2f(0.1,1.50);
    glVertex2f(-0.1,1.50);
    glVertex2f(-0.1,1.70);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(.1,1.85);
    glVertex2f(.1,1.7);
    glVertex2f(.14,1.7);
    glVertex2f(.14,1.85);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-.1,1.85);
    glVertex2f(-.1,1.7);
    glVertex2f(-.14,1.7);
    glVertex2f(-.14,1.85);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(.1,1.5);
    glVertex2f(.1,1.35);
    glVertex2f(.14,1.35);
    glVertex2f(.14,1.5);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-.1,1.5);
    glVertex2f(-.1,1.35);
    glVertex2f(-.14,1.35);
    glVertex2f(-.14,1.5);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1,1.70);
    glVertex2f(0.1,1.50);
    glVertex2f(-0.1,1.50);
    glEnd();
    glPopMatrix();
    glPopMatrix();


    //CyanObject +3
    glPushMatrix();
    glPushMatrix();
    glColor3f(0.0,1.0,1.0);
    glTranslatef(objMoveCyan,move5,0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1,1.70);
    glVertex2f(0.0,1.40);
    glVertex2f(-0.1,1.70);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.0,1.40);
    glVertex2f(0.1,1.40);
    glVertex2f(0.1,1.37);
    glVertex2f(0.0,1.37);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.1,1.40);
    glVertex2f(0.12,1.40);
    glVertex2f(0.12,1.30);
    glVertex2f(0.1,1.30);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.0,1.40);
    glVertex2f(-0.1,1.40);
    glVertex2f(-0.1,1.37);
    glVertex2f(0.0,1.37);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.1,1.40);
    glVertex2f(-0.12,1.40);
    glVertex2f(-0.12,1.30);
    glVertex2f(-0.1,1.30);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();


    //Red Object Bomb kill
    glPushMatrix();
    glTranslatef(objMoveBomb,move6, 0.0);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.11,.30);
    glVertex2f(-.09,.35);
    glVertex2f(-0.07,.30);
    glVertex2f(-0.07,.30);
    glVertex2f(-.05,.35);
    glVertex2f(-0.03,.30);
    glVertex2f(-0.03,.30);
    glVertex2f(-.01,.35);
    glVertex2f(0.01,.30);
    glVertex2f(0.01,.30);
    glVertex2f(.03,.35);
    glVertex2f(0.05,.30);
    glVertex2f(0.05,.30);
    glVertex2f(.07,.35);
    glVertex2f(0.09,.30);

    glVertex2f(-0.11,.20);
    glVertex2f(-.09,.15);
    glVertex2f(-0.07,.20);
    glVertex2f(-0.07,.20);
    glVertex2f(-.05,.15);
    glVertex2f(-0.03,.20);
    glVertex2f(-0.03,.20);
    glVertex2f(-.01,.15);
    glVertex2f(0.01,.20);
    glVertex2f(0.01,.20);
    glVertex2f(.03,.15);
    glVertex2f(0.05,.20);
    glVertex2f(0.05,.20);
    glVertex2f(.07,.15);
    glVertex2f(0.09,.20);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.1,.30);
    glVertex2f(-0.12,.30);
    glVertex2f(-0.2,.25);
    glVertex2f(-0.12,.20);
    glVertex2f(0.1,.20);
    glVertex2f(0.18,.25);
    glEnd();
    /* glBegin(GL_POLYGON);
     for(int i=0; i<200; i++)
     {
         float pi=3.1416;
         float A=(i*2*pi)/50 ;
         float r=0.2;
         float x = r * cos(A);
         float y = r * sin(A);
         glVertex2f(x,y );
     }
     glEnd();*/

    glPopMatrix();
    glPopMatrix();

}

void drawMenu()
{

    glPushMatrix();

    glColor3f(.13, .65, .94);
    glBegin(GL_QUADS);
    glVertex2f(.32,.5);
    glVertex2f(-.6,.5);
    glVertex2f(-.6,-.5);
    glVertex2f(.32,-.5);
    glEnd();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0,0,255);
    glVertex2f(.1,.3);
    glVertex2f(-.4,.3);
    glVertex2f(-.4,.1);
    glVertex2f(.1,.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(255,0,0);
    glVertex2f(.1,-.03);
    glVertex2f(-.4,-.03);
    glVertex2f(-.4,-.23);
    glVertex2f(.1,-.23);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3f(0,0,255);
    glVertex2f(.18,-.25);
    glVertex2f(-.43,-.25);
    glVertex2f(-.43,-.43);
    glVertex2f(.18,-.43);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    Sprint(-.2,.18,start);

    Sprint(-.2,-.14,exitGame);

    Sprint(-.4,-.3,instruction);
    Sprint(-.4,-.36,instruction2);
    Sprint(-.4,-.42,instruction3);

}

void drawScore()
{
    glPushMatrix();
    glColor3f(0,0,255);
    glBegin(GL_QUADS);
    glVertex2f(.999,.97);
    glVertex2f(.70,.97);
    glVertex2f(.70,.3);
    glVertex2f(.999,.3);
    glEnd();
    glPopMatrix();


    Sprint(.72,.91,scoreText);
    itoa (score, buffer, 10);
    SprintScore(buffer, 6, .75,.85);

    Sprint(.72,.77,scoreText2);
    itoa (score2, buffer, 10);
    SprintScore(buffer, 6, .75,.71);

    Sprint(.72,.63,Winner);
    if(score>score2)
    {
        Sprint(.73,.57,Winner1);
        if(score>HighScore)
        {
            writef2.open("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\highScore.txt");
            if(writef2.is_open())
            {
                writef2<<score;
                writef2.close();
            }
            else
                cout<<"error";
            HighScore=score;
        }
    }
    else if(score2>score)
    {
        Sprint(.73,.57,Winner2);
        if(score2>HighScore)
        {
            writef2.open("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\highScore.txt");
            if(writef2.is_open())
            {
                writef2<<score2;
                writef2.close();
            }
            else
                cout<<"error";
            HighScore=score2;
        }
    }
    else
        Sprint(.75,.57,Tie);

    Sprint(.72,.49,highScore);
}

void specialkey(int key, int x, int y)
{
    if(prob!=1)
    {
        switch(key)
        {
        /*case GLUT_KEY_UP:
            speed += 0.02;
            break;

        case GLUT_KEY_DOWN:
            if(speed>=0.06)
                speed -= 0.02;
            else
                speed=0;
            break;*/

        case GLUT_KEY_LEFT:
            if(carPos != 0)
            {

                prevcarPos=carPos;
                cout<<prevcarPos<<endl;
                carPos--;
            }
            if(carPos==carPos2)
            {
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\carhorn.wav",SND_ASYNC);
                counter++;
                if(counter>1)
                {
                    if(writef.is_open())
                    {
                        sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\crash.wav",SND_SYNC);
                        writef<<"Car1 Score : "<<score<<"   "<<"Car2 Score : "<<score2<<endl;
                        writef.close();
                    }
                    counter=0;
                    screen=0;
                    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
                }
            }
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:
            if(carPos != 3)
            {
                prevcarPos=carPos;
                carPos++;
            }
            if(carPos==carPos2)
            {
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\carhorn.wav",SND_ASYNC);
                counter++;
                if(counter>1)
                {
                    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\crash.wav",SND_SYNC);
                    if(writef.is_open())
                    {
                        writef<<"Car1 Score : "<<score<<"   "<<"Car2 Score : "<<score2<<endl;
                        writef.close();
                    }
                    counter=0;
                    screen=0;
                    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
                }
            }
            glutPostRedisplay();
            break;

        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if(prob2!=1)
    {
        switch(key)
        {

        case 97:
            if(carPos2 != 0)
            {
                prevcarPos2=carPos2;
                carPos2--;
            }
            if(carPos==carPos2)
            {
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\carhorn.wav",SND_ASYNC);
                counter++;
                if(counter>1)
                {
                    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\crash.wav",SND_SYNC);
                    if(writef.is_open())
                    {
                        writef<<"Car1 Score : "<<score<<"   "<<"Car2 Score : "<<score2<<endl;
                        writef.close();
                    }
                    counter=0;
                    screen=0;
                    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
                }
            }
            glutPostRedisplay();
            break;

        case 100:
            if(carPos2 != 3)
            {
                prevcarPos2=carPos2;
                carPos2++;
            }
            if(carPos==carPos2)
            {
                sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\carhorn.wav",SND_ASYNC|SND_LOOP);
                counter++;
                if(counter>1)
                {
                    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\crash.wav",SND_SYNC);
                    if(writef.is_open())
                    {
                        writef<<"Car1 Score : "<<score<<"   "<<"Car2 Score : "<<score2<<endl;
                        writef.close();
                    }
                    counter=0;
                    screen=0;
                    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
                }
            }
            glutPostRedisplay();
            break;
        }
    }

    switch(key)
    {
    case 27:

        if(writef.is_open())
        {
            writef<<"Car1 Score : "<<score<<"   "<<"Car2 Score : "<<score2<<endl;
            writef.close();
        }

        Sprint(-.1,-.1,Winner1);
        //score=0;
        //score2=0;
        screen=0;
        sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
        break;
    }
}

void mouse(int button,int state,int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(screen==0)
        {
            if(x>=240 && x<=439 && y>=278 && y<=360)
            {
                carPos=1;
                carPos2=3;
                screen=1;
                score=0;
                score2=0;
                prevcarPos=0;
                prevcarPos2=3;
                prob=0;
                prob2=0;

            }
            else if(x>=240 && x<=439 && y>=347 && y<=492)
                exit(1);
        }


    }
}

void mouseMotion(int x, int y)
{
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    //cout<<x<<", "<<y<<endl;
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    if(screen==0)
    {
        readf.open("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\highScore.txt");
        if(!readf.fail())
        {
            readf>>HighScoreGet;

            HighScore=HighScoreGet;
            readf.close();
        }
        else
            cout<<"error";

        drawRoad();
        drawMenu();
        drawScore();
        itoa (HighScore, buffer, 10);
        SprintScore(buffer, 6, .75,.43);
        carPos=-1;
        carPos2=-1;
        //sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC);
    }
    else if(screen==1)
    {
        drawRoad();
        drawCar();
        drawCar2();
        drawScore();
        drawRandomBonus();
    }

    glutSwapBuffers();
}


int main (int argc, char** argv)
{
    sndPlaySound("E:\\Study_stuffs\\Rich_BSC\\LEARNING OpenGL\\CarRacing\\background.wav",SND_ASYNC|SND_LOOP);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow("Car Racing");
    glutDisplayFunc(display);
    glutSpecialFunc(specialkey);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMotion);

    glutMouseFunc(mouse);
    glutTimerFunc(25, update,0);
    glutMainLoop();

    system("pause");
    return 0;
}
