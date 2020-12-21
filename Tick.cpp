#include <chrono>

static const std::chrono::high_resolution_clock::time_point StartTime = std::chrono::high_resolution_clock::now();

float WorldTick()
{
	std::chrono::high_resolution_clock::time_point CurrentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff =
		std::chrono::time_point_cast<std::chrono::microseconds>(CurrentTime)
		- std::chrono::time_point_cast<std::chrono::microseconds>(StartTime);
	//std::chrono::duration<double> diff = CurrentTime.time_since_epoch() - StartTime.time_since_epoch();
	float Tick = diff.count();
	return Tick;
};