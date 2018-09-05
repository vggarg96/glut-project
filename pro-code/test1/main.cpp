
#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>

#define FONT GLUT_BITMAP_HELVETICA_18
#define LINE_SEP 2
#define CHAR_W 7
#define CHAR_H 13
#define CARRIAGE_RETURN 13
static GLfloat color[4][3]= {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0}};
static GLint vertice[4][2]= {{100,250},{250,250},{250,100},{100,100}};
float width[4]= {5.0,4.0,3.0,2.0};
int n,cnt=0;
#define INF 99999
int graph[10][10];
int dist[10][10];


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


void emitString(char *s, int tx, int ty)
{
    int x,y;

    x = tx;
    y = ty;
    while( *s )
    {
        if( *s == CARRIAGE_RETURN )
        {
            x = tx;
            y += CHAR_H + LINE_SEP;
        }
        else
        {
            glRasterPos2i(x,y);
            glutBitmapCharacter(FONT,*s);
            x += CHAR_W;
        }
        ++s;
    }
}

void frontpage()
{
    float z=233/255.0;
    glClearColor(z,z,z,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glColor3f(241/255.0,104/255.0,78/255.0);
    emitString(" * * GRAPHICAL IMPLEMENTATION OF FLYOD ALGORITHM * *",75,460);
    emitString(" * * FOR SHORTEST PATH * *",160,435);
    emitString(" SUBMITTED BY: VAIBHAV GARG",140,150);
    emitString(" (1BG15CS113)",180,130);
    emitString(" UNDER THE GUIDANCE OF:SPURTHI G S & CHANDANA K M",140,100);
    emitString(" (PROFESSOR,DeptofCSE)",180,80);

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
        for(j=0; j<10*q; j++)
            for(k=0; k<q; k++);
        glFlush();
        //transform(round1(x),round1(y),tx,ty);
    }
}


int floyd (int x,int y)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = graph[i][j];
    //for(j=0;j<n;j++)
    if(graph[x][y]!=999)
    {
        glColor3fv(color[x]);
        LineWithDDA(vertice[x][0],vertice[x][1],vertice[y][0],vertice[y][1],1000);
        return dist[x][y];
    }
    for (i = 0; i < n; i++)
    {
        if (graph[x][i]!= 999 && graph[i][y]==999)
        {
            printf("%d\t%d\t%d",x,i,y);
            cnt+=graph[x][i];
            glColor3fv(color[x]);
            LineWithDDA(vertice[x][0],vertice[x][1],vertice[i][0],vertice[i][1],1000);
            x=i;
            floyd(x,y);
        }
        else if(graph[x][i]!= 999 && graph[i][y]!=999)
        {
            cnt+=graph[x][i];
            printf("%d\t%d\t%d",x,i,y);
            glColor3fv(color[x]);
            LineWithDDA(vertice[x][0],vertice[x][1],vertice[i][0],vertice[i][1],1000);
            glColor3fv(color[i]);
            cnt+=graph[x][y];
            LineWithDDA(vertice[i][0],vertice[i][1],vertice[y][0],vertice[y][1],1000);
        }

    }
    return cnt;
}

void printall()
{
    int i, j;
    glPointSize(5.0);
    glColor3d(0.64,0.164,0.164);
    glBegin(GL_POINTS);
    glVertex2iv(vertice[0]);
    glVertex2iv(vertice[1]);
    glVertex2iv(vertice[2]);
    glVertex2iv(vertice[3]);
    glEnd();

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
    setpoint(x,y);
    emitString("start",vertice[x][0]-5,vertice[x][1]-15);
    emitString("end",vertice[y][0]-5,vertice[y][1]+15);
    cnt=0;
    z=floyd(x,y);
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
    case 2:
        printf("enter in two condition\n");
        print2vertex();
        break;
    case 1:
        printall();
        break;
    case 3: exit(0);
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
    floydWarshall();
    glutInit(&argc, argv);		/* initialize GLUT system */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1300,650);		/* width=500pixels height=420pixels */
    glutCreateWindow("FLOYDS");	/* create window */

    /* set background to black */
    glutDisplayFunc(frontpage);
    myinit();
    glutCreateMenu(display);
    glutAddMenuEntry("print all vertex",1);
    glutAddMenuEntry("print 2 vertex",2);
    glutAddMenuEntry("exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);                                /* set window's display callback */
    glutMainLoop();
    return 0;
}
