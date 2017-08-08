#ifndef UIENTRY_H
#define UIENTRY_H

#include "BaseWidget.h"
#include "../String16.h"

class EntryBuffer
{
public:
    static EntryBuffer *New(const String16 &initialString);

    String16 text() const;
    void text(const String16 &text);
    uint length() const;

    uint maxLength() const;
    void maxLength(uint maxLength);

};

class UiEntry : public BaseWidget
{
public:
    static UiEntry *New();
    static UiEntry *New(const String16 &text);
    static UiEntry *New(EntryBuffer *buffer);

    bool activatesDefault() const;
    void activatesDefault(bool a);
    float alignment() const;
    void alignment(float a);
    EntryBuffer *buffer() const;
    void buffer(EntryBuffer *buffer);
    ushort getLength() const;
    GdkRectangle getTextArea() const;
    bool hasFrame() const;
    void hasFrame(bool h);
    GtkInputHints inputHints() const;
    void inputHints(GtkInputHints a);
    GtkInputPurpose inputPurpose() const;
    void inputPurpose(GtkInputPurpose a);
    int maxLength() const;
    void maxLength(int maxLength);
    int maxWidthChars() const;
    void maxWidthChars(int w);
    bool overwrite() const;
    void overwrite(bool o);
    double progressFraction() const;
    void progressFraction(double a);
    double pulseStep() const;
    void pulseStep(double a);
    String16 text() const;
    void text(const String16 &text);
    bool visibility() const;
    void visibility(bool v);
    int widthChars() const;
    void widthChars(int w);

    void Pulse();
    void GrabFocusWithoutSelection();

    class Signals : public BaseWidget::Signals
    {
    public:
        static RawSignal Activate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, EventArgs *)
        static RawSignal Backspace(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, EventArgs *)
        static RawSignal CopyClipboard(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, EventArgs *)
        static RawSignal CutClipboard(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, EventArgs *)
        static RawSignal DeleteFromCursor(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, GtkDeleteType, int, EventArgs *)
        static RawSignal InsertAtCursor(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, String16, EventArgs *)
        static RawSignal MoveCursor(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, GtkMovementStep, int, bool, EventArgs *)
        static RawSignal PasteClipboard(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, EventArgs *)
        static RawSignal PopulatePopup(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, BaseWidget *, EventArgs *)
        static RawSignal PreEditChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, String16, EventArgs *)
        static RawSignal ToggleOverwrite(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiEntry *, EventArgs *)
    };
};

class UiSearchEntry : UiEntry
{
public:
    static UiSearchEntry *New();

    class Signals : public UiEntry::Signals
    {
    public:
        static Signal NextMatch(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSearchEntry *, EventArgs *)
        static Signal PreviousMatch(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSearchEntry *, EventArgs *)
        static Signal SearchChanged(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSearchEntry *, EventArgs *)
        static Signal StopSearch(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiSearchEntry *, EventArgs *)
    };
};
#endif // UIENTRY_H
