//
// Created by chenhui on 24-1-15.
//

#ifndef HYBRIDMPM_LOG_H
#define HYBRIDMPM_LOG_H


#include <spdlog/spdlog.h>

template<typename... Ts>
[[noreturn]] inline void AssertionFailed(const char* function, const char* file, unsigned int line,
                                         const char* condition, Ts&&... messages) {
  spdlog::error("In file: {} : {} \n In function {} : {} \ncondition: {}",
                file,
                line,
                function,
                std::forward<Ts>(messages)...,
                condition);
  throw std::runtime_error("Assertion failed");
}

[[noreturn]] inline void AssertionFailed(const char* function, const char* file, unsigned int line,
                                         const char* condition) {
  AssertionFailed(function, file, line, condition, "Assertion failed");
}

/**
   Throws a std::runtime_error when the condition is false.
   First parameter is an expression that evaluates to a boolean.
   Second parameter is optional. It can be a string description of the error.
   Use it as follows:
      int t=3;
      ZIRAN_ASSERT(t>4,"t should be greater than 4");
*/
#define MPM_ASSERT(condition, ...)                                                               \
  do {                                                                                           \
    if (condition) {                                                                             \
                                                                                                 \
    } else {                                                                                     \
      AssertionFailed((const char*)__FUNCTION__, __FILE__, __LINE__, #condition, ##__VA_ARGS__); \
    }                                                                                            \
  } while (false)



#endif   // HYBRIDMPM_LOG_H
