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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file LinearRegressionMv.h
    \brief This file defines the LinearRegressionMv class, which represents a
           multivariate linear regression
  */

#ifndef LINEARREGRESSIONMV_H
#define LINEARREGRESSIONMV_H

#include "functions/ContinuousFunction.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

/** The LinearRegressionMv class represents a multivariate linear regression.
    \brief Multivariate linear regression
  */
template <size_t M> class LinearRegression :
  public ContinuousFunction<double, double, M - 1>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs linear regression from parameters
  LinearRegression(const Eigen::Matrix<double, M, 1>& coefficients =
    Eigen::Matrix<double, M, 1>::Ones(), double variance = 1.0);
  /// Copy constructor
  LinearRegression(const LinearRegression& other);
  /// Assignment operator
  LinearRegression& operator = (const LinearRegression& other);
  /// Destructor
  ~LinearRegression();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the coefficients
  void setCoefficients(const Eigen::Matrix<double, M, 1>& coefficients);
  /// Returns the coefficients
  const Eigen::Matrix<double, M, 1>& getCoefficients() const;
  /// Sets the variance
  void setVariance(double variance) throw (BadArgumentException<double>);
  /// Returns the variance
  double getVariance() const;
  /// Returns the precision
  double getPrecision() const;
  /// Returns a sample of the regression variable at value
  virtual double getValue(const Eigen::Matrix<double, M - 1, 1>& value) const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Regression weights
  Eigen::Matrix<double, M, 1> mCoefficients;
  /// Variance
  double mVariance;
  /// Precision
  double mPrecision;
  /** @}
    */

};

#include "statistics/LinearRegressionMv.tpp"

#endif // LINEARREGRESSIONMV_H
