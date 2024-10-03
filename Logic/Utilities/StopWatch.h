#include <SFML/System/Clock.hpp>
#include <memory>
#include <chrono>
//singleton
class StopWatch {
public:
    // get singleton instance
    static StopWatch& getInstance() {
        static StopWatch instance;
        return instance;
    }

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    // elapsed time in seconds
    float getElapsedTime() const {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(now - start_time);
        return elapsed.count();
    }

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

private:
    // private constructor
    StopWatch() {}

    // avoid copy and assignment
    StopWatch(const StopWatch&) = delete;
    StopWatch& operator=(const StopWatch&) = delete;

    std::chrono::high_resolution_clock::time_point start_time;
};
