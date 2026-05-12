#include "logger.h"
#include <iostream>

void Logger::LogStart(long long time, int k, int i, int j) {
    std::cout << "start " << time << " " << k << " " << i << " " << j << "\n";
}

void Logger::LogFinish(long long time, int k, int i, int j) {
    std::cout << "finish " << time << " " << k << " " << i << " " << j << "\n";
}

void Logger::LogReady(long long time, int k, int j) {
    std::cout << "ready " << time << " " << k << " " << j << "\n";
}

void Logger::LogWait(long long time, int k, int i, int j, int p) {
    std::cout << "wait " << time << " " << k << " " << i << " " << j << " " << p << "\n";
}

void Logger::LogStop(long long time) {
    std::cout << "stop " << time;
}
