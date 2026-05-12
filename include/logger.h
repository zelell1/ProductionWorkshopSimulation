#pragma once

class Logger {
public:
    static void LogStart(long long time, int k, int i, int j);

    static void LogFinish(long long time, int k, int i, int j);

    static void LogReady(long long time, int k, int j);

    static void LogWait(long long time, int k, int i, int j, int p);
    
    static void LogStop(long long time);
};
