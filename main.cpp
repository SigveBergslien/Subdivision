/*
 * main.cpp
 *
 *  Created on: 26. feb. 2010
 *      Author: ziggy
 */


#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>

#include "ModelViewer.h"

using namespace std;

using std::endl;

float rot;

ModelViewer* box= new ModelViewer();

#define RUN_GRAPHICS_DISPLAY 0x00;

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  Tish afhis event signifies
 * to call display() from the thread in which the OpenGL
 * context was created.
 */

Uint32 display(Uint32 interval, void *param) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = RUN_GRAPHICS_DISPLAY;
    event.user.data1 = 0;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
    return interval;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-3.0);//camera following the bike
    glRotatef(rot,0.1,0.1,0.1);
    box->draw();
	/*
    glBegin(GL_TRIANGLES);						// Drawing Using Triangles
	glVertex3f(0.0,1.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(1.0,0.0,0.0);
	glEnd();
	*/
    rot++;
    SDL_GL_SwapBuffers();
}

int main(int argc, char ** argv) {

    SDL_Surface * surf;
    Uint32 width = 640;
    Uint32 height = 480;
    Uint32 colour_depth = 16; // in bits
    Uint32 delay = 1000/60; // in milliseconds

    // Initialise SDL - when using C/C++ it's common to have to
    // initialise libraries by calling a function within them.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
            cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
            SDL_Quit();
    }

    // When we close a window quit the SDL application
    // Create a new window with an OpenGL surface
    if (!(surf = SDL_SetVideoMode(width, height, colour_depth, SDL_OPENGL))) {
            cout << "Failed to initialise video mode: " << SDL_GetError() << endl;
            SDL_Quit();
    }

    // Set the state of our new OpenGL context
    glViewport(0,0,(GLsizei)(width),(GLsizei)(height));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)(width)/(GLfloat)(height),1.0f,1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                // Black Background
    glClearDepth(1.0f);                                    // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations

    // Call the function "display" every delay milliseconds
    SDL_AddTimer(delay, display, NULL);

    bool running= true;
        SDL_Event event;

           while(running && (SDL_WaitEvent(&event))) {
               switch(event.type) {
                   case SDL_USEREVENT:
                       display();
                       break;

                   case SDL_KEYDOWN:
                	   switch(event.key.keysym.sym){
                	          case SDLK_LEFT:
                	        	  box->reset();
                	            break;
                	          case SDLK_RIGHT:
                	        	  box->subDivide();
                	              break;
                	          case SDLK_UP:
                	        	  box->catmullClark();
                	              break;
                	          default:
                	            break;
                	         }
    					   break;
                   case SDL_QUIT:
                       running = false;
                       break;

                   default:
                       break;
               }   // End switch
           }   // End while
    return 0;
}
