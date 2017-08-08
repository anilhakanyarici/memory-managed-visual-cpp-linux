#include "FrameClock.h"

Delegate(StaticSignalMethod, void, FrameClock *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, FrameClock *, EventArgs *);

long FrameTimings::getFrameCounter() const { return gdk_frame_timings_get_frame_counter((GdkFrameTimings *)this); }
long FrameTimings::getFrameTime() const { return gdk_frame_timings_get_frame_time((GdkFrameTimings *)this); }
long FrameTimings::getPresentationTime() const { return gdk_frame_timings_get_presentation_time((GdkFrameTimings *)this); }
long FrameTimings::getPredictedPresentationTime() const { return gdk_frame_timings_get_predicted_presentation_time((GdkFrameTimings *)this); }
long FrameTimings::getRefreshInterval() const { return gdk_frame_timings_get_refresh_interval((GdkFrameTimings *)this); }
bool FrameTimings::complete() const { return gdk_frame_timings_get_complete((GdkFrameTimings *)this); }

FrameTimings *FrameTimings::Ref() { return (FrameTimings *)(gdk_frame_timings_ref((GdkFrameTimings *)this)); }
void FrameTimings::Unref() { gdk_frame_timings_unref((GdkFrameTimings *)this); }

long FrameClock::getFrameTime() const { return gdk_frame_clock_get_frame_time((GdkFrameClock *)this); }
long FrameClock::getFrameCounter() const { return gdk_frame_clock_get_frame_counter((GdkFrameClock *)this); }
long FrameClock::getHistoryStart() const { return gdk_frame_clock_get_history_start((GdkFrameClock *)this); }
FrameTimings *FrameClock::getCurrentTimings() const { return (FrameTimings *)(gdk_frame_clock_get_current_timings((GdkFrameClock *)this)); }

FrameTimings *FrameClock::GetTimings(long frameCounter) const { return (FrameTimings *)(gdk_frame_clock_get_timings((GdkFrameClock *)this, frameCounter)); }
void FrameClock::RequestPhase(GdkFrameClockPhase phase) { gdk_frame_clock_request_phase((GdkFrameClock *)this, phase); }
void FrameClock::BeginUpdate() { gdk_frame_clock_begin_updating((GdkFrameClock *)this); }
void FrameClock::EndUpdate() { gdk_frame_clock_end_updating((GdkFrameClock *)this); }

Signal FrameClock::SetSignal(RawSignal s)
{
    VSignal *rs = (VSignal *)s;
    rs->id = g_signal_connect((GdkFrameClock *)this, rs->signalName, rs->callBack, rs);
    return rs;
}

bool FrameClock::RemoveSignal(Signal s)
{
    VSignal *rs = (VSignal *)s;
    delete rs;
    return true;
}

RawSignal FrameClock::Signals::AfterPaint(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "after-paint";
    void (*gtkmethod) (GdkFrameClock *, gpointer) = [](GdkFrameClock *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((FrameClock *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (FrameClock *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FrameClock::Signals::BeforePaint(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "before-paint";
    void (*gtkmethod) (GdkFrameClock *, gpointer) = [](GdkFrameClock *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((FrameClock *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (FrameClock *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FrameClock::Signals::FlushEvents(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "flush-events";
    void (*gtkmethod) (GdkFrameClock *, gpointer) = [](GdkFrameClock *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((FrameClock *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (FrameClock *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FrameClock::Signals::Layout(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "layout";
    void (*gtkmethod) (GdkFrameClock *, gpointer) = [](GdkFrameClock *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((FrameClock *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (FrameClock *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FrameClock::Signals::Paint(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "paint";
    void (*gtkmethod) (GdkFrameClock *, gpointer) = [](GdkFrameClock *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((FrameClock *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (FrameClock *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FrameClock::Signals::ResumeEvents(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "resume-events";
    void (*gtkmethod) (GdkFrameClock *, gpointer) = [](GdkFrameClock *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((FrameClock *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (FrameClock *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal FrameClock::Signals::Update(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "update";
    void (*gtkmethod) (GdkFrameClock *, gpointer) = [](GdkFrameClock *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);
        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((FrameClock *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (FrameClock *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
