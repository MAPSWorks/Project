
 
GLuint texture[9]; //the array for our texture

//GLfloat angle = 0.0;

//function to load the RAW file

GLuint LoadTexture1( const char * filename, int width, int height )
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

    glGenTextures( 1, &texture ); //generate the texture with the loaded data
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the textureto it’s array
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //set texture environment parameters
//And if you go and use extensions, you can use Anisotropic filtering textures which are of an
    //even better quality, but this will do for now.
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    //Here we are setting the parameter to repeat the texture instead of clamping the texture
    //to the edge of our shape. 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return texture; //return whether it was successfull
}

void FreeTexture1( GLuint texture )
{
  glDeleteTextures( 1, &texture );
}

void square10 (void) {
    glBindTexture( GL_TEXTURE_2D, texture[9] ); //bind our texture to our shape
    //glRotatef( angle, 1.0f, 1.0f, 1.0f );
    glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-5.80,-3.0); //with our vertices we have to assign a texcoord
    glTexCoord2d(1.0,0.0); glVertex2d(+5.80,-3.0); //so thatour texture has some points to draw to
    glTexCoord2d(1.0,1.0); glVertex2d(+5.80,+3.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-5.80,+3.0);
    glEnd();

}
void display10 (void) 
{
	int a=0;
	//printf("enter 1 to go to project");
	
    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glEnable( GL_TEXTURE_2D );
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    square10();
    glutSwapBuffers();

}
void reshape10 (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0)
;
    glMatrixMode (GL_MODELVIEW);
}

