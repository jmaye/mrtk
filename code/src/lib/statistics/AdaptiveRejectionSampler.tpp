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

#include <algorithm>

#include "statistics/Randomizer.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename Y, typename X>
X AdaptiveRejectionSampler::getSample(const Function<Y, X>& logpdf, const
    Function<Y, X>& logpdfprime, const std::vector<X>& initPoints, const X&
    minSupport, const X& maxSupport) {
}

template <typename Y, typename X>
void AdaptiveRejectionSampler::getSamples(const Function<Y, X>& logpdf, const
    Function<Y, X>& logpdfprime, const std::vector<X>& initPoints,
    std::vector<X>& samples, size_t numSamples, const X&
    minSupport, const X& maxSupport) {
  std::vector<std::tuple<X, Y, Y> > points;
  points.reserve(initPoints.size());
  for (auto it = initPoints.begin(); it != initPoints.end(); ++it)
    points.push_back(std::tuple<X, Y, Y>(*it, logpdf(*it), logpdfprime(*it)));
  // TODO: CHECK VALIDITY CONDITIONS
  samples.clear();
  samples.reserve(numSamples);
  const static Randomizer<double> randomizer;
  while (samples.size() != numSamples) {
    std::sort(points.begin(), points.end(), TupleCompare());
    std::vector<X> z;
    z.reserve(points.size() + 1);
    std::vector<X> hu;
    hu.reserve(points.size() + 1);
    z.push_back(minSupport);
    hu.push_back(std::get<2>(points[0]) * (z[0] - std::get<0>(points[0]))
      + std::get<1>(points[0]));
    for (size_t i = 0; i < points.size(); ++i) {
      const std::tuple<X, Y, Y>& point1 = points[i];
      if (i != points.size() - 1) {
        const std::tuple<X, Y, Y>& point2 = points[i + 1];
        z.push_back(std::get<0>(point1) + (std::get<1>(point1) -
          std::get<1>(point2) + std::get<2>(point2) * (std::get<0>(point2) -
          std::get<0>(point1))) / (std::get<2>(point2) - std::get<2>(point1)));
      }
      else
        z.push_back(maxSupport);
      hu.push_back(std::get<2>(point1) * (z[i + 1] - std::get<0>(point1)) +
        std::get<1>(point1));
    }
    std::vector<X> scum;
    scum.reserve(z.size() + 1);
    scum.push_back(0);
    double cu = 0;
    for (size_t i = 0; i < z.size() - 1; ++i) {
      cu += 1.0 / std::get<2>(points[i]) * (exp(hu[i + 1]) - exp(hu[i]));
      scum.push_back(cu);
    }
    for (size_t i = 0; i < scum.size(); ++i)
      scum[i] /= cu;
    double u = randomizer.sampleUniform(0, 1);
    size_t segment = 0;
    for (size_t i = 0; i < scum.size(); ++i) {
      if (scum[i] > u)
        break;
      segment = i;
    }
    const double x = z[segment] + 1.0 / std::get<2>(points[segment]) * log(1.0 +
      std::get<2>(points[segment]) * cu * (u - scum[segment]) /
      exp(hu[segment]));
    u = randomizer.sampleUniform(0, 1);
    const double hux = std::get<2>(points[segment]) * (x -
      std::get<0>(points[segment])) + std::get<1>(points[segment]);
    if (u < exp(logpdf(x) - hux))
      samples.push_back(x);
    else
      points.push_back(std::tuple<X, Y, Y>(x, logpdf(x), logpdfprime(x)));
  }
}
