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
#include "statistics/MultinomialDistribution.h"
#include "statistics/BetaDistribution.h"
#include "statistics/GammaDistribution.h"

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
    typename ConjugatePrior<C>::Result>::addPoints1(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  const size_t numPoints = itEnd - itStart;
  const size_t K = mCompPrior.size();
  Eigen::Matrix<int, Eigen::Dynamic, 1> assignments(numPoints);
  typename DirichletDistribution<M>::RandomVariable weights =
    mDirPrior.getSample();
  const static Randomizer<double, M> randomizer;
  for (size_t i = 0; i < numPoints; ++i)
    assignments(i) = randomizer.sampleCategorical(weights);
  std::vector<typename ConjugatePrior<C>::Result::RandomVariable>
    components;
  components.reserve(K);
  for (size_t i = 0; i < K; ++i)
    components.push_back(mCompPrior[i].getSample());
  EstimatorBayes<CategoricalDistribution<M> > estDir(mDirPrior);
  std::vector<EstimatorBayes<C> > estComp;
  estComp.reserve(K);
  for (size_t i = 0; i < K; ++i)
    estComp.push_back(EstimatorBayes<C>(mCompPrior[i]));
  size_t numIter = 0;
  while (numIter != mMaxNumIter) {
    estDir = EstimatorBayes<CategoricalDistribution<M> >(mDirPrior);
    for (size_t i = 0; i < K; ++i)
      estComp[i] = EstimatorBayes<C>(mCompPrior[i]);
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      Eigen::Matrix<double, M, 1> probabilities(K);
      for (size_t i = 0; i < K; ++i)
        probabilities(i) = weights(i) * C(components[i])(*it);
      probabilities /= probabilities.sum();
      const size_t assignment = randomizer.sampleCategorical(probabilities);
      assignments(row) = assignment;
    }
    typename MultinomialDistribution<M>::RandomVariable numPointsComp =
      MultinomialDistribution<M>::RandomVariable::Zero(K);
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      estComp[assignments(row)].addPoint(*it);
      numPointsComp(assignments(row))++;
    }
    estDir.addPoint(numPointsComp);
    weights = estDir.getDist().getSample();
    for (size_t i = 0; i < mCompPrior.size(); ++i)
      components[i] = estComp[i].getDist().getSample();
    numIter++;
  }
  std::cout << "weights mode: " << estDir.getDist().getMode().transpose()
    << std::endl;
  std::cout << "components mode: " << std::endl;
  for (size_t i = 0; i < mCompPrior.size(); ++i)
    std::cout << "mean: " << std::get<0>(estComp[i].getDist().getMode())
      << " variance: " << std::get<1>(estComp[i].getDist().getMode())
      << std::endl;
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPoints2(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  const size_t numPoints = itEnd - itStart;
  const size_t K = mCompPrior.size();
  Eigen::Matrix<double, M, 1> numPointsComp =
    Eigen::Matrix<double, M, 1>::Zero(K);
  Eigen::Matrix<int, Eigen::Dynamic, 1> assignments(numPoints);
  Eigen::Matrix<double, M, 1> probabilities = mDirPrior.getSample();
  const static Randomizer<double, M> randomizer;
  for (size_t i = 0; i < numPoints; ++i) {
    assignments(i) = randomizer.sampleCategorical(probabilities);
    numPointsComp(assignments(i))++;
  }
  std::vector<EstimatorBayes<C> > estComp;
  estComp.reserve(K);
  for (size_t i = 0; i < K; ++i)
    estComp.push_back(EstimatorBayes<C>(mCompPrior[i]));
  const double alpha = 1.0;
  size_t numIter = 0;
  while (numIter != mMaxNumIter) {
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      numPointsComp(assignments(row))--;
      Eigen::Matrix<double, M, 1> probabilities(K);
      for (size_t i = 0; i < K; ++i)
        probabilities(i) = (numPointsComp(i) + alpha / K) *
          estComp[i].getPredDist()(*it);
      probabilities /= probabilities.sum();
      const size_t assignment = randomizer.sampleCategorical(probabilities);
      numPointsComp(assignment)++;
      assignments(row) = assignment;
    }
    for (size_t i = 0; i < K; ++i)
      estComp[i] = EstimatorBayes<C>(mCompPrior[i]);
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      estComp[assignments[row]].addPoint(*it);
    }
    numIter++;
  }
  std::cout << "weights mode: " << (numPointsComp / numPoints).transpose()
    << std::endl;
  std::cout << "components mode: " << std::endl;
  for (size_t i = 0; i < mCompPrior.size(); ++i)
    std::cout << "mean: " << std::get<0>(estComp[i].getDist().getMode())
      << " variance: " << std::get<1>(estComp[i].getDist().getMode())
      << std::endl;
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPoints3(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  const size_t numPoints = itEnd - itStart;
  Eigen::Matrix<int, Eigen::Dynamic, 1> assignments =
    Eigen::Matrix<int, Eigen::Dynamic, 1>::Zero(numPoints);
  double alpha = 0.5;
  const double a = 1.0;
  const double b = 1.0;
  size_t numIter = 0;
  const static Randomizer<double, Eigen::Dynamic> randomizer;
  size_t K = 0;
  std::vector<EstimatorBayes<C> > estComp;
  estComp.push_back(EstimatorBayes<C>(mCompPrior[0]));
  std::vector<size_t> numPointsComp(1, numPoints);
  while (numIter != mMaxNumIter) {
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      numPointsComp[assignments(row)]--;
      if (numPointsComp[assignments(row)] == 0) {
        numPointsComp.erase(numPointsComp.begin() + assignments(row));
        estComp.erase(estComp.begin() + assignments(row));
        for (size_t i = 0; i < numPoints; ++i)
          if (assignments(i) > assignments(row))
            assignments(i)--;
        K--;
      }
      Eigen::Matrix<double, Eigen::Dynamic, 1>
        probabilities(estComp.size() + 1);
      for (size_t i = 0; i < estComp.size(); ++i)
        probabilities(i) = numPointsComp[i] * estComp[i].getPredDist()(*it);
      EstimatorBayes<C> estCompNew(mCompPrior[0]);
      estCompNew.addPoint(*it);
      probabilities(estComp.size()) = alpha * estCompNew.getPredDist()(*it);
      probabilities /= probabilities.sum();
      const size_t assignment = randomizer.sampleCategorical(probabilities);
      if (assignment == K + 1) {
        estComp.push_back(estCompNew);
        numPointsComp.push_back(1);
        K++;
      }
      else
        numPointsComp[assignment]++;
      assignments(row) = assignment;
    }
    for (size_t i = 0; i < estComp.size(); ++i)
      estComp[i] = EstimatorBayes<C>(mCompPrior[0]);
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      estComp[assignments(row)].addPoint(*it);
    }
    const double eta = BetaDistribution(alpha + 1, numPoints).getSample()(0);
    const double pi = (a + K - 1) / (a + K - 1 + numPoints * (b - log(eta)));
    const size_t assignment =
      randomizer.sampleCategorical(Eigen::Matrix<double, 2, 1>(pi, 1 - pi));
//    if (assignment)
//      alpha = randomizer.sampleGamma(a + K, b - log(eta));
//    else
//      alpha = randomizer.sampleGamma(a + K - 1, b - log(eta));
    std::cout << "Iteration: " << numIter << " K = " << K << " alpha = "
      << alpha << std::endl;
    for (size_t i = 0; i < K; ++i)
      std::cout << "mean: " << std::get<0>(estComp[i].getDist().getMode())
        << " variance: " << std::get<1>(estComp[i].getDist().getMode())
        << " points: " << numPointsComp[i] << std::endl;
    numIter++;
  }
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}
