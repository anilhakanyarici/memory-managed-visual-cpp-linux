#ifndef FRAMECLOCK_H
#define FRAMECLOCK_H

#include "EventArgs.h"

class FrameTimings
{
public:
    long getFrameCounter() const;
    long getFrameTime() const;
    long getPresentationTime() const;
    long getPredictedPresentationTime() const;
    long getRefreshInterval() const;
    bool complete() const;

    FrameTimings *Ref();
    void Unref();
};

class FrameClock : public VObject
{
public:

    long getFrameTime() const;
    long getFrameCounter() const;
    long getHistoryStart() const;
    FrameTimings *getCurrentTimings() const;

    FrameTimings *GetTimings(long frameCounter) const;
    void RequestPhase(GdkFrameClockPhase phase);
    void BeginUpdate();
    void EndUpdate();
    Signal SetSignal(RawSignal s);
    bool RemoveSignal(Signal s);

    class Signals
    {
    public:
        static RawSignal AfterPaint(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FrameClock *, EventArgs *)
        static RawSignal BeforePaint(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FrameClock *, EventArgs *)
        static RawSignal FlushEvents(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FrameClock *, EventArgs *)
        static RawSignal Layout(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FrameClock *, EventArgs *)
        static RawSignal Paint(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FrameClock *, EventArgs *)
        static RawSignal ResumeEvents(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FrameClock *, EventArgs *)
        static RawSignal Update(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(FrameClock *, EventArgs *)
    };
};

#endif // FRAMECLOCK_H
