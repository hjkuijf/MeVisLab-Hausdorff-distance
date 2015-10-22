//----------------------------------------------------------------------------------
//! The ML module class HausdorffDistance.
/*!
// \file    mlHausdorffDistance.cpp
// \author  Hugo Kuijf
// \date    2013-05-02
//
// 
*/
//----------------------------------------------------------------------------------

// Local includes
#include "mlHausdorffDistance.h"

// FLANN includes
#include "flann/flann.hpp"

ML_START_NAMESPACE

  //! Implements code for the runtime type system of the ML
  ML_MODULE_CLASS_SOURCE(HausdorffDistance, Module);

//----------------------------------------------------------------------------------
//! Constructor
//----------------------------------------------------------------------------------
HausdorffDistance::HausdorffDistance() : Module(0, 0)
{
  // See section 'Implementing the Constructor()' in ML Programming Guide for details.
  // Suppress calls of handleNotification on field changes to
  // avoid side effects during initialization phase.
  handleNotificationOff();

  // Add fields to the module and set their values.
  _input0Fld = addBase("input0");
  _input1Fld = addBase("input1");

  _percentileFld = addDouble("percentile", 0.95);

  _updateFld = addNotify("update");

  _input0Fld->addAllowedType<XMarkerList>();
  _input1Fld->addAllowedType<XMarkerList>();

  _hausdorffDistanceAToBFld = addDouble("hausdorffDistanceAToB", 0);
  _hausdorffDistanceBToAFld = addDouble("hausdorffDistanceBToA", 0);
  _hausdorffPercentileAToBFld = addDouble("hausdorffPercentileAToB", 0);
  _hausdorffPercentileBToAFld = addDouble("hausdorffPercentileBToA", 0);

  _distancesAToBFld = addString("distancesAToB", "");
  _distancesBToAFld = addString("distancesBToA", "");

  // Reactivate calls of handleNotification on field changes.
  handleNotificationOn();
}

//----------------------------------------------------------------------------------
//! Handle field changes of the field field.
//----------------------------------------------------------------------------------
void HausdorffDistance::handleNotification(Field *field)
{

  if (field == _input0Fld) {
    handleNotificationInput(_input0Fld, _input0XMarkerList);
  }
  if (field == _input1Fld) {
    handleNotificationInput(_input1Fld, _input1XMarkerList);
  }

  if (field == _updateFld && _input0XMarkerList != NULL && _input1XMarkerList != NULL) {
    // A to B
    process(_input0XMarkerList, _input1XMarkerList, _hausdorffDistanceAToBFld, _hausdorffPercentileAToBFld, _distancesAToBFld);

    // B to A
    process(_input1XMarkerList, _input0XMarkerList, _hausdorffDistanceBToAFld, _hausdorffPercentileBToAFld, _distancesBToAFld);
  }
}

void HausdorffDistance::handleNotificationInput( const BaseField* inputFld, XMarkerList*& inputXMarkerList )
{
  Base* baseValue = inputFld->getBaseValue();
  inputXMarkerList = mlbase_cast<XMarkerList*>(baseValue);

  if (baseValue == NULL) {
    std::cout << "No " << inputFld->getName() << std::endl;
  } else if(inputXMarkerList == NULL) {
    std::cout << "No valid xMarkerList at " << inputFld->getName() << std::endl;
  } else {
    //std::cout << "Valid  " << inputFld->getName() << std::endl;
  }
}



void HausdorffDistance::hausdorffDistance( const std::vector<MLdouble>& distances, DoubleField * const outputField ) const
{
  outputField->setDoubleValue(*std::max_element(distances.begin(), distances.end()));
}

// Brute force search, slow
void HausdorffDistance::computeDistances( const XMarkerList* const aList, const XMarkerList* const bList, std::vector<MLdouble>& distances ) const
{
  // Compute the hausdorffDistance
  const MLint sizeAList(aList->getSize());
  const MLuint sizeBList(bList->getSize());

  distances.resize(sizeAList, 0); 

#pragma omp parallel for
  for (MLint i = 0; i < sizeAList; ++i) 
  {
    MLdouble minDistance(ML_DOUBLE_MAX);

    const XMarker* const aMarker = (XMarker*)aList->getConstItemAt(i);

    for (MLuint j(0); j < sizeBList; ++j) {
      const XMarker* const bMarker = (XMarker*)bList->getConstItemAt(j);

      const MLdouble distance(aMarker->pos.distance(bMarker->pos));

      if (distance < minDistance) {
        minDistance = distance;
      }
    }

    distances[i] = minDistance; 
  }
}

void HausdorffDistance::hausdorffDistancePercentile( const std::vector<MLdouble> &distances, DoubleField * const outputField ) const
{
  std::vector<MLdouble> tempDistances(distances);

  const MLdouble percentile(_percentileFld->getDoubleValue());

  auto middle = tempDistances.begin();
  std::advance(middle, MLuint(percentile * tempDistances.size() + 0.5));

  std::nth_element(tempDistances.begin(), middle, tempDistances.end() );

  outputField->setDoubleValue(*middle);
}

void HausdorffDistance::process( const XMarkerList* const aList, const XMarkerList* const bList, DoubleField* const distanceFld, DoubleField* const percentileList, StringField* const distancesFld)
{
  std::vector<MLdouble> distanceList;
  std::vector<MLdouble> distanceListKNN;

  //computeDistances(aList, bList, distanceList); // slow

  computeDistancesFlann(aList, bList, distanceListKNN); // fast

  hausdorffDistance(distanceListKNN, distanceFld);
  hausdorffDistancePercentile(distanceListKNN, percentileList);

  std::stringstream outputStringStream;
  std::copy(distanceListKNN.begin(), distanceListKNN.end(), std::ostream_iterator<MLdouble>(outputStringStream, " "));
  distancesFld->setStringValue(outputStringStream.str());
}

// KD-tree based search, fast
void HausdorffDistance::computeDistancesFlann( const XMarkerList* const aList, const XMarkerList* const bList, std::vector<MLdouble>& distances ) const
{
  typedef MLdouble DataType;

  const MLuint nQueryPoints = aList->getSize();
  const MLuint nDataPoints  = bList->getSize();
  const MLuint nDimensions  = 3;

  distances.resize(nQueryPoints, 0);

  DataType* aListData;
  DataType* bListData;

  ML_CHECK_NEW(aListData, DataType [nQueryPoints * nDimensions]);
  ML_CHECK_NEW(bListData, DataType [nDataPoints * nDimensions]);

  for (MLuint i(0); i < nQueryPoints; ++i) {
    aListData[i*nDimensions + 0] = ((XMarker*)aList->getConstItemAt(i))->x();
    aListData[i*nDimensions + 1] = ((XMarker*)aList->getConstItemAt(i))->y();
    aListData[i*nDimensions + 2] = ((XMarker*)aList->getConstItemAt(i))->z();
  }

  for (MLuint i(0); i < nDataPoints; ++i) {
    bListData[i*nDimensions + 0] = ((XMarker*)bList->getConstItemAt(i))->x();
    bListData[i*nDimensions + 1] = ((XMarker*)bList->getConstItemAt(i))->y();
    bListData[i*nDimensions + 2] = ((XMarker*)bList->getConstItemAt(i))->z();
  }

  flann::Matrix<DataType> aMatrix(aListData, nQueryPoints, nDimensions);
  flann::Matrix<DataType> bMatrix(bListData, nDataPoints, nDimensions);


  flann::Index<flann::L2_3D<DataType> > bIndex(bMatrix, flann::KDTreeSingleIndexParams());
  bIndex.buildIndex();

  flann::Matrix<int> indices(new int[nQueryPoints], aMatrix.rows, 1);
  flann::Matrix<DataType> dists(new DataType[nQueryPoints], aMatrix.rows, 1);

  flann::SearchParams searchParams(flann::FLANN_CHECKS_UNLIMITED, 0);
  //searchParams.cores = 0;

  // Performs kNN search. Note that the returned distances are squared.
  bIndex.knnSearch(aMatrix, indices, dists, 1, searchParams);


  // Copy dists to distances and apply sqrt at the same time
  std::transform(dists.ptr(), dists.ptr() + nQueryPoints, distances.begin(), std::ptr_fun<DataType, DataType>(sqrt));

  ML_DELETE_ARRAY(aListData);
  ML_DELETE_ARRAY(bListData);

  delete[] indices.ptr();
  delete[] dists.ptr();
}

ML_END_NAMESPACE