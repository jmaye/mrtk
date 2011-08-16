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

/** \file EstimatorBayesNormal1v.h
    \brief This file implements a Bayesian estimator for univariate normal
           distributions.
  */

#ifndef ESTIMATORBAYESNORMAL1V_H
#define ESTIMATORBAYESNORMAL1V_H

#include "statistics/NormalDistribution.h"
#include "statistics/GammaDistribution.h"
#include "base/Serializable.h"

template <typename D, size_t M = 1> class EstimatorBayes;

/** The class EstimatorBayes is implemented for univariate normal
    distributions.
    \brief Univariate normal distribution Bayesian estimator
  */
template <> class EstimatorBayes<NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorBayes(const NormalDistribution<1>& meanPrior = NormalDistribution<1>(),
    const GammaDistribution& variancePrior = GammaDistribution());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes<NormalDistribution<1> >& other);
  /// Assignment operator
  EstimatorBayes<NormalDistribution<1> >& operator =
    (const EstimatorBayes<NormalDistribution<1> >& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(NormalDistribution<1>& dist, const
    NormalDistribution<1>::VariableType& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

#include "statistics/EstimatorBayesNormal1v.tpp"

#endif // EstimatorBayesNORMAL1V
