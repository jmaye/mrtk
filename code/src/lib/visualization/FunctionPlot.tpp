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

template <typename Y, typename X, size_t M>
FunctionPlot<Y, X, M>::FunctionPlot(const std::string& title, const
  Function<Y, X>& function, const Eigen::Matrix<X, M, 1>& minimum, const
  Eigen::Matrix<X, M, 1>& maximum) :
  mTitle(title),
  mMinimum(minimum),
  mMaximum(maximum) {
}

template <typename Y, typename X, size_t M>
FunctionPlot<Y, X, M>::FunctionPlot(const FunctionPlot<Y, X, M>& other) :
  mTitle(other.mTitle),
  mMinimum(other.mMinimum),
  mMaximum(other.mMaximum) {
}

template <typename Y, typename X, size_t M>
FunctionPlot<Y, X, M>& FunctionPlot<Y, X, M>::operator =
  (const FunctionPlot<Y, X, M>& other) {
  mTitle = other.mTitle;
  mMinimum = other.mMinimum;
  mMaximum = other.mMaximum;
  return *this;
}

template <typename Y, typename X, size_t M>
FunctionPlot<Y, X, M>::~FunctionPlot() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename Y, typename X, size_t M>
void FunctionPlot<Y, X, M>::setTitle(const std::string& title) {
  mTitle = title;
}

template <typename Y, typename X, size_t M>
const std::string& FunctionPlot<Y, X, M>::getTitle() const {
  return mTitle;
}

template <typename Y, typename X, size_t M>
void FunctionPlot<Y, X, M>::setMinimum(const Eigen::Matrix<X, M, 1>& minimum) {
  mMinimum = minimum;
}

template <typename Y, typename X, size_t M>
const Eigen::Matrix<X, M, 1>& FunctionPlot<Y, X, M>::getMinimum() const {
  return mMinimum;
}

template <typename Y, typename X, size_t M>
void FunctionPlot<Y, X, M>::setMaximum(const Eigen::Matrix<X, M, 1>& maximum) {
  mMaximum = maximum;
}

template <typename Y, typename X, size_t M>
const Eigen::Matrix<X, M, 1>& FunctionPlot<Y, X, M>::getMaximum() const {
  return mMaximum;
}
