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

/** \file EstimatorMLMultinomial.h
    \brief This file implements an ML estimator for multinomial distributions.
  */

#ifndef ESTIMATORMLMULTINOMIAL_H
#define ESTIMATORMLMULTINOMIAL_H

#include "statistics/MultinomialDistribution.h"
#include "base/Serializable.h"

#include <vector>

/** The class EstimatorML is implemented for multinomial distributions.
    \brief Multinomial distribution ML estimator
  */
template <size_t M> class EstimatorML<MultinomialDistribution<M>, M> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorML();
  /// Copy constructor
  EstimatorML(const EstimatorML<MultinomialDistribution<M>, M>& other);
  /// Assignment operator
  EstimatorML<MultinomialDistribution<M>, M>& operator =
    (const EstimatorML<MultinomialDistribution<M>, M>& other);
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
  /// Returns the estimated success probabilities
  const Eigen::Matrix<double, M, 1>& getSuccessProbabilities() const;
  /// Returns the estimated number of trials
  size_t getNumTrials() const;
  /// Add a point to the estimator
  void addPoint(const Eigen::Matrix<size_t, M, 1>& point);
  /// Add points to the estimator
  void addPoints(const std::vector<Eigen::Matrix<size_t, M, 1> >& points);
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
  /// Estimated success probabilities
  Eigen::Matrix<double, M, 1> mSuccessProbabilities;
  /// Estimated number of trials
  size_t mNumTrials;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorMLMultinomial.tpp"

#endif // ESTIMATORMLMULTINOMIAL
