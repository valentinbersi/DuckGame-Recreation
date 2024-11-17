#include "Timer.h"

#include <chrono>
#include <thread>

Timer::Timer():
        frameTicks(std::chrono::milliseconds::zero()),
        previousFrameTicks(std::chrono::milliseconds::zero()) {}

void Timer::start() { previousFrameTicks = std::chrono::steady_clock::now(); }

std::chrono::duration<Timer::Seconds> Timer::iterationStartSeconds() {
    frameTicks = std::chrono::steady_clock::now();
    const std::chrono::duration<float> deltaTime = frameTicks - previousFrameTicks;
    return deltaTime;
}

std::chrono::milliseconds Timer::iterationStartMilliseconds() {
    frameTicks = std::chrono::steady_clock::now();
    const std::chrono::milliseconds deltaTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(frameTicks - previousFrameTicks);
    return deltaTime;
}

void Timer::iterationEnd(const u64 fps) {
    previousFrameTicks = frameTicks;
    std::this_thread::sleep_for(frameTicks + framesPerSecondToMillisecondsPerFrame(fps) -
                                std::chrono::steady_clock::now());
}
