#ifndef CALENDAR_H
#define CALENDAR_H

#include <gtk/gtk.h>
#include "BaseWidget.h"

class DateTime;

class UiCalendar : public BaseWidget
{
public:
    static UiCalendar *New();
    static UiCalendar *New(DateTime date);
    static UiCalendar *New(DateTime date, GtkCalendarDisplayOptions options);

    GtkCalendarDisplayOptions displayOptions() const;
    void displayOptions(GtkCalendarDisplayOptions options);
    DateTime getDate() const;

    void Select(DateTime date);
    void Select(uint year, uint month);
    void Select(uint day);
    void Mark(uint day);
    void UnMark(uint day);
    void IsMarked(uint day);
    void ClearMarks();

    class Signals : public BaseWidget::Signals
    {
    public:
        static RawSignal DaySelectedSingleClick(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCalendar *, EventArgs *)
        static RawSignal DaySelectedDoubleClick(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCalendar *, EventArgs *)
        static RawSignal MonthChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCalendar *, EventArgs *)
        static RawSignal SwitchedNextMonth(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCalendar *, EventArgs *)
        static RawSignal SwitchedPreviousMonth(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCalendar *, EventArgs *)
        static RawSignal SwitchedNextYear(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCalendar *, EventArgs *)
        static RawSignal SwitchedPreviousYear(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiCalendar *, EventArgs *)
    };
};

#endif // CALENDAR_H
