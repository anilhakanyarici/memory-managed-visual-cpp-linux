#ifndef UIHEADERBAR_H
#define UIHEADERBAR_H

#include "BaseContainer.h"
#include "../String16.h"

class UiHeaderBar : public BaseContainer
{
public:
    static UiHeaderBar *New(const String16 &title);

    BaseWidget *customTitle() const;
    void customTitle(BaseWidget *widget);
    bool hasSubtitle() const;
    void hasSubtitle(bool hs);
    bool showCloseButton() const;
    void showCloseButton(bool hs);
    String16 subtitle() const;
    void subtitle(const String16 &title) const;
    String16 title() const;
    void title(const String16 &title) const;

    void PackEnd(BaseWidget *widget);
    void PackStart(BaseWidget *widget);

    class Signals : public BaseContainer::Signals{};
};

#endif // UIHEADERBAR_H
