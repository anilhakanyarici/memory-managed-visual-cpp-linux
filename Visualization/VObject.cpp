#include "VObject.h"

Signal VObject::Connect(RawSignal s)
{
    VSignal *rs = (VSignal *)s;
    rs->id = g_signal_connect(this, rs->signalName, rs->callBack, rs);
    return rs;
}
bool VObject::Disconnect(Signal s)
{
    VSignal *rs = (VSignal *)s;
    g_signal_handler_disconnect(this, rs->id);
    delete rs;
    return true;
}
