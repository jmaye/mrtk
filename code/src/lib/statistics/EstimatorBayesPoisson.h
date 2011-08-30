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

/** \file EstimatorBayesPoisson.h
    \brief This file implements a Bayesian estimator for Poisson distributions
           with conjugate prior
  */

#include "statistics/PoissonDistribution.h"
#include "statistics/GammaDistribution.h"
#include "statistics/NegativeBinomialDistribution.h"

#include <vector>

/** The class EstimatorBayes is implemented for Poisson distributions with
    conjugate prior.
    \brief Poisson distribution Bayesian estimator
  */
template <> class EstimatorBayes<PoissonDistribution> :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with hyperparameters prior
  EstimatorBayes(double alpha = 1.0, double beta = 1.0);
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes<PoissonDistribution>& other);
  /// Assignment operator
  EstimatorBayes<PoissonDistribution>& operator =
    (const EstimatorBayes<PoissonDistribution>& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the posterior mean distribution
  const GammaDistribution<double>& getPostMeanDist() const;
  /// Returns the posterior predictive distribution
  const NegativeBinomialDistribution& getPostPredDist() const;
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
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
  /// Posterior mean distribution
  GammaDistribution<double> mPostMeanDist;
  /// Posterior predictive distribution
  NegativeBinomialDistribution mPostPredDist;
  /// Hyperparameter alpha (alpha - 1 prior counts)
  double mAlpha;
  /// Hyperparameter beta (beta prior observations)
  double mBeta;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorBayesPoisson.tpp"
