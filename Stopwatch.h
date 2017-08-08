#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <sys/time.h>
#include "Object.h"

class Stopwatch
{
public:
    Stopwatch();

    long elapsedMicroseconds();
    bool isRunning();

    void Reset();
    void Restart();
    void Start();
    long Stop();

    static Stopwatch StartNew() { Stopwatch sw; sw.Start(); return sw; }

private:
    timeval _tvs;
    timeval _tve;
    long _elapsedusec;
    bool _started;
};

#endif // STOPWATCH_H
