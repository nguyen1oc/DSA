/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt
 * to change this license Click
 * nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this
 * template
 */

/*
 * File:   Softmax.cpp
 * Author: ltsach
 *
 * Created on August 25, 2024, 2:46 PM
 */

#include "layer/Softmax.h"

#include <filesystem>  //require C++17

#include "ann/functions.h"
#include "sformat/fmt_lib.h"
namespace fs = std::filesystem;

Softmax::Softmax(int axis, string name) : m_nAxis(axis) {
  if (trim(name).size() != 0)
    m_sName = name;
  else
    m_sName = "Softmax_" + to_string(++m_unLayer_idx);
}

Softmax::Softmax(const Softmax& orig) {}

Softmax::~Softmax() {}

xt::xarray<double>Softmax::forward(xt::xarray<double> X){
    //cout<<"Softmax forward: \n";
    m_aCached_Y = softmax(X, m_nAxis);
    //cout<<"no prob dog";
    //cout<<xt::adapt(m_aCached_Y.shape())<<endl;
    return m_aCached_Y;
}

xt::xarray<double> Softmax::backward(xt::xarray<double> DY) {
    auto jacobians = diag_stack(m_aCached_Y) - outer_stack(m_aCached_Y, m_aCached_Y);
    xt::xarray<double> results = matmul_on_stack(jacobians, DY);
    //cout<<"softmax bd: Dx shaep"<<xt::adapt(results.shape())<<endl;
    return results;
}

string Softmax::get_desc() {
  string desc = fmt::format("{:<10s}, {:<15s}: {:4d}", "Softmax",
                            this->getname(), m_nAxis);
  return desc;
}
