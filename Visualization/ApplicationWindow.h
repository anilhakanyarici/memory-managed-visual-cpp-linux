#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include "UiWindow.h"
class Application;
class ApplicationWindow : public UiWindow
{
public:
    static ApplicationWindow *New(Application *app);

    bool showMenubar() const;
    void showMenubar(bool v);
    bool getWindowId() const;
};

#endif // APPLICATIONWINDOW_H
