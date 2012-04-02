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

/** \file NormalScaledInvChiSquareDistribution.h
    \brief This file defines the NormalNormalScaledInvChiSquareDistribution class,
           which represents a normal scaled inverse chi-square distribution
  */

#ifndef NORMALSCALEDINVCHISQUAREDISTRIBUTION_H
#define NORMALSCALEDINVCHISQUAREDISTRIBUTION_H

#include "statistics/DistributionTuple.h"
#include "statistics/SampleDistribution.h"
#include "statistics/ScaledInvChiSquareDistribution.h"
#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "base/Serializable.h"

/** The NormalScaledInvChiSquareDistribution class represents an normal scaled
    inverse chi-square distribution.
    \brief Normal scaled inverse chi-square distribution
  */
class NormalScaledInvChiSquareDistribution :
  public DistributionTuple<double, double>,
  public SampleDistribution<std::tuple<double, double> >,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /*! \brief Constructs distribution from parameters
  *
  * Location of mean: mu
  * Scale of mean: sigma / kappa
  * Scale of variance: sigma
  * Degrees of freedom of variance: nu
  */
  NormalScaledInvChiSquareDistribution(double mu = 0.0, double kappa = 1,
    double nu = 1, double sigma = 1.0);
  /// Copy constructor
  NormalScaledInvChiSquareDistribution(const
    NormalScaledInvChiSquareDistribution& other);
  /// Assignment operator
  NormalScaledInvChiSquareDistribution& operator = (const
    NormalScaledInvChiSquareDistribution& other);
  /// Destructor
  virtual ~NormalScaledInvChiSquareDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the variance distribution
  ScaledInvChiSquareDistribution getVarianceDist() const;
  /// Returns the marginal mean distribution
  StudentDistribution<1> getMargMeanDist() const;
  /// Returns mu parameter
  double getMu() const;
  /// Sets mu parameter
  void setMu(double mu);
  /// Returns kappa parameter
  double getKappa() const;
  /// Sets kappa parameter
  void setKappa(double kappa);
  /// Returns nu parameter
  double getNu() const;
  /// Sets nu parameter
  void setNu(double nu);
  /// Returns sigma parameter
  double getSigma() const;
  /// Sets sigma parameter
  void setSigma(double sigma);
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Access the probablity density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
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
  /// Mu parameter: prior mean
  double mMu;
  /// Kappa parameter: prior sample size
  double mKappa;
  /// Nu parameter: prior sample size
  double mNu;
  /// Sigma parameter: prior scale
  double mSigma;
  /** @}
    */

};

#include "statistics/NormalScaledInvChiSquareDistribution.tpp"

#endif // NORMALSCALEDINVCHISQUAREDISTRIBUTION_H
