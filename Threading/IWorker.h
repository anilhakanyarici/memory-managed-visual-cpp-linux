#ifndef IWORKER_H
#define IWORKER_H

class IWorker
{
    friend class Thread;
protected:
    virtual void Coroutine() = 0;
};

class MethodWorker : public IWorker
{
public:
    MethodWorker(void (*startRoutine) (void));

protected:
    void Coroutine() override final;

private:
    void (*_startRoutine) (void);
};


#endif // IWORKER_H
