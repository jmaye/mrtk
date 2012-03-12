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
EstimatorBayes<MixtureDistribution<C, M>, typename ConjugatePrior<C>::Result>::
    EstimatorBayes(const DirichletDistribution<M>& dirPrior, const
    std::vector<typename ConjugatePrior<C>::Result>& compPrior, size_t
    maxNumIter) :
    mDirPrior(dirPrior),
    mCompPrior(compPrior),
    mMaxNumIter(maxNumIter) {
}

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M>, typename ConjugatePrior<C>::Result>::
    EstimatorBayes(const EstimatorBayes& other) :
    mDirPrior(other.mDirPrior),
    mCompPrior(other.mCompPrior),
    mMaxNumIter(other.mMaxNumIter) {
}

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M>, typename ConjugatePrior<C>::Result>&
    EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::operator = (const EstimatorBayes&
    other) {
  if (this != &other) {
    mDirPrior = other.mDirPrior;
    mCompPrior = other.mCompPrior;
    mMaxNumIter = other.mMaxNumIter;
  }
  return *this;
}

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M>, typename ConjugatePrior<C>::Result>::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::read(std::istream& stream) {
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::write(std::ostream& stream) const {
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::read(std::ifstream& stream) {
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename C, size_t M>
size_t EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::getMaxNumIter() const {
  return mMaxNumIter;
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  typename DirichletDistribution<M>::RandomVariable weights =
    mDirPrior.getSample();
  std::vector<typename ConjugatePrior<C>::Result::RandomVariable>
    components;
  components.reserve(mCompPrior.size());
  for (size_t i = 0; i < mCompPrior.size(); ++i)
    components.push_back(mCompPrior[i].getSample());
  size_t numIter = 0;
  while (numIter != mMaxNumIter) {
    EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >
      estDir(mDirPrior);
    std::vector<EstimatorBayes<C> > estComp;
    estComp.reserve(mCompPrior.size());
    for (size_t i = 0; i < mCompPrior.size(); ++i)
      estComp.push_back(EstimatorBayes<C>(mCompPrior[i]));
    double newLogLikelihood = 0;
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      Eigen::Matrix<double, M, 1> probabilities(mCompPrior.size());
      for (size_t i = 0; i < mCompPrior.size(); ++i)
        probabilities(i) = weights(i) * C(std::get<0>(components[i]),
          std::get<1>(components[i]))(*it);
      newLogLikelihood += log(probabilities.sum());
      probabilities /= probabilities.sum();
      CategoricalDistribution<M> assignDist(probabilities);
      typename CategoricalDistribution<M>::RandomVariable assignment =
        assignDist.getSample();
      estDir.addPoint(assignment);
      for (size_t i = 0; i < mCompPrior.size(); ++i)
        if (assignment(i))
          estComp[i].addPoint(*it);
    }
    weights = estDir.getDist().getSample();
    for (size_t i = 0; i < mCompPrior.size(); ++i)
      components[i] = estComp[i].getDist().getSample();
    std::cout << "weights: " << weights.transpose() << std::endl;
    for (size_t i = 0; i < mCompPrior.size(); ++i)
      std::cout << "mean: " << std::get<0>(components[i]) << " variance: "
        << std::get<1>(components[i]) << std::endl;
    numIter++;
  }
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}
