/******************************************************************
 __     __    _     _       __    _      _   __
/ /`_  / /\  | |   \ \  /  / /\  | |\ | | | / /`
\_\_/ /_/--\ |_|__  \_\/  /_/--\ |_| \| |_| \_\_,

 Copyright (c) 2020 H. Elwood Gilliland III
 This open source framework is available under the MIT License,
 see LICENSE file accompanying this file for more information
*******************************************************************/
#pragma once

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

using namespace std::chrono;

class Stopwatch {
public:
  Stopwatch() { start=0; }
  milliseconds start;
  void Start() {
   start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  }
  void Stop() {
    milliseconds stop = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::chrono::duration<double> elapsed_seconds = stop-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
  }
};
