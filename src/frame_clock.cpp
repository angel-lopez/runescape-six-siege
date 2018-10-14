#include <chrono>

#if !defined(FRAME_CLOCK)
#define FRAME_CLOCK

using namespace std::chrono;

class FrameClock
{
private:
  high_resolution_clock::time_point lastFrameTime;
  high_resolution_clock::time_point currentTime;
  high_resolution_clock::time_point measureCurrentTime();
  high_resolution_clock::duration getElapsedFrameTime();
  int getElapsedFrameTimeInMicroSeconds();
  double getElapsedFrameTimeInSeconds();
public:
  FrameClock();
  ~FrameClock();
  double measureFrameTimeInSeconds();
};

FrameClock::FrameClock()
{
  lastFrameTime = measureCurrentTime();
}

FrameClock::~FrameClock()
{
}

high_resolution_clock::time_point FrameClock::measureCurrentTime()
{
  currentTime = std::chrono::high_resolution_clock::now();
  return currentTime;
}

high_resolution_clock::duration FrameClock::getElapsedFrameTime()
{
  return measureCurrentTime() - lastFrameTime;
}

int FrameClock::getElapsedFrameTimeInMicroSeconds()
{
  return duration_cast<std::chrono::microseconds>(getElapsedFrameTime()).count();
}

double FrameClock::getElapsedFrameTimeInSeconds()
{
  return getElapsedFrameTimeInMicroSeconds() / (double)1000000;
}

double FrameClock::measureFrameTimeInSeconds()
{
  double frameTimeInSeconds = getElapsedFrameTimeInSeconds();
  lastFrameTime = currentTime;
  return frameTimeInSeconds;
}


#endif // FRAME_CLOCK
