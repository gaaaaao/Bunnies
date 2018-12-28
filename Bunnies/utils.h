#pragma once
#include <chrono>
#include <thread>

typedef std::chrono::system_clock Time;
typedef std::chrono::milliseconds Ms;
typedef std::chrono::duration<double> dsec;

void sleep(long long ms);
