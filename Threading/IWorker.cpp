#include "IWorker.h"


MethodWorker::MethodWorker(void (*startRoutine)())
{
    this->_startRoutine = startRoutine;
}

void MethodWorker::Coroutine()
{
    this->_startRoutine();
}
