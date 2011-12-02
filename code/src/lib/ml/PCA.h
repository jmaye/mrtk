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

/** \file PCA.h
    \brief This file defines the PCA class, which implements a PCA algorithm
  */

#ifndef PCA_H
#define PCA_H

#include "exceptions/BadArgumentException.h"

#include <Eigen/Core>

#include <vector>

/** This class implements a Principal Component Analysis (PCA) algorithm.
    \brief Principal Component Analysis (PCA)
  */
template <typename T, size_t D, size_t M> class PCA {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  PCA();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Analyze the input data points
  static void analyze(const std::vector<Eigen::Matrix<T, D, 1> >& data,
    std::vector<Eigen::Matrix<T, M, 1> >& transformedData,
    Eigen::Matrix<T, D, 1>& eigenValues, Eigen::Matrix<T, D, D>& eigenVectors)
    throw (BadArgumentException<size_t>);
  /** @}
    */

protected:

};

#include "ml/PCA.tpp"

#endif // PCA_H
