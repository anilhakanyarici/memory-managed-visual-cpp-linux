#include "UiCalendar.h"
#include "../DateTime.h"

Delegate(StaticSignalMethod, void, BaseWidget *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, BaseWidget *, EventArgs *);

UiCalendar *UiCalendar::New()
{
    GtkWidget *w = gtk_calendar_new();
    DateTime date = DateTime::Now();
    gtk_calendar_select_month(GTK_CALENDAR(w), (uint)date.month(), (uint)date.year());
    gtk_calendar_select_day(GTK_CALENDAR(w), (uint)date.day());
    return (UiCalendar *)w;
}

UiCalendar *UiCalendar::New(DateTime date)
{
    GtkWidget *w = gtk_calendar_new();
    gtk_calendar_select_month(GTK_CALENDAR(w), (uint)date.month(), (uint)date.year());
    gtk_calendar_select_day(GTK_CALENDAR(w), (uint)date.day());
    return (UiCalendar *)w;
}

UiCalendar *UiCalendar::New(DateTime date, GtkCalendarDisplayOptions options)
{
    GtkWidget *w = gtk_calendar_new();
    gtk_calendar_select_month(GTK_CALENDAR(w), (uint)date.month(), (uint)date.year());
    gtk_calendar_select_day(GTK_CALENDAR(w), (uint)date.day());
    gtk_calendar_set_display_options(GTK_CALENDAR(w), options);
    return (UiCalendar *)w;
}

GtkCalendarDisplayOptions UiCalendar::displayOptions() const { return gtk_calendar_get_display_options(GTK_CALENDAR(this)); }

void UiCalendar::displayOptions(GtkCalendarDisplayOptions options)
{
    gtk_calendar_set_display_options(GTK_CALENDAR(this), options);
}

DateTime UiCalendar::getDate() const
{
    uint y, m, d;
    gtk_calendar_get_date(GTK_CALENDAR(this), &y, &m, &d);
    return DateTime(y, m, d);
}

void UiCalendar::Select(DateTime date)
{
    gtk_calendar_select_month(GTK_CALENDAR(this), (uint)date.month(), (uint)date.year());
    gtk_calendar_select_day(GTK_CALENDAR(this), (uint)date.day());
}

void UiCalendar::Select(uint year, uint month)
{
    gtk_calendar_select_month(GTK_CALENDAR(this), month, year);
}

void UiCalendar::Select(uint day)
{
    gtk_calendar_select_day(GTK_CALENDAR(this), day);
}

void UiCalendar::Mark(uint day)
{
    gtk_calendar_mark_day(GTK_CALENDAR(this), day);
}

void UiCalendar::UnMark(uint day)
{
    gtk_calendar_unmark_day(GTK_CALENDAR(this), day);
}

void UiCalendar::IsMarked(uint day)
{
    gtk_calendar_get_day_is_marked(GTK_CALENDAR(this), day);
}

void UiCalendar::ClearMarks()
{
    gtk_calendar_clear_marks(GTK_CALENDAR(this));
}

RawSignal UiCalendar::Signals::DaySelectedSingleClick(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "day-selected";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiCalendar::Signals::DaySelectedDoubleClick(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "day-selected-double-click";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiCalendar::Signals::MonthChanged(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "month-changed";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiCalendar::Signals::SwitchedNextMonth(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "next-month";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiCalendar::Signals::SwitchedPreviousMonth(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "next-year";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiCalendar::Signals::SwitchedNextYear(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "prev-month";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}

RawSignal UiCalendar::Signals::SwitchedPreviousYear(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "prev-year";
    void (*gtkmethod) (GtkWidget *, gpointer) = [](GtkWidget *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((BaseWidget *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (BaseWidget *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
