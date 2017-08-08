#include "UiCheckButton.h"

UiCheckButton *UiCheckButton::New() { return (UiCheckButton *)gtk_check_button_new(); }

UiCheckButton *UiCheckButton::New(const String16 &label, bool mnemonic)
{
    ByteArray utf8 = label.ToCString();
    if(mnemonic)
        return (UiCheckButton *)gtk_check_button_new_with_mnemonic((const char *)utf8.data());
    else
        return (UiCheckButton *)gtk_check_button_new_with_label((const char *)utf8.data());
}
