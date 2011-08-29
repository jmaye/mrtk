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

/** \file LinearRegressionPred1v.h
    \brief This file defines the LinearRegressionPred1v class, which represents
           a univariate predictive linear regression (line)
  */

#ifndef LINEARREGRESSIONPRED1V_H
#define LINEARREGRESSIONPRED1V_H

#include "statistics/StudentDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

template <size_t M = 2> class LinearRegressionPred;

/** The LinearRegressionPred1v class represents a univariate predictive linear
    regression, i.e. a line.
    \brief Univariate predictive linear regression
  */
template <> class LinearRegressionPred<2> :
  public StudentDistribution<1>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs linear regression from parameters
  LinearRegressionPred(const Eigen::Matrix<double, 2, 1>& coefficients =
    Eigen::Matrix<double, 2, 1>::Ones(), const Eigen::Matrix<double, 2, 2>&
    coeffCovariance = Eigen::Matrix<double, 2, 2>::Identity(), double basis =
    0.0, double regressionVariance = 1.0);
  /// Copy constructor
  LinearRegressionPred(const LinearRegressionPred<2>& other);
  /// Assignment operator
  LinearRegressionPred<2>& operator = (const LinearRegressionPred<2>& other);
  /// Destructor
  ~LinearRegressionPred();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the coefficients
  void setCoefficients(const Eigen::Matrix<double, 2, 1>& coefficients);
  /// Returns the coefficients
  const Eigen::Matrix<double, 2, 1>& getCoefficients() const;
  /// Sets the coefficients covariance
  void setCoeffCovariance(const Eigen::Matrix<double, 2, 2>& coeffCovariance);
  /// Returns the coefficients covariance
  const Eigen::Matrix<double, 2, 2>& getCoeffCovariance() const;
  /// Sets the regression variance
  void setRegressionVariance(double variance);
  /// Returns the regression variance
  double getRegressionVariance() const;
  /// Sets the basis
  void setBasis(double basis);
  /// Returns the basis
  double getBasis() const;
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
  Eigen::Matrix<double, 2, 1> mCoefficients;
  /// Regression weights covariance
  Eigen::Matrix<double, 2, 2> mCoeffCovariance;
  /// Regression variance
  double mRegressionVariance;
  /// Basis
  double mBasis;
  /** @}
    */

};

#include "statistics/LinearRegressionPred1v.tpp"

#endif // LINEARREGRESSIONPRED1V_H
