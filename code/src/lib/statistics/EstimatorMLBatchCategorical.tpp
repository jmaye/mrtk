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
/* Methods                                                                    */
/******************************************************************************/

template <size_t M>
void EstimatorMLBatch<CategoricalDistribution<M>, M>::estimate(
  CategoricalDistribution<M>& dist, const
  std::vector<Eigen::Matrix<size_t, M, 1> >& points) {
  if (points.size()) {
    Eigen::Matrix<double, M, 1> successProbabilities =
      Eigen::Matrix<double, M, 1>::Zero();
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = 0; j < M; ++j)
        successProbabilities(j) += points[i](j);
    }
    successProbabilities /= points.size();
    dist.setSuccessProbabilities(successProbabilities);
  }
}
