/*
 * framework.cpp
 *
 *  Created on: Oct 18, 2013
 *      Author: witek
 */
#ifndef FRAMEWORK_CPP
#define FRAMEWORK_CPP


#include "sdl_gl_framework.hpp"
#include "stdio.h"

SDL_Window *win = NULL;
SDL_GLContext mainGLContext;

bool fw::initGLSdl(const char* winName, uint32 w, uint32 h, bool fullScreen )
{

	//INIT SDL
	 if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
	        //std::cout << SDL_GetError() << std::endl;
	        fprintf( stderr, "%s\n", SDL_GetError() );
	        return false;
	  	  }

	 //SET OPENGL CONTEXT TO 3.0
	 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	  win = SDL_CreateWindow( winName, SDL_WINDOWPOS_CENTERED, 100, w, h, SDL_WINDOW_OPENGL |( fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN ));
	     if (win == 0){
	        fprintf( stderr, "%s\n", SDL_GetError() );
	         return false;
	     }

	    mainGLContext = SDL_GL_CreateContext( win );

	  //GLEW

	GLenum glewError = glewInit();

	if ( glewError == GLEW_OK ){

			if( !glewIsSupported("GL_ARB_vertex_buffer_object") )
				{
					fprintf(stderr,"VBO is not supported by your graphic card\n");
				} else printf("VBO is supported!\n");


			if( !glewIsSupported("GL_VERSION_3_0"))
			{
				printf("OpenGL 3.0 not supported!\n");
				fprintf(stderr, "OpenGL 3.0 not supported!\n( twoja karta graficzna jest stara jak skala, lub masz stare drivery... ;)");
			}



			// Set up V-Sync for LINUX ONLY!
#ifdef LINUX
			if( glxewIsSupported("GLX_SGI_swap_control") )
			{
				glXSwapIntervalSGI( VSYNC );
				printf("V-sync is enabled ;)\n");
			} else
				{
					printf("V-sync in not supported\n");
					fprintf( stderr, "V-sync in not supported\n");
				}
#endif


			//Other Setting

			// Enable depth test
			glEnable(GL_DEPTH_TEST);

		    // Accept fragment if it closer to the camera than the former one
			glDepthFunc(GL_LESS);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	} else{
			printf ("GLEW FAIL\n");

			fprintf(stderr,"Unable to initialize GLEW: %s\n", glewGetErrorString(glewError));

			return false;
		}

	return true;
}


void fw::cleanGLSdl()
{
	SDL_GL_DeleteContext( mainGLContext );
	SDL_DestroyWindow(win);

	SDL_Quit();
}

SDL_Window* fw::getWindowPointer()
{
	return win;
}





#endif // FRAMEWORK_CPP
