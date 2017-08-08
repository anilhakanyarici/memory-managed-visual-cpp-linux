#ifndef STACK_H
#define STACK_H

#include "BaseContainer.h"

class Stack : public BaseContainer
{
public:
    static Stack *New();

    BaseWidget *visibleChild() const;
    void visibleChild(BaseWidget *c);
    String16 visibleChildName() const;
    void visibleChildName(const String16 &c);
    bool getTransitionRunning() const;
    bool homogeneous() const;
    void homogeneous(bool c);
    bool hHomogeneous() const;
    void hHomogeneous(bool c);
    bool vHomogeneous() const;
    void vHomogeneous(bool c);
    bool interpolateSize() const;
    void interpolateSize(bool c);
    uint transitionDuration() const;
    void transitionDuration(uint c);
    GtkStackTransitionType transitionType() const;
    void transitionType(GtkStackTransitionType c);

    void AddNamed(BaseWidget *child, const String16 &name);
    void AddTitled(BaseWidget *child, const String16 &name, const String16 &title);
    BaseWidget *GetChildByName(const String16 &name);
    void SetVisibleChildFull(const String16 &name, GtkStackTransitionType transition);

    class Signals : public BaseContainer::Signals{};
};

#endif // STACK_H
