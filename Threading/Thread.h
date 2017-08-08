#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include "../Defs.h"
#include "IWorker.h"

class Thread final: public MethodWorker, public IEquatable<Thread>
{
public:
    Thread(void (*startRoutine) (void), int stackSize = 8388608);
    Thread(IWorker *worker, int stackSize = 8388608);

    ~Thread();

    int getPriority() const;
    bool hasStarted() const;
    int id() const;
    bool isAlive() const;
    bool isCurrent() const;
    bool isMain() const;
    int stackSize() const;

    bool Cancel();
    bool Detach();
    bool Equals(const Thread &other) const;
    bool Join();
    void Kill();
    void SetPriority(int priority);
    int Signal(int sig);
    void Start(int detachState = PTHREAD_CREATE_JOINABLE);

    static Thread current();
    static int idealWorkerCount();
    static int processId();

    static void *GetSpecifiedData(uint key);
    static void SetSpecifiedData(uint key, const void *data);
    static void Sleep(ulong microsecond);
    static void Yield();

    Thread(const Thread &thread);
    Thread &operator =(const Thread &thread);

private:
    struct _impl;
    _impl *_pImpl;

    Thread(const pthread_t &thread);
};


#endif // THREAD_H
