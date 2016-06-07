#include<stdlib.h>
#include <glut.h>
#include <windows.h>
#include <stdio.h>
//#include<unistd.h>
#include<process.h>
#include <math.h>
#include"cover.h"
void display (void);
//GLuint texture[8];

double angle = 0.0;
int zoom=0;
static GLfloat thetaearth[]={4.0,0.0,0.0};
static GLfloat thetaEarth2[]={0.0,0.0,0.0};
static GLfloat theta[]={4.0,0.0,0.0};
static GLint axis=2;


//this will hold the information of all the vertices x,y,z
typedef struct
{
   
    int X;
   //x position of the current vertex
    int Y;
   
    int Z;
   

   //u(x) exture cooridante of the current vertex 
    double U;
   
    double V;//to convert the angles in degrees into radiance
}VERTICES;

const double PI = 3.1415926535897;
//determines the vertices how far apart they are
const int space = 10;
//this will hold out the total number of vertices
const int VertexCount = (90 / space) * (360 / space) * 4;
//this shows ho many vertices we are going to use
VERTICES VERTEX[VertexCount];

GLuint LoadTextureRAW( const char * filename );

void DisplaySphere (double R, GLuint texture)
{
//this variable will control which vertex we are working with   
    int b;
 
    glScalef (0.0125 * R, 0.0125 * R, 0.0125 * R);   
    glRotatef (90, 1, 0, 0);//we are rotating it because if you run it it is side ways
    glBindTexture (GL_TEXTURE_2D, texture);
    glBegin (GL_TRIANGLE_STRIP);//we are using this because it is fast
   
    for ( b = 0; b <= VertexCount; b++)
    {
        glTexCoord2f (VERTEX[b].U, VERTEX[b].V);
   //assigning the texture coordinates to the current vertex    
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);
   
    }
   

   
    for ( b = 0; b <= VertexCount; b++)
    {
       
        glTexCoord2f (VERTEX[b].U, -VERTEX[b].V);
       
        glVertex3f (VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
   
    }
   
    glEnd();
}

void CreateSphere (double R, double H, double K, double Z)
{
   
    int n;//set n to zero to start off with 1st vertex
   
    double a;
   
    double b;
    n = 0;
   

   //assign our b loop to go through 90 degree in intervals of our variable
    for( b = 0; b <= 90 - space; b+=space){
       
    for( a = 0; a <= 360 - space; a+=space){
           

           
    VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
           //calculating x value
    VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
           
    VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
           
    VERTEX[n].V = (2 * b) / 360;
           
    VERTEX[n].U = (a) / 360;
           
    n++;
           

           //calculating the texture coordinates and have used 2*b as a texture as it will be twice as wide as its height
    VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
           
    VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
           
    VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
           
    VERTEX[n].V = (2 * (b + space)) / 360;
           
    VERTEX[n].U = (a) / 360;
           
    n++;
           

           
    VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
           
    VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
           
    VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
           
    VERTEX[n].V = (2 * b) / 360;
           
    VERTEX[n].U = (a + space) / 360;
           
    n++;
           

           //we are adding space variable to both a and b
    VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) /180 * PI) - H;
           
    VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) /180 * PI) + K;
           
    VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
           
    VERTEX[n].V = (2 * (b + space)) / 360;
           
    VERTEX[n].U = (a + space) / 360;
           
    n++;
           

           
    }
   
}
}
void sphere2(void)//moon
{
	glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
	glPushMatrix();
	    glColor3d(1.0,1.0,1.0);
		glTranslated(0.0,0.0,12);
		//light();
		glutSolidSphere(0.5,50,50);
	glPopMatrix();
}	
GLfloat view[]={0.0,0.0,80.0};

GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //The following code will read in our RAW file
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

glGenTextures( 1, &texture ); //generate the texturewith the loaded data
glBindTexture( GL_TEXTURE_2D, texture ); //bind thetexture to it’s array
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE ); //set texture environment parameters



//And if you go and use extensions, you can use Anisotropicfiltering textures which are of an
//even better quality, but this will do for now.
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR );

//Here we are setting the parameter to repeat the textureinstead of clamping the texture
//to the edge of our shape.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );   
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );

    //Generate the texture with mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_BGR_EXT, GL_UNSIGNED_BYTE, data );
    free( data ); //free the texture
    return texture; //return whether it was successfull
}

void FreeTexture( GLuint texture )
{
    glDeleteTextures( 1, &texture );
}

void square (void) {
    //bind our texture to our shape
    glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-3.0,-3.0); //with our vertices we have to assign a texcoord
    glTexCoord2d(1.0,0.0); glVertex2d(+3.0,-3.0); //so thatour texture has some points to draw to
    glTexCoord2d(1.0,1.0); glVertex2d(+3.0,+3.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-3.0,+3.0);
    glEnd();
}
void init (void)
{
   
    glEnable(GL_DEPTH_TEST);
   
    glEnable( GL_TEXTURE_2D );
   
    glDepthFunc(GL_LEQUAL);
   
    glCullFace(GL_BACK);
   
    glFrontFace(GL_CCW);
   
    glEnable(GL_CULL_FACE);
   
    texture[0] = LoadTexture( "earth.bmp", 2048, 1024 );
 	CreateSphere(100,0,0,0);
	 
}
GLfloat ang=0.25;
void spinsphere()
{
	theta[axis]+=0.05;
	thetaearth[2]+=ang;
	if(theta[axis]>360.0) theta[axis]=-360;
	glutPostRedisplay();
}

void reshape (int w, int h)
{
   
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
   
    glMatrixMode (GL_PROJECTION);
   
    glLoadIdentity ();
	glLoadIdentity();
	if(w<=h)
		glOrtho(-10.0,10.0,-10.0 * (GLfloat)h/(GLfloat)w, 10.0 *(GLfloat)h/(GLfloat)w,-50.0,50.0);
	else
		glOrtho(-10.0 * (GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-50.0,50.0);

   
    //gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
   
    glMatrixMode (GL_MODELVIEW);
}

GLint Asia, win;
static int cs;
void contient(int value);
void createmenu()
{
	cs=glutCreateMenu(contient);
	glutAddMenuEntry("Asia", 1);
	glutAddMenuEntry("Africa", 2);
	glutAddMenuEntry("Europe", 3);
	glutAddMenuEntry("North America", 4);
	glutAddMenuEntry("South America", 5);
	glutAddMenuEntry("Australia", 6);
	glutAddMenuEntry("Antartica", 7);

	 glutAttachMenu(GLUT_RIGHT_BUTTON); //for right mouse click
	// glutAttachMenu(GLUT_LEFT_BUTTON);  //for left mouse click
}
void init1 (void)
{
   glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture[1] );
	square();
    texture[1] = LoadTexture( "Asia.bmp", 806, 726 );
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0,499.0,0.0,499.0);
}
void init2 (void)
{
   glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture[2] );
	square();
    texture[0] = LoadTexture( "Africa.bmp", 1300, 1292 );
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0,499.0,0.0,499.0);
}
void init3 (void)
{
   glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture[3] );
	square();
    texture[0] = LoadTexture( "Europe.bmp", 780, 706 );
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0,499.0,0.0,499.0);
}
void init4 (void)
{
   glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture[4] );
	square();
    texture[0] = LoadTexture( "NAmerica.bmp", 2300, 2134 );
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0,499.0,0.0,499.0);
}
void init5 (void)
{
   glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture[5] );
	square();
    texture[0] = LoadTexture( "SAmerica.bmp", 736, 955 );
    glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0,499.0,0.0,499.0);
}
void init6 (void)
{
   glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture[6] );
	square();
    texture[0] = LoadTexture( "Australia.bmp", 1024, 715 );
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0,499.0,0.0,499.0);
}
void init7 (void)
{
   glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture[7] );
	square();
    texture[0] = LoadTexture( "Antarctica.bmp", 720,628 );
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0,499.0,0.0,499.0);
}

void display1(void)
{	
    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glEnable( GL_TEXTURE_2D );
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    square();
    glutSwapBuffers();
}

void reshape1 (int w, int h) 
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}



void contient(int value)
{
	ang=0;
	if(value == 1)
	{	
		zoom=1;
		thetaEarth2[0]=4;
		thetaEarth2[1]=thetaearth[1];
		thetaEarth2[2]=thetaearth[2];
		for(float i=thetaearth[2];i!=100;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[2]=i;
			display();
		}
		for(float i=thetaearth[1];i!=40;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[1]=i;
			display();
		}

		for(float i=1;i<=3;i+=0.01)
		{	
			zoom=i;
			display();
		}
		glutInitWindowSize(500,500);
		glutInitWindowPosition(0,0);
		Asia = glutCreateWindow("ASIA");
		init1();
		
		glutDisplayFunc(display1);
		glutReshapeFunc(reshape1);
	}
	if(value == 2)
	{
			zoom=1;
		thetaEarth2[0]=4;
		thetaEarth2[1]=thetaearth[1];
		thetaEarth2[2]=thetaearth[2];
		for(float i=thetaearth[2];i!=160;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[2]=i;
			display();
		}
		for(float i=thetaearth[1];i!=350;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[1]=i;
			display();
		}

		for(float i=1;i<=3;i+=0.01)
		{	
			zoom=i;
			display();
		}
		glutInitWindowSize(500,500);
		glutInitWindowPosition(0,0);
		Asia = glutCreateWindow("AFRICA");
		init2();
		glutDisplayFunc(display1);
		glutReshapeFunc(reshape1);
	}
	if(value == 3)
	{
		zoom=1;
		thetaEarth2[0]=4;
		thetaEarth2[1]=thetaearth[1];
		thetaEarth2[2]=thetaearth[2];
		for(float i=thetaearth[2];i!=160;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[2]=i;
			display();
		}
		for(float i=thetaearth[1];i!=40;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[1]=i;
			display();
		}

		for(float i=1;i<=3;i+=0.01)
		{	
			zoom=i;
			display();
		}
		glutInitWindowSize(500,500);
		glutInitWindowPosition(0,0);
		Asia = glutCreateWindow("EUROPE");
		init3();
		glutDisplayFunc(display1);
		glutReshapeFunc(reshape1);
	}
	if(value == 4)
	{
		zoom=1;
		thetaEarth2[0]=4;
		thetaEarth2[1]=thetaearth[1];
		thetaEarth2[2]=thetaearth[2];
		for(float i=thetaearth[2];i!=290;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[2]=i;
			display();
		}
		for(float i=thetaearth[1];i!=40;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[1]=i;
			display();
		}

		for(float i=1;i<=3;i+=0.01)
		{	
			zoom=i;
			display();
		}
		glutInitWindowSize(600,600);
		glutInitWindowPosition(0,0);
		Asia = glutCreateWindow("NORTH AMERICA");
		init4();
		glutDisplayFunc(display1);
		glutReshapeFunc(reshape1);
	}
	if(value == 5)
	{
		zoom=1;
		thetaEarth2[0]=4;
		thetaEarth2[1]=thetaearth[1];
		thetaEarth2[2]=thetaearth[2];
		for(float i=thetaearth[2];i!=250;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[2]=i;
			display();
		}
		for(float i=thetaearth[1];i!=350;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[1]=i;
			display();
		}

		for(float i=1;i<=3;i+=0.01)
		{	
			zoom=i;
			display();
		}
		glutInitWindowSize(500,500);
		glutInitWindowPosition(0,0);
		Asia = glutCreateWindow("SOUTH AMERICA");
		init5();
		glutDisplayFunc(display1);
		glutReshapeFunc(reshape1);
	}
	if(value == 6)
	{
		zoom=1;
		thetaEarth2[0]=4;
		thetaEarth2[1]=thetaearth[1];
		thetaEarth2[2]=thetaearth[2];
		for(float i=thetaearth[2];i!=45;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[2]=i;
			display();
		}
		for(float i=thetaearth[1];i!=320;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[1]=i;
			display();
		}

		for(float i=1;i<=3;i+=0.01)
		{	
			zoom=i;
			display();
		}
		glutInitWindowSize(500,500);
		glutInitWindowPosition(0,0);
		Asia = glutCreateWindow("AUSRALIA");
		init6();
		glutDisplayFunc(display1);
		glutReshapeFunc(reshape1);
	}
	if(value == 7)
	{
		zoom=1;
		thetaEarth2[0]=4;
		thetaEarth2[1]=thetaearth[1];
		thetaEarth2[2]=thetaearth[2];
		for(float i=thetaearth[2];i!=25;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[2]=i;
			display();
		}
		for(float i=thetaearth[1];i!=270;i+=0.25)
		{	
			if(i>360.0)
				i-=360.0;
			thetaEarth2[1]=i;
			display();
		}

		for(float i=1;i<=3;i+=0.01)
		{	
			zoom=i;
			display();
		}
		glutInitWindowSize(500,500);
		glutInitWindowPosition(0,0);
		Asia = glutCreateWindow("ANARTICA");
		init7();
		glutDisplayFunc(display1);
		glutReshapeFunc(reshape1);
	}
}

//int flag =0;
void keys(unsigned char key,int x,int y)
{
	ang=0;
if(key=='b'||key=='B')
	{	
		glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
   
    glutInitWindowSize (1920,1080);
   
    glutInitWindowPosition (0,0);
   
    glutCreateWindow ("3D GLOBE");
	glutDisplayFunc(display);
    init();
	
	createmenu(); 

  
    
	glutIdleFunc (spinsphere);
	
	
    glutKeyboardFunc(keys);
	
    glutReshapeFunc (reshape);

		
	}
	
	if(key=='a'||key=='A')
	{
		thetaearth[2]-=5.0;

	}
	if(key=='s'||key=='S')
		thetaearth[1]+=5.0;
	if(key=='w'||key=='W')
		thetaearth[1]-=5.0;
	if(key=='d'||key=='D')
		thetaearth[2]+=5.0;
	if(key=='r'||key=='R')
	{
		zoom=0;
		ang=0.25;
	}
		if(key=='q' || key =='Q')
		exit(0);

}


int stop=0;



void display (void)
{
   
    glClearDepth(1);
   
    glClearColor (0.0,0.0,0.0,0.0);
   
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    glLoadIdentity();
    glTranslatef(0,0,-10);
   	if(zoom<1)
	{
		glRotatef(thetaearth[1],1.0,0.0,0.0);
		glRotatef(thetaearth[2],0.0,1.0,0.0);
		glRotatef(thetaearth[0],0.0,0.0,1.0);
	}
		//	glPushMatrix();
	if(zoom>=1)
	{	
		glLoadIdentity();
		glScalef(zoom,zoom,zoom);
		glRotatef(thetaEarth2[1],1.0,0.0,0.0);
		glRotatef(thetaEarth2[2],0.0,1.0,0.0);
		glRotatef(thetaEarth2[0],0.0,0.0,1.0);
	}
	DisplaySphere(5, texture[0]);
		//earth
//	glPopMatrix();
	glLoadIdentity();
	glRotatef(theta[1],1.0,0.0,1.0);
	glRotatef(theta[2],1.0,1.0,0.0);
	glRotatef(theta[1],0.0,0.0,1.0);
//	light();
	sphere2();//moon
    glutSwapBuffers();
}
GLint a;


int main (int argc, char **argv)
{
	
	
    glutInit (&argc, argv);

	 glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (1920,1080);
    glutInitWindowPosition (0,0);
	glutCreateWindow ("3D GLOBE");
    glutDisplayFunc (display10);
    glutIdleFunc (display10);
    glutReshapeFunc (reshape10);
	
    //Load our texture
    texture[9] = LoadTexture1( "docd.bmp", 1754, 1240 );
	glutKeyboardFunc(keys);

    glutMainLoop ();
   
    return 0;
}