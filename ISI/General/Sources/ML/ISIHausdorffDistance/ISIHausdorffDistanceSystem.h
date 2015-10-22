//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    ISIHausdorffDistanceSystem.h
// \author  Hugo Kuijf
// \date    2013-05-02
*/
//----------------------------------------------------------------------------------


#ifndef __ISIHausdorffDistanceSystem_H
#define __ISIHausdorffDistanceSystem_H


// DLL export macro definition
#ifdef ISIHAUSDORFFDISTANCE_EXPORTS
  // Use the ISIHAUSDORFFDISTANCE_EXPORT macro to export classes and functions
  #define ISIHAUSDORFFDISTANCE_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols
  #define ISIHAUSDORFFDISTANCE_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif


#endif // __ISIHausdorffDistanceSystem_H
