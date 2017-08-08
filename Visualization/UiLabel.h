#ifndef UILABEL_H
#define UILABEL_H

#include "BaseWidget.h"
#include "../String16.h"

class UiLabel : public BaseWidget
{
public:
    static UiLabel *New(const String16 &text);

    float angle() const;
    void angle(float v);
    PangoEllipsizeMode ellipsize() const;
    void ellipsize(PangoEllipsizeMode j);
    GtkJustification justify() const;
    void justify(GtkJustification j);
    float xAlign() const;
    void xAlign(float v);
    float yAlign() const;
    void yAlign(float v);
    int widthChars() const;
    void widthChars(int v);
    int maxWidthChars() const;
    void maxWidthChars(int v);
    bool lineWrap() const;
    void lineWrap(bool v);
    PangoWrapMode lineWrapMode() const;
    void lineWrapMode(PangoWrapMode j);
    int lineCount() const;
    void lineCount(int v);
    bool useMarkup() const;
    void useMarkup(bool v);
    bool useUnderline() const;
    void useUnderline(bool v);
    bool singleLineMode() const;
    void singleLineMode(bool v);
    Position getLayoutOffset() const;
    bool selectable() const;
    void selectable(bool v);
    String16 text() const;
    void text(const String16 &text);
    String16 label() const;
    void label(const String16 &text);

    void SetMarkup(const String16 &markup);
    void SetMarkupWithMNemonic(const String16 &markup);
    void SetPattern(const String16 &pattern);


    class Signals : public BaseWidget::Signals
    {
    public:
        static RawSignal CopyClipboard(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiLabel *, EventArgs *)
        static RawSignal MoveCursor(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiLabel *, GtkMovementStep, int, bool, EventArgs *)
    };
};

#endif // UILABEL_H
