
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#define FONT GLUT_BITMAP_HELVETICA_18
#define LINE_SEP 2
#define CHAR_W 7
#define CHAR_H 13
#define CARRIAGE_RETURN 13
static GLfloat color[4][3]= {{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0}};
static GLint vertice[25][2];

int n,cnt=0,w;
int graph[10][10];
int dist[10][10];
void myinit();

void setvertex(){
    int k,j,x;
    for(j=0; j<n; j++)
        for(k=0; k<2; k++){
            x=rand()%350;
            while(x<50)
                x=rand()%350;
            vertice[j][k]=x;
        }
}
void delay(int q)
{
    int k,j;
    for(j=0; j<10*q; j++)
        for(k=0; k<q; k++);
}

void printSolution(int dist[10][10],int n)
{
    int i,j;
    printf ("Following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}



void floydWarshall ()
{
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = graph[i][j];
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }

    }
    printSolution(dist,n);
}



/* emitString(s, x, y) -- displays string s at location x,y  */

void emitString1(char *string, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}
void emitString(char *string, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
void emitString2(char *string, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
    }
}
void emitString3(char *string, float x, float y)
{
    char *c;
    glRasterPos2f(x, y);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

void frontpage()
{
    float z=233/255.0;
    glClearColor(z,z,z,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glColor3f(241/255.0,104/255.0,78/255.0);
    emitString1(" B.N.M  INSTITUTE OF TECHNOLOGY",175,450);
    glColor3f(255/255.0, 121/255.0,0/255.0);
    emitString(" DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",153,400);
    glColor3f(255/255.0, 191/255.0,0/255.0);
    emitString(" COMPUTER GRAPHICS AND VISUALIZATION (15CSL68)",158,350);
    glColor3f(52/255.0, 52/255.0,52/255.0);
    emitString(" A MINI PROJECT ON",220,300);
    emitString(" FLOYD WARSHALL ALGORITHM ",200,270);
    glColor3f(128/255.0, 0/255.0,32/255.0);
    emitString3(" BY:",30,150);
    emitString3(" NAME: VAIBHAV GARG",50,140);
    emitString3(" USN: 1BG15CS113",50,130);
    emitString3(" UNDER THE GUIDANCE OF:SPURTHI G S & CHANDANA K M",50,100);
    emitString3(" (PROFESSOR,DeptofCSE)",50,80);
    glColor3f(34/255.0, 139/255.0,34/255.0);
    emitString2(" ALGORITHM",300,210);
    emitString2(" FLOYD WARSHALL ALGORITHM",315,195);
    emitString2(" 1. START",340,180);
    emitString2(" 2. ENTER THE NO OF CITIES AND ADJANCEY MATRIX",340,165);
    emitString2(" 3. CHECK FOR PATH BETWEEN THE 2 CITIES ",340,150);
    emitString2(" 4. IF ITS SHORTEST THEN CONTINUE",340,135);
    emitString2(" 5. ELSE  UPDATE THE PATH BETWEEN THOS 2 CITIES",340,120);
    emitString2(" 6. PRINT THE DISTANCE MATRIX",340,105);
    emitString2(" 7. STOP",340,90);
    emitString2(" PRESS 'a' TO PRINT THE GIVEN PATHS",50,50);
    emitString2(" PRESS 'b' TO PRINT THE SHORTEST PATH AMONG ALL PAIRS",50,30);
    emitString2(" PRESS 'c' TO PRINT THE SHORTEST PATH AMONG 2 CITIES",250,50);
    emitString2(" PRESS 'e' TO EXIT",250,30);
    glColor3f(1.0,0.0,0.0);
    glRecti(35,45,45,55);
    glRecti(35,25,45,35);
    glRecti(235,45,245,55);
    glRecti(235,25,245,35);
    glFlush();
}


void setpoint(GLint x, GLint y)
{
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void LineWithDDA(int x0, int y0, int x1, int y1,int q)
{
    int j,k;
    int dy = y1 - y0;
    int dx = x1 - x0;
    int steps, i;
    float xinc, yinc, x = x0, y =  y0;
    if (abs(dx)>abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    xinc = (float)dx / (float)steps;
    yinc = (float)dy / (float)steps;
    setpoint(x,y);
    //transform(round1(x),round1(y),tx,ty);
    for (i = 0; i<steps; i++)
    {
        x += xinc;
        y += yinc;
        setpoint(x,y);
        delay(q);
        glFlush();
     }
}

void setcity(int x,int y)
{
    glColor3f(0.6,0.15,0.48);
    glBegin(GL_POLYGON);
    glVertex2i(x,y);
    glVertex2i(x+10,y);
    glVertex2i(x+10,y+10);
    glVertex2i(x,y+10);
    glEnd();
}
int floyd (int x,int y,int q)
{
    int i, j;
    //for(j=0;j<n;j++)
    if(graph[x][y]!=999)
    {
        glColor3fv(color[x]);
        LineWithDDA(vertice[x][0],vertice[x][1],vertice[y][0],vertice[y][1],q);
        return graph[x][y];
    }
    char b[30];
    for (i = 0; i < n; i++)
    {
        if (graph[x][i]!= 999 && graph[i][y]==999)
        {
            cnt+=graph[x][i];
            sprintf(b,"City %d",x);
            emitString(b,vertice[x][0]+20,vertice[x][1]);
            setcity(vertice[x][0],vertice[x][1]);
            sprintf(b,"City %d",i);
            emitString(b,vertice[i][0]+20,vertice[i][1]);
            setcity(vertice[i][0],vertice[i][1]);
            glColor3fv(color[x]);
            LineWithDDA(vertice[x][0],vertice[x][1],vertice[i][0],vertice[i][1],q);
            x=i;
            floyd(x,y,q);
        }
        else if(graph[x][i]!= 999 && graph[i][y]!=999)
        {
            cnt+=graph[x][i];
            sprintf(b,"City %d",x);
            emitString(b,vertice[x][0]+20,vertice[x][1]);
            setcity(vertice[x][0],vertice[x][1]);
            sprintf(b,"City %d",i);
            emitString(b,vertice[i][0]+20,vertice[i][1]);
            setcity(vertice[i][0],vertice[i][1]);
            glColor3fv(color[x]);
            LineWithDDA(vertice[x][0],vertice[x][1],vertice[i][0],vertice[i][1],q);
            cnt+=graph[x][y];
            sprintf(b,"City %d",i);
            emitString(b,vertice[i][0]+20,vertice[i][1]);
            setcity(vertice[i][0],vertice[i][1]);
            sprintf(b,"City %d",y);
            emitString(b,vertice[y][0]+20,vertice[y][1]);
            setcity(vertice[y][0],vertice[y][1]);
            glColor3fv(color[i]);
            LineWithDDA(vertice[i][0],vertice[i][1],vertice[y][0],vertice[y][1],q);
        }

    }
    return cnt;
}

void printAllShortestPath()
{
    int i, j;
    glPointSize(5.0);
    glColor3d(0.64,0.164,0.164);
    for (i = 0; i < n; i++){
    setcity(vertice[i][0],vertice[i][1]);
    char b[30];
    glColor3f(0.2,0.5,0.1);
    sprintf(b,"City %d",i);
    emitString(b,vertice[i][0]+20,vertice[i][1]);
    }
     for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            char b[30];
            glColor3f(0.2,0.5,0.1);
            sprintf(b,"path from %d to %d cost %d\n",i,j,dist[i][j]);
            emitString(b,350,400-i*60-j*15);
            glLineWidth(4.0);
            glColor3fv(color[i]);
            LineWithDDA(vertice[i][0],vertice[i][1],vertice[j][0],vertice[j][1],100);
        }
    }
    delay(10000);
    glFlush();
    glutPostRedisplay();


}
void print2vertex()		/* function called whenever redisplay needed */
{
    int z,x,y;
    printf("Enter the two cities:\n");
    scanf("%d%d",&x,&y);
    printf("\nROUTE EXIST BETWEEN %d and %d\n",x,y);
    emitString("start",vertice[x][0]-5,vertice[x][1]-15);
    emitString("end",vertice[y][0]-5,vertice[y][1]+15);
    cnt=0;
    z=floyd(x,y,1000);
    char c[30];
   if(z<dist[x][y]){
        printf("cost of jounney=%d\n",z);
        sprintf(c,"cost of jounney=%d\n",z);
   }
    else{
        printf("cost of jounney=%d\n",dist[x][y]);
        sprintf(c,"cost of jounney=%d\n",dist[x][y]);
    }
    emitString(c,200,400);

    glEnd();
    glFlush();
    delay(5000);
    glutPostRedisplay();
}


void printGivenPath(){
    int i,j;
    for (i = 0; i < n; i++){
    setcity(vertice[i][0],vertice[i][1]);
    char b[30];
    glColor3f(1.0,1.0,1.0);
    sprintf(b,"City %d",i);
    emitString(b,vertice[i][0]+20,vertice[i][1]);
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(graph[i][j]!=999){
                glLineWidth(4.0);
                glBegin(GL_LINES);
                glVertex2i(vertice[i][0],vertice[i][1]);
                glVertex2i(vertice[j][0],vertice[j][1]);
                glEnd();
            }
        }
    }
    glFlush();
    delay(10000);
        glutPostRedisplay();
}
void exitscreen(){
    glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    emitString("THANK YOU",250,300);
    glFlush();

    delay(10000);
}
void keyfunc(unsigned char key, int x, int y)
{
    glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	switch (key)
		{
        case 'a': printGivenPath();
                break;
        case 'b': printAllShortestPath();
            break;
            case 'c':print2vertex();
                break;
            case 'e': exitscreen();
                exit(0);
		}
}
void mymouse(int btn,int state,int x,int y){
    glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && (x>=91 && x<=116 && y<=588 && y>=576))
        printGivenPath();
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && (x>=91 && x<=116 && y<=614 && y>=603))
        printAllShortestPath();
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && (x>=609 && x<=635 && y<=588 && y>=576))
        print2vertex();
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && (x>=609 && x<=635 && y<=614 && y>=603)){
        exitscreen();
        exit(0);
    }
    //else if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
      //  printf("%d and %d\n",x,y);
}

void myinit()
{
    /* set current color to white */
    glLoadIdentity();			/* start with the identity matrix */
    gluOrtho2D(0,500,0,500);		/* how object is mapped to window */
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
//	char c;
//	while(1){
    int i,j;
    printf("enter the no of cities\n");
    scanf("%d",&n);
    printf("enter the distance matrix of the cities\n");
    for(i=0; i<n; i++)
        for(j=0; j<n; j++){
            scanf("%d",&graph[i][j]);
            if(graph[i][j]==0)
                graph[i][j]=999;
        }
    setvertex();
    for(i=0; i<n; i++)
    printf("%d   %d\n",vertice[i][0],vertice[i][1]);
    floydWarshall();
    glutInit(&argc, argv);		/* initialize GLUT system */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1300,650);		/* width=500pixels height=420pixels */
    glutCreateWindow("FLOYDS");	/* create window */
    glutDisplayFunc(frontpage);
    glutMouseFunc(mymouse);
    myinit();
    glutKeyboardFunc(keyfunc);
    glutMainLoop();
    return 0;
}
