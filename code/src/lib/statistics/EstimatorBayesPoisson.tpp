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

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    EstimatorBayes(const GammaDistribution<double>& prior) :
    mMeanDist(prior),
    mPredDist(mMeanDist.getShape(), 1.0 / (mMeanDist.getInvScale() + 1)) {
}

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mMeanDist(other.mMeanDist),
    mPredDist(other.mPredDist) {
}

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >&
    EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanDist = other.mMeanDist;
    mPredDist = other.mPredDist;
  }
  return *this;
}

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    read(std::istream& stream) {
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    write(std::ostream& stream) const {
  stream << "Mean distribution: " << std::endl << mMeanDist << std::endl <<
    "Mean mode: " << mMeanDist.getMode() << std::endl <<
    "Mean variance: " << mMeanDist.getVariance() << std::endl <<
    "Predictive distribution: " << std::endl << mPredDist << std::endl <<
    "Predictive mean: " << mPredDist.getMean() << std::endl <<
    "Predictive variance: " << mPredDist.getVariance();
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    read(std::ifstream& stream) {
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const GammaDistribution<double>&
    EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    getMeanDist() const {
  return mMeanDist;
}

const NegativeBinomialDistribution&
    EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    getPredDist() const {
  return mPredDist;
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    addPoint(const Point& point) {
  mMeanDist.setShape(mMeanDist.getShape() + point);
  mMeanDist.setInvScale(mMeanDist.getInvScale() + 1);
  mPredDist.setProbability(1.0 / (mMeanDist.getInvScale() + 1));
  mPredDist.setNumTrials(mMeanDist.getShape());
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
