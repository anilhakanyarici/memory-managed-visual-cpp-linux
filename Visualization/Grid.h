#ifndef GRID_H
#define GRID_H

#include "BaseContainer.h"

class Grid : public BaseContainer
{
public:
    static Grid *New();

    GtkBaselinePosition baselinePosition(int row) const;
    void baselinePosition(GtkBaselinePosition rs, int row);
    int baselineRow() const;
    void baselineRow(int rs);
    bool columnHomogeneous() const;
    void columnHomogeneous(bool rh);
    uint columnSpacing() const;
    void columnSpacing(uint rs);
    bool rowHomogeneous() const;
    void rowHomogeneous(bool rh);
    uint rowSpacing() const;
    void rowSpacing(uint rs);


    void Attach(BaseWidget *widget, int left, int top, int width, int height);
    void AttachNextTo(BaseWidget *child, BaseWidget *sibling, GtkPositionType side, int width, int height);
    BaseWidget *GetChildAt(int left, int top);
    void InsertColumn(int position);
    void InsertNextTo(BaseWidget *sibling, GtkPositionType side);
    void InsertRow(int position);
    void RemoveColumn(int position);
    void RemoveRow(int position);

    class Signals : public BaseContainer::Signals{};
};

#endif // GRID_H
