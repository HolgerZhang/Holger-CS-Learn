// Project: Sort  File: Timer
// Created by holger on 2020/12/14.

#ifndef SORT_TIMER_HPP_
#define SORT_TIMER_HPP_

#include <iostream>
#include <ctime>

/**
 * Timer Class
 */
class Timer {
 public:
  Timer() {
    time_ = std::clock();
  }

  double runtime() const {
    return (double) (std::clock() - time_) / CLOCKS_PER_SEC;
  }

  static std::string now() {
    time_t time_now;
    char buffer[80];
    std::time(&time_now);
    struct tm *info = localtime(&time_now);
    std::strftime(buffer, 80, "%Y%m%d_%H%M%S", info);
    return buffer;
  }

 private:
  std::clock_t time_;
};

#endif //SORT_TIMER_HPP_
