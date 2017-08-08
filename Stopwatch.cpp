#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
    this->_started = false;
    this->_elapsedusec = 0;
}

long Stopwatch::elapsedMicroseconds()
{
    if(this->_started){
        gettimeofday(&this->_tve, 0);
        return this->_elapsedusec + (this->_tve.tv_sec - this->_tvs.tv_sec) * 1000000l + (this->_tve.tv_usec - this->_tvs.tv_usec);
    }
    return this->_elapsedusec;
}
bool Stopwatch::isRunning()
{
    return this->_started;
}
void Stopwatch::Reset()
{
    if(this->_started)
        gettimeofday(&this->_tvs, 0);
    this->_elapsedusec = 0;
}

void Stopwatch::Restart()
{
    gettimeofday(&this->_tvs, 0);
    this->_elapsedusec = 0;
    this->_started = true;
}
void Stopwatch::Start()
{
    if(!this->_started){
        gettimeofday(&this->_tvs, 0);
    }
    this->_started = true;
}
long Stopwatch::Stop()
{
    if(this->_started){
        gettimeofday(&this->_tve, 0);
        this->_elapsedusec += (this->_tve.tv_sec - this->_tvs.tv_sec) * 1000000l + (this->_tve.tv_usec - this->_tvs.tv_usec);
    }
    this->_started = false;
    return this->elapsedMicroseconds();
}
