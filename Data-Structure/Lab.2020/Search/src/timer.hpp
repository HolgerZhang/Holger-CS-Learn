// Project: Sort  File: Timer
// Created by holger on 2020/12/14.

#ifndef SORT_TIMER_HPP_
#define SORT_TIMER_HPP_

#include <iostream>
#include <ctime>

/**
 * Timer Class
 */
class Time {
 public:
  Time() {
    time_ = std::clock();
  }
  double runtime() const {
    return (double) (std::clock() - time_) / CLOCKS_PER_SEC;
  }
 private:
  std::clock_t time_;
};

#endif //SORT_TIMER_HPP_
