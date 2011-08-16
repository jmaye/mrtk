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

void EstimatorMLBatch<NormalDistribution<1> >::estimate(NormalDistribution<1>&
  dist, const std::vector<NormalDistribution<1>::VariableType>&
  points) {
  if (points.size()) {
    Eigen::Map<Eigen::VectorXd> dataMapped(&points[0], points.size());
    double mean = dataMapped.sum() / points.size();
    double variance = (dataMapped.cwise() - mean).cwise().square().sum() /
      points.size();
    dist.setMean(mean);
    dist.setVariance(variance);
  }
}
