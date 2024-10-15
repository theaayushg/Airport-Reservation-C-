//
//  ECConsoleUITextField.cpp
//  
//
//  Created by Yufeng Wu on 5/24/23.
//

#include "ECConsoleUITextField.h"

using namespace std;

ECConsoleUITextField::ECConsoleUITextField(ECTextViewImp *textViewPtr, int positionX, int positionY, int fieldLength)
    : ECConsoleUIItem(positionX, positionY, positionX + fieldLength - 1, positionY), textViewPtr(textViewPtr), fieldLength(fieldLength), fieldContent(": Your name here!"), isEditable(false) {
    textViewPtr->SetCursorY(positionY);
}

std::string ECConsoleUITextField::GetTextAtRow(int row) const {
    if (row == GetYUL()) {
        return fieldContent;
    }
    return "";
}

int ECConsoleUITextField::GetHighlightPosition(int &leftEdge, int &rightEdge) const {
    if (fieldContent.size() >= 2) {
        leftEdge = 0;
        rightEdge = GetXUL() + fieldContent.size();
        if (isEditable) {
            textViewPtr->SetCursorX(rightEdge);
        }
        return GetXLR();
    }
    return -1;
}

void ECConsoleUITextField::HdlKeyEnter() {
    isEditable = true;
    textViewPtr->SetCursorX(GetXUL());
    textViewPtr->SetCursorY(GetYUL());
    if (fieldContent == ": Your name here!") {
        fieldContent = ": ";
    }
}

void ECConsoleUITextField::HdlBackspaceKey() {
    if (fieldContent.size() > 2 && isEditable) {
        fieldContent.pop_back();
    }
}

void ECConsoleUITextField::HdlOtherKey() {
    if (isEditable) {
        int key = textViewPtr->GetPressedKey();
        if (key == BACKSPACE) {
            HdlBackspaceKey();
        } else if (key == CTRL_C) {
            isEditable = false;
        } else {
            // Ensure the content doesn't exceed the available length, accounting for the initial ": "
            if (fieldContent.size() < fieldLength - 1) {
                if(isprint(key)) {  // Additional check to ensure the key is printable
                    fieldContent.push_back(static_cast<char>(key));
                }
            }
        }
    }
}
