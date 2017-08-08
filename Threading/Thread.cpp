#include <signal.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "Thread.h"
#include "../Exception.h"

struct Thread::_impl
{
    pthread_t _thread = 0;
    int _stackSize;
    int _priority = 0;
    IWorker *_worker = 0;
    uint _refc = 1;
    static void *run(void *thread);
};

Thread::Thread(void (*startRoutine) (void), int stackSize) : MethodWorker(startRoutine)
{
    this->_pImpl = new Thread::_impl();
    this->_pImpl->_stackSize = stackSize;
    this->_pImpl->_worker = this;
}

Thread::Thread(IWorker *worker, int stackSize) : MethodWorker(nullptr)
{
    this->_pImpl = new Thread::_impl();
    this->_pImpl->_stackSize = stackSize;
    this->_pImpl->_worker = worker;
}

Thread::~Thread()
{
    if(this->_pImpl != nullptr){
        if(this->_pImpl->_refc == 1){
            delete this->_pImpl;
        } else this->_pImpl->_refc--;
    }
}

bool Thread::Cancel()
{
    return pthread_cancel(this->_pImpl->_thread) == 0;
}

bool Thread::Detach()
{
    return pthread_detach(this->_pImpl->_thread);
}

bool Thread::Equals(const Thread &other) const
{
    return pthread_equal(this->_pImpl->_thread, other._pImpl->_thread) == 0;
}

int Thread::getPriority() const
{
    return this->_pImpl->_priority;
}

bool Thread::hasStarted() const
{
    return this->_pImpl->_thread != 0;
}

int Thread::stackSize() const
{
    return this->_pImpl->_stackSize;
}

int Thread::id() const
{
    return syscall(SYS_gettid) - syscall(SYS_getpid);
}

bool Thread::isAlive() const
{
    if(this->_pImpl->_thread == 0)
        return false;
    return pthread_kill(this->_pImpl->_thread, 0) != ESRCH;
}

bool Thread::isCurrent() const
{
    return pthread_equal(this->_pImpl->_thread, pthread_self()) != 0;
}

bool Thread::isMain() const
{
    return syscall(SYS_gettid) == syscall(SYS_getpid);
}

bool Thread::Join()
{
    void *retVal;
    return pthread_join(this->_pImpl->_thread, &retVal) == 0;
}

void Thread::Kill()
{
    if(this->isCurrent())
        return;
    pthread_kill(this->_pImpl->_thread, SIGKILL);
}

int Thread::idealWorkerCount()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

int Thread::processId()
{
    return syscall(SYS_getpid);
}

void Thread::SetSpecifiedData(uint key, const void *data)
{
    pthread_setspecific(key, data);
}

void Thread::SetPriority(int priority)
{
    if(this->_pImpl->_thread != 0){
        this->_pImpl->_priority = priority;
    } else {
        if(pthread_setschedprio(this->_pImpl->_thread, priority) == 0)
            this->_pImpl->_priority = priority;
    }
}

int Thread::Signal(int sig)
{
    if(this->isCurrent())
        return -1;
    return pthread_kill(this->_pImpl->_thread, sig);
}

void Thread::Start(int detachState)
{
    if(this->_pImpl->_thread != 0)
        throw ThreadStateException("The thread has already been started.");
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, this->_pImpl->_stackSize);
    sched_param scp;
    pthread_attr_getschedparam(&attr, &scp);
    scp.__sched_priority = this->_pImpl->_priority;
    pthread_attr_setschedparam(&attr, &scp);
    pthread_attr_setdetachstate(&attr, detachState);
    pthread_create(&this->_pImpl->_thread, &attr, Thread::_impl::run, this);
}

Thread Thread::current()
{
    return Thread(pthread_self());
}

void *Thread::GetSpecifiedData(uint key)
{
    return pthread_getspecific(key);
}

void Thread::Yield()
{
    pthread_yield();
}

Thread::Thread(const Thread &thread) : MethodWorker(nullptr)
{
    this->_pImpl = thread._pImpl;
    if(this->_pImpl != nullptr)
        this->_pImpl->_refc++;
}

Thread &Thread::operator =(const Thread &thread)
{
    if(this->_pImpl != thread._pImpl){
        if(this->_pImpl != nullptr){
            if(this->_pImpl->_refc == 1){
                delete this->_pImpl;
            } else this->_pImpl->_refc--;
        }
        this->_pImpl = thread._pImpl;
        if(thread._pImpl != nullptr)
            this->_pImpl->_refc++;
    } return *this;
}

void Thread::Sleep(ulong microsecond)
{
    usleep(microsecond);
}

void *Thread::_impl::run(void *thread)
{
    Thread *t = (Thread *)thread;
    t->_pImpl->_worker->Coroutine();
    return 0;
}

Thread::Thread(const pthread_t &thread) : MethodWorker(nullptr)
{
    this->_pImpl = new Thread::_impl();
    this->_pImpl->_thread = thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    size_t stackSize;
    pthread_attr_getstacksize(&attr, &stackSize);
    this->_pImpl->_stackSize = stackSize;

    sched_param scp;
    pthread_attr_getschedparam(&attr, &scp);
    this->_pImpl->_priority = scp.__sched_priority;
}
