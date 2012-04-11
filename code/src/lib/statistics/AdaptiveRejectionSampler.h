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

/** \file AdaptiveRejectionSampler.h
    \brief This file defines the AdaptiveRejectionSampler namespace, which
           implements adaptive rejection sampling
  */

#ifndef ADAPTIVEREJECTIONSAMPLER_H
#define ADAPTIVEREJECTIONSAMPLER_H

#include <vector>

#include "functions/Function.h"
#include "statistics/SampleDistribution.h"

/** The AdaptiveRejectionSampler namespace implements adaptive rejection
    sampling.
    \brief Adaptive rejection sampler
  */
namespace AdaptiveRejectionSampler {
  /** \name Methods
    @{
    */
  /// Access a sample drawn from the distribution
  template <typename Y, typename X>
  static X getSample(const Function<Y, X>& logpdf, const Function<Y, X>&
    logpdfprime, const std::vector<X>& initPoints);
  /// Access samples drawn from the distribution
  template <typename Y, typename X>
  static void getSamples(const Function<Y, X>& logpdf, const Function<Y, X>&
    logpdfprime, const std::vector<X>& initPoints, std::vector<X>& samples,
    size_t numSamples);
  /** @}
    */

};

#include "statistics/AdaptiveRejectionSampler.tpp"

#endif // ADAPTIVEREJECTIONSAMPLER_H
