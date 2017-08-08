#include "StackSwitcher.h"

StackSwitcher *StackSwitcher::New() { return (StackSwitcher *)gtk_stack_switcher_new(); }

Stack *StackSwitcher::stack() const { return (Stack *)gtk_stack_switcher_get_stack(GTK_STACK_SWITCHER(this)); }

void StackSwitcher::stack(Stack *s) { gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(this), GTK_STACK(s)); }

