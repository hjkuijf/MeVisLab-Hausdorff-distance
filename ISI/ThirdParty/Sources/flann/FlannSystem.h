//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    FlannSystem.h
// \author  Hugo Kuijf
// \date    2013-05-31
*/
//----------------------------------------------------------------------------------


#ifndef __FlannSystem_H
#define __FlannSystem_H


// DLL export macro definition
#ifdef WIN32
#ifdef FLANN_EXPORTS
// Use the ISIHNN_EXPORT macro to export classes and functions
#define FLANN_EXPORT __declspec(dllexport)
#else
// If included by external modules, exported symbols are declared as import symbols
#define FLANN_EXPORT __declspec(dllimport)
#endif

#else
// No export declarations are necessary for non-Windows systems
#define FLANN_EXPORT
#endif


#endif // __FlannSystem_H


