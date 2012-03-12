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

EstimatorBayesImproper<NormalDistribution<1> >::EstimatorBayesImproper() :
    mNumPoints(0),
    mValid(false),
    mValuesSum(0),
    mSquaredValuesSum(0) {
}

EstimatorBayesImproper<NormalDistribution<1> >::EstimatorBayesImproper(const
    EstimatorBayesImproper& other) :
    mPostMeanDist(other.mPostMeanDist),
    mPostVarianceDist(other.mPostVarianceDist),
    mPostPredDist(other.mPostPredDist),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid),
    mValuesSum(other.mValuesSum),
    mSquaredValuesSum(other.mSquaredValuesSum) {
}

EstimatorBayesImproper<NormalDistribution<1> >&
    EstimatorBayesImproper<NormalDistribution<1> >::operator =
    (const EstimatorBayesImproper& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostVarianceDist = other.mPostVarianceDist;
    mPostPredDist = other.mPostPredDist;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
    mValuesSum = other.mValuesSum;
    mSquaredValuesSum = other.mSquaredValuesSum;
  }
  return *this;
}

EstimatorBayesImproper<NormalDistribution<1> >::~EstimatorBayesImproper() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayesImproper<NormalDistribution<1> >::read(std::istream&
    stream) {
}

void EstimatorBayesImproper<NormalDistribution<1> >::write(std::ostream& stream)
    const {
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl
    << "posterior mean mode: " << mPostMeanDist.getMode() << std::endl
    << "posterior mean variance: " << mPostMeanDist.getVariance() << std::endl
    << "posterior variance distribution: " << std::endl
    << mPostVarianceDist
    << std::endl
    << "posterior variance mode: " << mPostVarianceDist.getMode() << std::endl
    << "posterior variance variance: " << mPostVarianceDist.getVariance()
    << std::endl
    << "posterior predictive distribution: " << std::endl
    << mPostPredDist << std::endl
    << "posterior predictive mean: " << mPostPredDist.getMean() << std::endl
    << "posterior predictive variance: " << mPostPredDist.getVariance()
    << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

void EstimatorBayesImproper<NormalDistribution<1> >::read(std::ifstream&
    stream) {
}

void EstimatorBayesImproper<NormalDistribution<1> >::write(std::ofstream&
    stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const StudentDistribution<1>&
    EstimatorBayesImproper<NormalDistribution<1> >::getPostMeanDist() const {
  return mPostMeanDist;
}

const ScaledInvChiSquareDistribution&
    EstimatorBayesImproper<NormalDistribution<1> >::getPostVarianceDist()
    const {
  return mPostVarianceDist;
}

const StudentDistribution<1>&
    EstimatorBayesImproper<NormalDistribution<1> >::getPostPredDist() const {
  return mPostPredDist;
}

size_t EstimatorBayesImproper<NormalDistribution<1> >::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorBayesImproper<NormalDistribution<1> >::getValid() const {
  return mValid;
}

void EstimatorBayesImproper<NormalDistribution<1> >::reset() {
  mNumPoints = 0;
  mValid = false;
  mValuesSum = 0;
  mSquaredValuesSum = 0;
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoint(const Point&
    point) {
  mNumPoints++;
  mValuesSum += point;
  mSquaredValuesSum += point * point;
  try {
    mValid = true;
    const double mean = mValuesSum / mNumPoints;
    const double variance = mSquaredValuesSum / (mNumPoints - 1) -
      mValuesSum * mValuesSum * 2 / ((mNumPoints - 1) * mNumPoints) +
      mean * mean * ((double)mNumPoints / (mNumPoints - 1));
    mPostMeanDist.setDegrees(mNumPoints - 1);
    mPostMeanDist.setLocation(mean);
    mPostMeanDist.setScale(variance / mNumPoints);
    mPostVarianceDist.setDegrees(mNumPoints - 1);
    mPostVarianceDist.setScale(variance);
    mPostPredDist.setDegrees(mNumPoints - 1);
    mPostPredDist.setLocation(mean);
    mPostPredDist.setScale(variance * (1 + 1.0 / mNumPoints));
  }
  catch (...) {
    mValid = false;
  }
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
