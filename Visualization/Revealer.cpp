#include "Revealer.h"


Revealer *Revealer::New() { return (Revealer *)gtk_revealer_new(); }

bool Revealer::revealChild() const { return gtk_revealer_get_reveal_child(GTK_REVEALER(this)); }

void Revealer::revealChild(bool c) { gtk_revealer_set_reveal_child(GTK_REVEALER(this), (c)); }

uint Revealer::transitionDuration() const { return gtk_revealer_get_transition_duration(GTK_REVEALER(this)); }

void Revealer::transitionDuration(uint c) { gtk_revealer_set_transition_duration(GTK_REVEALER(this), (c)); }

bool Revealer::isRevealed() const { return gtk_revealer_get_child_revealed(GTK_REVEALER(this)); }
