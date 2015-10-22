//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    ISIHausdorffDistanceInit.h
// \author  Hugo Kuijf
// \date    2013-05-02
*/
//----------------------------------------------------------------------------------


#ifndef __ISIHausdorffDistanceInit_H
#define __ISIHausdorffDistanceInit_H


ML_START_NAMESPACE

//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
int ISIHausdorffDistanceInit ();

ML_END_NAMESPACE

#endif // __ISIHausdorffDistanceInit_H
