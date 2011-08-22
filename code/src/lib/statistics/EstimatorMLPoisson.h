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

/** \file EstimatorMLPoisson.h
    \brief This file implements an ML estimator for Poisson distributions.
  */

#include "statistics/PoissonDistribution.h"
#include "base/Serializable.h"

#include <vector>

/** The class EstimatorML is implemented for Poisson distributions.
    \brief Poisson distribution ML estimator
  */
template <> class EstimatorML<PoissonDistribution> :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  EstimatorML();
  /// Copy constructor
  EstimatorML(const EstimatorML<PoissonDistribution>& other);
  /// Assignment operator
  EstimatorML<PoissonDistribution>& operator =
    (const EstimatorML<PoissonDistribution>& other);
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
  /// Add a point to the estimator
  void addPoint(size_t point);
  /// Add points to the estimator
  void addPoints(const std::vector<size_t>& points);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorMLPoisson.tpp"
