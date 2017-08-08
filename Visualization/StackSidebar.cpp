#include "StackSidebar.h"

StackSidebar *StackSidebar::New() { return (StackSidebar *)gtk_stack_sidebar_new(); }

Stack *StackSidebar::stack() const { return (Stack *)gtk_stack_sidebar_get_stack(GTK_STACK_SIDEBAR(this)); }

void StackSidebar::stack(Stack *s) { gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(this), GTK_STACK(s)); }
