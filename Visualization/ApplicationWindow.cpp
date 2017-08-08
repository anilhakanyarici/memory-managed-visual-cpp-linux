#include "ApplicationWindow.h"
#include "Application.h"

ApplicationWindow *ApplicationWindow::New(Application *app)
{
    return (ApplicationWindow *)gtk_application_window_new(GTK_APPLICATION(app));
}

bool ApplicationWindow::showMenubar() const { return gtk_application_window_get_show_menubar(GTK_APPLICATION_WINDOW(this)); }

void ApplicationWindow::showMenubar(bool v) { gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(this), v); }

bool ApplicationWindow::getWindowId() const { return gtk_application_window_get_show_menubar(GTK_APPLICATION_WINDOW(this)); }
