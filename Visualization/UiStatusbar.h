#ifndef UISTATUSBAR_H
#define UISTATUSBAR_H

#include "Box.h"

class UiStatusbar : public Box
{
public:
    static UiStatusbar *New();

    Box *getMessageArea() const;

    uint ContextId(const String16 &description);
    uint Push(uint contextId, const String16 &text);
    void Pop(uint contextId);
    void Remove(uint contextId, uint messageId);
    void RemoveAll(uint contextId);

    class Signals : public Box::Signals
    {
    public:
        static RawSignal TextPopped(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiStatusbar *, uint, String16, EventArgs *)
        static RawSignal TextPushed(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiStatusbar *, uint, String16, EventArgs *)
    };
};

#endif // UISTATUSBAR_H
