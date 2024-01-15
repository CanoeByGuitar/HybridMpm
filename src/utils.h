//
// Created by chenhuiwang on 2024/1/5.
//

#ifndef HYBRIDMPM_UTILS_H
#define HYBRIDMPM_UTILS_H

#include <iostream>

#define MPM_ASSERT(condition, message)                                                 \
  do {                                                                                 \
    if (!(condition)) {                                                                \
      std::cerr << "Assertion failed: " << #condition << ", " << message << std::endl; \
      std::abort();                                                                    \
    }                                                                                  \
  } while (false)
#endif   // HYBRIDMPM_UTILS_H
