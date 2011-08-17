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
void EstimatorML<LinearRegression<M>, M>::estimate(LinearRegression<M>&
  dist, const std::vector<Eigen::Matrix<double, M, 1> >& points, double tol)
  throw (InvalidOperationException) {
  if (points.size()) {
    Eigen::Matrix<double, Eigen::Dynamic, 1> targets(points.size());
    Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(points.size(),
      (int)M);
    for (size_t i = 0; i < points.size(); ++i) {
      targets(i) = points[i](M - 1);
      designMatrix(i, 0) = 1.0;
      designMatrix.row(i).segment(1, M - 1) = points[i].segment(0, M - 1);
    }
    Eigen::Matrix<double, M, M> invCheckMatrix =
      designMatrix.transpose() * designMatrix;
    if (points.size() < M || invCheckMatrix.determinant() < tol)
      throw InvalidOperationException("EstimatorML<LinearRegression<M>, M>::estimate(): data cannot be fitted");
    Eigen::Matrix<double, M, 1> coefficients = invCheckMatrix.inverse() *
      designMatrix.transpose() * targets;
    double variance = 0.0;
    for (size_t i = 0; i < points.size(); ++i)
      variance += (targets(i) - (coefficients.transpose() *
        designMatrix.row(i).transpose())(0)) * (targets(i) -
        (coefficients.transpose() * designMatrix.row(i).transpose())(0));
    variance /= points.size();
    dist.setCoefficients(coefficients);
    dist.setVariance(variance);
  }
}
