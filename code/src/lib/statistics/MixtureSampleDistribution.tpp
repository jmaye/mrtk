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

template <typename D, size_t M>
MixtureSampleDistribution<D, M>::MixtureSampleDistribution(const std::vector<D>&
  distributions, const CategoricalDistribution<M> weights) :
  MixtureDistribution<D, M>(distributions, weights) {
}

template <typename D, size_t M>
MixtureSampleDistribution<D, M>::MixtureSampleDistribution(const
  MixtureSampleDistribution<D, M>& other) :
  MixtureDistribution<D, M>(other) {
}

template <typename D, size_t M>
MixtureSampleDistribution<D, M>& MixtureSampleDistribution<D, M>::operator =
  (const MixtureSampleDistribution<D, M>& other) {
  if (this != &other) {
    this->MixtureDistribution<D, M>::operator=(other);
  }
  return *this;
}

template <typename D, size_t M>
MixtureSampleDistribution<D, M>::~MixtureSampleDistribution() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename D, size_t M>
typename MixtureSampleDistribution<D, M>::VariableType
  MixtureSampleDistribution<D, M>::getSample() const {
  Eigen::Matrix<size_t, M, 1> component = this->mWeights.getSample();
  for (size_t i = 0; i < M; ++i) {
    if (component(i) == 1)
      return this->mDistributions[i].getSample();
  }
  return this->mDistributions[0].getSample();
}

template <typename D, size_t M>
void MixtureSampleDistribution<D, M>::getSamples(std::vector<VariableType>&
  samples, size_t numSamples) const {
  samples.clear();
  for (size_t i = 0; i < numSamples; ++i)
    samples.push_back(getSample());
}