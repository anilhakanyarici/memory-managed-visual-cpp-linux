#ifndef BOX_H
#define BOX_H

#include "BaseContainer.h"

class Box : public BaseContainer
{
public:
    static Box *New(GtkOrientation orientation, int spacing);

    bool homogeneous() const;
    void homogeneous(bool h);
    int spacing() const;
    void spacing(int h);
    GtkBaselinePosition baselinePosition() const;
    void baselinePosition(GtkBaselinePosition h);
    BaseWidget *centerWidget() const;
    void centerWidget(BaseWidget *w);

    void End(BaseWidget *widget, bool expand, bool fill, uint padding);
    void Start(BaseWidget *widget, bool expand, bool fill, uint padding);
    void ReorderChild(BaseWidget *widget, int position);
    void QueryChildPacking(BaseWidget *widget, bool *expand, bool *fill, uint *padding, GtkPackType *packType);
    void SetChildPacking(BaseWidget *widget, bool expand, bool fill, uint padding, GtkPackType packType);

    class Signals : public BaseContainer::Signals{};
};


#endif // BOX_H
