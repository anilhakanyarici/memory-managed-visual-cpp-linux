#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "BaseBin.h"
#include "../String16.h"
#include "UiImage.h"

class UiButton : public BaseBin
{
public:
    static UiButton *New();
    static UiButton *New(const String16 &label);

    String16 label() const;
    void label(const String16 &label);

    bool alwaysShowImage() const;
    void alwaysShowImage(bool v);
    bool useUnderline() const;
    void useUnderline(bool v);
    UiImage *image() const;
    void image(UiImage * v);
    GtkPositionType imagePosition() const;
    void imagePosition(GtkPositionType v);

    void Click();

    class Signals : public BaseBin::Signals
    {
    public:
        static RawSignal Activate(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiButton *, EventArgs *)
        static RawSignal Clicked(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(UiButton *, EventArgs *)
    };
};

#endif // UIBUTTON_H
