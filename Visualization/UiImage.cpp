#include "UiImage.h"

UiImage *UiImage::New()
{
    return (UiImage *)gtk_image_new();
}

UiImage *UiImage::New(const String16 &fileName)
{
    GtkWidget *im = gtk_image_new();
    ByteArray utf8 = fileName.ToCString();
    gtk_image_set_from_file(GTK_IMAGE(im), (const char *)utf8.data());
    return (UiImage *)im;
}

UiImage *UiImage::New(Pixelbuffer *buffer)
{
    return (UiImage *)gtk_image_new_from_pixbuf(GDK_PIXBUF(buffer));
}

int UiImage::pixelSize() const { return gtk_image_get_pixel_size(GTK_IMAGE(this)); }

void UiImage::pixelSize(int size) { gtk_image_set_pixel_size(GTK_IMAGE(this), size); }

void UiImage::Clear()
{
    gtk_image_clear(GTK_IMAGE(this));
}

void UiImage::SetFromFile(const String16 &fileName)
{
    ByteArray utf8 = fileName.ToCString();
    gtk_image_set_from_file(GTK_IMAGE(this), (const char *)utf8.data());
}

void UiImage::SetFromResource(const String16 &resourcePath)
{
    ByteArray utf8 = resourcePath.ToCString();
    gtk_image_set_from_resource(GTK_IMAGE(this), (const char *)utf8.data());
}

void UiImage::SetFromIconName(const String16 &iconName, GtkIconSize size)
{
    ByteArray utf8 = iconName.ToCString();
    gtk_image_set_from_icon_name(GTK_IMAGE(this), (const char *)utf8.data(), size);
}

Pixelbuffer *Pixelbuffer::New(UiImage *image)
{
    return (Pixelbuffer *)gtk_image_get_pixbuf(GTK_IMAGE(image));
}

int Pixelbuffer::getChannelCount() const { return gdk_pixbuf_get_n_channels(GDK_PIXBUF(this)); }

GdkColorspace Pixelbuffer::getColorspace() const { return gdk_pixbuf_get_colorspace(GDK_PIXBUF(this)); }

bool Pixelbuffer::hasAlpha() const { return gdk_pixbuf_get_has_alpha(GDK_PIXBUF(this)); }

int Pixelbuffer::bitCountPerSample() const { return gdk_pixbuf_get_bits_per_sample(GDK_PIXBUF(this)); }

ByteArray Pixelbuffer::getPixels() const
{
    guint len;
    guchar *data = gdk_pixbuf_get_pixels_with_length(GDK_PIXBUF(this), &len);
    ByteArray array = ByteArray((byte *)data, len);
    g_free(data);
    return array;
}

int Pixelbuffer::getHeight() const { return gdk_pixbuf_get_height(GDK_PIXBUF(this)); }

int Pixelbuffer::getWidth() const { return gdk_pixbuf_get_width(GDK_PIXBUF(this)); }

int Pixelbuffer::getRowstride() const { return gdk_pixbuf_get_width(GDK_PIXBUF(this)); }

ulong Pixelbuffer::byteSize() const { return (ulong)gdk_pixbuf_get_byte_length(GDK_PIXBUF(this)); }

void Pixelbuffer::ScaleSimple(int destWidth, int destHeight, GdkInterpType interpType)
{
    gdk_pixbuf_scale_simple(GDK_PIXBUF(this), destWidth, destHeight, interpType);
}

String16 Pixelbuffer::GetOption(const String16 &key)
{
    ByteArray utf8 = key.ToCString();
    const gchar *op = gdk_pixbuf_get_option(GDK_PIXBUF(this), (const gchar *)utf8.data());
    return String16((const char *)op);
}

void Pixelbuffer::Free() { g_free(this); }
