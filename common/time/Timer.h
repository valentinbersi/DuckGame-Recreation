#pragma once

#include <chrono>

#include "Types.h"

class Timer {
    constexpr static u32 MILLISECONDS_IN_SECOND = 1000;

    std::chrono::steady_clock::time_point frameTicks;
    std::chrono::steady_clock::time_point previousFrameTicks;

public:
    using Milliseconds = i64;
    using Seconds = float;

    Timer();

    /**
     * Start the clock
     */
    void start();

    /**
     * Calculates the time since the last call to this method and returns it in seconds. Should be
     * called every new iteration of a game loop.
     * @return the time elapsed since the last iteration and the current one in seconds
     */
    std::chrono::duration<Seconds> iterationStartSeconds();

    /**
     * Calculates the time since the last call to this method and returns it in milliseconds. Should
     * be called every new iteration of a game loop.
     * @return the time elapsed since the last iteration and the current one in milliseconds
     */
    std::chrono::milliseconds iterationStartMilliseconds();

    /**
     * Sleep enough time so the game runs at the given fps
     * @param fps the fps that the game should run at
     */
    void iterationEnd(u64 fps);

    /**
     * Convert frames per second to milliseconds per frame
     * @param fps the frames per second
     * @return the milliseconds per frame
     */
    constexpr static std::chrono::milliseconds framesPerSecondToMillisecondsPerFrame(u64 fps);
};

constexpr std::chrono::milliseconds Timer::framesPerSecondToMillisecondsPerFrame(const u64 fps) {
    return std::chrono::milliseconds(MILLISECONDS_IN_SECOND / fps);
}
