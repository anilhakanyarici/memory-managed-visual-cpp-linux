#include "Device.h"
#include "Display.h"
#include "Screen.h"
#include "DWindow.h"

Delegate(StaticSignalMethod, void, VObject *, EventArgs *);
Delegate(InstanceSignalMethod, void, void *, VObject *, EventArgs *);

String16 Device::name() const { return String16(gdk_device_get_name(GDK_DEVICE(this))); }
String16 Device::vendorId() const { return String16(gdk_device_get_vendor_id(GDK_DEVICE(this))); }
String16 Device::productId() const { return String16(gdk_device_get_product_id(GDK_DEVICE(this))); }
GdkInputSource Device::source() const { return gdk_device_get_source(GDK_DEVICE(this)); }
GdkInputMode Device::mode() const { return gdk_device_get_mode(GDK_DEVICE(this)); }
void Device::mode(GdkInputMode m) { gdk_device_set_mode(GDK_DEVICE(this), m); }
Device *Device::associatedDevice() const { return (Device *)gdk_device_get_associated_device(GDK_DEVICE(this)); }
GdkDeviceType Device::deviceType() const { return gdk_device_get_device_type(GDK_DEVICE(this)); }
Display *Device::display() const { return (Display *)gdk_device_get_display(GDK_DEVICE(this)); }
bool Device::hasCursor() const { return gdk_device_get_has_cursor(GDK_DEVICE(this)); }
bool Device::axesCount() const { return gdk_device_get_n_axes(GDK_DEVICE(this)); }
bool Device::keysCount() const { return gdk_device_get_n_keys(GDK_DEVICE(this)); }
DWindow *Device::lastEventWindow() const { return (DWindow *)gdk_device_get_last_event_window(GDK_DEVICE(this)); }

void Device::Warp(Screen *scr, int x, int y) { gdk_device_warp(GDK_DEVICE(this), GDK_SCREEN(scr), x, y); }

Array<Device *> Device::GetSlaveDevices() const
{
    GList* list = gdk_screen_list_visuals(GDK_SCREEN(this));
    guint len = g_list_length(list);
    Array<Device *> visuals = Array<Device *>(len);

    GList *curr = list;
    int i = 0;
    while(curr != NULL){
        visuals[i] = (Device *)curr->data;
        curr = curr->next;
        i++;
    }
    g_list_free(list);
    return visuals;
}

RawSignal Device::Signals::Changed(SignalCallback eventMethod, void *instance, void *userData)
{
    VSignal *s = new VSignal();
    s->eventMethod = (void *)eventMethod;
    s->userData = userData;
    s->instance = instance;
    s->signalName = "changed";
    void (*gtkmethod) (GdkDevice *, gpointer) = [](GdkDevice *sender, gpointer g) -> void{
        VSignal *signal = (VSignal *)g;
        EventArgs *eArgs = new EventArgs(nullptr);

        signal->args = eArgs;
        signal->args->EventSignal = signal;
        signal->args->UserData = signal->userData;
        if(signal->instance == nullptr){
            StaticSignalMethod ssm = (StaticSignalMethod)signal->eventMethod;
            ssm((Device *)sender, signal->args);
        } else {
            InstanceSignalMethod ism = (InstanceSignalMethod)signal->eventMethod;
            ism(signal->instance, (Device *)sender, signal->args);
        }
        delete eArgs;
    };
    s->callBack = G_CALLBACK(gtkmethod);
    return s;
}
