#include "Stack.h"
#include "../String16.h"


Stack *Stack::New() { return (Stack *)gtk_stack_new(); }

BaseWidget *Stack::visibleChild() const { return (BaseWidget *)gtk_stack_get_visible_child(GTK_STACK(this)); }

void Stack::visibleChild(BaseWidget *c) { gtk_stack_set_visible_child(GTK_STACK(this), GTK_WIDGET(c)); }

String16 Stack::visibleChildName() const { return String16(gtk_stack_get_visible_child_name(GTK_STACK(this))); }

void Stack::visibleChildName(const String16 &c)
{
    ByteArray utf8 = c.ToCString();
    gtk_stack_set_visible_child_name(GTK_STACK(this), (const gchar *)utf8.data());
}

bool Stack::getTransitionRunning() const { return gtk_stack_get_transition_duration(GTK_STACK(this)); }

bool Stack::homogeneous() const { return gtk_stack_get_homogeneous(GTK_STACK(this)); }

void Stack::homogeneous(bool c) { gtk_stack_set_homogeneous(GTK_STACK(this), (c)); }

bool Stack::hHomogeneous() const { return gtk_stack_get_hhomogeneous(GTK_STACK(this)); }

void Stack::hHomogeneous(bool c) { gtk_stack_set_hhomogeneous(GTK_STACK(this), (c)); }

bool Stack::vHomogeneous() const { return gtk_stack_get_vhomogeneous(GTK_STACK(this)); }

void Stack::vHomogeneous(bool c) { gtk_stack_set_vhomogeneous(GTK_STACK(this), (c)); }

bool Stack::interpolateSize() const { return gtk_stack_get_interpolate_size(GTK_STACK(this)); }

void Stack::interpolateSize(bool c) { gtk_stack_set_interpolate_size(GTK_STACK(this), (c)); }

uint Stack::transitionDuration() const { return gtk_stack_get_transition_duration(GTK_STACK(this)); }

void Stack::transitionDuration(uint c) { gtk_stack_set_transition_duration(GTK_STACK(this), (c)); }

GtkStackTransitionType Stack::transitionType() const { return gtk_stack_get_transition_type(GTK_STACK(this)); }

void Stack::transitionType(GtkStackTransitionType c) { gtk_stack_set_transition_type(GTK_STACK(this), (c)); }

void Stack::AddNamed(BaseWidget *child, const String16 &name)
{
    ByteArray utf8 = name.ToCString();
    gtk_stack_add_named(GTK_STACK(this), GTK_WIDGET(child), (const gchar *)utf8.data());
}

void Stack::AddTitled(BaseWidget *child, const String16 &name, const String16 &title)
{
    ByteArray utf8Name = name.ToCString();
    ByteArray utf8Title = title.ToCString();
    gtk_stack_add_titled(GTK_STACK(this), GTK_WIDGET(child), (const gchar *)utf8Name.data(), (const gchar *)utf8Title.data());
}

BaseWidget *Stack::GetChildByName(const String16 &name)
{
    ByteArray utf8Name = name.ToCString();
    return (BaseWidget *)gtk_stack_get_child_by_name(GTK_STACK(this), (const gchar *)utf8Name.data());
}

void Stack::SetVisibleChildFull(const String16 &name, GtkStackTransitionType transition)
{
    ByteArray utf8Name = name.ToCString();
    gtk_stack_set_visible_child_full(GTK_STACK(this), (const gchar *)utf8Name.data(), transition);
}
