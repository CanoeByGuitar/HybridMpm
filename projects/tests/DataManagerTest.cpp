//
// Created by ChenhuiWang on 2024/2/27.

// Copyright (c) 2024 Tencent. All rights reserved.
//

#include <datastructure/DataManager.h>
#include <Eigen/Core>

using DATA::DataManager;
using DATA::AttributeName;

using Mat3 = Eigen::Matrix3f;
using Vec3 = Eigen::Vector3f;
int main() {
    /// Ranges
    Range r1 {1, 2};
    Range r2 {4, 5};
    std::cout << r1 << "\n" << r2 << "\n";

    /// Disjoint Ranges
    Range r3 {1, 2};
    Range r4 {2, 5};
    DisjointRanges dr1({r1, r2});
    DisjointRanges dr2({r3, r4});
    std::cout << dr1.ToString() << "\n" << dr2.ToString() << "\n";
    Range r5 {9, 12};
    dr2.Append(r5);
    std::cout << dr2.ToString() << "\n";

    /// DataManager
    std::vector<Mat3>  matVec(3, Mat3::Identity());
    std::vector<Vec3>  vec3Vec(3, Vec3::Zero());
    std::vector<float> floatVec(3, 1.0f);

    DataManager dm;
    dm.Add(AttributeName<Mat3>("F"), Range(0, 3), std::move(matVec));
    dm.Add(AttributeName<Vec3>("V"), Range(3, 6), std::move(vec3Vec));
    dm.Add(AttributeName<float>("M"), Range(6, 9), std::move(floatVec));

    auto F_scratch = dm.Get(AttributeName<Mat3>("F"));
    auto V_scratch = dm.Get(AttributeName<Vec3>("V"));
    auto M_scratch = dm.Get(AttributeName<float>("M"));

    for(auto iter = M_scratch.Iter(); iter ; iter++){
        *iter = (float)iter.EntryId();
    }

    for(int i = 0; i < 9; i++) {
        const float* vptr = M_scratch.GetValue(i);
        if (vptr) {
            std::cout << *vptr;
        } else {
            std::cout << "N";
        }
    }
    std::cout << "\n";

    std::cout << "ok";
}