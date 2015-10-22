//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    FlannInit.h
// \author  Hugo Kuijf
// \date    2013-05-31
*/
//----------------------------------------------------------------------------------


#ifndef __FlannInit_H
#define __FlannInit_H


ML_START_NAMESPACE

  //! Calls init functions of all modules to add their types to the runtime type
  //! system of the ML.
  int FlannInit ();

ML_END_NAMESPACE

#endif // __FlannInit_H


