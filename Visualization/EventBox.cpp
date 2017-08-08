#include "EventBox.h"

EventBox *EventBox::New()
{
    return (EventBox *)gtk_event_box_new();
}

bool EventBox::aboveChild() const { return gtk_event_box_get_above_child(GTK_EVENT_BOX(this)); }

void EventBox::aboveChild(bool u) { gtk_event_box_set_above_child(GTK_EVENT_BOX(this), u); }

bool EventBox::visibleWindow() const { return gtk_event_box_get_visible_window(GTK_EVENT_BOX(this)); }

void EventBox::visibleWindow(bool u) { gtk_event_box_set_visible_window(GTK_EVENT_BOX(this), u); }
