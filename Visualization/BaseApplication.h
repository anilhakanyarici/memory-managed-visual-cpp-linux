#ifndef BASEAPPLICATION_H
#define BASEAPPLICATION_H

#include <gtk/gtk.h>
#include "../String16.h"
#include "../ByteArray.h"
#include "EventArgs.h"
#include "CancellationToken.h"
#include "VObject.h"

class BaseApplication;

class BaseApplication : public VObject
{
public:
    String16 applicationId() const;
    void applicationId(const String16 &v);
    int inactivityTimeout() const;
    void inactivityTimeout(int v);
    GApplicationFlags flags() const;
    void flags(GApplicationFlags v);
    String16 resourcePath() const;
    void resourcePath(const String16 &v);
    bool isBusy() const;
    int isRegistered() const;
    int isRemote() const;

    void Activate();
    void AddMainAction(const String16 &longName, char shortName, GOptionFlags flags, GOptionArg arg, const String16 &description, const String16 &argDescription);
    bool Register(CancellationToken *token);
    void Hold();
    void MarkBusy();
    void Release();
    int Run(int argc, char **argv);
    void Quit();
    void UnmarkBusy();
    void Unref();

    static bool IdIsValid(const String16 &id);

    class Signals
    {
     public:
        static Signal Activate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseApplication *, EventArgs *)
        static Signal Shutdown(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseApplication *, EventArgs *)
        static Signal Startup(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(BaseApplication *, EventArgs *)
    };
};

#endif // BASEAPPLICATION_H
