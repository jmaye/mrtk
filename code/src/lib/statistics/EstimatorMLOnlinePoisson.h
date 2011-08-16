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

/** \file EstimatorMLOnlinePoisson.h
    \brief This file implements an online ML estimator for Poisson
           distributions.
  */

#ifndef ESTIMATORMLONLINEPOISSON_H
#define ESTIMATORMLONLINEPOISSON_H

#include "statistics/PoissonDistribution.h"
#include "base/Serializable.h"

/** The class EstimatorMLOnline is implemented for Poisson distributions.
    \brief Poisson distribution ML estimator
  */
template <> class EstimatorMLOnline<PoissonDistribution> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<PoissonDistribution>& other);
  /// Assignment operator
  EstimatorMLOnline<PoissonDistribution>& operator =
    (const EstimatorMLOnline<PoissonDistribution>& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
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
  void addPoint(PoissonDistribution& dist, const
    PoissonDistribution::VariableType& point);
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

#include "statistics/EstimatorMLOnlinePoisson.tpp"

#endif // ESTIMATORMLONLINEPOISSON
