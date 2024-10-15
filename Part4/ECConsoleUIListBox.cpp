//
//  ECConsoleUIListBox.cpp
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#include "ECConsoleUIListBox.h"
#include "ECConsoleUIItem.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void ECConsoleUIListBox::AddChoice(const string &text)
{
    tRows.push_back(text);
}

void ECConsoleUIListBox::Choose(int rIndex)
{
    if (rIndex >= 0 && rIndex < tRows.size())
        indexChoice = rIndex;
    
}

std::string ECConsoleUIListBox::GetTextAtRow(int r) const
{
    std::string output;
    if (r >= GetYUL() && r <= GetYLR()){
        output = tRows[FirstVis + r - GetYUL()];
    }
    return output;
}

int ECConsoleUIListBox::GetHighlightPosition(int &xLeft, int &xRight) const
{
    if (indexChoice >= FirstVis && indexChoice < FirstVis + visRows)
    {
        xLeft = 0;
        xRight = GetWidth();
        return indexChoice - FirstVis;
    }
    else
        return -1;
}

void ECConsoleUIListBox :: HdlKeyUp()
{
    if (indexChoice == 0)
        return;
    if (indexChoice > 0){
        Choose(GetChoice()-1);
    }
    if(GetChoice() == FirstVis){
        if(FirstVis > 0){
            FirstVis--;
        }
    }
}

void ECConsoleUIListBox :: HdlKeyDown()
{
    if (indexChoice != tRows.size()){
        Choose(GetChoice()+1);
    }
    if(GetChoice() == FirstVis + visRows){
        if(FirstVis < tRows.size() - visRows){
            FirstVis++;
        }
    }
}

void ECConsoleUIListBox :: Delete()
{
    tRows.clear();
}

int ECConsoleUIListBox::Size() const {
    return tRows.size();
}

void ECConsoleUIListBox::ClearChoices() {
    tRows.clear();
}