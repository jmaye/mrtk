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

EstimatorBayes<ExponentialDistribution>::EstimatorBayes(const
    GammaDistribution<double>& prior) :
    mRateDist(prior) {
}

EstimatorBayes<ExponentialDistribution>::EstimatorBayes(const EstimatorBayes&
    other) :
    mRateDist(other.mRateDist) {
}

EstimatorBayes<ExponentialDistribution>&
    EstimatorBayes<ExponentialDistribution>::operator = (const EstimatorBayes&
    other) {
  if (this != &other) {
    mRateDist = other.mRateDist;
  }
  return *this;
}

EstimatorBayes<ExponentialDistribution>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<ExponentialDistribution>::read(std::istream& stream) {
}

void EstimatorBayes<ExponentialDistribution>::write(std::ostream& stream)
    const {
  stream << "Rate distribution: " << std::endl << mRateDist << std::endl <<
    "Rate mode: " << mRateDist.getMode() << std::endl <<
    "Rate variance: " << mRateDist.getVariance();
}

void EstimatorBayes<ExponentialDistribution>::read(std::ifstream& stream) {
}

void EstimatorBayes<ExponentialDistribution>::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const GammaDistribution<double>&
    EstimatorBayes<ExponentialDistribution>::getRateDist() const {
  return mRateDist;
}

void EstimatorBayes<ExponentialDistribution>::addPoint(const Point& point) {
  mRateDist.setShape(mRateDist.getShape() + 1);
  mRateDist.setInvScale(mRateDist.getInvScale() + point);
}

void EstimatorBayes<ExponentialDistribution>::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
