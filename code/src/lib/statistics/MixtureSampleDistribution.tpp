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

#include "statistics/Randomizer.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename D, size_t M>
MixtureSampleDistribution<D, M>::MixtureSampleDistribution(const std::vector<D>&
    compDistributions, const CategoricalDistribution<M> assignDistribution) :
    MixtureDistribution<D, M>(compDistributions, assignDistribution) {
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
typename MixtureSampleDistribution<D, M>::RandomVariable
    MixtureSampleDistribution<D, M>::getSample() const {
  const static Randomizer<double, M> randomizer;
  return this->mCompDistributions[randomizer.sampleCategorical(
    this->mAssignDistribution.getSuccessProbabilities())].getSample();
}

template <typename D, size_t M>
void MixtureSampleDistribution<D, M>::getSamples(std::vector<RandomVariable>&
    samples, size_t numSamples) const {
  samples.clear();
  samples.reserve(numSamples);
  for (size_t i = 0; i < numSamples; ++i)
    samples.push_back(getSample());
}
