#include <GL/glut.h>
#include <fstream>
#include "math.h"

using namespace std;

int dir;
int d = 1;
int num = 7;
int key1 = 3;
int Score = 0;
int hightScore;
int Scale = 25;
int N = 50, M = 30;
int w = Scale * N;
int h = Scale * M;

char sScore[15];
char sHightScore[15];
float xm = 0.0;
float ym = 0.0;
bool down = false;

struct {
    int x;
    int y;
} s[100];

class Fruct {
public:
    int x, y;
    void New()
    {
        x = rand() % N;
        y = rand() % (M - 3);
    }
    void DrawFruct()
    {
        glColor3f(1.0, 0.9, 0.0);
        glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
    }
} m[2];

class Bomb {
public:
    int x, y;

    void New()
    {
        x = rand() % N;
        y = rand() % (M - 3);
    }
    void DrawBomb()
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for (float i = 0; i < 2 * 3.14; i += 3.14 / 4) {
            glVertex2f((x + 0.5) * Scale + (0.5) * Scale * (1.1) * sin(i),
                (y + 0.5) * Scale + (0.5) * Scale * (1.1) * cos(i));
        }
        glEnd();
    }
} u[10];

void draw_string(void* font, const char* string)
{
    while (*string)
        glutStrokeCharacter(font, *string++);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); // Start
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(705.0, 650.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 650.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 550.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(705.0, 550.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON); // Rules
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(705.0, 510.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 510.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 410.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(705.0, 410.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON); // Exit
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 230.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(540.0, 230.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(540.0, 140.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 140.0, 0.0);
    glEnd();

    glLineWidth(4.0f);
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(w / (2.38), h / (1.3), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "START");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(w / (2.38), h / (1.7), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "RULES");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(w / (2.229), h / (4.4), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "EXIT");
    glPopMatrix();

    glFinish();
    glutSwapBuffers();
}

void DrawExit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(750.0, 150.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 150.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(500.0, 90.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(750.0, 90.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 80.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(580.0, 80.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(580.0, 30.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(670.0, 30.0, 0.0);
    glEnd();

    glLineWidth(7.0f);
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(w / (6), h / (1.5), 0);
    glScalef(1.1f, 1.1f, 1.1f);
    draw_string(GLUT_STROKE_ROMAN, "Game over!");
    glPopMatrix();

    glLineWidth(2.5f);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(w / (2.4), h / 7, 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "Return to MENU");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w / (2.07), h / (15.3), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "EXIT");
    glPopMatrix();

    glLineWidth(3.5f);
    glColor3f(0.9, 0.3, 0.5);
    glPushMatrix();
    glTranslatef(w / (2.8), h / (2.1), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "Final score:");
    glPopMatrix();

    sprintf(sScore, "%9d", Score);
    glPushMatrix();
    glTranslatef(w / (2.8), h / (2.1), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, sScore);
    glPopMatrix();

    ifstream inFile("Snake.bin", ios_base::binary);
    while (inFile.peek() != EOF)
        inFile >> sHightScore;
    inFile.close();
    hightScore = atoi(sHightScore);
    if (Score > hightScore) {
        sprintf(sHightScore, "%9d", Score);
        ofstream outFile("Snake.bin", ios_base::binary);
        outFile << sScore;
        outFile.close();
    }
    glPushMatrix();
    glTranslatef(w / (2.8), h / (2.55), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "High score:");
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w / (1.6), h / (2.55), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, sHightScore);
    glPopMatrix();

    glFinish();
    glutSwapBuffers();
}

void DrawRules()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(710.0, 150.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(490.0, 150.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(490.0, 90.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(710.0, 90.0, 0.0);
    glEnd();

    glLineWidth(1.8f);
    glColor3f(0.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(w / 3, h / (1.2), 0);
    glScalef(0.5f, 0.5f, 0.5f);
    draw_string(GLUT_STROKE_ROMAN, "How to play:");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w / (3), h / (1.5), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "1.Eat fruit to score points:");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w / (3), h / (1.7), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "2.Do not eat bombs:");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w / (3), h / (2.0), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "3.Do not eat yourself.");
    glPopMatrix();
    glPushMatrix();
    glTranslatef(w / (3), h / (2.4), 0);
    glScalef(0.2f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "4.Do not leave the window border.");
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(w / (2.5), h / 7, 0);
    glScalef(0.19f, 0.2f, 0.2f);
    draw_string(GLUT_STROKE_ROMAN, "Return to MENU");
    glPopMatrix();

    glLineWidth(3.0f);
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(w / (2.7), h / (3.3), 0);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_string(GLUT_STROKE_ROMAN, "Good luck!");
    glPopMatrix();

    glColor3f(1.0, 0.9, 0.0);
    glRectf(780.0, 500.0, 805.0, 525.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (float i = 0; i < 2 * 3.14; i += 3.14 / 4) {
        glVertex2f(720.0 + (0.5) * Scale * (1.1) * sin(i),
            450.0 + (0.5) * Scale * (1.1) * cos(i));
    }
    glEnd();

    glFinish();
    glutSwapBuffers();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tick()
{
    // Movement of the snake's body:
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    // Movement of the snake's head:
    switch (dir) {
    case 0:
        s[0].y += 1;
        break;
    case 1:
        s[0].x -= 1;
        break;
    case 2:
        s[0].x += 1;
        break;
    case 3:
        s[0].y -= 1;
        break;
    }
    int h = 0;
    // The snake's length increases on eating a fruit:
    for (int i = 0; i < 5; i++)
        if ((s[0].x == m[i].x) && (s[0].y == m[i].y)) {
            num++;
            m[i].New();
            if (h != 11) {
                u[h].New();
                h++;
            }
            else {
                h = 0;
                u[h].New();
            }
            Score += 2;
        }

    // The snake's length decreases on eating a bomb:
    for (int i = 0; i < 10; i++)
        if ((s[0].x == u[i].x) && (s[0].y == u[i].y)) {
            if (num == 2)
                key1 = 2;
            if (num > 3)
                num = num - 2;
            else
                num = 2;
            u[i].New();
            if (Score > 0)
                Score--;
            if (Score < 0)
                Score = 0;
        }

    // Game ends on touching the boundary:
    if (s[0].x > N || s[0].x < 0 || s[0].y > (M - 3) || s[0].y < 0) {
        key1 = 2;
    }

    // The snake's length decreases if it eats its tail:
    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y) {
            num = 3;
            if (Score > 0)
                Score -= 3;
            if (Score < 0)
                Score = 0;
        }
}

void DrawSnake()
{
    glColor3f(0.0, 1.0, 0.0);
    for (int i = 0; i < num; i++) {
        glRectf(s[i].x * Scale, s[i].y * Scale, (s[i].x + 1) * Scale,
            (s[i].y + 1) * Scale);
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateGlutWindow()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Mode selection: single buffer and RGBA colors
    glutInitWindowSize(w, h);
    glutCreateWindow("Snake");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

void timer(int = 0)
{
    if (d == 2) {
        display();
    }
    Tick();

    glutTimerFunc(80, timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    CreateGlutWindow();
    glutDisplayFunc(display);
    glutTimerFunc(80, timer, 0);
    glutSpecialFunc(MyKeyboard);
    glutMouseFunc(MousePressed);
    glutMainLoop(); //  enter GLUT event processing loop
    return 0;
}
