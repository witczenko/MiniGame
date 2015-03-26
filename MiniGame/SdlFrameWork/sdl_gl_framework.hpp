/*
 * framework.hpp
 *
 *  Created on: Oct 17, 2013
 *      Author: witek
 */

#ifndef FRAMEWORK_HPP_
#define FRAMEWORK_HPP_

//INCLUDES
#include "SDL.h"
#include "GL/glew.h"

//My basics types
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;
typedef float float32;
typedef double float64;


//Framework
namespace fw
{

//SDL + OPENGL
   bool initGLSdl(const char* winName, uint32 w, uint32 h, bool fullScreen );
   SDL_Window* getWindowPointer();
   void cleanGLSdl();

}


#endif /* FRAMEWORK_HPP_ */
