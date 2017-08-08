#ifndef UIIMAGE_H
#define UIIMAGE_H

#include "BaseWidget.h"
#include "../IO/FileStream.h"

class Pixelbuffer;

class UiImage : public BaseWidget
{
public:
    static UiImage *New();
    static UiImage *New(const String16 &fileName);
    static UiImage *New(Pixelbuffer *buffer);

    int pixelSize() const;
    void pixelSize(int size);

    void Clear();
    void SetFromFile(const String16 &fileName);
    void SetFromResource(const String16 &resourcePath);
    void SetFromIconName(const String16 &iconName, GtkIconSize size);

    class Signals : public BaseWidget::Signals{};
};

class Pixelbuffer
{
public:
    static Pixelbuffer *New(UiImage *image);

    int getChannelCount() const;
    GdkColorspace getColorspace() const;
    bool hasAlpha() const;
    int bitCountPerSample() const;
    ByteArray getPixels() const;
    int getHeight() const;
    int getWidth() const;
    int getRowstride() const;
    ulong byteSize() const;

    void ScaleSimple(int destWidth, int destHeight, GdkInterpType interpType);
    String16 GetOption(const String16 &key);
    void Free();
};

#endif // UIIMAGE_H
