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

/** \file EstimatorMLNormal1v.h
    \brief This file implements an ML estimator for univariate normal
           distributions.
  */

#ifndef ESTIMATORMLNORMAL1V_H
#define ESTIMATORMLNORMAL1V_H

#include "statistics/NormalDistribution.h"
#include "base/Serializable.h"

#include <vector>

template <typename D, size_t M = 1, size_t N = 1> class EstimatorML;

/** The class EstimatorML is implemented for univariate normal distributions.
    \brief Univariate normal distribution ML estimator
  */
template <> class EstimatorML<NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorML();
  /// Copy constructor
  EstimatorML(const EstimatorML<NormalDistribution<1> >& other);
  /// Assignment operator
  EstimatorML<NormalDistribution<1> >& operator =
    (const EstimatorML<NormalDistribution<1> >& other);
  /// Destructor
  virtual ~EstimatorML();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Returns the estimated mean
  double getMean() const;
  /// Returns the estimated variance
  double getVariance() const;
  /// Add a point to the estimator
  void addPoint(double point);
  /// Add points to the estimator
  void addPoints(const std::vector<double>& points);
  /// Reset the estimator
  void reset();
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
  /// Estimated mean
  double mMean;
  /// Estimated variance
  double mVariance;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorMLNormal1v.tpp"

#endif // ESTIMATORMLNORMAL1V
