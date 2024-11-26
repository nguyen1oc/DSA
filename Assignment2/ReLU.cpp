/*
 * Click nbfs:nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   ReLU.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:44 PM
 */

#include "layer/ReLU.h"

#include "ann/functions.h"
#include "sformat/fmt_lib.h"

ReLU::ReLU(string name) {
  if (trim(name).size() != 0)
    m_sName = name;
  else
    m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::ReLU(const ReLU& orig) { m_sName = "ReLU_" + to_string(++m_unLayer_idx); }

ReLU::~ReLU() {}

xt::xarray<double> ReLU::forward(xt::xarray<double> X){
    m_aMask = (X >= 0);
    // cout<<"Reluforward: "<<endl;
    // cout<<"mask shaep "<<xt::adapt(m_aMask.shape())<<endl;
    // cout<<"X shaep "<<xt::adapt(X.shape())<<endl;
    return xt::where(m_aMask, X, 0.0);
}
// xt::xarray<double> ReLU::backward(xt::xarray<double> DY){
//     cout<<"in relu "<<endl;
//     return DY * m_aMask;
// }

xt::xarray<double> ReLU::backward(xt::xarray<double> DY) {
    // cout<<"Relu backward: \n";
    // cout<<"DY:" <<xt::adapt(DY.shape())<<endl;
    // cout<<"m_Amaks: "<<xt::adapt(m_aMask.shape())<<endl;

    return m_aMask * DY;
}

string ReLU::get_desc() {
  string desc = fmt::format("{:<10s}, {:<15s}:", "ReLU", this->getname());
  return desc;
}
