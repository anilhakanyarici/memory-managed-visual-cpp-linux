#ifndef CANCELLATIONTOKEN_H
#define CANCELLATIONTOKEN_H

#include <gtk/gtk.h>

class CancellationToken
{
public:
    static CancellationToken *New();

    bool isCancelled();
    int fd() const;

    void Cancel();
    void ReleaseFd();
    void Reset();
    void PopCurrent();
    void PushCurrent();

    static CancellationToken *current();
};

#endif // CANCELLATIONTOKEN_H
