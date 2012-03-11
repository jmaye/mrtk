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

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M> >::EstimatorBayes(const
    DirichletDistribution<M>& dirPrior, const
    std::vector<typename ConjugatePrior<C>::Result>& compPrior, size_t
    maxNumIter) :
    mMaxNumIter(maxNumIter) {
}

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M> >::EstimatorBayes(const EstimatorBayes&
    other) :
    mMaxNumIter(other.mMaxNumIter) {
}

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M> >&
    EstimatorBayes<MixtureDistribution<C, M> >::operator = (const
    EstimatorBayes& other) {
  if (this != &other) {
    mMaxNumIter = other.mMaxNumIter;
  }
  return *this;
}

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M> >::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M> >::read(std::istream& stream) {
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M> >::write(std::ostream& stream)
    const {
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M> >::read(std::ifstream& stream) {
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M> >::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename C, size_t M>
size_t EstimatorBayes<MixtureDistribution<C, M> >::getMaxNumIter() const {
  return mMaxNumIter;
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M> >::setMaxNumIter(size_t
    maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  DirichletDistribution<M> dirPrior;
  std::vector<NormalScaledInvChiSquareDistribution> compPrior;
  compPrior.push_back(NormalScaledInvChiSquareDistribution(0, 1, 1, 1.5));
  compPrior.push_back(NormalScaledInvChiSquareDistribution(5, 1, 1, 1.7));
  compPrior.push_back(NormalScaledInvChiSquareDistribution(10, 1, 1, 1.2));
  compPrior.push_back(NormalScaledInvChiSquareDistribution(-5, 1, 1, 1.3));
  compPrior.push_back(NormalScaledInvChiSquareDistribution(-10, 1, 1, 1.5));
  typename DirichletDistribution<M>::RandomVariable weights =
    dirPrior.getSample();
  std::vector<typename NormalScaledInvChiSquareDistribution::RandomVariable>
    components;
  for (size_t i = 0; i < 5; ++i)
    components.push_back(compPrior[i].getSample());
  size_t numIter = 0;
  while (numIter != mMaxNumIter) {
    EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >
      estDir(dirPrior);
    std::vector<EstimatorBayes<NormalDistribution<>,
      NormalScaledInvChiSquareDistribution> > estComp;
    for (size_t i = 0; i < 5; ++i)
      estComp.push_back(EstimatorBayes<NormalDistribution<>,
        NormalScaledInvChiSquareDistribution>(compPrior[i]));
    double newLogLikelihood = 0;
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      Eigen::Matrix<double, 5, 1> probabilities;
      for (size_t i = 0; i < 5; ++i)
        probabilities(i) = weights(i) *
          NormalDistribution<>(std::get<0>(components[i]),
          std::get<1>(components[i]))(*it);
      newLogLikelihood += log(probabilities.sum());
      probabilities /= probabilities.sum();
      CategoricalDistribution<M> assignDist(probabilities);
      typename CategoricalDistribution<M>::RandomVariable assignment =
        assignDist.getSample();
      estDir.addPoint(assignment);
      for (size_t i = 0; i < 5; ++i)
        if (assignment(i))
          estComp[i].addPoint(*it);
    }
    std::ofstream logFile("log.txt", std::ios::app);
    logFile << newLogLikelihood << std::endl;
    weights = estDir.getProbDist().getSample();
    for (size_t i = 0; i < 5; ++i)
      components[i] = estComp[i].getMeanVarianceDist().getSample();
    std::cout << "weights: " << weights.transpose() << std::endl;
    for (size_t i = 0; i < 5; ++i)
      std::cout << "mean: " << std::get<0>(components[i]) << " variance: "
        << std::get<1>(components[i]) << std::endl;
    numIter++;
  }
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
