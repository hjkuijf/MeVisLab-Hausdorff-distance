//----------------------------------------------------------------------------------
//! Dynamic library and runtime type system initialization.
/*!
// \file    FlannInit.cpp
// \author  Hugo Kuijf
// \date    2013-05-31
*/
//----------------------------------------------------------------------------------


// Local includes
#include "FlannSystem.h"

// Include definition of ML_INIT_LIBRARY.
#include "mlLibraryInitMacros.h"

// Include base wrapper objects
//#include "mlFLANNBaseWrapper.h"

// Include all module headers ...
//#include "mlFLANNMatrixTest.h"
//#include "mlFLANNTest.h"


ML_START_NAMESPACE

  //----------------------------------------------------------------------------------
  //! Calls init functions of all modules to add their types to the runtime type
  //! system of the ML.
  //----------------------------------------------------------------------------------
  int FlannInit ()
{
  ML_TRACE_IN("FlannInit ()")

  // Initialize baseWrapper objects

  // Add initClass calls from all other modules here...

  return 1;
}

ML_END_NAMESPACE


  //! Calls the init method implemented above during load of shared library.
  ML_INIT_LIBRARY(FlannInit)

