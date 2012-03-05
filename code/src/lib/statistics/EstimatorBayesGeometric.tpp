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

EstimatorBayes<GeometricDistribution>::EstimatorBayes(const BetaDistribution&
    prior) :
    mProbDist(prior) {
}

EstimatorBayes<GeometricDistribution>::EstimatorBayes(const EstimatorBayes&
    other) :
    mProbDist(other.mProbDist) {
}

EstimatorBayes<GeometricDistribution>&
    EstimatorBayes<GeometricDistribution>::operator = (const EstimatorBayes&
    other) {
  if (this != &other) {
    mProbDist = other.mProbDist;
  }
  return *this;
}

EstimatorBayes<GeometricDistribution>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<GeometricDistribution>::read(std::istream& stream) {
}

void EstimatorBayes<GeometricDistribution>::write(std::ostream& stream) const {
  stream << "Mean distribution: " << std::endl << mProbDist << std::endl <<
    "Mean mode: " << mProbDist.getMode() << std::endl <<
    "Mean variance: " << mProbDist.getVariance();
}

void EstimatorBayes<GeometricDistribution>::read(std::ifstream& stream) {
}

void EstimatorBayes<GeometricDistribution>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const BetaDistribution&
    EstimatorBayes<GeometricDistribution>::getProbDist() const {
  return mProbDist;
}

void EstimatorBayes<GeometricDistribution>::addPoint(const Point& point) {
  mProbDist.setAlpha(mProbDist.getAlpha() + 1);
  mProbDist.setBeta(mProbDist.getBeta() + point);
}

void EstimatorBayes<GeometricDistribution>::addPoints(const ConstPointIterator&
    itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
