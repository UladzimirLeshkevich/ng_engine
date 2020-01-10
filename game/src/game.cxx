//http://www.youtube.com/user/thecplusplusguy
//Thanks for the typed in code to Tapit85

//https://compgraphics.info/OpenGL/lighting/light_sources.php
//https://www.youtube.com/watch?v=y7RBvPFwOzE
//https://pastebin.com/y6RhBygS

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

void drawCube(float size)
{
    float difamb[] = {1.0, 0.5, 0.3, 1.0};
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
    // front face
    glNormal3f(0.0, 0.0, 1.0);
    //              glColor3f(1.0,0.0,0.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    // left face
    glNormal3f(-1.0, 0.0, 0.0);
    //              glColor3f(0.0,1.0,0.0);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    // back face
    glNormal3f(0.0, 0.0, -1.0);
    //              glColor3f(0.0,0.0,1.0);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    // right face
    glNormal3f(1.0, 0.0, 0.0);
    //              glColor3f(1.0,1.0,0.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    // top face
    glNormal3f(0.0, 1.0, 0.0);
    //              glColor3f(1.0,0.0,1.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    // bottom face
    glNormal3f(0.0, -1.0, 0.0);
    //              glColor3f(0.0,1.0,1.0);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glEnd();
}

float angle = 0.0;
const int triangle = 1;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); //background color and alpha
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //      glEnable(GL_COLOR_MATERIAL);
    float dif[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    float amb[] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float pos[] = {0.0, 3.0, 3.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 0.0); // angle, x-axis, y-axis, z-axis
    drawCube(1.0);
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen;
    screen = SDL_SetVideoMode(800, 800, 32, SDL_SWSURFACE | SDL_OPENGL | 0);
    //screen = SDL_SetVideoMode(800, 800, 32, SDL_SWSURFACE | SDL_OPENGL | 0);
    //screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE|SDL_FULLSCREEN);
    bool running = true;
    const int FPS = 30;
    Uint32 start;
    SDL_Event event;
    init();
    while (true)
    {
        start = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
                break;
            }
        }

        display();
        SDL_GL_SwapBuffers();
        angle += 0.5;
        if (angle > 360)
            angle -= 360;
        if (1000 / FPS > SDL_GetTicks() - start)
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
    }
    SDL_Quit();
    return 0;
}
