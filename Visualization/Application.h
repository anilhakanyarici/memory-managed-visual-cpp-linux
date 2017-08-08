#ifndef APPLICATION_H
#define APPLICATION_H

#include "AccelGroup.h"
#include "Adjustment.h"
#include "ApplicationWindow.h"
#include "Atom.h"
#include "BaseApplication.h"
#include "BaseBin.h"
#include "BaseContainer.h"
#include "BaseMenuShell.h"
#include "BaseRange.h"
#include "BaseWidget.h"
#include "Box.h"
#include "ButtonBox.h"
#include "CairoGC.h"
#include "CancellationToken.h"
#include "Color.h"
#include "Cursor.h"
#include "Device.h"
#include "Display.h"
#include "DWindow.h"
#include "EventArgs.h"
#include "EventBox.h"
#include "Fixed.h"
#include "FlowBox.h"
#include "FrameClock.h"
#include "Grid.h"
#include "Layout.h"
#include "ListBox.h"
#include "Overlay.h"
#include "Paned.h"
#include "Revealer.h"
#include "Screen.h"
#include "Stack.h"
#include "StackSidebar.h"
#include "StackSwitcher.h"
#include "StyleContext.h"
#include "UiAboutDialog.h"
#include "UiActionBar.h"
#include "UiButton.h"
#include "UiCalendar.h"
#include "UiCheckButton.h"
#include "UiDialog.h"
#include "UiDrawingArea.h"
#include "UiEntry.h"
#include "UiFileChooserDialog.h"
#include "UiFrame.h"
#include "UiHeaderBar.h"
#include "UiImage.h"
#include "UiInfoBar.h"
#include "UiLabel.h"
#include "UiLevelBar.h"
#include "UiMenu.h"
#include "UiProgressBar.h"
#include "UiRadioButton.h"
#include "UiScale.h"
#include "UiScrolledWindow.h"
#include "UiSeparator.h"
#include "UiSpinButton.h"
#include "UiSpinner.h"
#include "UiStatusbar.h"
#include "UiSwitch.h"
#include "UiToggleButton.h"
#include "UiWindow.h"
#include "Viewport.h"
#include "Visual.h"
#include "VObject.h"
#include "WidgetPath.h"

#include "../Array.h"

class UiWindow;

class Application : public BaseApplication
{
public:
    static Application *New(const String16 &id, GApplicationFlags flags);

    UiWindow *getActiveWindow() const;
    Array<UiWindow *> getWindows();

    void AddWindow(UiWindow *window);
    void RemoveWindow(UiWindow *window);
    uint Inhibit(UiWindow *window, GtkApplicationInhibitFlags flags, const String16 &reason);
    void Uninhibit(uint cookie);
    bool IsInhibited(GtkApplicationInhibitFlags flags);

    class Signals : public BaseApplication::Signals
    {
        static Signal WindowAdded(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Application *, UiWindow *, EventArgs *)
        static Signal WindowRemoved(SignalCallback eventMethod, void *instance = nullptr, void *userData = nullptr); //Callback(Application *, UiWindow *, EventArgs *)
    };
};

#endif // APPLICATION_H
