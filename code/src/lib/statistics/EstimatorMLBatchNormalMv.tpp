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
void EstimatorMLBatch<NormalDistribution<M>, M>::estimate(NormalDistribution<M>&
  dist, const std::vector<typename NormalDistribution<M>::VariableType>&
  points) {
  if (points.size()) {
    Eigen::Matrix<double, M, 1> mean = Eigen::Matrix<double, M, 1>::Zero();
    for (size_t i = 0; i < points.size(); ++i)
      mean += points[i];
    mean /= points.size();
    Eigen::Matrix<double, M, M> covariance =
      Eigen::Matrix<double, M, M>::Zero();
    for (size_t i = 0; i < points.size(); ++i)
      covariance += (points[i] - mean) * (points[i] - mean).transpose();
    covariance /= points.size();
    dist.setMean(mean);
    dist.setCovariance(covariance);
  }
}
