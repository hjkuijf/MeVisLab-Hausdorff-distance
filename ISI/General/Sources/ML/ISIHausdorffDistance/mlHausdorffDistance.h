//----------------------------------------------------------------------------------
//! The ML module class HausdorffDistance.
/*!
// \file    mlHausdorffDistance.h
// \author  Hugo Kuijf
// \date    2013-05-02
//
// 
*/
//----------------------------------------------------------------------------------


#ifndef __mlHausdorffDistance_H
#define __mlHausdorffDistance_H


// Local includes
#include "ISIHausdorffDistanceSystem.h"

// ML includes
#include <mlModuleIncludes.h>
#include <mlXMarkerList.h>

ML_START_NAMESPACE


//! 
class ISIHAUSDORFFDISTANCE_EXPORT HausdorffDistance : public Module
{
public:

  //! Constructor.
  HausdorffDistance ();

  //! Handles field changes of the field \p field.
  virtual void handleNotification (Field *field);

  void process( const XMarkerList* const aList, const XMarkerList* const bList, DoubleField* const distanceFld, DoubleField* const percentileList, StringField* const distancesFld);

  void computeDistancesFlann( const XMarkerList* const, const XMarkerList* const, std::vector<MLdouble>& ) const;

  void hausdorffDistancePercentile( const std::vector<MLdouble> &distances, DoubleField * const outputField ) const;

  void hausdorffDistance( const std::vector<MLdouble>& distances, DoubleField * const outputField ) const;

  void computeDistances( const XMarkerList* const firstList, const XMarkerList* const secondList, std::vector<MLdouble>& distances ) const;

  void handleNotificationInput(const BaseField* inputFld, XMarkerList*& inputXMarkerList);

private:

  // ----------------------------------------------------------
  //! \name Module field declarations
  //@{
  // ----------------------------------------------------------

  //! First xMarkerList
  BaseField *_input0Fld;
  //! Second xMarkerList
  BaseField *_input1Fld;

  //! Percentile
  DoubleField *_percentileFld;

  //! HD A to B
  DoubleField *_hausdorffDistanceAToBFld;
  //! HD B to A
  DoubleField *_hausdorffDistanceBToAFld;

  //! HD A to B
  DoubleField *_hausdorffPercentileAToBFld;
  //! HD B to A
  DoubleField *_hausdorffPercentileBToAFld;

  //! Distances
  StringField *_distancesAToBFld;
  StringField *_distancesBToAFld;

  //! Update
  NotifyField *_updateFld;
  //@}

  XMarkerList *_input0XMarkerList;
  XMarkerList *_input1XMarkerList;

  // Implements interface for the runtime type system of the ML.
  ML_MODULE_CLASS_HEADER(HausdorffDistance)
};


ML_END_NAMESPACE

#endif // __mlHausdorffDistance_H