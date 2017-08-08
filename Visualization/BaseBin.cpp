#include "BaseBin.h"

BaseWidget *BaseBin::binChild() { return (BaseWidget *)gtk_bin_get_child(GTK_BIN(this)); }
