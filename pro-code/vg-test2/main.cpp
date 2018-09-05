
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#define FONT GLUT_BITMAP_HELVETICA_18
#define LINE_SEP 2
#define CHAR_W 7
#define CHAR_H 13
#define CARRIAGE_RETURN 13
static GLfloat color[4][3]= {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0}};
static GLint vertice[25][2];
float width[4]= {5.0,4.0,3.0,2.0};
int n,cnt=0,w;
#define INF 99999
int graph[10][10];
int dist[10][10];
void myinit();

void setvertex(){
    int k,j;
    for(j=1; j<=n; j++)
        for(k=0; k<2; k++)
            vertice[j][k]=rand()%500;
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
        //transform(round1(x),round1(y),tx,ty);
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
    for (i =0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = graph[i][j];
    //for(j=0;j<n;j++)
    if(graph[x][y]!=999)
    {
        glColor3fv(color[x]);
        LineWithDDA(vertice[x][0],vertice[x][1],vertice[y][0],vertice[y][1],q);
        return dist[x][y];
    }
    for (i = 0; i < n; i++)
    {
        if (graph[x][i]!= 999 && graph[i][y]==999)
        {
            cnt+=graph[x][i];
            setcity(vertice[x][0],vertice[x][1]);
            setcity(vertice[i][0],vertice[i][1]);
            glColor3fv(color[x]);
            LineWithDDA(vertice[x][0],vertice[x][1],vertice[i][0],vertice[i][1],q);
            x=i;
            floyd(x,y,q);
        }
        else if(graph[x][i]!= 999 && graph[i][y]!=999)
        {
            cnt+=graph[x][i];
            setcity(vertice[x][0],vertice[x][1]);
            setcity(vertice[i][0],vertice[i][1]);
            glColor3fv(color[x]);
            LineWithDDA(vertice[x][0],vertice[x][1],vertice[i][0],vertice[i][1],q);
            cnt+=graph[x][y];
            setcity(vertice[i][0],vertice[i][1]);
            setcity(vertice[y][0],vertice[y][1]);
            glColor3fv(color[i]);
            LineWithDDA(vertice[i][0],vertice[i][1],vertice[y][0],vertice[y][1],q);
        }

    }
    return cnt;
}

void printall()
{
    int i, j;
    glPointSize(5.0);
    glColor3d(0.64,0.164,0.164);
    setcity(vertice[1][0],vertice[1][1]);
    setcity(vertice[2][0],vertice[2][1]);
    setcity(vertice[3][0],vertice[3][1]);
    setcity(vertice[0][0],vertice[0][1]);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("path from %d to %d cost %d\n",i,j,dist[i][j]);
            glLineWidth(width[i]);
            glColor3fv(color[i]);
            LineWithDDA(vertice[i][0],vertice[i][1],vertice[j][0],vertice[j][1],100);
        }
    }
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
    if(z<dist[x][y])
        printf("cost of jounney=%d\n",z);
    else
        printf("cost of jounney=%d\n",dist[x][y]);
    emitString("route",(vertice[x][0]+vertice[y][0])/2+20,(vertice[x][1]+vertice[y][1])/2);
    glEnd();
    glFlush();
    glutPostRedisplay();
}

void display(int ch)
{
    glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT);		/* clear the display */
    //printf("enter choice\n");
    //scanf("%d",&ch);
    printf("selected choice =%d\n",ch);
    switch(ch)
    {

    case 1:
        printall();
        delay(100);
        break;
    case 2:
        printf("enter in two condition\n");
        print2vertex();
        delay(100);
        break;
    case 3:
        emitString(" THANK YOU",153,400);
        delay(10000);
        exit(0);
        break;
    }
}

void keyfunc(unsigned char key, int x, int y)
{
	switch (key)
		{
		//case 13: display();
			//break;
        case 48: printall();
		}

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
        for(j=0; j<n; j++)
            scanf("%d",&graph[i][j]);
    setvertex();
    for(i=0; i<n; i++)
            printf("%d   %d\n",vertice[i][0],vertice[i][1]);
    floydWarshall();
    glutInit(&argc, argv);		/* initialize GLUT system */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1300,650);		/* width=500pixels height=420pixels */
    w=glutCreateWindow("FLOYDS");	/* create window */

    /* set background to black */
    glutDisplayFunc(frontpage);
    myinit();
    glutKeyboardFunc(keyfunc);
    //glutCreateMenu(display);

    //glutAddMenuEntry("print all vertex",1);
    //glutAddMenuEntry("print 2 vertex",2);
    //glutAddMenuEntry("exit",3);
    //glutAttachMenu(GLUT_RIGHT_BUTTON);                                /* set window's display callback */
    glutMainLoop();
    return 0;
}
