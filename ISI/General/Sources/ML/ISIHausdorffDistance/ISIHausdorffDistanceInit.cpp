//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    ISIHausdorffDistanceInit.cpp
// \author  Hugo Kuijf
// \date    2013-05-02
*/
//----------------------------------------------------------------------------------


// Local includes
#include "ISIHausdorffDistanceSystem.h"

// Include definition of ML_INIT_LIBRARY.
#include "mlLibraryInitMacros.h"

// Include all module headers ...
#include "mlHausdorffDistance.h"


ML_START_NAMESPACE

//----------------------------------------------------------------------------------
//! Calls init functions of all modules to add their types to the runtime type
//! system of the ML.
//----------------------------------------------------------------------------------
int ISIHausdorffDistanceInit ()
{
  HausdorffDistance::initClass();
  // Add initClass calls from all other modules here...

  return 1;
}

ML_END_NAMESPACE


//! Calls the init method implemented above during load of shared library.
ML_INIT_LIBRARY(ISIHausdorffDistanceInit)