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

EstimatorBayes<NormalDistribution<1> >::EstimatorBayes(const
  NormalDistribution<1>& meanPrior, const GammaDistribution<double>&
  variancePrior) :
  mMeanPosterior(meanPrior),
  mVariancePosterior(variancePrior),
  mNumPoints(0),
  mValid(false) {
}

EstimatorBayes<NormalDistribution<1> >::EstimatorBayes(const
  EstimatorBayes<NormalDistribution<1> >& other) :
  mMeanPosterior(other.mMeanPosterior),
  mVariancePosterior(other.mVariancePosterior),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

EstimatorBayes<NormalDistribution<1> >&
  EstimatorBayes<NormalDistribution<1> >::operator =
  (const EstimatorBayes<NormalDistribution<1> >& other) {
  if (this != &other) {
    mMeanPosterior = other.mMeanPosterior;
    mVariancePosterior = other.mVariancePosterior;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

EstimatorBayes<NormalDistribution<1> >::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<NormalDistribution<1> >::read(std::istream& stream) {
}

void EstimatorBayes<NormalDistribution<1> >::write(std::ostream& stream) const {
  stream << "mean posterior: " << std::endl << mMeanPosterior << std::endl
    << "variance posterior: " << std::endl << mVariancePosterior << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

void EstimatorBayes<NormalDistribution<1> >::read(std::ifstream& stream) {
}

void EstimatorBayes<NormalDistribution<1> >::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t EstimatorBayes<NormalDistribution<1> >::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorBayes<NormalDistribution<1> >::getValid() const {
  return mValid;
}

void EstimatorBayes<NormalDistribution<1> >::addPoint(double point) {
}

void EstimatorBayes<NormalDistribution<1> >::addPoints(const
  std::vector<double>& points) {
}
