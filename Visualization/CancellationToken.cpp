#include "CancellationToken.h"

CancellationToken *CancellationToken::New() { return (CancellationToken *)g_cancellable_new(); }

bool CancellationToken::isCancelled() { return g_cancellable_is_cancelled(G_CANCELLABLE(this)); }
int CancellationToken::fd() const { return g_cancellable_get_fd(G_CANCELLABLE(this)); }

void CancellationToken::Cancel() { g_cancellable_cancel(G_CANCELLABLE(this)); }
void CancellationToken::ReleaseFd() { g_cancellable_release_fd(G_CANCELLABLE(this)); }
void CancellationToken::Reset() { g_cancellable_reset(G_CANCELLABLE(this)); }
void CancellationToken::PopCurrent() { g_cancellable_pop_current(G_CANCELLABLE(this)); }
void CancellationToken::PushCurrent() { g_cancellable_push_current(G_CANCELLABLE(this)); }

CancellationToken *CancellationToken::current() { return (CancellationToken *)g_cancellable_get_current(); }
