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

template <size_t M>
EstimatorML<NormalDistribution<1> >::EstimatorML() :
  mMean(0),
  mVariance(0),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorML<NormalDistribution<1> >::EstimatorML(const
  EstimatorML<NormalDistribution<1> >& other) :
  mMean(other.mMean),
  mVariance(other.mVariance),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorML<NormalDistribution<1> >&
  EstimatorML<NormalDistribution<1> >::operator =
  (const EstimatorML<NormalDistribution<1> >& other) {
  if (this != &other) {
    mMean = other.mMean;
    mVariance = other.mVariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorML<NormalDistribution<1> >::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<NormalDistribution<1> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<NormalDistribution<1> >::write(std::ostream& stream)
  const {
  stream << "mean: " << mMean << std::endl
    << "variance: " << mVariance << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<NormalDistribution<1> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<NormalDistribution<1> >::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<NormalDistribution<1> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<NormalDistribution<1> >::getValid() const {
  return mValid;
}

template <size_t M>
double EstimatorML<NormalDistribution<1> >::getMean() const {
  return mMean;
}

template <size_t M>
double EstimatorML<NormalDistribution<1> >::getVariance() const {
  return mVariance;
}

template <size_t M>
void EstimatorML<NormalDistribution<1> >::reset() {
  mNumPoints = 0;
  mValid = false;
  mMean = 0;
  mVariance = 0;
}

template <size_t M>
void EstimatorML<NormalDistribution<1> >::addPoint(double point) {
  mNumPoints++;
  if (mNumPoints == 1)
    mMean = point;
  else {
    mMean += 1.0 / mNumPoints * (point - mean);
    mValid = true;
  }
  mVariance += 1.0 / mNumPoints * ((point - mean) * (point - mean) - variance);
  if (variance == 0.0)
    mValid = false;
}

template <size_t M>
void EstimatorML<NormalDistribution<1> >::addPoints(const std::vector<double>&
  points) {
  for (size_t i = 0; i < points.size(); ++i)
    addPoint(points[i]);
}
