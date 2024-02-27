//
// Created by ChenhuiWang on 2024/2/27.

// Copyright (c) 2024 Tencent. All rights reserved.
//

#include <datastructure/DataManager.h>
#include <Eigen/Core>

using DATA::DataManager;

int main(){
    using Mat3 = Eigen::Matrix3f;
    using Vec3 = Eigen::Vector3f;

    std::vector<Mat3> matVec(100);
    DataArray<Mat3> F("F", Range(0, 100), std::move(matVec));
}