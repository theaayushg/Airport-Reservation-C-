//
//  ECConsoleUITextField.h
//  
//
//  Created by Yufeng Wu on 5/24/23.
//
#ifndef EC_CONSOLE_UI_TEXT_FIELD_H
#define EC_CONSOLE_UI_TEXT_FIELD_H

#include <string>
#include "ECConsoleUIItem.h"
#include "ECTextViewImp.h"

class ECConsoleUITextField : public ECConsoleUIItem {
public:
    ECConsoleUITextField(ECTextViewImp *textViewPtr, int positionX, int positionY, int fieldLength);
    virtual std::string GetTextAtRow(int row) const override;
    virtual int GetHighlightPosition(int &leftEdge, int &rightEdge) const override;
    virtual void HdlKeyEnter();
    void HdlBackspaceKey();
    virtual void HdlOtherKey();
    virtual bool IsHandlingKeys() const override { return true; };

private:
    ECTextViewImp *textViewPtr;
    int positionX, positionY, fieldLength;
    std::string fieldContent;
    bool isEditable;
};

#endif /* EC_CONSOLE_UI_TEXT_FIELD_H */
