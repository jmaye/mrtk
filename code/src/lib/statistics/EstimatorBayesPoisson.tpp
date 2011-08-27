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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

EstimatorBayes<PoissonDistribution>::EstimatorBayes(double alpha, double beta) :
  mAlpha(alpha),
  mBeta(beta),
  mNumPoints(0),
  mValid(false) {
}

EstimatorBayes<PoissonDistribution>::EstimatorBayes(const
  EstimatorBayes<PoissonDistribution>& other) :
  mPostMeanDist(other.mPostMeanDist),
  mPostPredDist(other.mPostPredDist),
  mAlpha(other.mAlpha),
  mBeta(other.mBeta),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

EstimatorBayes<PoissonDistribution>&
  EstimatorBayes<PoissonDistribution>::operator =
  (const EstimatorBayes<PoissonDistribution>& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostPredDist = other.mPostPredDist;
    mAlpha = other.mAlpha;
    mBeta = other.mBeta;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

EstimatorBayes<PoissonDistribution>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<PoissonDistribution>::read(std::istream& stream) {
}

void EstimatorBayes<PoissonDistribution>::write(std::ostream& stream) const {
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl << "posterior predictive distribution: " << std::endl
    << mPostPredDist << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

void EstimatorBayes<PoissonDistribution>::read(std::ifstream& stream) {
}

void EstimatorBayes<PoissonDistribution>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const GammaDistribution<double>& EstimatorBayes<PoissonDistribution>::
getPostMeanDist() const {
  return mPostMeanDist;
}

const NegativeBinomialDistribution& EstimatorBayes<PoissonDistribution>::
getPostPredDist() const {
  return mPostPredDist;
}

size_t EstimatorBayes<PoissonDistribution>::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorBayes<PoissonDistribution>::getValid() const {
  return mValid;
}

void EstimatorBayes<PoissonDistribution>::reset() {
  mNumPoints = 0;
  mValid = false;
}

void EstimatorBayes<PoissonDistribution>::addPoint(size_t point) {
  mNumPoints++;
  mAlpha += point;
  mBeta += 1;
  mPostMeanDist.setShape(mAlpha);
  mPostMeanDist.setInvScale(mBeta);
  mPostPredDist.setSuccessProbability(mAlpha / (1 + mAlpha));
  mPostPredDist.setNumTrials(mBeta);
  mValid = true;
}

void EstimatorBayes<PoissonDistribution>::addPoints(const
  std::vector<size_t>& points) {
  for (size_t i = 0; i < points.size(); ++i)
    addPoint(points[i]);
  std::cout << "post mean: " << mPostMeanDist.getMean() << std::endl;
  std::cout << "post pred mean: " << mPostPredDist.getNumTrials() * mPostPredDist.getSuccessProbability() / (1 - mPostPredDist.getSuccessProbability()) << std::endl;
}
