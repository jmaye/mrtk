/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include <QtCore/QString>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(const std::string& title,
  const Function<Y, X>& function, const Eigen::Matrix<X, 1, 1>& minimum, const
  Eigen::Matrix<X, 1, 1>& maximum, const X& resolution) throw
  (BadArgumentException<Eigen::Matrix<X, 1, 1> >, BadArgumentException<X>) :
  FunctionPlot<Y, X, 1>(title, minimum, maximum),
  mPlot(this),
  mResolution(resolution) {
  if (maximum(0) < minimum(0))
    throw BadArgumentException<Eigen::Matrix<X, 1, 1> >(maximum, "ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(): maximum must be larger than minimum");
  if (resolution <= 0)
    throw BadArgumentException<X>(resolution, "ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(): resolution must be strictly positive");
  if (resolution > maximum(0) - minimum(0))
    throw BadArgumentException<X>(resolution, "ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(): resolution must be smaller than the range");
  mPlot.setTitle(QString(title.c_str()));
  mXData.resize(round((maximum(0) - minimum(0)) / resolution));
  mYData.resize(round((maximum(0) - minimum(0)) / resolution));
  X xValue = minimum(0);
  for (size_t i = 0; i < (size_t)mXData.size(); ++i) {
    mXData[i] = xValue;
    mYData[i] = function(xValue);
    xValue += resolution;
  }
  mCurve.setData(mXData, mYData);
  mCurve.attach(&mPlot);
  mPlot.replot();
  setFixedSize(mPlot.sizeHint());
}

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(const
  ContinuousFunctionPlot<Y, X>& other) :
  FunctionPlot<Y, X, 1>(other),
  mPlot(other.mPlot),
  mCurve(other.mCurve),
  mXData(other.mXData),
  mYData(other.mYData),
  mResolution(other.mResolution) {
}

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X>& ContinuousFunctionPlot<Y, X>::operator =
  (const ContinuousFunctionPlot<Y, X>& other) {
  this->FunctionPlot<Y, X, 1>::operator=(other);
  mPlot = other.mPlot;
  mCurve = other.mCurve;
  mXData = other.mXData;
  mYData = other.mYData;
  mResolution = other.mResolution;
  return *this;
}

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X>::~ContinuousFunctionPlot() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename Y, typename X>
void ContinuousFunctionPlot<Y, X>::setResolution(const X& resolution) {
  mResolution = resolution;
}

template <typename Y, typename X>
const X& ContinuousFunctionPlot<Y, X>::getResolution() const {
  return mResolution;
}
