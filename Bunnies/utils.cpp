#include "pch.h"
#include "utils.h"

void sleep(long long ms){ std::this_thread::sleep_for(Ms(ms)); }

void sleep_util(std::chrono::time_point<std::chrono::system_clock> start, double dur)
{
	dsec pass = Time::now() - start;
	dsec remain = dsec(dur) - pass;
	sleep(std::max(std::chrono::duration_cast<Ms>(remain).count(), 0ll));
}