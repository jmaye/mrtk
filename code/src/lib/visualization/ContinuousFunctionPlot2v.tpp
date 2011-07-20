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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X, 2>::ContinuousFunctionPlot(const std::string&
  title, const ContinuousFunction<Y, X, 2>& function, const
  Eigen::Matrix<X, 2, 1>& minimum, const Eigen::Matrix<X, 2, 1>& maximum, const
  X& resolution) throw (BadArgumentException<Eigen::Matrix<X, 2, 1> >,
  BadArgumentException<X>) :
  FunctionPlot<Y, X, 2>(title, minimum, maximum),
  mResolution(resolution) {
  if (maximum(0) < minimum(0))
    throw BadArgumentException<Eigen::Matrix<X, 2, 1> >(maximum,
      "ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(): maximum must be larger than minimum",
      __FILE__, __LINE__);
  if (resolution <= 0)
    throw BadArgumentException<X>(resolution,
      "ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(): resolution must be strictly positive",
      __FILE__, __LINE__);
  if (resolution > maximum(0) - minimum(0))
    throw BadArgumentException<X>(resolution,
      "ContinuousFunctionPlot<Y, X>::ContinuousFunctionPlot(): resolution must be smaller than the range",
      __FILE__, __LINE__);
  Qwt3D::SurfacePlot::setTitle(title.c_str());
  setRotation(30, 0, 15);
  setScale(1, 1, 1);
  setShift(0.15, 0, 0);
  setZoom(0.9);
  for (size_t i = 0; i != coordinates()->axes.size(); ++i) {
    coordinates()->axes[i].setMajors(7);
    coordinates()->axes[i].setMinors(4);
  }
  coordinates()->axes[Qwt3D::X1].setLabelString("x-axis");
  coordinates()->axes[Qwt3D::Y1].setLabelString("y-axis");
  coordinates()->axes[Qwt3D::Z1].setLabelString("z-axis");
  setCoordinateStyle(Qwt3D::FRAME);
  setPlotStyle(Qwt3D::FILLED);
  X xValue = minimum(0);
  size_t xSize = round((maximum(0) - minimum(0)) / resolution);
  size_t ySize = round((maximum(1) - minimum(1)) / resolution);
  mData = new double*[xSize];
  for (size_t i = 0; i < xSize; ++i) {
    Qwt3D::Cell cell;
    X yValue = minimum(1);
    mData[i] = new double[ySize];
    for (size_t j = 0; j < ySize; ++j) {
      mData[i][j] = function(Eigen::Matrix<X, 2, 1>(xValue, yValue));
      yValue += resolution;
    }
    xValue += resolution;
  }
  loadFromData(mData, xSize, ySize, minimum(0), maximum(0), minimum(1),
    maximum(1));
}

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X, 2>::ContinuousFunctionPlot(const
  ContinuousFunctionPlot<Y, X, 2>& other) :
  FunctionPlot<Y, X, 2>(other),
  mData(other.mData),
  mResolution(other.mResolution) {
}

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X, 2>& ContinuousFunctionPlot<Y, X, 2>::operator =
  (const ContinuousFunctionPlot<Y, X, 2>& other) {
  this->FunctionPlot<Y, X, 2>::operator=(other);
  mData = other.mData;
  mResolution = other.mResolution;
  return *this;
}

template <typename Y, typename X>
ContinuousFunctionPlot<Y, X, 2>::~ContinuousFunctionPlot() {
  size_t xSize = round((this->getMaximum()(0) - this->getMinimum()(0)) /
    mResolution);
  for (size_t i = 0; i < xSize; ++i) {
    delete []mData[i];
  }
  delete []mData;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename Y, typename X>
void ContinuousFunctionPlot<Y, X, 2>::setResolution(const X& resolution) {
  mResolution = resolution;
}

template <typename Y, typename X>
const X& ContinuousFunctionPlot<Y, X, 2>::getResolution() const {
  return mResolution;
}
