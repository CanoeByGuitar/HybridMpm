//
// Created by chenhuiwang on 2024/1/5.
//

#ifndef HYBRIDMPM_DEF_H
#define HYBRIDMPM_DEF_H

#include "ds.h"
#include <Eigen/Dense>
#include <array>

using vec2  = Eigen::Vector2f;
using vec3  = Eigen::Vector3f;
using mat2  = Eigen::Matrix2f;
using mat3  = Eigen::Matrix3f;
using vec2i = Eigen::Vector2i;

class Particles : public DataManager {
public:
  DataArray<float>* Mass;
  DataArray<vec2>*  X;
  DataArray<vec2>*  V;

  Particles(std::vector<float>&& mass, std::vector<vec2>&& pos, std::vector<vec2>&& vel) {
    Add<float>("m", std::move(mass));
    Add<vec2>("X", std::move(pos));
    Add<vec2>("V", std::move(vel));
    Mass = GetPointer<float>("mass");
    X    = GetPointer<vec2>("X");
    V    = GetPointer<vec2>("V");
  }
};


struct GridState {
  vec2  v;
  float m;
  vec2  new_v;

  GridState() {
    v     = vec2::Zero();
    m     = 0.f;
    new_v = vec2::Zero();
  }
};

inline vec3 CalcQuadratic(float o, float x) {
  float d0 = x - o;
  float d1 = d0 - 1;
  float d2 = 1 - d1;
  return vec3{0.5f * (1.5f - d0) * (1.5f - d0), 0.75f - d1 * d1, 0.5f * (1.5f - d2) * (1.5f - d2)};
}

inline vec3 CalcQuadraticGrad(float o, float x){
  // todo: test
  float d0 = x - o;
  float d1 = d0 - 1;
  float d2 = 1 - d1;
  return vec3{
    1.5f - d0,
    -2.f * d1,
    d2 - 1.5f
  };
}

/// given x: particle position / dx , x can affect 3 grid nodes(quadratic interpolation)
/// output
/// base_node:
/// w:
/// dw:
inline void ComputeBSplineWeights(const vec2& x, std::array<int, 2>& base_node,
                                  std::array<vec3, 2>& w, std::array<vec3, 2>& dw) {

  for (int i = 0; i < 2; i++) {
    base_node[i] = (int)(x[i] - 0.5);
  }

  for (int i = 0; i < 2; i++) {
    w[i] = CalcQuadratic((float)base_node[i], x[i]);
  }

  for (int i = 0; i < 2; i++){
    dw[i] = CalcQuadraticGrad((float)base_node[i], x[i]);
  }
}

class MpmGrid {
public:
  float                  dx = 0.f;
  size_t                 w = 0, h = 0;
  std::vector<GridState> grid;

  MpmGrid(float dx, size_t w, size_t h)
    : dx(dx)
    , w(w)
    , h(h) {
    grid.resize(w * h);
  }

  GridState& operator()(size_t i, size_t j) { return grid[i * h + j]; }
};





#endif   // HYBRIDMPM_DEF_H
