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

#include <RInside.h>

#include "statistics/Randomizer.h"
#include "functions/LogSumExpFunction.h"
#include "statistics/BetaDistribution.h"
#include "statistics/BernoulliDistribution.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename C, size_t M>
EstimatorBayes<MixtureDistribution<C, M>, typename ConjugatePrior<C>::Result>::
    EstimatorBayes(const DirichletDistribution<M>& dirPrior, const typename
    ConjugatePrior<C>::Result& compPrior, size_t maxNumIter) :
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
const Eigen::Matrix<int, Eigen::Dynamic, 1>&
    EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::getAssignments() const {
  return mAssignments;
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPointsR(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  // TODO: PASS THE PRIOR PARAMETERS DOWN TO GNU-R
  // TODO: OUTPUT COMPONENTS PARAMETERS
  const size_t numPoints = itEnd - itStart;
  const size_t K = mDirPrior.getAlpha().size();
  const size_t dim = Traits::template getDim<Point, true>(*itStart);
  RInside R;
  Rcpp::NumericMatrix data(numPoints, dim);
  for (auto it = itStart; it != itEnd; ++it)
    for (size_t i = 0; i < dim; ++i)
      data(it - itStart, i) = Traits::template getData<Point, true>(*it, i);
  R["x"] = data;
  R["iter"] = mMaxNumIter;
  R["K"] = K;
  std::string expression = "library('bayesm');\
    Data=list(y=x);\
    Prior=list(ncomp=K);\
    Mcmc=list(R=iter,keep=1);\
    out=rnmixGibbs(Data=Data,Prior=Prior,Mcmc=Mcmc);\
    out$nmix$zdraw[iter,]";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector out(ans);
  mAssignments.resize(numPoints);
  for (auto it = itStart; it != itEnd; ++it)
    mAssignments(it - itStart) = out(it - itStart);
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  const size_t numPoints = itEnd - itStart;
  const size_t K = mDirPrior.getAlpha().size();
  mAssignments.resize(numPoints);
  Eigen::Matrix<double, M, 1> numPointsComp =
    Eigen::Matrix<double, M, 1>::Zero(K);
  typename DirichletDistribution<M>::RandomVariable p = mDirPrior.getSample();
  const static Randomizer<double, M> randomizer;
  for (auto it = itStart; it != itEnd; ++it) {
    const size_t row = it - itStart;
    mAssignments(row) = randomizer.sampleCategorical(p);
    numPointsComp(mAssignments(row))++;
  }
  std::vector<EstimatorBayes<C> > estComp;
  estComp.reserve(K);
  for (size_t i = 0; i < K; ++i)
    estComp.push_back(EstimatorBayes<C>(mCompPrior));
  std::vector<typename ConjugatePrior<C>::Result::RandomVariable> components;
  components.reserve(K);
  for (size_t i = 0; i < K; ++i)
    components.push_back(estComp[i].getDist().getSample());
  std::vector<C> compDist;
  compDist.reserve(K);
  for (size_t i = 0; i < K; ++i)
    compDist.push_back(C(components[i]));
  size_t numIter = 0;
  const LogSumExpFunction<double, M> lse;
  Eigen::Matrix<double, M, 1> logProbabilities(K);
  while (numIter != mMaxNumIter) {
    for (size_t i = 0; i < K; ++i)
      estComp[i] = EstimatorBayes<C>(mCompPrior);
    for (auto it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      estComp[mAssignments(row)].addPoint(*it);
    }
    for (size_t i = 0; i < K; ++i) {
      components[i] = estComp[i].getDist().getSample();
      compDist[i] = C(components[i]);
    }
    for (auto it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      numPointsComp(mAssignments(row))--;
      for (size_t i = 0; i < K; ++i)
        logProbabilities(i) = log(p(i)) + compDist[i].logpdf(*it);
      const double lseProb = lse(logProbabilities);
      const size_t assignment = randomizer.sampleCategorical(
        (logProbabilities.cwise() - lseProb).cwise().exp());
      numPointsComp(assignment)++;
      mAssignments(row) = assignment;
    }
    p = DirichletDistribution<M>(mDirPrior.getAlpha() + numPointsComp).
      getSample();
    numIter++;
  }
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPointsDPR(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  // TODO: PASS THE PRIOR PARAMETERS DOWN TO GNU-R
  // TODO: OUTPUT COMPONENTS PARAMETERS
  const size_t numPoints = itEnd - itStart;
  const size_t K = mDirPrior.getAlpha().size();
  const size_t dim = Traits::template getDim<Point, true>(*itStart);
  RInside R;
  Rcpp::NumericMatrix data(numPoints, dim);
  for (auto it = itStart; it != itEnd; ++it)
    for (size_t i = 0; i < dim; ++i)
      data(it - itStart, i) = Traits::template getData<Point, true>(*it, i);
  R["x"] = data;
  R["iter"] = mMaxNumIter;
  R["K"] = K;
  std::string expression = "library('bayesm');\
    Data=list(y=x);\
    Prioralpha=list(Istarmin=1,Istarmax=10,power=.8);\
    Prior=list(Prioralpha=Prioralpha);\
    Mcmc=list(R=iter,keep=1,maxuniq=200);\
    out=rDPGibbs(Data=Data,Prior=Prior,Mcmc=Mcmc);\
    out$nmix$zdraw[iter,]";
  SEXP ans = R.parseEval(expression);
  Rcpp::NumericVector out(ans);
  mAssignments.resize(numPoints);
  for (auto it = itStart; it != itEnd; ++it)
    mAssignments(it - itStart) = out(it - itStart);
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPointsDP(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  const size_t numPoints = itEnd - itStart;
  mAssignments = Eigen::Matrix<int, Eigen::Dynamic, 1>::Zero(numPoints);
  std::vector<size_t> numPointsComp(1, numPoints);
  std::vector<EstimatorBayes<C> > estComp;
  estComp.push_back(EstimatorBayes<C>(mCompPrior));
  std::vector<typename ConjugatePrior<C>::Result::RandomVariable> components;
  components.push_back(mCompPrior.getSample());
  std::vector<C> compDist;
  compDist.push_back(C(components[0]));
  const static Randomizer<double, Eigen::Dynamic> randomizer;
  const LogSumExpFunction<double, Eigen::Dynamic> lse;
  size_t K = 1;
  double alpha = 1.0;
  size_t numIter = 0;
  while (numIter != mMaxNumIter) {
    std::cout << "numIter: " << numIter << std::endl;
    std::cout << "K: " << K << std::endl;
    std::cout << "alpha: " << alpha << std::endl;
    for (auto it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      numPointsComp[mAssignments(row)]--;
      if (numPointsComp[mAssignments(row)] == 0) {
        numPointsComp.erase(numPointsComp.begin() + mAssignments(row));
        estComp.erase(estComp.begin() + mAssignments(row));
        components.erase(components.begin() + mAssignments(row));
        compDist.erase(compDist.begin() + mAssignments(row));
        for (size_t i = 0; i < numPoints; ++i)
          if (mAssignments(i) > mAssignments(row))
            mAssignments(i)--;
        K--;
      }
      Eigen::Matrix<double, Eigen::Dynamic, 1> logProbabilities(K + 1);
      for (size_t i = 0; i < K; ++i)
        logProbabilities(i) = log(numPointsComp[i]) + compDist[i].logpdf(*it);
      EstimatorBayes<C> estCompNew(mCompPrior);
      typename ConjugatePrior<C>::Result::RandomVariable compNew =
        mCompPrior.getSample();
      C compNewDist = C(compNew);
      logProbabilities(K) = log(alpha) + compNewDist.logpdf(*it);
      const double lseProb = lse(logProbabilities);
      const size_t assignment = randomizer.sampleCategorical(
        (logProbabilities.cwise() - lseProb).cwise().exp());
      if (assignment == K) {
        estComp.push_back(estCompNew);
        components.push_back(compNew);
        compDist.push_back(compNewDist);
        numPointsComp.push_back(1);
        K++;
      }
      else
        numPointsComp[assignment]++;
      mAssignments(row) = assignment;
    }
    for (size_t i = 0; i < K; ++i)
      estComp[i] = EstimatorBayes<C>(mCompPrior);
    for (auto it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      estComp[mAssignments(row)].addPoint(*it);
    }
    for (size_t i = 0; i < K; ++i) {
      components[i] = estComp[i].getDist().getSample();
      compDist[i] = C(components[i]);
    }
//    const double nu = BetaDistribution(alpha + 1, numPoints).getSample()(0);
//    const double a = 1;
//    const double b = 2;
//    const double pi = (a + K - 1) / (a + K - 1 + numPoints * (b - log(nu)));
//    const size_t comp = BernoulliDistribution(pi).getSample()(0);
//    if (comp)
//      alpha = randomizer.sampleGamma(a + K, b - log(nu));
//    else
//      alpha = randomizer.sampleGamma(a + K - 1, b - log(nu));
    numIter++;
  }
}

template <typename C, size_t M>
void EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}

template <typename C, size_t M>
template <typename Z, typename IsNumeric<Z>::Result::Numeric>
size_t EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::Traits::getDim(const typename
    C::RandomVariable& point) {
  return 1;
}

template <typename C, size_t M>
template <typename Z, typename IsNumeric<Z>::Result::Numeric>
typename C::DomainType EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::Traits::getData(const typename
    C::RandomVariable& point, size_t idx) {
  return point;
}

template <typename C, size_t M>
template <typename Z,
  typename Not<typename IsNumeric<Z>::Result>::Result::Numeric>
size_t EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::Traits::getDim(const typename
    C::RandomVariable& point) {
  return point.size();
}

template <typename C, size_t M>
template <typename Z,
  typename Not<typename IsNumeric<Z>::Result>::Result::Numeric>
typename C::DomainType EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result>::Traits::getData(const typename
    C::RandomVariable& point, size_t idx) {
  return point(idx);
}
