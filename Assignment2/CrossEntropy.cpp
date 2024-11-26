/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   CrossEntropy.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"

#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction) : ILossLayer(reduction) {}

CrossEntropy::CrossEntropy(const CrossEntropy& orig) : ILossLayer(orig) {}

CrossEntropy::~CrossEntropy() {}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t) {
  // Todo CODE YOUR
  m_aYtarget = t;
  m_aCached_Ypred = X;
  //cout<<"CE forward"<<endl;
  double ans = -1;
  ans = cross_entropy(X, t);
  return ans;
}

xt::xarray<double> CrossEntropy::backward() {
    int Norm = m_aYtarget.shape()[0];
    xt::xarray<double> results =  -m_aYtarget/(m_aCached_Ypred + 1e-7);
    //cout<<"CE backward: "<<xt::adapt(results.shape())<<endl;
    return results;
}
