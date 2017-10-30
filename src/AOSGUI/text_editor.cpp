/*
text_editor.cpp
This file is part of:
GAME PENCIL ENGINE
https://create.pawbyte.com
Copyright (c) 2014-2017 Nathan Hurde, Chase Lee.

Copyright (c) 2014-2017 PawByte.
Copyright (c) 2014-2017 Game Pencil Engine contributors ( Contributors Page )

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-Game Pencil Engine <https://create.pawbyte.com>


*/

#include "text_editor.h"
GPE_LogManager * GPE_Main_Logs = NULL;

GPE_TextAreaInputBasic::GPE_TextAreaInputBasic(bool saveFirstEdit)
{
    redrawDelay = 0;
    redrawDelayMax = 2;
    parseForErrorsTimerGoal = 60;
    parseForErrorsTimerPos = 0;
    missingSymbolDetected = false;
    missingSymbolStartXPos = 0;
    missingSymbolStartYPos = 0;
    misingSymbolSuggestedEndYPos = 0;
    misingSymbolSuggestedEndXPos = 0;

    highlightXPos = 0;
    highlightYPos = 0;
    guiListTypeName = "textarea";
    suggestedTextMaxInViewCount = 7;
    iSuggestedStartPos = 0;
    iSuggestionPos = 0;
    maxSuggestedTextWidth = 0;
    codeBeingSuggested = false;
    lastDoubleClickAction = 0;
    undoableActionOccurred = false;
    currentPositionInHistory = 0;
    hasLineBreak = true;
    isReadOnly = false;
    isCodeEditor = true;
    isTextLog= false;
    codeEditorType = 0;
    showXScroll = false;
    showYScroll = false;
    useWordWrap = false;
    displayMode = 0;
    cursorXPos = 0;
    cursorYPos = 0;
    prevCursorXPos = cursorXPos;
    prevCursorYPos = cursorYPos;
    cursorTimer = 0;
    showCursor = false;
    inputFieldPos = 0;
    maxLength = 2048;
    maxLineCount = 32768;
    lineCountBoxWidth = 48;
    lineStartXPos = 0;
    charactersWithinView = 16;
    linesWithinView = 4;
    lineStartYPos = 0;
    textInputString = "";
    lineToEdit = "";

    tabDelay = 0;
    bscDelay = 0;
    delDelay = 0;
    enterDelay = 0;
    upDelay = 0;
    downDelay = 0;
    leftDelay = 0;
    rightDelay = 0;
    dKeyDelay = 0;
    textXScroll = new GPE_ScrollBar_XAxis();
    textYScroll = new GPE_ScrollBar_YAxis();
    TEXTBOX_FONT_SIZE_WIDTH = 10;
    TEXTBOX_FONT_SIZE_HEIGHT = 10;
    if( FONT_TEXTINPUT!=NULL)
    {
         FONT_TEXTINPUT->get_metrics("A",&TEXTBOX_FONT_SIZE_WIDTH,&TEXTBOX_FONT_SIZE_HEIGHT);
    }
    textSpaceRect.x = 0;
    textSpaceRect.y = 0;
    textSpaceRect.w = 32;
    textSpaceRect.h = 32;

    textEditorButtonBar = NULL;
    create_buttonbar();

    selectionCursorXPos = 0;
    selectionCursorYPos = 0;
    selectionEndCursorXPos = 0;
    selectionEndCursorYPos = 0;


    symbolCursorXPos = -1;
    symbolCursorYPos = -1;
    symbolEndCursorXPos = -1;
    symbolEndCursorYPos = -1;

    commentLineText = new GPE_SyntaxLine();
    datatypeLineText = new GPE_SyntaxLine();
    functionLineText = new GPE_SyntaxLine();
    variableLineText = new GPE_SyntaxLine();
    projectFunctionLineText = new GPE_SyntaxLine();
    projectKeywordLineText = new GPE_SyntaxLine();
    keywordLineText = new GPE_SyntaxLine();
    normalLineText = new GPE_SyntaxLine();
    numberLineText = new GPE_SyntaxLine();
    dQuoteLineText = new GPE_SyntaxLine();
    sQuoteLineText = new GPE_SyntaxLine();
    symbolLineText = new GPE_SyntaxLine();
    clear_all_lines();
    listOfStrings.push_back("");
    barBox.w = 640;
    barBox.h = 480;
    if( saveFirstEdit)
    {
        save_edit();
    }
}

GPE_TextAreaInputBasic::GPE_TextAreaInputBasic(int newX, int newY, int boxW, int boxH,std::string startName,std::string placeHolderText, bool saveFirstEdit)
{
    redrawDelay = 0;
    redrawDelayMax = 2;
    parseForErrorsTimerGoal = 60;
    parseForErrorsTimerPos = 0;
    missingSymbolDetected = false;
    missingSymbolStartXPos = 0;
    missingSymbolStartYPos = 0;
    misingSymbolSuggestedEndYPos = 0;
    misingSymbolSuggestedEndXPos = 0;
    highlightXPos = 0;
    highlightYPos = 0;
    guiListTypeName = "textarea";
    codeBeingSuggested = false;
    maxSuggestedTextWidth= 0;
    suggestedTextMaxInViewCount = 7;
    iSuggestedStartPos = 0;
    iSuggestionPos = 0;
    lastDoubleClickAction = 0;
    undoableActionOccurred = false;
    currentPositionInHistory = 0;
    hasLineBreak = true;
    isCodeEditor = true;
    isTextLog= false;
    codeEditorType = 0;
    isReadOnly = false;
    isEnabled = true;
    barBox.x = newX;
    barBox.y = newY;
    barBox.w = boxW;
    barBox.h = boxH;
    textSpaceRect.x = newX;
    textSpaceRect.y = newY;
    textSpaceRect.w = boxW;
    textSpaceRect.h = boxH;
    showXScroll = false;
    showYScroll = false;
    useWordWrap = false;
    displayMode = 0;
    cursorXPos = 0;
    cursorYPos = 0;
    prevCursorXPos = cursorXPos;
    prevCursorYPos = cursorYPos;
    cursorTimer = 0;
    showCursor = false;
    inputFieldPos = 0;
    maxLength = 2048;
    maxLineCount = 32768;
    lineCountBoxWidth = 48;
    lineStartXPos = 0;
    charactersWithinView = 16;
    linesWithinView = 4;
    lineStartYPos = 0;
    placeHolderString = placeHolderText;
    textInputString = "";
    lineToEdit = "";
    listOfStrings.push_back("");
    bscDelay = 0;
    delDelay = 0;
    enterDelay = 0;
    upDelay = 0;
    downDelay = 0;
    leftDelay = 0;
    rightDelay = 0;
    dKeyDelay = 0;
    tabDelay=0;

    textXScroll = new GPE_ScrollBar_XAxis();
    textYScroll = new GPE_ScrollBar_YAxis();
    TEXTBOX_FONT_SIZE_WIDTH = 12;
    TEXTBOX_FONT_SIZE_HEIGHT = 12;
    if( FONT_TEXTINPUT!=NULL)
    {
         FONT_TEXTINPUT->get_metrics("A",&TEXTBOX_FONT_SIZE_WIDTH,&TEXTBOX_FONT_SIZE_HEIGHT);
    }
    textEditorButtonBar = NULL;
    create_buttonbar();

    selectionCursorXPos = 0;
    selectionCursorYPos = 0;
    selectionEndCursorXPos = 0;
    selectionEndCursorYPos = 0;

    symbolCursorXPos = -1;
    symbolCursorYPos = -1;
    symbolEndCursorXPos = -1;
    symbolEndCursorYPos = -1;

    commentLineText = new GPE_SyntaxLine();
    normalLineText = new GPE_SyntaxLine();
    datatypeLineText = new GPE_SyntaxLine();
    functionLineText = new GPE_SyntaxLine();
    numberLineText = new GPE_SyntaxLine();
    projectFunctionLineText = new GPE_SyntaxLine();
    projectKeywordLineText = new GPE_SyntaxLine();
    keywordLineText = new GPE_SyntaxLine();
    dQuoteLineText = new GPE_SyntaxLine();
    sQuoteLineText = new GPE_SyntaxLine();
    symbolLineText = new GPE_SyntaxLine();
    if( saveFirstEdit)
    {
        save_edit();
    }
}

GPE_TextAreaInputBasic::~GPE_TextAreaInputBasic()
{
    if( textXScroll!=NULL)
    {
        delete textXScroll;
        textXScroll = NULL;
    }

    if( textYScroll!=NULL)
    {
        delete textYScroll;
        textYScroll= NULL;
    }
    if( textEditorButtonBar!=NULL)
    {
        delete textEditorButtonBar;
        textEditorButtonBar = NULL;
    }
    if( commentLineText!=NULL)
    {
        delete commentLineText;
        commentLineText = NULL;
    }
    if( datatypeLineText!=NULL)
    {
        delete datatypeLineText;
        datatypeLineText = NULL;
    }
    if( dQuoteLineText!=NULL)
    {
        delete dQuoteLineText;
        dQuoteLineText = NULL;
    }
    if( functionLineText!=NULL)
    {
        delete functionLineText;
        functionLineText = NULL;
    }
    if( keywordLineText!=NULL)
    {
        delete keywordLineText;
        keywordLineText = NULL;
    }
    if( normalLineText!=NULL)
    {
        delete normalLineText;
        normalLineText = NULL;
    }

    if( numberLineText!=NULL)
    {
        delete numberLineText;
        numberLineText = NULL;
    }

    if( sQuoteLineText!=NULL)
    {
        delete sQuoteLineText;
        sQuoteLineText = NULL;
    }

    if( symbolLineText!=NULL)
    {
        delete symbolLineText;
        symbolLineText = NULL;
    }

    if( projectFunctionLineText!=NULL)
    {
        delete projectFunctionLineText;
        projectFunctionLineText = NULL;
    }

    if( projectKeywordLineText!=NULL)
    {
        delete projectKeywordLineText;
        projectKeywordLineText = NULL;
    }
    if( variableLineText!=NULL)
    {
        delete variableLineText;
        variableLineText = NULL;
    }
    int iD = 0;
    GPE_TextAreaInputBasic * tempText = NULL;
    for( iD = (int)savedHistory.size()-1; iD >=0; iD--)
    {
        tempText = savedHistory.at(iD);
        if( tempText!=NULL)
        {
            delete tempText;
            tempText = NULL;
        }
    }

    GPE_TextAnchor * tempAnchor = NULL;
    for( iD = (int)anchorPositions.size()-1; iD >=0; iD--)
    {
        tempAnchor = anchorPositions.at(iD);
        if( tempAnchor!=NULL)
        {
            delete tempAnchor;
            tempAnchor = NULL;
        }
    }
    savedHistory.clear();
    listOfStrings.clear();
    if( textEditorButtonBar!=NULL)
    {
        delete textEditorButtonBar;
        textEditorButtonBar = NULL;
    }
}

void GPE_TextAreaInputBasic::activate_self()
{
    isEnabled = true;
    isInUse = true;
    isClicked = true;
    showCursor = true;
    cursorTimer = 0;
}

void GPE_TextAreaInputBasic::add_line( std::string newLine, bool scrollToBottom)
{
    listOfStrings.push_back( trim_right_inplace(newLine) );
    if( scrollToBottom)
    {
        scroll_to_pos( (int)listOfStrings.size()-1, 0 );
    }
}

void GPE_TextAreaInputBasic::adjust_fortabs()
{
    if( cursorXPos > 0 && MAIN_GUI_SETTINGS!=NULL && MAIN_GUI_SETTINGS->autoFindMouseTabs )
    {
        if( (int)listOfStrings.size() > cursorYPos )
        {
            std::string currStrToCheck = listOfStrings[cursorYPos];
            int currLineSize = (int)currStrToCheck.size();
            if( currLineSize > cursorXPos )
            {
                if( (int)currStrToCheck[cursorXPos]==' ')
                {
                    int preSpacesCounted = 0;
                    int postSpacesCounted = 0;
                    int allSpacesCounted = 0;
                    int i = 0;

                    for( i = cursorXPos-1; i>= 0; i--)
                    {
                        if( currStrToCheck[i]==' ')
                        {
                            preSpacesCounted++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    for( i = cursorXPos+1; i < currLineSize; i++)
                    {
                        if( currStrToCheck[i]==' ')
                        {
                            postSpacesCounted++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    allSpacesCounted = preSpacesCounted+postSpacesCounted+1;
                    preSpacesCounted = preSpacesCounted%MAIN_GUI_SETTINGS->tabSpaceCount;
                    postSpacesCounted = postSpacesCounted%MAIN_GUI_SETTINGS->tabSpaceCount;
                    if( allSpacesCounted%MAIN_GUI_SETTINGS->tabSpaceCount==0)
                    {
                        if( preSpacesCounted >postSpacesCounted )
                        {
                            cursorXPos+=postSpacesCounted+1;
                        }
                        else
                        {
                            cursorXPos-=preSpacesCounted;
                        }
                        scroll_to_cursor();
                    }
                }
            }
            else
            {
                cursorXPos = (int)currStrToCheck.size();
            }
        }
    }
}

bool GPE_TextAreaInputBasic::can_redo()
{
    if( currentPositionInHistory >=0 && currentPositionInHistory <= (int)savedHistory.size()-1)
    {
        return true;
    }
    return false;
}

bool GPE_TextAreaInputBasic::can_undo()
{
    if( currentPositionInHistory > 0 && (int)savedHistory.size() > 0)
    {
        return true;
    }
    return false;
}

void GPE_TextAreaInputBasic::clear_line(int lineNumber)
{

}

void GPE_TextAreaInputBasic::clear_all_lines()
{
    listOfStrings.clear();
    cursorXPos = 0;
    cursorYPos = 0;
    selectionCursorXPos = 0;
    selectionCursorYPos = 0;
    selectionEndCursorXPos = 0;
    selectionEndCursorYPos = 0;
    lineStartYPos = 0;
    linesWithinView = 0;
}

void GPE_TextAreaInputBasic::clear_text_anchors()
{
    if( (int)anchorPositions.size() > 0)
    {
        GPE_TextAnchor * tAnchor = NULL;
        for( int i = (int)anchorPositions.size()-1; i >=0; i--)
        {
            tAnchor = anchorPositions[i];
            delete tAnchor;
            tAnchor = NULL;
        }
        anchorPositions.clear();
    }
}

void GPE_TextAreaInputBasic::create_buttonbar()
{
    if( textEditorButtonBar!=NULL)
    {
        delete textEditorButtonBar;
        textEditorButtonBar = NULL;
    }
    textEditorButtonBar = new GPE_ToolIconButtonBar(0, 0,24);
    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/plane.png","Export Text",TEXTAREA_OPTION_EXPORT,false );
    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/file.png","Import Text",TEXTAREA_OPTION_IMPORT,true );
    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/eraser.png","Clear Text ",TEXTAREA_OPTION_CLEAR );
    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/backward.png","Undo Action",TEXTAREA_OPTION_UNDO,false );
    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/forward.png","Redo Action",TEXTAREA_OPTION_REDO,true );

    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/cut.png","Cut",TEXTAREA_OPTION_CUT,false );
    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/copy.png","Copy",TEXTAREA_OPTION_COPY,true );
    textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/paste.png","Paste",TEXTAREA_OPTION_PASTE,true );

    //textEditorButtonBar->adkb_dton(APP_DIRECTORY_NAME+"resources/gfx/buttons/info.png","Text Info (Not Available Yet)",TEXTAREA_OPTION_TEXTINFO,true );
    textEditorButtonBar->limit_width(true);
}

void GPE_TextAreaInputBasic::copy_selection()
{
    if( selectionCursorYPos >=0 && selectionCursorYPos < (int)listOfStrings.size() && selectionEndCursorYPos >=0 && selectionEndCursorYPos < (int)listOfStrings.size() )
    {
        int minHighlightXPos = 0, maxHighlightXPos = 0;
        std::string newClipBoardText = "";
        std::string strToCopy = "";
        if(selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos)
        {
            std::string tempStrToUse = "";
            int minHighlightYPos = std::min(selectionCursorYPos, selectionEndCursorYPos);
            int maxHighlightYPos = std::max(selectionCursorYPos, selectionEndCursorYPos);

            if( selectionCursorYPos > selectionEndCursorYPos)
            {
                minHighlightXPos = selectionEndCursorXPos;
                maxHighlightXPos = selectionCursorXPos;
            }
            else
            {
                maxHighlightXPos = selectionEndCursorXPos;
                minHighlightXPos = selectionCursorXPos;
            }
            if(minHighlightYPos!=maxHighlightYPos)
            {
                tempStrToUse = listOfStrings.at(minHighlightYPos);
                strToCopy = get_substring(tempStrToUse,minHighlightXPos,(int)std::string::npos);
                if( maxHighlightYPos-minHighlightYPos > 1)
                {
                    for( int i= minHighlightYPos+1; i <=maxHighlightYPos-1; i++ )
                    {
                        tempStrToUse = listOfStrings[i];
                        strToCopy += "\n"+tempStrToUse;
                    }
                }
                tempStrToUse = listOfStrings.at(maxHighlightYPos);
                strToCopy += "\n"+get_substring(tempStrToUse,0,maxHighlightXPos);
            }
            else
            {
                strToCopy = listOfStrings.at(selectionCursorYPos);
                minHighlightXPos = std::min(selectionCursorXPos, selectionEndCursorXPos);
                maxHighlightXPos = std::max(selectionCursorXPos, selectionEndCursorXPos);
                strToCopy = get_substring(strToCopy,minHighlightXPos,maxHighlightXPos-minHighlightXPos);
            }
            SDL_SetClipboardText(strToCopy.c_str() );
            //MAIN_OVERLAY->update_temporary_message("Selection copied","","",0.25);
        }
    }
}

bool GPE_TextAreaInputBasic::compile_into_code(std::ofstream * fileTarget, int leftTabAmount, bool useNewLines, bool useLastNewLine )
{
    if( fileTarget!=NULL && leftTabAmount >=0)
    {
        if( fileTarget->is_open() )
        {
            std::string nestedTabsStr = generate_tabs( leftTabAmount  );
            if( !parse_code_javascript() )
            {
                return false;
            }
            int strSize = (int)listOfStrings.size();

            for( int i = 0; i < strSize-1; i++)
            {
                if( (int)listOfStrings[i].size() > 0 )
                {
                    if( useNewLines)
                    {
                        *fileTarget << nestedTabsStr+listOfStrings[i] << "\n";
                    }
                    else
                    {
                        *fileTarget <<nestedTabsStr+listOfStrings[i] << " ";
                    }
                }
            }
            if( (int)listOfStrings[strSize-1].size() > 0 )
            {
                if( useNewLines)
                {
                    if( useLastNewLine)
                    {
                        *fileTarget << nestedTabsStr+listOfStrings[strSize-1] << "\n";
                    }
                    else
                    {
                        *fileTarget << nestedTabsStr+listOfStrings[strSize-1];
                    }
                }
                else
                {
                    *fileTarget <<nestedTabsStr+listOfStrings[strSize-1] << " ";
                }
            }
            return true;
        }
    }
    return false;
}

int GPE_TextAreaInputBasic::compare_with(GPE_TextAreaInputBasic * other)
{
    if( other!=NULL)
    {
        if( (int)listOfStrings.size() == (int)other->listOfStrings.size()  && (int)listOfStrings.size() > 0 )
        {
            std::string myString = "";
            std::string otherString = "";
            for( int i = (int)listOfStrings.size()-1; i>=0; i--)
            {
                myString = listOfStrings[i];
                otherString = other->listOfStrings[i];
                if( (int)myString.size()==(int)otherString.size() )
                {
                    if( myString.compare(otherString)!=0 )
                    {
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
            }
            return 1;
        }
        return 0;
    }
    return -1;
}

bool GPE_TextAreaInputBasic::copy_all()
{
    if( has_content() )
    {
        std::string superLongClipboardStr = "";
        for( int i = 0; i < (int)listOfStrings.size(); i++)
        {
            superLongClipboardStr+=listOfStrings[i]+"\n";
        }
        if( SDL_SetClipboardText( superLongClipboardStr.c_str() )!=0 )
        {
           return false;
        }
        return true;
    }
    return false;
}

void GPE_TextAreaInputBasic::copy_source(GPE_TextAreaInputBasic * other, bool overwriteSelf)
{
    if( other!=NULL)
    {
        if( overwriteSelf)
        {
            clear_all_lines();
        }
        cursorXPos = other->cursorXPos;
        cursorYPos = other->cursorYPos;
        lineStartXPos = other->lineStartXPos;
        lineStartYPos = other->lineStartYPos;
        selectionCursorXPos = other->selectionCursorXPos;
        selectionCursorYPos = other->selectionCursorYPos;
        selectionEndCursorXPos= other->selectionEndCursorXPos;
        selectionEndCursorYPos = other->selectionEndCursorYPos;

        for( int i = 0; i < (int)other->listOfStrings.size(); i++)
        {
            listOfStrings.push_back( other->listOfStrings[i] );
        }
    }
}

void GPE_TextAreaInputBasic::cut_selection()
{
    if( !isReadOnly)
    {
        copy_selection();
        delete_selection();
    }
}

void GPE_TextAreaInputBasic::delete_content()
{

}

void GPE_TextAreaInputBasic::delete_selection()
{
    if( !isReadOnly)
    {
        if( selectionCursorYPos >=0 && selectionCursorYPos < (int)listOfStrings.size() && selectionEndCursorYPos >=0 && selectionEndCursorYPos < (int)listOfStrings.size() )
        {
            if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos)
            {
                int minHighlightXPos = 0, maxHighlightXPos = 0;
                std::string newClipBoardText = "";
                std::string strToCopy = "";
                std::string tempStrToUse = "";
                if(selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos)
                {
                    int minHighlightYPos = std::min(selectionCursorYPos, selectionEndCursorYPos);
                    int maxHighlightYPos = std::max(selectionCursorYPos, selectionEndCursorYPos);

                    if( selectionCursorYPos > selectionEndCursorYPos)
                    {
                        minHighlightXPos = selectionEndCursorXPos;
                        maxHighlightXPos = selectionCursorXPos;
                    }
                    else
                    {
                        maxHighlightXPos = selectionEndCursorXPos;
                        minHighlightXPos = selectionCursorXPos;
                    }

                    if(minHighlightYPos!=maxHighlightYPos)
                    {
                        tempStrToUse = listOfStrings.at(minHighlightYPos);
                        if( minHighlightXPos >= 0)
                        {
                            strToCopy = get_substring(tempStrToUse,0,minHighlightXPos);
                        }
                        tempStrToUse = listOfStrings.at(maxHighlightYPos);
                        if( maxHighlightXPos <= (int)tempStrToUse.size() )
                        {
                            strToCopy += get_substring(tempStrToUse,maxHighlightXPos);
                        }
                        for( int i=maxHighlightYPos; i >= minHighlightYPos;i-- )
                        {
                            listOfStrings.erase(listOfStrings.begin()+i);
                        }
                        if( (int)strToCopy.size() > 0)
                        {
                            cursorXPos = selectionCursorXPos = selectionEndCursorXPos = minHighlightXPos;
                            cursorYPos = selectionCursorYPos = selectionEndCursorYPos = minHighlightYPos;
                            listOfStrings.insert(listOfStrings.begin()+minHighlightYPos,strToCopy);
                        }
                        else if( (int)listOfStrings.size() > minHighlightYPos)
                        {
                            listOfStrings.insert(listOfStrings.begin()+minHighlightYPos,"");
                            cursorXPos = selectionCursorXPos = selectionEndCursorXPos = 0;
                            cursorYPos = selectionCursorYPos = selectionEndCursorYPos = minHighlightYPos;
                        }
                        else
                        {
                            listOfStrings.push_back("");
                            cursorXPos = selectionCursorXPos = selectionEndCursorXPos = 0;
                            cursorYPos = selectionCursorYPos = selectionEndCursorYPos = (int)listOfStrings.size()-1;
                        }
                    }
                    else
                    {
                        minHighlightXPos = std::min(selectionCursorXPos, selectionEndCursorXPos);
                        maxHighlightXPos = std::max(selectionCursorXPos, selectionEndCursorXPos);
                        tempStrToUse = listOfStrings.at(selectionCursorYPos);
                        strToCopy = get_substring(tempStrToUse,0,minHighlightXPos);
                        strToCopy += get_substring(tempStrToUse,maxHighlightXPos);
                        listOfStrings.erase(listOfStrings.begin()+minHighlightYPos);
                        if( strToCopy.size() > 0)
                        {
                            listOfStrings.insert(listOfStrings.begin()+minHighlightYPos,strToCopy);
                            cursorXPos = selectionCursorXPos = selectionEndCursorXPos = minHighlightXPos;
                            cursorYPos = selectionCursorYPos = selectionEndCursorYPos = minHighlightYPos;
                        }
                        else if( (int)listOfStrings.size() > minHighlightYPos)
                        {
                            listOfStrings.insert(listOfStrings.begin()+minHighlightYPos,"");
                            tempStrToUse = listOfStrings.at(minHighlightYPos);
                            cursorXPos = selectionCursorXPos = selectionEndCursorXPos = 0;
                            cursorYPos = selectionCursorYPos = selectionEndCursorYPos = minHighlightYPos;
                        }
                        else
                        {
                            listOfStrings.push_back("");
                            cursorXPos = selectionCursorXPos = selectionEndCursorXPos = 0;
                            cursorYPos = selectionCursorYPos = selectionEndCursorYPos = (int)listOfStrings.size()-1;
                        }
                    }
                    save_edit();
                }
            }

            if( listOfStrings.size() <=0)
            {
                listOfStrings.push_back("");
                cursorXPos = selectionCursorXPos = selectionEndCursorXPos = 0;
                cursorYPos = selectionCursorYPos = selectionEndCursorYPos = 0;
                save_edit();
            }
            if( cursorXPos < 0)
            {
                cursorXPos = selectionCursorXPos = selectionEndCursorXPos = 0;
                cursorYPos = selectionCursorYPos = selectionEndCursorYPos = (int)listOfStrings.size()-1;
            }
            lineToEdit = listOfStrings[cursorYPos];

        }
        else
        {
            cursorXPos = selectionCursorXPos = selectionEndCursorXPos = 0;
            cursorYPos = selectionCursorYPos = selectionEndCursorYPos = 0;
            lineToEdit = listOfStrings[cursorYPos];
        }
    }
}

void GPE_TextAreaInputBasic::duplicate_text()
{
    if( !isReadOnly)
    {
        std::string prevClipboard = SDL_GetClipboardText();

        if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
        {
            //adds selection to below...
            if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos)
            {
                copy_selection();
                if( selectionCursorYPos > selectionEndCursorYPos)
                {
                    cursorXPos = selectionCursorXPos;
                    cursorYPos = selectionCursorYPos;
                }
                else
                {
                    if( selectionCursorXPos > selectionEndCursorXPos)
                    {
                        cursorXPos = selectionCursorXPos;
                        cursorYPos = selectionEndCursorYPos;
                    }
                    else
                    {
                        cursorXPos = selectionEndCursorXPos;
                        cursorYPos = selectionEndCursorYPos;
                    }
                }
                int prevCX = cursorXPos;
                int prevCY = cursorYPos;
                paste_clipboard();
                cursorXPos = prevCX;
                cursorYPos = prevCY;
                SDL_SetClipboardText(prevClipboard.c_str() );
            }
            else
            {
                std::string cLineToCopy = listOfStrings[cursorYPos];
                listOfStrings.insert(listOfStrings.begin()+cursorYPos+1,cLineToCopy);
                save_edit();
            }
        }
    }
}

void GPE_TextAreaInputBasic::export_text(std::string newFileName)
{
    if( !newFileName.empty() )
    {
        std::ofstream myfile (newFileName.c_str() );
        if (myfile.is_open())
        {
            int strSize = (int)listOfStrings.size();
            for( int i = 0; i < strSize; i++)
            {
                if( i !=strSize-1)
                {
                    myfile << listOfStrings[i] << "\n";
                }
                else
                {
                    myfile << listOfStrings[i];
                }
            }
            myfile.close();
        }
        else
        {
            display_user_alert("Unable to save text",newFileName);
        }
    }
}

void GPE_TextAreaInputBasic::export_text_anchors(std::string newFileName)
{
    if( !newFileName.empty() )
    {
        std::ofstream myfile (newFileName.c_str() );
        if (myfile.is_open())
        {
            int strSize = (int)anchorPositions.size();
            GPE_TextAnchor * tAnchor = NULL;
            for( int i = 0; i < strSize; i++)
            {
                tAnchor = anchorPositions[i];
                if( tAnchor!=NULL)
                {
                    myfile <<  tAnchor->lineNumber << "," << tAnchor->characterNumber;
                    if( i !=strSize-1)
                    {
                        myfile << "\n";
                    }
                }
            }
            myfile.close();
        }
        else
        {
            display_user_alert("Unable to save text anchors",newFileName);
        }
    }
}

int GPE_TextAreaInputBasic::find_all_strings(std::string strTarget,bool matchCase, bool addAnchor, std::string areaTitle)
{
    int stringsFoundInSearch = 0;
    if( strTarget.size() > 0)
    {
        //int tempXCursor = cursorXPos;
        //int tempYCursor = cursorYPos;
        int tempLineXStart = lineStartXPos;
        int tempLineYStart = lineStartYPos;
        GPE_TextAnchor * nTextAnchor = NULL;
        clear_text_anchors();
        cursorXPos = 0;
        cursorYPos = 0;
        clear_text_anchors();
        while( find_string(strTarget,true,matchCase,false) ==true)
        {
            //add to list
            stringsFoundInSearch++;
            if( addAnchor && GPE_Main_Logs!=NULL)
            {
                nTextAnchor = new GPE_TextAnchor(selectionCursorYPos,selectionCursorXPos,areaTitle,"",GPE_ANCHOR_REGULAR);
                GPE_Main_Logs->log_general_comment( "Adding anchor.." );
                GPE_Main_Logs->searchAnchors.push_back(nTextAnchor);
            }
            else
            {
                nTextAnchor = new GPE_TextAnchor(selectionCursorYPos,selectionCursorXPos,"Found ["+strTarget+"]","",GPE_ANCHOR_REGULAR);
                anchorPositions.push_back(nTextAnchor);
            }
            cursorXPos+=(int)strTarget.size();
        }
        selectionCursorXPos = selectionEndCursorXPos = 0;
        selectionCursorYPos = selectionEndCursorYPos = 0;
        scroll_to_pos(tempLineYStart,tempLineXStart);
    }
    return stringsFoundInSearch;
}

void GPE_TextAreaInputBasic::find_mouse_cursor(int *mXCursor, int *mYCursor, GPE_Rect * viewedSpace, GPE_Rect * cam )
{
    viewedSpace = GPE_find_camera(viewedSpace);
    cam = GPE_find_camera(cam);
    if( viewedSpace!=NULL && cam!=NULL && (int)listOfStrings.size() > 0)
    {
        if( point_within_rect(userInput->mouse_x,userInput->mouse_y,&textSpaceRect)  )
        {
            *mYCursor = (float)(userInput->mouse_y - viewedSpace->y-textEditorButtonBar->get_y2pos()+cam->y)/(float)GPE_AVERAGE_LINE_HEIGHT; //gets the barBox.y pos essentially
            *mYCursor+=lineStartYPos;
            if( *mYCursor < lineStartYPos)
            {
                *mYCursor = lineStartYPos;
            }
            if( *mYCursor >= (int)listOfStrings.size() )
            {
                *mYCursor = (int)listOfStrings.size() - 1;
            }

            if( *mYCursor < 0 )
            {
                *mYCursor = 0;
            }
            if( (int)listOfStrings.size()==0)
            {
                listOfStrings.push_back("");
            }
            if( MAIN_GUI_SETTINGS->showTextEditorLineCount )
            {
                *mXCursor = (float)(userInput->mouse_x - barBox.x-viewedSpace->x-lineCountBoxWidth+cam->x)/TEXTBOX_FONT_SIZE_WIDTH+lineStartXPos;
            }
            else
            {
                *mXCursor = (float)(userInput->mouse_x - barBox.x-viewedSpace->x+cam->x)/TEXTBOX_FONT_SIZE_WIDTH+lineStartXPos;
            }
            std::string newString = listOfStrings.at(*mYCursor);
            int maxCursorSpace = (int)newString.size();
            if( *mXCursor > maxCursorSpace )
            {
                *mXCursor = maxCursorSpace;
            }
            if( *mXCursor < 0 )
            {
                *mXCursor = 0;
            }
        }
    }
}

bool GPE_TextAreaInputBasic::find_connected_symbols()
{
    symbolCursorXPos = -1;
    symbolCursorYPos = -1;
    symbolEndCursorXPos = -1;
    symbolEndCursorYPos = -1;
    if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
    {
        lineToEdit =listOfStrings[cursorYPos];
        int seekedCursorYPos = cursorYPos;
        if( (int)lineToEdit.size() > 0)
        {
            int fCursorXPos = cursorXPos;
            std::string beginSymbol;
            std::string endSymbol;
            std::string charStr = "";
            bool foundBookedSymbol = false;
            bool searchForEndSymbol = false;;

            int subStrSearchBeginPos = cursorXPos;
            int subStrSearchEndPos = cursorXPos;
            int foundOtherMatches = 0;
            int foundSeekedMatches = 0;
            if( cursorXPos >=0 && cursorXPos <(int)lineToEdit.size() )
            {
                fCursorXPos = cursorXPos;
                subStrSearchBeginPos = fCursorXPos;
                subStrSearchEndPos = fCursorXPos;
            }
            charStr = get_substring(lineToEdit,fCursorXPos,1);
            if( charStr =="(")
            {
                beginSymbol = "(";
                endSymbol = ")";
                symbolCursorXPos = fCursorXPos;
                symbolCursorYPos = cursorYPos;
                foundBookedSymbol = true;
                searchForEndSymbol = true;
            }
            else if( charStr =="{")
            {
                beginSymbol = "{";
                endSymbol = "}";
                symbolCursorXPos = fCursorXPos;
                symbolCursorYPos = cursorYPos;
                foundBookedSymbol = true;
                searchForEndSymbol = true;
             }
            else if( charStr =="[")
            {
                beginSymbol = "[";
                endSymbol = "]";
                symbolCursorXPos = fCursorXPos;
                symbolCursorYPos = cursorYPos;
                foundBookedSymbol = true;
                searchForEndSymbol = true;
            }
            else if( charStr ==")")
            {
                beginSymbol = "(";
                endSymbol = ")";
                symbolEndCursorXPos = fCursorXPos;
                symbolEndCursorYPos = cursorYPos;
                foundBookedSymbol = true;
            }
            else if( charStr =="}")
            {
                beginSymbol = "{";
                endSymbol = "}";
                symbolEndCursorXPos = fCursorXPos;
                symbolEndCursorYPos = cursorYPos;
                foundBookedSymbol = true;
            }
            else if( charStr =="]")
            {
                beginSymbol = "[";
                endSymbol = "]";
                symbolEndCursorXPos = fCursorXPos;
                symbolEndCursorYPos = cursorYPos;
                foundBookedSymbol = true;
            }

            if( foundBookedSymbol==false && fCursorXPos-1>=0 && fCursorXPos-1 < (int)lineToEdit.size() )
            {
                charStr = get_substring(lineToEdit,fCursorXPos-1,1);
                if( charStr =="(")
                {
                    beginSymbol = "(";
                    endSymbol = ")";
                    symbolCursorXPos = fCursorXPos-1;
                    symbolCursorYPos = cursorYPos;
                    foundBookedSymbol = true;
                    searchForEndSymbol = true;
                    fCursorXPos-=1;
                }
                else if( charStr =="{")
                {
                    beginSymbol = "{";
                    endSymbol = "}";
                    symbolCursorXPos = fCursorXPos-1;
                    symbolCursorYPos = cursorYPos;
                    foundBookedSymbol = true;
                    searchForEndSymbol = true;
                    fCursorXPos-=1;
                 }
                else if( charStr =="[")
                {
                    beginSymbol = "[";
                    endSymbol = "]";
                    symbolCursorXPos = fCursorXPos-1;
                    symbolCursorYPos = cursorYPos;
                    foundBookedSymbol = true;
                    searchForEndSymbol = true;
                    fCursorXPos-=1;
                }
                else if( charStr ==")")
                {
                    beginSymbol = "(";
                    endSymbol = ")";
                    symbolEndCursorXPos = fCursorXPos-1;
                    symbolEndCursorYPos = cursorYPos;
                    foundBookedSymbol = true;
                    fCursorXPos-=1;
                }
                else if( charStr =="}")
                {
                    beginSymbol = "{";
                    endSymbol = "}";
                    symbolEndCursorXPos = fCursorXPos-1;
                    symbolEndCursorYPos = cursorYPos;
                    foundBookedSymbol = true;
                    fCursorXPos-=1;
                }
                else if( charStr =="]")
                {
                    beginSymbol = "[";
                    endSymbol = "]";
                    symbolEndCursorXPos = fCursorXPos-1;
                    symbolEndCursorYPos = cursorYPos;
                    foundBookedSymbol = true;
                    fCursorXPos-=1;
                }
            }

            if( fCursorXPos >= (int)lineToEdit.size() )
            {
                fCursorXPos = (int)lineToEdit.size()-1;
            }

            if( foundBookedSymbol )
            {
                std::string searchedStr = listOfStrings[seekedCursorYPos];
                std::string tempStr;
                int prevFoundXPos = 0;
                if( searchForEndSymbol)
                {
                    foundOtherMatches = 0;
                    foundSeekedMatches = 0;
                    prevFoundXPos = symbolCursorXPos+1;
                    while( seekedCursorYPos < (int)listOfStrings.size() )
                    {
                        searchedStr = listOfStrings[seekedCursorYPos];

                        if( prevFoundXPos!=(int)std::string::npos)
                        {
                            subStrSearchBeginPos = searchedStr.find(beginSymbol,prevFoundXPos);
                            subStrSearchEndPos = searchedStr.find(endSymbol,prevFoundXPos);

                            if( subStrSearchBeginPos!=(int)std::string::npos && subStrSearchEndPos!=(int)std::string::npos)
                            {
                                if( subStrSearchBeginPos > subStrSearchEndPos)
                                {
                                    foundSeekedMatches++;
                                    prevFoundXPos = subStrSearchEndPos+1;
                                }
                                else
                                {
                                    foundOtherMatches++;
                                    prevFoundXPos = subStrSearchBeginPos+1;
                                }
                            }
                            else if(subStrSearchEndPos!=(int)std::string::npos)
                            {
                                foundSeekedMatches++;
                                prevFoundXPos = subStrSearchEndPos+1;
                            }
                            else if(subStrSearchBeginPos!=(int)std::string::npos)
                            {
                                foundOtherMatches++;
                                prevFoundXPos = subStrSearchBeginPos+1;
                            }
                            else
                            {
                                seekedCursorYPos++;
                                prevFoundXPos = subStrSearchBeginPos = 0;
                                subStrSearchEndPos = 0;
                            }

                            if( foundSeekedMatches > foundOtherMatches )
                            {
                                symbolEndCursorXPos = subStrSearchEndPos;
                                symbolEndCursorYPos = seekedCursorYPos;
                                return true;
                            }
                        }

                        if( subStrSearchBeginPos >=(int)searchedStr.size() )
                        {
                            subStrSearchBeginPos = (int)std::string::npos ;
                        }
                        if( subStrSearchEndPos >=(int)searchedStr.size() )
                        {
                            subStrSearchEndPos = (int)std::string::npos ;
                        }
                        if( subStrSearchBeginPos==(int)std::string::npos && subStrSearchEndPos==(int)std::string::npos)
                        {
                            seekedCursorYPos++;
                            prevFoundXPos = subStrSearchBeginPos = subStrSearchEndPos = 0;
                        }
                    }
                }
                else
                {
                    //reverse iterate
                    foundOtherMatches = 0;
                    foundSeekedMatches = 0;
                    subStrSearchBeginPos = prevFoundXPos;
                    subStrSearchEndPos = prevFoundXPos;
                    seekedCursorYPos = cursorYPos;

                    if( symbolEndCursorXPos > 0)
                    {
                        prevFoundXPos = symbolEndCursorXPos-1;
                    }
                    else if( seekedCursorYPos > 0 && seekedCursorYPos <(int)listOfStrings.size() )
                    {
                        seekedCursorYPos -=1;
                        searchedStr = listOfStrings[seekedCursorYPos];
                        prevFoundXPos = (int)searchedStr.size()-1;
                    }
                    else
                    {
                        return false;
                    }

                    int cSearchCursorXPos = 0;

                    while( seekedCursorYPos >= 0 )
                    {
                        searchedStr = listOfStrings[seekedCursorYPos];

                        for( cSearchCursorXPos = prevFoundXPos; cSearchCursorXPos>=0; cSearchCursorXPos--)
                        {
                            charStr = get_substring(searchedStr,cSearchCursorXPos,1);
                            if( charStr ==beginSymbol)
                            {
                                foundSeekedMatches++;
                            }
                            else if( charStr ==endSymbol)
                            {
                                foundOtherMatches++;
                            }
                            if( foundSeekedMatches > foundOtherMatches )
                            {
                                symbolCursorXPos = cSearchCursorXPos;
                                symbolCursorYPos = seekedCursorYPos;
                                return true;
                            }
                        }
                        seekedCursorYPos--;
                        if( seekedCursorYPos>=0 && seekedCursorYPos < (int)listOfStrings.size() )
                        {
                            searchedStr = listOfStrings[seekedCursorYPos];
                            prevFoundXPos = (int)searchedStr.size()-1;
                        }
                    }
                }
            }
        }
    }
    symbolCursorXPos = -1;
    symbolCursorYPos = -1;
    symbolEndCursorXPos = -1;
    symbolEndCursorYPos = -1;
    return false;
}

bool GPE_TextAreaInputBasic::find_string(std::string strTarget, bool searchDown, bool matchCase, bool startAtFront)
{
    if( (int)strTarget.size() > 0 && has_content() )
    {
        int searchCursorXPos = 0;
        int searchCursorYPos = 0;
        std::size_t foundSubXPos;
        int foundSubYPos = 0;
        std::string strToSearch = "";
        if( searchDown)
        {
            //search down
            if( startAtFront==false)
            {
                searchCursorXPos = cursorXPos;
                searchCursorYPos = cursorYPos;
            }
            if( searchCursorYPos <0 || searchCursorYPos >= (int)listOfStrings.size() )
            {
                searchCursorYPos = 0;
            }
            strToSearch = listOfStrings.at(searchCursorYPos);
            foundSubXPos= strToSearch.find(strTarget, searchCursorXPos);
            if( (int)foundSubXPos!=(int)std::string::npos)
            {
                foundSubYPos = searchCursorYPos;
                selectionCursorXPos = foundSubXPos;
                cursorXPos = selectionEndCursorXPos = foundSubXPos+(int)strTarget.size();
                cursorYPos = selectionCursorYPos = foundSubYPos;
                selectionEndCursorYPos = foundSubYPos;
                scroll_to_selection();
                return true;
            }
            else
            {
                for( int i = searchCursorYPos+1; i < (int)listOfStrings.size();i++)
                {
                    strToSearch = listOfStrings[i];
                    foundSubXPos= strToSearch.find(strTarget, 0);
                    if( (int)foundSubXPos!=(int)std::string::npos)
                    {
                        foundSubYPos = i;
                        selectionCursorXPos = foundSubXPos;
                        cursorXPos = selectionEndCursorXPos = foundSubXPos+(int)strTarget.size();
                        cursorYPos = selectionCursorYPos = foundSubYPos;
                        selectionEndCursorYPos = foundSubYPos;
                        scroll_to_selection();
                        return true;
                    }
                }
            }
        }
        else
        {
            //search up
            if( startAtFront==false)
            {
                searchCursorYPos = listOfStrings.size()-1;
                searchCursorXPos = (listOfStrings.at(searchCursorYPos).size() );
            }
            else
            {
                searchCursorXPos = cursorXPos;
                searchCursorYPos = cursorYPos;
            }
        }
    }
    return false;
}

void GPE_TextAreaInputBasic::find_documentation_description(int tCursorX, int tCursorY)
{
    documentationIsBeingShown = false;
    iSuggestedStartPos = 0;
    iSuggestionPos = 0;
    int  i = 0;

    if( tCursorY < 0)
    {
        tCursorY = cursorYPos;
    }

    if( tCursorX < 0)
    {
        tCursorX = cursorXPos;
    }

    if( tCursorY >=(int)listOfStrings.size() )
    {
        tCursorY = (int)listOfStrings.size() -1;
    }


    if( !codeBeingSuggested && tCursorY >=0 && tCursorY < (int)listOfStrings.size() && isCodeEditor)
    {
        maxSuggestedTextWidth = 0;
        std::string currentStringInView = "";
        tempCLineXStartPos = 0;
        tempCLineXEndPos = tCursorX;
        //int tempCLineYPos = tCursorY;
        std::string cLineToParse = listOfStrings.at(tCursorY);
        GPE_Compiler_Term * tempTerm = NULL;
        highlightXPos = tCursorX;
        highlightYPos = tCursorY;
        if( tCursorX >=0 && (int)tCursorX <=(int)cLineToParse.size() && (int)cLineToParse.size() > 0)
        {
            if( tCursorX==(int)cLineToParse.size() )
            {
                tempCLineXEndPos = tCursorX-1;
            }
            if( tempCLineXEndPos < 0)
            {
                tempCLineXEndPos = 0;
            }
            //goes back one if character isn't alpha numeric
            if( !char_is_alnum(cLineToParse[tempCLineXEndPos],false,true) )
            {
                if( (int)cLineToParse.size() > tempCLineXEndPos-1)
                {
                    if( char_is_alnum(cLineToParse[tempCLineXEndPos-1],false,true) )
                    {
                        tempCLineXEndPos--;
                    }
                }
            }
            //makes sure our subtext is alphanumeric without spaces
            if( char_is_alnum(cLineToParse[tempCLineXEndPos],false,true) )
            {
                int formerEndLinePos = tempCLineXEndPos;
                for( i = formerEndLinePos-1; i< (int)cLineToParse.size(); i++)
                {
                    if( char_is_alnum(cLineToParse[i],false,true) ==false )
                    {
                        tempCLineXEndPos = i-1;
                        break;
                    }
                    else
                    {
                        tempCLineXEndPos = i;
                    }
                }

                for( i = tempCLineXEndPos-1; i >=0; i--)
                {
                    if( char_is_alnum(cLineToParse[i],false,true) ==false )
                    {
                        tempCLineXStartPos = i+1;
                        break;
                    }
                    else
                    {
                        tempCLineXStartPos = i;
                    }
                }
                if( tempCLineXStartPos > lineStartXPos)
                {
                    highlightXPos = tempCLineXStartPos;
                }
                //makes sure the length is long enough to check for
                if(tempCLineXEndPos - tempCLineXStartPos >= 2)
                {
                    currentStringInView = get_substring(cLineToParse, tempCLineXStartPos, tempCLineXEndPos-tempCLineXStartPos+1);

                    //Avoids rechecking if term is already being highlighted
                    if( GPE_MAIN_HIGHLIGHTER->highlightedTerm!=NULL)
                    {
                        if( GPE_MAIN_HIGHLIGHTER->highlightedTerm->termString == currentStringInView)
                        {
                            documentationIsBeingShown = true;
                            return;
                        }
                        else
                        {
                            GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                        }
                    }

                    if( codeEditorType==0)
                    {
                        for( i = GPE_MAIN_HIGHLIGHTER->activeProjectKeywords.size()-1; i>=0; i--)
                        {
                            tempTerm = GPE_MAIN_HIGHLIGHTER->activeProjectKeywords[i];
                            if( tempTerm!=NULL)
                            {
                                if( tempTerm->termString==currentStringInView)
                                {
                                    GPE_MAIN_HIGHLIGHTER->highlightedTerm = tempTerm;
                                    documentationIsBeingShown = true;
                                    return;
                                }
                            }
                        }

                        for( i = GPE_MAIN_HIGHLIGHTER->activeProjectKeywords.size()-1; i>=0; i--)
                        {
                            tempTerm = GPE_MAIN_HIGHLIGHTER->activeProjectKeywords[i];
                            if( tempTerm!=NULL)
                            {
                                if( tempTerm->termString == currentStringInView)
                                {
                                    GPE_MAIN_HIGHLIGHTER->highlightedTerm = tempTerm;
                                    documentationIsBeingShown = true;
                                    return;
                                }
                            }
                        }
                        tempTerm = GPE_MAIN_HIGHLIGHTER->find_matching_function( currentStringInView);
                        if( tempTerm!=NULL)
                        {
                            GPE_MAIN_HIGHLIGHTER->highlightedTerm = tempTerm;
                            documentationIsBeingShown = true;
                            return;
                        }

                        tempTerm = GPE_MAIN_HIGHLIGHTER->find_matching_variable( currentStringInView);
                        if( tempTerm!=NULL)
                        {
                            GPE_MAIN_HIGHLIGHTER->highlightedTerm = tempTerm;
                            documentationIsBeingShown = true;
                            return;
                        }
                    }
                }
                else
                {
                    GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                }
            }
            else
            {
                GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
            }
        }
        else
        {
            GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
        }
    }
    else
    {
        GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
    }
}

void GPE_TextAreaInputBasic::find_suggested_text()
{
    codeBeingSuggested = false;
    maxSuggestedTextWidth = 0;
    iSuggestedStartPos = 0;
    iSuggestionPos = 0;
    suggestedCompilerTerms.clear();
    int  i = 0;
    if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
    {
        std::string currentStringInView = "";
        tempCLineXStartPos = 0;
        tempCLineXEndPos = cursorXPos;
        //int tempCLineYPos = cursorYPos;
        std::string cLineToParse = listOfStrings[cursorYPos];
        GPE_Compiler_Term * tempTerm = NULL;
        if( cursorXPos >=0 && (int)cursorXPos <=(int)cLineToParse.size() && (int)cLineToParse.size() > 0)
        {
            if( cursorXPos==(int)cLineToParse.size() )
            {
                tempCLineXEndPos = cursorXPos-1;
            }
            if( tempCLineXEndPos < 0)
            {
                tempCLineXEndPos = 0;
            }
            //goes back one if character isn't alpha numeric
            if( !char_is_alnum(cLineToParse[tempCLineXEndPos],false,true) )
            {
                if( (int)cLineToParse.size() > tempCLineXEndPos-1)
                {
                    if( char_is_alnum(cLineToParse[tempCLineXEndPos-1],false,true) )
                    {
                        tempCLineXEndPos--;
                    }
                }
            }
            //makes sure our subtext is alphanumeric without spaces
            if( char_is_alnum(cLineToParse[tempCLineXEndPos],false,true) )
            {
                for( i = tempCLineXEndPos-1; i >=0; i--)
                {
                    if( char_is_alnum(cLineToParse[i],false,true) ==false )
                    {
                        tempCLineXStartPos = i+1;
                        break;
                    }
                }

                //makes sure the length is long enough to check for
                if(tempCLineXEndPos - tempCLineXStartPos >= 2)
                {
                    currentStringInView = cLineToParse.substr( tempCLineXStartPos, tempCLineXEndPos-tempCLineXStartPos+1);
                    //css suggestions
                    if( codeEditorType==1)
                    {

                    }
                    else if( codeEditorType==0)
                    {
                        //Project Level Functions and Keywords
                        for( i = GPE_MAIN_HIGHLIGHTER->activeProjectFunctions.size()-1; i>=0; i--)
                        {
                            tempTerm = GPE_MAIN_HIGHLIGHTER->activeProjectFunctions[i];
                            if( tempTerm!=NULL)
                            {
                                if( string_starts(tempTerm->termString,currentStringInView) )
                                {
                                    suggestedCompilerTerms.push_back(tempTerm);
                                }
                            }
                        }

                        for( i = GPE_MAIN_HIGHLIGHTER->activeProjectKeywords.size()-1; i>=0; i--)
                        {
                            tempTerm = GPE_MAIN_HIGHLIGHTER->activeProjectKeywords[i];
                            if( tempTerm!=NULL)
                            {
                                if( string_starts(tempTerm->termString,currentStringInView) )
                                {
                                    suggestedCompilerTerms.push_back(tempTerm);
                                }
                            }
                        }

                        //Language suggestions
                        if( GPE_MAIN_HIGHLIGHTER!=NULL && GPE_MAIN_HIGHLIGHTER->defaultLanguage!=NULL)
                        {
                            for( i = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageConstants.size()-1; i>=0; i--)
                            {
                                tempTerm = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageConstants[i];
                                if( tempTerm!=NULL)
                                {
                                    if( string_starts(tempTerm->termString,currentStringInView) )
                                    {
                                        suggestedCompilerTerms.push_back(tempTerm);
                                    }
                                }
                            }

                            for( i = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageFunctions.size()-1; i>=0; i--)
                            {
                                tempTerm = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageFunctions[i];
                                if( tempTerm!=NULL)
                                {
                                    if( string_starts(tempTerm->termString,currentStringInView) )
                                    {
                                        suggestedCompilerTerms.push_back(tempTerm);
                                    }
                                }
                            }

                            for( i = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageKeywords.size()-1; i>=0; i--)
                            {
                                tempTerm = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageKeywords[i];
                                if( tempTerm!=NULL)
                                {
                                    if( string_starts(tempTerm->termString,currentStringInView) )
                                    {
                                        suggestedCompilerTerms.push_back(tempTerm);
                                    }
                                }
                            }

                            for( i = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageVariables.size()-1; i>=0; i--)
                            {
                                tempTerm = GPE_MAIN_HIGHLIGHTER->defaultLanguage->languageVariables[i];
                                if( tempTerm!=NULL)
                                {
                                    if( string_starts(tempTerm->termString,currentStringInView) )
                                    {
                                        suggestedCompilerTerms.push_back(tempTerm);
                                    }
                                }
                            }
                        }
                    }
                    int tTermWidth = 0;
                    maxSuggestedTextWidth = 0;
                    //soon add optional sorting [alphabetically] of these terms here....
                    for(  i = 0; i < (int)suggestedCompilerTerms.size(); i++)
                    {
                        tempTerm = suggestedCompilerTerms[i];
                        if( tempTerm!=NULL)
                        {
                            if( tempTerm->termType==CTERM_FUNCTION)
                            {
                                tTermWidth = (int)tempTerm->termString.size()+(int)tempTerm->get_parameters().size()+(int)tempTerm->termFunctionReturnType.size()+3; // functionName(parameters)
                            }
                            else
                            {
                                tTermWidth = (int)tempTerm ->termString.size();
                            }
                            //User Global
                            if( (int)tempTerm->termScope.size() > 0 && tempTerm->termScope!="User Global" )
                            {
                                tTermWidth+=tempTerm->termScope.size()+1;
                            }

                            if( tTermWidth > maxSuggestedTextWidth)
                            {
                                maxSuggestedTextWidth = tTermWidth;
                            }
                        }
                    }
                    TEXTBOX_FONT_SIZE_WIDTH = 12;
                    TEXTBOX_FONT_SIZE_HEIGHT = 12;

                    if( FONT_TEXTINPUT!=NULL)
                    {
                         FONT_TEXTINPUT->get_metrics("A",&TEXTBOX_FONT_SIZE_WIDTH,&TEXTBOX_FONT_SIZE_HEIGHT);
                    }
                    maxSuggestedTextWidth=64+maxSuggestedTextWidth*TEXTBOX_FONT_SIZE_WIDTH;
                }
            }
        }
    }
    if( (int)suggestedCompilerTerms.size() > 0)
    {
        codeBeingSuggested = true;
    }
}

int GPE_TextAreaInputBasic::get_xcursor()
{
    return cursorXPos;
}

int GPE_TextAreaInputBasic::get_ycursor()
{
    return cursorYPos;
}

int GPE_TextAreaInputBasic::get_renderbox_height()
{
    int returnVal = barBox.h-textEditorButtonBar->get_height();
    /*switch(MAIN_SEARCH_CONTROLLER->textSearchMode)
    {
        case 1:
        case 2:
            returnVal = barBox.h-textEditorButtonBar->get_height()-48;
        break;
        case 3:
            returnVal = barBox.h-textEditorButtonBar->get_height()-80;
        break;
        default:
           returnVal = barBox.h-textEditorButtonBar->get_height();
        break;
    }*/
    if( showXScroll)
    {
        returnVal-=16;
    }
    return returnVal;
}

std::string GPE_TextAreaInputBasic::get_string()
{
    std::string returnString = "";
    for(int i=0; i < (int)listOfStrings.size(); i+=1)
    {
        returnString+=listOfStrings[i]+"\n";
    }
    return returnString;
}

std::string GPE_TextAreaInputBasic::get_string_spaces()
{
    std::string returnString = "";
    int listSize = (int)listOfStrings.size();
    for(int i=0; i < listSize; i+=1)
    {
        if( i ==listSize-1)
        {
            returnString+=listOfStrings[i]+" ";
        }
        else
        {
            returnString+=listOfStrings[i];
        }
    }
    return returnString;
}

int GPE_TextAreaInputBasic::get_line_count()
{
    return (int)listOfStrings.size();
}

std::string GPE_TextAreaInputBasic::get_line_string(int lineNumberIn)
{
    if( lineNumberIn >=0 && lineNumberIn < (int)listOfStrings.size() )
    {
        return listOfStrings.at(lineNumberIn);
    }
    return "";
}

std::string GPE_TextAreaInputBasic::get_short_hightlighted()
{
    if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos )
    {
        int yLineToCopy = std::min( selectionCursorYPos, selectionEndCursorYPos);
        if( (int)listOfStrings.size() > yLineToCopy)
        {
            int tempYlineLength = (int)listOfStrings[yLineToCopy].size();
            int minXPosToCopy = 0, maxXPosToCopy = 0;
            if(selectionCursorYPos==selectionEndCursorYPos)
            {
                minXPosToCopy = std::min( selectionCursorXPos, selectionEndCursorXPos);
                maxXPosToCopy = std::max( selectionCursorXPos, selectionEndCursorXPos);
            }
            else
            {
                if( selectionCursorYPos > selectionEndCursorYPos)
                {
                    minXPosToCopy = selectionEndCursorXPos;
                }
                else
                {
                    minXPosToCopy = selectionCursorXPos;
                }
                maxXPosToCopy = tempYlineLength;
            }
            if( tempYlineLength > minXPosToCopy && tempYlineLength >= maxXPosToCopy )
            {
                return listOfStrings[yLineToCopy].substr(minXPosToCopy,maxXPosToCopy-minXPosToCopy);
            }
        }
    }
    return "";
}

std::vector <std::string> GPE_TextAreaInputBasic::get_all_strings()
{
    return listOfStrings;
}

int GPE_TextAreaInputBasic::get_most_anchors_characters()
{
    int maxCharsUsed = 0;
    GPE_TextAnchor * tAnchor;
    for( int i = 0; i < (int)anchorPositions.size();i++)
    {
        tAnchor = anchorPositions[i];
        if( tAnchor!=NULL)
        {
            if( (int)tAnchor->lineMessage.size() > maxCharsUsed )
            {
                maxCharsUsed = (int)tAnchor->lineMessage.size();
            }
        }
    }
    return maxCharsUsed;
}

int GPE_TextAreaInputBasic::get_most_characters_used()
{
    int maxCharsUsed = 0;
    for( int i = 0; i < (int)listOfStrings.size();i++)
    {
        if( (int)listOfStrings[i].size() > maxCharsUsed)
        {
            maxCharsUsed = (int)listOfStrings[i].size();
        }
    }
    return maxCharsUsed;
}

void GPE_TextAreaInputBasic::handle_scrolling()
{

}

bool GPE_TextAreaInputBasic::has_content()
{
    if((int)listOfStrings.size() > 1)
    {
        return true;
    }
    else if((int)listOfStrings.size()==1 )
    {
        std::string firstLine = listOfStrings[0];
        if( (int)firstLine.size() > 0)
        {
            return true;
        }
    }
    return false;
}

bool GPE_TextAreaInputBasic::has_selection()
{
    if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos )
    {
        return true;
    }
    return false;
}

bool GPE_TextAreaInputBasic::import_text(std::string newFileName)
{
    if( !newFileName.empty() )
    {
        std::ifstream newTxtFile( newFileName.c_str() );
        //If the level file could be loaded
        if( !newTxtFile.fail() )
        {
            //makes sure the file is open
            if (newTxtFile.is_open())
            {
                std::string currLine = "";
                clear_all_lines();
                while ( newTxtFile.good() )
                {
                    getline (newTxtFile,currLine); //gets the next line of the file
                    currLine = trim_right_inplace(currLine);
                    currLine = string_replace_all(currLine,"\t","   ");
                    if(!currLine.empty() )
                    {
                        listOfStrings.push_back(currLine);
                    }
                    else
                    {
                        listOfStrings.push_back("");
                    }
                }
                newTxtFile.close();
                save_edit();
                return true;
            }
        }
    }
    return false;
}

void GPE_TextAreaInputBasic::init_save_history()
{
    GPE_TextAreaInputBasic * tempText;
    for( int iD = (int)savedHistory.size()-1; iD >=0; iD--)
    {
        tempText = savedHistory.at(iD);
        if( tempText!=NULL)
        {
            delete tempText;
            tempText = NULL;
        }
    }
    savedHistory.clear();
    currentPositionInHistory = 0;
    save_edit();
}

bool GPE_TextAreaInputBasic::is_read_only()
{
    return isReadOnly;
}

void GPE_TextAreaInputBasic::log_editable_action()
{
    if( undoableActionOccurred==false)
    {
        time(&lastUndoableActionTime);
        undoableActionOccurred = true;
    }
}

void GPE_TextAreaInputBasic::move_down(int yToMove )
{
    if( yToMove > 0)
    {
        lineStartYPos+=yToMove;
        if( lineStartYPos > (int)listOfStrings.size()-linesWithinView )
        {
            lineStartYPos = (int)listOfStrings.size()-linesWithinView;
        }
        find_documentation_description();
    }
}

void GPE_TextAreaInputBasic::move_up(int yToMove )
{
    if( yToMove > 0)
    {
        lineStartYPos-=yToMove;
        if( lineStartYPos < 0)
        {
            lineStartYPos = 0;
        }
        find_documentation_description();
    }
}

void GPE_TextAreaInputBasic::move_right(int xToMove )
{
    if( xToMove > 0)
    {
        lineStartXPos+=xToMove;
        if( lineStartXPos >= get_most_characters_used()-charactersWithinView )
        {
            lineStartXPos = get_most_characters_used()-charactersWithinView;
        }
        find_documentation_description();
    }
}

void GPE_TextAreaInputBasic::move_left(int xToMove )
{
    if( xToMove > 0)
    {
        lineStartXPos-=xToMove;
        if( lineStartXPos < 0 )
        {
            lineStartXPos = 0;
        }
        find_documentation_description();
    }
}

void GPE_TextAreaInputBasic::paste_clipboard()
{
    if(!isReadOnly)
    {
        std::string clipboardStr = SDL_GetClipboardText();
        if( clipboardStr.size() > 0)
        {
            clipboardStr = string_replace_all(clipboardStr,"\r\n","\n");
            clipboardStr = string_replace_all(clipboardStr,"\r","\n");
            clipboardStr = string_replace_all(clipboardStr,"\t","    ");
            if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
            {
                lineToEdit = listOfStrings[cursorYPos];
                if( cursorXPos >(int)lineToEdit.size() )
                {
                    cursorXPos = (int)lineToEdit.size() - 1;
                }
                if( cursorXPos < 0)
                {
                    cursorXPos = 0;
                }
                int newLinePos=clipboardStr.find_first_of("\n");
                if(newLinePos!=(int)std::string::npos)
                {
                    std::string cbNLString = split_first_string(clipboardStr,'\n');
                    if( (int)lineToEdit.size() >= cursorXPos)
                    {
                        textInputString = get_substring(lineToEdit,0,cursorXPos);
                    }
                    else
                    {
                        textInputString= "";
                    }
                    textInputString+=cbNLString;
                    std::string remainerOfStr="";
                    if( (int)lineToEdit.size() > cursorXPos )
                    {
                        remainerOfStr = get_substring(lineToEdit,cursorXPos);
                    }
                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                    listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                    cursorYPos+=1;
                    newLinePos=clipboardStr.find_first_of('\n');
                    while (newLinePos!=(int)std::string::npos)
                    {
                        cbNLString = split_first_string(clipboardStr,'\n');
                        listOfStrings.insert(listOfStrings.begin()+cursorYPos,cbNLString);
                        newLinePos=clipboardStr.find_first_of("\n");
                        cursorYPos+=1;
                    }
                    textInputString = clipboardStr;
                    textInputString+=remainerOfStr;
                    listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                    cursorXPos=(int)clipboardStr.size();
                }
                else
                {
                    if( (int)lineToEdit.size() >= cursorXPos)
                    {
                        textInputString = get_substring(lineToEdit,0,cursorXPos);
                    }
                    else
                    {
                        textInputString = "";
                    }
                    textInputString+=clipboardStr;
                    if( (int)lineToEdit.size() >= cursorXPos)
                    {
                        textInputString+=get_substring(lineToEdit,cursorXPos);
                    }
                    cursorXPos+=(int)clipboardStr.size();
                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                    listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                }
                save_edit();
            }
        }
    }
}

bool GPE_TextAreaInputBasic::parse_code_javascript()
{
    //resets symbol information
    missingSymbolDetected = false;


    if( has_content() )
    {
        foundSyntaxErrors.clear();
        missingSymbolStartXPos = 0;
        missingSymbolStartYPos = 0;
        misingSymbolSuggestedEndYPos = 0;
        misingSymbolSuggestedEndXPos = 0;

        int i = 0;
        std::string currStringToRender = "";
        std::string currentLineInView = "";

        int tempSynStringSize = 0;
        int currPosToParse = 0, lineEnd = 0;
        bool isInBlockCommentMode = false;
        bool isInDoubleQuoteMode = false;
        bool isInSingleQuoteMode = false;
        int maxLine = (int)listOfStrings.size();
        int endBlockCommentPos = 0;
        int endDQuoteCommentPos = 0;
        int endSQuoteCommentPos = 0;
        bool commentFoundInSymbols = false;
        int openBracesCount = 0;
        int openBracketsCount = 0;
        int openParenthesisCount = 0;
        for( i=0; i < maxLine; i++)
        {
            currStringToRender = listOfStrings[i];
            currPosToParse = 0;
            openParenthesisCount = 0;
            lineEnd = (int)currStringToRender.size();

            endBlockCommentPos=(int)std::string::npos;
            endDQuoteCommentPos=(int)std::string::npos;
            endSQuoteCommentPos=(int)std::string::npos;
            while (currPosToParse < lineEnd)
            {
                if( isInBlockCommentMode)
                {
                    endBlockCommentPos = currStringToRender.find("*/");
                    if( endBlockCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endBlockCommentPos+2;
                        isInBlockCommentMode = false;
                    }
                }
                else if( isInDoubleQuoteMode)
                {
                    endDQuoteCommentPos = currStringToRender.find('"',currPosToParse);
                    if( endDQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endDQuoteCommentPos+1;
                        isInDoubleQuoteMode = false;
                    }
                }
                else if( isInSingleQuoteMode)
                {
                    endSQuoteCommentPos = currStringToRender.find("'",currPosToParse);
                    if( endSQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endSQuoteCommentPos+1;
                        isInSingleQuoteMode = false;
                    }
                }
                else
                {
                    while (currPosToParse < lineEnd && currStringToRender[currPosToParse]==' ')
                    {
                        currPosToParse++;
                    }
                    if (currPosToParse < lineEnd)
                    {
                        if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currPosToParse + 1 < lineEnd && currStringToRender[currPosToParse + 1] == '/' )
                        {
                            currPosToParse = lineEnd;
                        }
                        else if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currStringToRender[currPosToParse + 1] == '*' )
                        {
                            isInBlockCommentMode = true;
                            currPosToParse+=2;
                        }
                        else if(currStringToRender[currPosToParse] == '"')
                        {
                            isInDoubleQuoteMode = true;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '\'')
                        {
                            isInSingleQuoteMode = true;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '(')
                        {
                            openParenthesisCount++;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '[')
                        {
                            openBracesCount++;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '{')
                        {
                            openBracketsCount++;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == ')')
                        {
                            if( isInDoubleQuoteMode==false && isInSingleQuoteMode==false && isInBlockCommentMode==false)
                            {
                                if( openParenthesisCount > 0)
                                {
                                    openParenthesisCount--;
                                }
                                else
                                {
                                    missingSymbolDetected= true;
                                    foundSyntaxErrors.push_back( "Invalid ')' found on line "+int_to_string(i+1)+ " @ "+int_to_string(currPosToParse)+" ParentCount ["+int_to_string(openParenthesisCount)+"].");
                                }
                            }
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == ']')
                        {
                            if( openBracesCount > 0)
                            {
                                openBracesCount--;
                            }
                            else
                            {
                                missingSymbolDetected= true;
                                foundSyntaxErrors.push_back("Invalid ']' found on line "+int_to_string(i+1)+" @ "+int_to_string(currPosToParse)+" BracesCount ["+int_to_string(openBracesCount)+"].");
                            }
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '}')
                        {
                            if( openBracketsCount > 0)
                            {
                                openBracketsCount--;
                            }
                            else
                            {
                                missingSymbolDetected= true;
                                foundSyntaxErrors.push_back("Invalid '}' found on line "+int_to_string(i+1)+" @ "+int_to_string(currPosToParse)+" BracketsCount ["+int_to_string(openBracketsCount)+"].");
                            }
                            currPosToParse++;
                        }
                        else if (isdigit(currStringToRender[currPosToParse]) )
                        {
                            currPosToParse++;
                            while( (currPosToParse < lineEnd && isdigit( currStringToRender[currPosToParse] )  ) || currStringToRender[currPosToParse] ==' ')
                            {
                                currPosToParse++;
                            }
                        }
                        /*
                        else if ( GPE_MAIN_HIGHLIGHTER->charIsSymbol(currStringToRender[currPosToParse]) )
                        {
                            commentFoundInSymbols = false;
                            while( ( commentFoundInSymbols==false && currPosToParse < lineEnd && GPE_MAIN_HIGHLIGHTER->charIsSymbol(currStringToRender[currPosToParse] ) )|| currStringToRender[currPosToParse] ==' ')
                            {
                                if( lineEnd > currPosToParse+1)
                                {
                                    if( currStringToRender[currPosToParse] == '/' && (currStringToRender[currPosToParse + 1] == '/' || currStringToRender[currPosToParse + 1] == '*' ) )
                                    {
                                        commentFoundInSymbols = true;
                                    }
                                    else if (currStringToRender[currPosToParse] == '*' && currStringToRender[currPosToParse + 1] == '/' )
                                    {
                                        commentFoundInSymbols = true;
                                    }
                                    else
                                    {
                                        currPosToParse++;
                                    }
                                }
                                else
                                {
                                    currPosToParse++;
                                }
                            }
                            currPosToParse++;
                        }
                        */
                        else if (char_is_alpha(currStringToRender[currPosToParse],true,true) )
                        {
                            //color = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;
                            currPosToParse++;
                            while (currPosToParse < lineEnd && char_is_alnum(currStringToRender[currPosToParse],true,true) )
                            {
                                currPosToParse++;
                            }
                        }
                        else
                        {
                            //color = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;
                            //anything else is just regular text as well...
                            currPosToParse++;
                        }
                    }
                }
            }
        }

        if( isInBlockCommentMode)
        {
            missingSymbolDetected = true;
            foundSyntaxErrors.push_back( "Missing Symbol: [*/] - End Block Comment" );
        }
        else if( isInDoubleQuoteMode)
        {
            missingSymbolDetected = true;
            foundSyntaxErrors.push_back("\"/ - End Quote" );
        }
        else if( isInSingleQuoteMode)
        {
            missingSymbolDetected = true;
            foundSyntaxErrors.push_back( "' - End Single Quote" );
        }
    }
    return !missingSymbolDetected;
}

void GPE_TextAreaInputBasic::process_self(GPE_Rect * viewedSpace, GPE_Rect * cam )
{
    viewedSpace = GPE_find_camera(viewedSpace);
    cam = GPE_find_camera(cam);
    hasScrollControl = false;
    prevCursorXPos = cursorXPos;
    prevCursorYPos = cursorYPos;
    GPE_GeneralGuiElement::process_self(viewedSpace,cam);
    if( clickedOutside)
    {
        hasArrowkeyControl = false;
        hasScrollControl = false;
    }
    else if( isClicked)
    {
        hasArrowkeyControl = true;
        hasScrollControl = true;
    }
    if( (int)listOfStrings.size()==0)
    {
        listOfStrings.push_back("");
        reset_self();
    }

    bool pasteCommandGiven = false;
    bool mouseHoveringInTextArea = false;
    if( textEditorButtonBar!=NULL )
    {
        if( !isReadOnly )
        {
            textEditorButtonBar->set_coords(barBox.x,barBox.y);
            //sets the buttonbar to the width of the text editor( minus width of yScroll width[16 ).
            textEditorButtonBar->set_width(barBox.w);
            textEditorButtonBar->set_height(32);
            textEditorButtonBar->process_self(viewedSpace,cam);

            if( textEditorButtonBar->selectedOption>= 0 && textEditorButtonBar->selectedOption < TEXTAREA_OPTION_MAX_OPTIONS)
            {
                if( textEditorButtonBar->selectedOption==TEXTAREA_OPTION_IMPORT)
                {
                    std::string importTextFileName = GPE_GetOpenFileName("Import Text","",MAIN_GUI_SETTINGS->fileOpenTextFileDir );
                    if( (int)importTextFileName.size() > 0)
                    {
                        //if( display_get_prompt("Warning!","Clearing this text area is irreversible. Are you sure you want to continue this operation?")==DISPLAY_QUERY_YES )
                        {
                            import_text( importTextFileName);
                        }
                    }
                }
                else if(textEditorButtonBar->selectedOption ==TEXTAREA_OPTION_REDO)
                {
                    if( can_redo() )
                    {
                        redo_edit();
                    }
                }
                else if(textEditorButtonBar->selectedOption ==TEXTAREA_OPTION_UNDO)
                {
                    if( can_undo() )
                    {
                        undo_edit();
                    }
                }
                else if( textEditorButtonBar->selectedOption==TEXTAREA_OPTION_EXPORT)
                {
                    std::string exportTextFileName = GPE_GetSaveFileName("Export Text","",MAIN_GUI_SETTINGS->fileOpenFunctionDir);
                    if( file_exists(exportTextFileName) )
                    {
                        if( display_get_prompt("Warning!","File Exists already, do you wish to overwrite it?)")==DISPLAY_QUERY_YES )
                        {
                            export_text( exportTextFileName);
                        }
                    }
                    else
                    {
                        export_text( exportTextFileName);
                    }
                }
                else if( textEditorButtonBar->selectedOption==TEXTAREA_OPTION_CLEAR)
                {
                    if( display_get_prompt("Warning!","Are you sure you want to continue this operation?")==DISPLAY_QUERY_YES )
                    {
                        clear_all_lines();
                        listOfStrings.push_back("");
                        save_edit();
                    }
                }
                else if( textEditorButtonBar->selectedOption==TEXTAREA_OPTION_COPY)
                {
                    copy_selection();
                }
                else if( textEditorButtonBar->selectedOption==TEXTAREA_OPTION_CUT)
                {
                    cut_selection();
                }
                else if( textEditorButtonBar->selectedOption==TEXTAREA_OPTION_PASTE)
                {
                    pasteCommandGiven = true;
                }
            }
        }

        if( !textEditorButtonBar->is_clicked() && (int)listOfStrings.size() >0 )
        {
            textInputString = "";
            showXScroll = false;
            showYScroll = false;
            cursorTimer+=1;

            if( cursorTimer > 15*FPS_RATIO )
            {
                showCursor = true;
            }
            if( cursorTimer > 30*FPS_RATIO )
            {
                showCursor = false;
                cursorTimer = 0;
            }
            if( isClicked)
            {
                isInUse = true;
                //inputFieldPos = 0;
                userInput->inkeys = "";
            }
            if( clickedOutside )
            {
                isInUse = false;
            }
            if( MAIN_GUI_SETTINGS->showTextEditorLineCount && isReadOnly==false )
            {
                lineCountBoxWidth = MAIN_GUI_SETTINGS->defaultLineCountWidth;
            }
            else
            {
                lineCountBoxWidth = 0;
            }
            if( textEditorButtonBar!=NULL)
            {
                textEditorButtonBar->set_coords(barBox.x,barBox.y);
                //sets the buttonbar to the width of the text editor( minus width of yScroll width[16 ).
                textEditorButtonBar->set_width(barBox.w);
                if( !isReadOnly)
                {
                    textEditorButtonBar->set_height(32);
                    textEditorButtonBar->enable_self();
                }
                else
                {
                    textEditorButtonBar->set_height(0);
                    textEditorButtonBar->disable_self();
                }

                renderBox.x = barBox.x+lineCountBoxWidth;
                renderBox.y = textEditorButtonBar->get_y2pos();
            }

            renderBox.w = barBox.w-lineCountBoxWidth;
            renderBox.h = get_renderbox_height();


            charactersWithinView = (renderBox.w/TEXTBOX_FONT_SIZE_WIDTH)-2;
            linesWithinView =( renderBox.h/GPE_AVERAGE_LINE_HEIGHT);


            if( linesWithinView < (int)listOfStrings.size() )
            {
                showYScroll = true;
            }
            if( textXScroll!=NULL)
            {
                if( charactersWithinView < get_most_characters_used() )
                {
                    showXScroll = true;
                    if( linesWithinView>1)
                    {
                        linesWithinView-=1;
                    }
                    //int prevYPos = lineStartYPos;
                    textXScroll->barBox.x = renderBox.x;
                    textXScroll->barBox.y = renderBox.y+renderBox.h-16;
                    textXScroll->barBox.w = barBox.w-lineCountBoxWidth;
                    textXScroll->barBox.h = 16;
                    textXScroll->fullRect.x = 0;
                    textXScroll->fullRect.y = 0;
                    textXScroll->fullRect.w = get_most_characters_used();
                    textXScroll->fullRect.h = renderBox.h;
                    if(showYScroll)
                    {
                        textXScroll->barBox.w-=textYScroll->barBox.w;
                        charactersWithinView-=1;
                    }

                    textXScroll->contextRect.x = lineStartXPos;
                    textXScroll->contextRect.y = 0;
                    textXScroll->contextRect.w = charactersWithinView;
                    textXScroll->contextRect.h = renderBox.h;

                    textXScroll->process_self(viewedSpace,cam,true );
                    if( textXScroll->has_moved() || textXScroll->is_scrolling() )
                    {
                        lineStartXPos = get_most_characters_used() * ( (float)textXScroll->scrollXPos/(float)textXScroll->barBox.w );
                    }
                }
                else
                {
                    lineStartXPos = 0;
                    textXScroll->reset_scroller();
                }
            }
            if( textYScroll!=NULL)
            {
                if( showYScroll )
                {
                    //int prevYPos = lineStartYPos;
                    textYScroll->barBox.x = barBox.x+barBox.w-16;
                    textYScroll->barBox.y = textEditorButtonBar->get_y2pos();
                    textYScroll->barBox.w = 16;
                    textYScroll->barBox.h = barBox.h-textEditorButtonBar->get_height();

                    textYScroll->fullRect.x = 0;
                    textYScroll->fullRect.y = 0;
                    textYScroll->fullRect.w = renderBox.w;
                    textYScroll->fullRect.h = (int)listOfStrings.size();
                    textYScroll->contextRect.x = 0;
                    textYScroll->contextRect.y = lineStartYPos;
                    textYScroll->contextRect.w = renderBox.w;
                    textYScroll->contextRect.h = linesWithinView;
                    if(showXScroll)
                    {
                        textYScroll->barBox.h-=textXScroll->barBox.h;
                        //textYScroll->contextRect.h-=1;
                    }
                    textYScroll->process_self(viewedSpace,cam,true );
                    if( textYScroll->has_moved() )
                    {
                        lineStartYPos =  round ( textYScroll->contextRect.y );
                    //    lineStartYPos =  ceil( ( (float)listOfStrings.size() ) * ( (float)textYScroll->scrollYPos/(float)textYScroll->barBox.h ) );
                    }

                    //updates the buttonbar to appear less awkward
                    textEditorButtonBar->set_width(barBox.w);
                }
                else
                {
                    lineStartYPos = 0;
                    textYScroll->reset_scroller();
                }
            }
            if( lineStartXPos < 0)
            {
                lineStartXPos = 0;
            }
            if( lineStartYPos < 0)
            {
                lineStartYPos = 0;
            }
            //just changes the cursor around if it is in the specific text area
            textSpaceRect.x = renderBox.x+1;
            textSpaceRect.y = renderBox.y+1;
            textSpaceRect.w = renderBox.w;
            textSpaceRect.h = renderBox.h;

            if( MAIN_GUI_SETTINGS->showTextEditorLineCount)
            {
                if(showYScroll)
                {
                    if(showXScroll)
                    {
                        textSpaceRect.x = renderBox.x;
                        textSpaceRect.y = renderBox.y;
                        textSpaceRect.w = barBox.w-lineCountBoxWidth-16;
                        textSpaceRect.h = renderBox.h-16;
                    }
                    else
                    {
                        textSpaceRect.x = renderBox.x;
                        textSpaceRect.y = renderBox.y;
                        textSpaceRect.w = barBox.w-lineCountBoxWidth-16;
                        textSpaceRect.h = renderBox.h;
                    }
                }
                else if(showXScroll)
                {
                    textSpaceRect.x = renderBox.x;
                    textSpaceRect.y = renderBox.y;
                    textSpaceRect.w = barBox.w-lineCountBoxWidth;
                    textSpaceRect.h = renderBox.h-16;
                }
                else
                {
                    textSpaceRect.x = renderBox.x;
                    textSpaceRect.y = renderBox.y;
                    textSpaceRect.w = barBox.w-lineCountBoxWidth;
                    textSpaceRect.h = renderBox.h;
                }
            }
            else if(showYScroll)
            {
                if( showXScroll)
                {
                    textSpaceRect.x = renderBox.x;
                    textSpaceRect.y = renderBox.y;
                    textSpaceRect.w = renderBox.w-16;
                    textSpaceRect.h = renderBox.h-16;
                }
                else
                {
                    textSpaceRect.x = renderBox.x;
                    textSpaceRect.y = renderBox.y;
                    textSpaceRect.w = renderBox.w-16;
                    textSpaceRect.h = renderBox.h;
                }
            }
            else if ( showXScroll)
            {
                textSpaceRect.x = renderBox.x;
                textSpaceRect.y = renderBox.y;
                textSpaceRect.w = renderBox.w;
                textSpaceRect.h = renderBox.h-16;
            }

            textSpaceRect.x = renderBox.x+viewedSpace->x-cam->x;
            textSpaceRect.y = renderBox.y+viewedSpace->y-cam->y;

            if( isHovered && (showXScroll || showYScroll ) )
            {
                hasScrollControl = true;
            }
            if( isInUse && isEnabled && cam!=NULL && textEditorButtonBar!=NULL)
            {
                if( point_within_rect(userInput->mouse_x,userInput->mouse_y,&textSpaceRect)  )
                {
                    mouseHoveringInTextArea = true;
                    GPE_change_cursor(SDL_SYSTEM_CURSOR_IBEAM);
                }
                if( mouseHoveringInTextArea && textXScroll->is_scrolling()==false && textYScroll->is_scrolling()==false )
                {
                    if( userInput->check_mouse_down(0) )
                    {
                        update_cursor_to_mouse(viewedSpace, cam);
                        if( lineStartXPos < 0)
                        {
                            lineStartXPos = 0;
                        }
                        if( lineStartYPos < 0)
                        {
                            lineStartYPos = 0;
                        }
                    }
                    //Handles the Mouse movements & buttons
                    if( userInput->check_mouse_doubleclicked(0) && RESOURCE_TO_DRAG==NULL )
                    {
                        update_cursor_to_mouse(viewedSpace, cam);
                        if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                        {
                            lineToEdit = listOfStrings[cursorYPos];

                            selectionCursorXPos = selectionEndCursorXPos = cursorXPos;
                            selectionCursorYPos = selectionEndCursorYPos = cursorYPos;
                            if( (int)lineToEdit.size() == 0 )
                            {
                                if( cursorYPos+1 < (int)listOfStrings.size() )
                                {
                                    cursorXPos = 0;
                                    cursorYPos++;
                                    selectionEndCursorYPos = cursorYPos;
                                    selectionCursorXPos = 0;
                                    selectionEndCursorXPos = 0;
                                }
                            }
                            else
                            {
                                int iPrev = cursorXPos;
                                int jNext = cursorXPos;
                                if( lastDoubleClickAction ==0)
                                {
                                    if( cursorXPos>=0 &&  cursorXPos <= (int)lineToEdit.size() )
                                    {
                                        if( lineToEdit[cursorXPos]==' ')
                                        {
                                            for(iPrev = cursorXPos-1; iPrev >=0; iPrev-- )
                                            {
                                                if( lineToEdit[iPrev]==' ')
                                                {
                                                    selectionCursorXPos--;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                            for(jNext = cursorXPos; jNext < (int)lineToEdit.size(); jNext++ )
                                            {
                                                if( lineToEdit[jNext]==' ')
                                                {
                                                    selectionEndCursorXPos++;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        else if( char_is_alnum( lineToEdit[cursorXPos],false,true) )
                                        {
                                            for(iPrev = cursorXPos-1; iPrev >=0; iPrev-- )
                                            {
                                                if( char_is_alnum( lineToEdit[iPrev],false,true) )
                                                {
                                                    selectionCursorXPos--;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }

                                            for(jNext = cursorXPos; jNext < (int)lineToEdit.size(); jNext++ )
                                            {
                                                if( char_is_alnum( lineToEdit[jNext],false,true) )
                                                {
                                                    selectionEndCursorXPos++;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            //for symbols
                                            for(iPrev = cursorXPos-1; iPrev >=0; iPrev-- )
                                            {
                                                if( char_is_alnum( lineToEdit[iPrev],true,true)==false)
                                                {
                                                    selectionCursorXPos--;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                            for(jNext = cursorXPos; jNext < (int)lineToEdit.size(); jNext++ )
                                            {
                                                if( char_is_alnum( lineToEdit[jNext],true,true)==false)
                                                {
                                                    selectionEndCursorXPos++;
                                                }
                                                else
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    lastDoubleClickAction = 1;
                                }
                                else if( (int)lineToEdit.size() > 0 )
                                {
                                    selectionCursorXPos = 0;
                                    selectionEndCursorXPos = (int)lineToEdit.size();
                                    cursorXPos = 0;
                                    lastDoubleClickAction = 0;
                                }
                                else if( cursorYPos+1 < (int)listOfStrings.size() )
                                {
                                    cursorXPos = 0;
                                    cursorYPos++;
                                    selectionEndCursorYPos = cursorYPos;
                                    selectionCursorXPos = 0;
                                    selectionEndCursorXPos = 0;
                                }
                                userInput->reset_all_input();
                                codeBeingSuggested = false;
                                find_documentation_description();
                            }
                        }
                    }
                    else if( userInput->check_mouse_pressed(0) )
                    {
                        //if( lastDoubleClickAction==0)
                        {
                            update_cursor_to_mouse(viewedSpace, cam);
                            if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                            {
                                selectionCursorXPos = selectionEndCursorXPos = cursorXPos;
                                selectionCursorYPos = selectionEndCursorYPos = cursorYPos;
                            }
                        }
                        codeBeingSuggested = false;
                        find_documentation_description();
                    }
                    else if( userInput->check_mouse_down(0) )
                    {
                        //if( lastDoubleClickAction==0)
                        {
                            update_cursor_to_mouse(viewedSpace, cam);
                            if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                            {
                                selectionEndCursorXPos = cursorXPos;
                                selectionEndCursorYPos = cursorYPos;
                            }
                        }
                        codeBeingSuggested = false;
                        find_documentation_description();
                    }
                    else if( userInput->check_mouse_down(1) )
                    {
                        GPE_open_context_menu();
                        MAIN_CONTEXT_MENU->set_width(128);

                        MAIN_CONTEXT_MENU->add_menu_option("Undo",0,rsm->texture_add(APP_DIRECTORY_NAME+"resources/buttons/backward.png"),-1,NULL,true,!isReadOnly && can_undo());
                        MAIN_CONTEXT_MENU->add_menu_option("Redo",1,rsm->texture_add(APP_DIRECTORY_NAME+"resources/buttons/forward.png"),-1,NULL,true,!isReadOnly && can_redo() );
                        MAIN_CONTEXT_MENU->add_menu_option("Cut",2,rsm->texture_add(APP_DIRECTORY_NAME+"resources/buttons/cut.png"),-1,NULL,false,!isReadOnly);
                        MAIN_CONTEXT_MENU->add_menu_option("Copy",3,rsm->texture_add(APP_DIRECTORY_NAME+"resources/buttons/copy.png"),-1,NULL,false,true);
                        MAIN_CONTEXT_MENU->add_menu_option("Paste",4,rsm->texture_add(APP_DIRECTORY_NAME+"resources/buttons/paste.png"),-1,NULL,false,!isReadOnly);
                        MAIN_CONTEXT_MENU->add_menu_option("Delete",5,rsm->texture_add(APP_DIRECTORY_NAME+"resources/buttons/remove.png"),-1,NULL,true,!isReadOnly);
                        MAIN_CONTEXT_MENU->add_menu_option("Select All",6,rsm->texture_add(APP_DIRECTORY_NAME+"resources/buttons/sticky-note.png"),-1,NULL,true,true);
                        int menuSelection = get_popupmenu_result();

                        if( menuSelection==0)
                        {
                            if( can_undo() && !isReadOnly )
                            {
                                undo_edit();
                            }
                        }
                        else if( menuSelection==1 && !isReadOnly )
                        {
                            if( can_redo() )
                            {
                                redo_edit();
                            }
                        }
                        if( menuSelection==6)
                        {
                            select_all();
                        }
                        else
                        {
                            switch(menuSelection)
                            {
                                case 2:
                                    cut_selection();
                                break;
                                case 3:
                                    copy_selection();
                                break;
                                case 4:
                                    pasteCommandGiven = true;
                                break;
                                case 5:
                                    delete_selection();
                                break;
                                default:
                                break;
                            }
                            reset_selection();
                        }
                        lastDoubleClickAction = 0;
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                    }
                    else if( userInput->mouseMovementInputReceivedInFrame && RESOURCE_TO_DRAG==NULL )
                    {
                        //Highlights documenation under mouse if found.
                        int tMouseX = 0, tMouseY = 0;
                        find_mouse_cursor(&tMouseX,&tMouseY, viewedSpace, cam);
                        if( tMouseX!=highlightXPos || tMouseY!=highlightYPos)
                        {
                            find_documentation_description(tMouseX,tMouseY);
                        }
                    }
                    else if( RESOURCE_TO_DRAG!=NULL && !isReadOnly )
                    {
                        if( userInput->check_mouse_released(0) )
                        {
                            if( point_within_rect(userInput->mouse_x,userInput->mouse_y,&textSpaceRect)  )
                            {
                                mouseHoveringInTextArea = true;
                                GPE_change_cursor(SDL_SYSTEM_CURSOR_IBEAM);

                                update_cursor_to_mouse(viewedSpace, cam);
                                if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                                {
                                    if( cursorXPos >=0 && cursorXPos <= (int)listOfStrings[cursorYPos].size() )
                                    {

                                        listOfStrings[cursorYPos] = get_substring(listOfStrings[cursorYPos],0,cursorXPos)+RESOURCE_TO_DRAG->get_name()+get_substring(listOfStrings[cursorYPos],cursorXPos);
                                        RESOURCE_TO_DRAG = NULL;
                                    }
                                }
                            }
                            else
                            {
                                record_error("Unable to drag resource into textArea...");
                            }
                        }
                    }
                }
                else if( userInput->check_mouse_down(0) && textXScroll->is_scrolling()==false && textYScroll->is_scrolling()==false )
                {
                    //if( lastDoubleClickAction==0)
                    if( userInput->mouse_x < textSpaceRect.x )
                    {
                        if( cursorXPos > 0)
                        {
                            cursorXPos-=1;
                        }
                        move_left(1);
                    }
                    else if( userInput->mouse_x > textSpaceRect.x+textSpaceRect.w )
                    {
                        lineToEdit = listOfStrings[cursorYPos];
                        if( cursorXPos > (int)lineToEdit.size()-1 )
                        {
                            cursorXPos+=1;
                        }
                        move_right(1);
                    }

                    if( userInput->mouse_y > textSpaceRect.y && userInput->mouse_y < textSpaceRect.y+4 )
                    {
                        if( cursorYPos > 0)
                        {
                            cursorYPos-=1;
                        }
                        move_up(1);
                    }
                    else if( userInput->mouse_y > textSpaceRect.y+textSpaceRect.h-4 )
                    {
                        if( cursorYPos < (int)listOfStrings.size()-1 )
                        {
                            cursorYPos+=1;
                        }
                        move_down(1);
                    }

                    update_cursor_to_mouse(viewedSpace, cam);
                    if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                    {
                        selectionEndCursorXPos = cursorXPos;
                        selectionEndCursorYPos = cursorYPos;
                    }
                    showCursor = false;
                    cursorTimer = 30;
                    codeBeingSuggested = false;
                    find_documentation_description();
                }
            }

            //special control action happening
            if(  MAIN_SEARCH_CONTROLLER->using_search()==false && isInUse && isEnabled && hasArrowkeyControl )
            {
                //used to delay events from happening superfast
                if( userInput->down[kb_backspace] && !userInput->pressed[kb_backspace] )
                {
                    bscDelay +=1;
                }
                else
                {
                    bscDelay = 0;
                }
                if( userInput->down[kb_delete] && !userInput->pressed[kb_delete] )
                {
                    delDelay += 0.5;
                }
                else
                {
                    delDelay = 0;
                }
                if( userInput->down[kb_tab]  && !userInput->pressed[kb_tab])
                {
                    tabDelay += 0.5;
                }
                if(userInput->down[kb_enter] && !userInput->pressed[kb_enter])
                {
                    enterDelay+=0.5;
                }
                else
                {
                    enterDelay = 0;
                }
                if( userInput->down[kb_left] && !userInput->pressed[kb_left] && !userInput->released[kb_left] )
                {
                    leftDelay+=1;
                }
                else
                {
                    leftDelay = 0;
                }

                if( userInput->down[kb_right] && !userInput->pressed[kb_right] && !userInput->released[kb_right] )
                {
                    rightDelay+=1;
                }
                else
                {
                    rightDelay = 0;
                }

                if(userInput->down[kb_up] && !userInput->pressed[kb_up] && !userInput->released[kb_up] )
                {
                    upDelay+=1;
                }
                else
                {
                    upDelay = 0;
                }
                if(userInput->down[kb_down] && !userInput->pressed[kb_down] && !userInput->released[kb_down])
                {
                    downDelay+=0.5;
                }
                else
                {
                    downDelay = 0;
                }

                if(userInput->down[kb_d] && !userInput->pressed[kb_d] && !userInput->released[kb_d])
                {
                    dKeyDelay+=0.5;
                }
                else
                {
                    dKeyDelay = 0;
                }

                if( userInput->down[kb_ctrl]  )
                {
                    GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                    if( userInput->released[kb_a])
                    {
                       select_all();
                    }
                    else if( userInput->released[kb_c])
                    {
                         copy_selection();
                    }
                    else if( userInput->released[kb_f] ||  userInput->released[kb_h] )
                    {
                         MAIN_SEARCH_CONTROLLER->findTextStringBox->set_string( get_short_hightlighted() );
                    }
                    else if( dKeyDelay > (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*FPS_RATIO  || ( !userInput->pressed[kb_d] && userInput->released[kb_d] ) )
                    {
                        if( !isReadOnly )
                        {
                            duplicate_text();
                            dKeyDelay = 0;
                        }
                    }
                    else if( userInput->released[kb_v] && !isReadOnly)
                    {
                        pasteCommandGiven = true;
                    }
                    else if( userInput->released[kb_x] && !isReadOnly)
                    {
                         cut_selection();
                         scroll_to_cursor();
                    }
                    else if( userInput->released[kb_y] && !isReadOnly)
                    {
                        if( can_redo() )
                        {
                            redo_edit();
                            userInput->reset_all_input();
                            process_self( viewedSpace,cam );
                        }
                    }
                    else if( userInput->released[kb_z] && !isReadOnly)
                    {
                        if( can_undo() )
                        {
                            undo_edit();
                            userInput->reset_all_input();
                            process_self( viewedSpace,cam );
                        }
                    }
                    else if( upDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*FPS_RATIO  || ( !userInput->pressed[kb_up] && userInput->released[kb_up] ) )
                    {
                        lineStartYPos--;
                        upDelay = 0;
                        showCursor = true;
                        cursorTimer = 0;
                    }
                    else if( downDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*FPS_RATIO  || ( !userInput->pressed[kb_down] && userInput->released[kb_down] ) )
                    {
                        lineStartYPos++;
                        downDelay = 0;
                        showCursor = true;
                        cursorTimer = 0;
                    }
                    else if( leftDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*FPS_RATIO  || ( !userInput->pressed[kb_left] && userInput->released[kb_left] ) )
                    {
                        if( userInput->shiftKeyIsPressed)
                        {
                            if( selectionCursorXPos==selectionEndCursorXPos && selectionCursorYPos==selectionEndCursorYPos )
                            {
                                selectionCursorXPos = cursorXPos;
                                selectionCursorYPos = cursorYPos;
                            }
                        }
                        if( cursorXPos <=0)
                        {
                            if( cursorYPos > 0)
                            {
                                cursorYPos--;
                                cursorXPos = (int)listOfStrings[cursorYPos].size()-1;
                                if( cursorXPos < 0)
                                {
                                    cursorXPos = 0;
                                }
                            }
                        }
                        else if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                        {
                            std::string currentLineToScroll = listOfStrings[cursorYPos];
                            if( cursorXPos >=(int)currentLineToScroll.size() )
                            {
                                cursorXPos = (int)currentLineToScroll.size()-1;
                            }
                            if( cursorXPos < 0)
                            {
                                if( cursorYPos >0 && cursorYPos < (int)listOfStrings.size() )
                                {
                                    cursorYPos--;
                                    cursorXPos = listOfStrings[cursorYPos].size()-1;
                                }
                            }
                            else if( cursorXPos < (int)currentLineToScroll.size() )
                            {
                                int iNCursorX = cursorXPos-1;
                                for( iNCursorX = cursorXPos-1; iNCursorX >=0; iNCursorX--)
                                {
                                    if( char_is_alnum(currentLineToScroll[iNCursorX],false,true)==false )
                                    {
                                        break;
                                    }
                                }
                                if( iNCursorX< 0)
                                {
                                    iNCursorX = 0;
                                }
                                cursorXPos = iNCursorX;
                            }
                            else
                            {
                                cursorXPos = 0;
                            }
                        }
                        scroll_to_cursor();
                        showCursor = true;
                        cursorTimer = 0;
                        if( userInput->shiftKeyIsPressed)
                        {
                            selectionEndCursorXPos = cursorXPos;
                            selectionEndCursorYPos = cursorYPos;
                        }
                        leftDelay = 0;
                    }
                    else if( rightDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*FPS_RATIO  || ( !userInput->pressed[kb_right] && userInput->released[kb_right] ) )
                    {
                        if( userInput->shiftKeyIsPressed)
                        {
                            if( selectionCursorXPos==selectionEndCursorXPos && selectionCursorYPos==selectionEndCursorYPos )
                            {
                                selectionCursorXPos = cursorXPos;
                                selectionCursorYPos = cursorYPos;
                            }
                        }
                        if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                        {
                            std::string currentLineToScroll = listOfStrings[cursorYPos];
                            if( cursorXPos >=(int)currentLineToScroll.size() )
                            {
                                if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size()-1 )
                                {
                                    cursorYPos++;
                                    cursorXPos = 0;
                                }
                            }
                            else if( cursorXPos >= 0 && cursorXPos < (int)currentLineToScroll.size() )
                            {
                                int iNCursorX = cursorXPos+1;
                                for( iNCursorX = cursorXPos+1; iNCursorX <(int)currentLineToScroll.size(); iNCursorX++)
                                {
                                    if( char_is_alnum(currentLineToScroll[iNCursorX],false,true)==false )
                                    {
                                        break;
                                    }
                                }
                                if( iNCursorX >=(int)currentLineToScroll.size() )
                                {
                                    iNCursorX >(int)currentLineToScroll.size()-1;
                                }
                                if( iNCursorX < 0)
                                {
                                    iNCursorX = 0;
                                }
                                cursorXPos = iNCursorX;
                            }
                        }
                        scroll_to_cursor();
                        showCursor = true;
                        cursorTimer = 0;
                        if( userInput->shiftKeyIsPressed)
                        {
                            selectionEndCursorXPos = cursorXPos;
                            selectionEndCursorYPos = cursorYPos;
                        }
                        rightDelay = 0;
                    }
                    codeBeingSuggested = false;
                }
                else
                {
                    dKeyDelay = 0;
                    if( userInput->mouseScrollingUp > 0)
                    {
                        //move_up( linesWithinView/4);
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                    }
                    else if( mouseHoveringInTextArea && userInput->mouseScrollingDown > 0)
                    {
                        //move_down( linesWithinView/4);
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                    }
                    else if(  (enterDelay > (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*1.3*FPS_RATIO || ( !userInput->pressed[kb_enter] && userInput->released[kb_enter] )  )  && !isReadOnly )
                    {
                        if( codeBeingSuggested )
                        {
                            if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                            {
                                std::string prevStr = listOfStrings[cursorYPos];
                                if( iSuggestionPos >= 0 && iSuggestionPos < (int)suggestedCompilerTerms.size() )
                                {
                                    GPE_Compiler_Term * tempTerm = suggestedCompilerTerms.at(iSuggestionPos);
                                    if( tempTerm!=NULL)
                                    {
                                        if( tempTerm->termType==CTERM_FUNCTION)
                                        {
                                            prevStr = prevStr.substr(0,tempCLineXStartPos)+tempTerm->termString+"()"+prevStr.substr(tempCLineXEndPos+1);
                                            cursorXPos = tempCLineXStartPos + (int)tempTerm->termString.size()+1;
                                        }
                                        else
                                        {
                                            prevStr = prevStr.substr(0,tempCLineXStartPos)+tempTerm->termString+prevStr.substr(tempCLineXEndPos+1);
                                            cursorXPos = tempCLineXStartPos + (int)tempTerm->termString.size();
                                        }
                                        listOfStrings[cursorYPos] = prevStr;
                                    }
                                }
                            }
                            codeBeingSuggested = false;
                            suggestedCompilerTerms.clear();
                            enterDelay = 0;
                            userInput->reset_all_input();
                        }
                        else
                        {
                            log_editable_action();
                            delete_selection();
                            lineToEdit = listOfStrings[cursorYPos];
                            //go to next line
                            std::string nextString = "";
                            if( (int)lineToEdit.size()> 0)
                            {
                                nextString = get_substring(lineToEdit,cursorXPos);
                                lineToEdit = get_substring(lineToEdit,0, cursorXPos);
                            }
                            else
                            {
                                lineToEdit = "";
                                nextString = "";
                            }
                            cursorXPos = 0;
                            if( (int)listOfStrings.size()>0 )
                            {
                                listOfStrings.erase(listOfStrings.begin()+cursorYPos );
                                listOfStrings.insert(listOfStrings.begin()+cursorYPos,lineToEdit);
                                int numbOfSpaces =  get_leading_space_count(lineToEdit);
                                cursorXPos = 0;
                                if( numbOfSpaces > 0)
                                {
                                    for(int i= 0; i < numbOfSpaces; i++)
                                    {
                                        nextString=" "+nextString;
                                    }
                                    cursorXPos = numbOfSpaces;
                                }
                                if( (int)lineToEdit.size()>0)
                                {
                                    std::string lastChar = get_substring(lineToEdit, (int)lineToEdit.size()-1 );
                                    if( lastChar.compare("{" )==0)
                                    {
                                        nextString=generate_tabs(1)+nextString;
                                        cursorXPos+=get_tab_space_count();
                                    }
                                }
                                listOfStrings.insert(listOfStrings.begin()+cursorYPos+1,nextString);
                                userInput->reset_all_input();
                            }
                            else
                            {
                                listOfStrings.push_back(lineToEdit);
                                listOfStrings.push_back(nextString);
                            }
                            if( cursorXPos < 0)
                            {
                                cursorXPos = 0;
                            }
                            cursorYPos+=1;
                            move_down();
                            showCursor = true;
                            cursorTimer = 0;
                            scroll_to_cursor();
                            codeBeingSuggested = false;
                            enterDelay = 0;
                        }
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                        enterDelay = 0;
                    }
                    else if( leftDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*1.3*FPS_RATIO  || ( !userInput->released[kb_left] && userInput->pressed[kb_left] ) )
                    {
                        if( userInput->shiftKeyIsPressed )
                        {
                            if( selectionCursorXPos==selectionEndCursorXPos && selectionCursorYPos==selectionEndCursorYPos )
                            {
                                selectionCursorXPos = cursorXPos;
                                selectionCursorYPos = cursorYPos;
                            }
                        }
                        else
                        {
                            reset_selection(-1);
                        }
                        if( cursorXPos > 0)
                        {
                            int tabCharCount = get_tab_space_count();
                            if( (int)lineToEdit.size() >= cursorXPos-tabCharCount )
							{
							    bool hasLeadingTabs = true;
							    for( int iCharPos = std::min( cursorXPos-1, (int)lineToEdit.size()-1 ); iCharPos >=0 && iCharPos >=cursorXPos-tabCharCount; iCharPos-- )
                                {
                                    if( lineToEdit[iCharPos]!=' ')
                                    {
                                        hasLeadingTabs = false;
                                    }
                                }
                                if( hasLeadingTabs)
                                {
                                    cursorXPos-=tabCharCount;
                                }
                                else
                                {
                                    cursorXPos-=1;
                                }
                            }
                            else
                            {
                                cursorXPos-=1;
                            }
                            //adjust_fortabs();
                        }
                        else if( cursorYPos > 0 )
                        {
                            cursorYPos-=1;
                            move_up();
                            std::string prevString = listOfStrings[cursorYPos];
                            cursorXPos = prevString.size();
                            if( cursorXPos < 0)
                            {
                                cursorXPos = 0;
                            }
                            adjust_fortabs();
                        }
                        if( userInput->shiftKeyIsPressed)
                        {
                            selectionEndCursorXPos = cursorXPos;
                            selectionEndCursorYPos = cursorYPos;
                        }
                        leftDelay = 0;
                        scroll_to_cursor();
                        codeBeingSuggested = false;
                        find_documentation_description();
                    }
                    else if( rightDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*1.3*FPS_RATIO  || ( !userInput->released[kb_right] && userInput->pressed[kb_right] ))
                    {
                        lineToEdit = listOfStrings[cursorYPos];
                        if( userInput->shiftKeyIsPressed)
                        {
                            if( selectionCursorXPos==selectionEndCursorXPos && selectionCursorYPos==selectionEndCursorYPos )
                            {
                                selectionCursorXPos = cursorXPos;
                                selectionCursorYPos = cursorYPos;
                            }
                        }
                        else
                        {
                            reset_selection(1);
                        }
                        //special shift action
                        cursorXPos+=1;
                        if( cursorXPos > (int)lineToEdit.size() )
                        {
                            //go to next line if available
                            if(cursorYPos < (int) listOfStrings.size()-1 )
                            {
                                cursorXPos = 0;
                                cursorYPos+=1;
                                move_down();
                            }
                            else
                            {
                                cursorXPos = (int)lineToEdit.size();
                            }
                        }
                        else
                        {
                            //adjust_fortabs();
                        }
                        if( userInput->shiftKeyIsPressed)
                        {
                            selectionEndCursorXPos = cursorXPos;
                            selectionEndCursorYPos = cursorYPos;
                        }
                        rightDelay = 0;
                        showCursor = true;
                        cursorTimer = 0;
                        scroll_to_cursor();
                        codeBeingSuggested = false;
                        find_documentation_description();
                    }
                    else if( upDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*2*FPS_RATIO  || ( !userInput->released[kb_up] && userInput->pressed[kb_up] ) )
                    {
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                        if( codeBeingSuggested )
                        {
                            if( iSuggestionPos > 0)
                            {
                                iSuggestionPos--;
                                if( iSuggestionPos < iSuggestedStartPos)
                                {
                                    iSuggestedStartPos = iSuggestionPos;
                                }
                            }
                            upDelay = -1;
                        }
                        else
                        {
                            if( userInput->shiftKeyIsPressed)
                            {
                                if( selectionCursorXPos==selectionEndCursorXPos && selectionCursorYPos==selectionEndCursorYPos )
                                {
                                    selectionCursorXPos = cursorXPos;
                                    selectionCursorYPos = cursorYPos;
                                }
                            }
                            else
                            {
                                reset_selection(-1);
                            }
                            //special shift action
                            if( cursorYPos>0)
                            {
                                cursorYPos-=1;
                                if( lineStartYPos==cursorYPos+1)
                                {
                                    move_up();
                                }
                                else if( cursorYPos < lineStartYPos || cursorYPos > lineStartYPos+linesWithinView)
                                {
                                    lineStartYPos = cursorYPos;
                                }
                                std::string prevLine = listOfStrings[cursorYPos];
                                if( cursorXPos >= (int)prevLine.size() )
                                {
                                    cursorXPos = (int)prevLine.size()-1;
                                    if( cursorXPos<0)
                                    {
                                        cursorXPos = 0;
                                    }
                                }
                            }
                            if( userInput->shiftKeyIsPressed)
                            {
                                selectionEndCursorXPos = cursorXPos;
                                selectionEndCursorYPos = cursorYPos;
                            }
                            upDelay = 0;
                            showCursor = true;
                            cursorTimer = 0;
                            adjust_fortabs();
                            scroll_to_cursor();
                            find_documentation_description();
                        }
                    }
                    else if( downDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*2*FPS_RATIO  || ( !userInput->released[kb_down] && userInput->pressed[kb_down] ) )
                    {
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm  = NULL;
                        if( codeBeingSuggested )
                        {
                            if( iSuggestionPos < (int)suggestedCompilerTerms.size()-1 )
                            {
                                iSuggestionPos++;
                                if( iSuggestionPos >= iSuggestedStartPos+suggestedTextMaxInViewCount)
                                {
                                    iSuggestedStartPos = iSuggestionPos;
                                    if( iSuggestedStartPos+suggestedTextMaxInViewCount >=(int)suggestedCompilerTerms.size() )
                                    {
                                        iSuggestedStartPos = (int)suggestedCompilerTerms.size() -  suggestedTextMaxInViewCount;
                                    }
                                    if( iSuggestedStartPos < 0)
                                    {
                                        iSuggestedStartPos = 0;
                                    }
                                }
                            }
                            downDelay = -1;
                        }
                        else
                        {
                            if( userInput->shiftKeyIsPressed)
                            {
                                if( selectionCursorXPos==selectionEndCursorXPos && selectionCursorYPos==selectionEndCursorYPos )
                                {
                                    selectionCursorXPos = cursorXPos;
                                    selectionCursorYPos = cursorYPos;
                                }
                            }
                            else
                            {
                                reset_selection(1);
                            }
                            //special shift action
                            if( cursorYPos < (int)listOfStrings.size()-1 )
                            {
                                cursorYPos+=1;
                                if( lineStartYPos>=cursorYPos+linesWithinView-1)
                                {
                                    move_down();
                                }
                                else if( cursorYPos < lineStartYPos || cursorYPos > lineStartYPos+linesWithinView)
                                {
                                    lineStartYPos = cursorYPos;
                                }
                                std::string nextLine = listOfStrings[cursorYPos];
                                if( cursorXPos >= (int)nextLine.size() )
                                    {
                                        cursorXPos = (int)nextLine.size()-1;
                                        if( cursorXPos<0)
                                        {
                                            cursorXPos = 0;
                                        }
                                    }
                                }
                                if( userInput->shiftKeyIsPressed)
                                {
                                    selectionEndCursorXPos = cursorXPos;
                                    selectionEndCursorYPos = cursorYPos;
                                }
                                downDelay = 0;
                                showCursor = true;
                                cursorTimer = 0;
                                adjust_fortabs();
                                scroll_to_cursor();
                                find_documentation_description();
                            }
                    }
                    else if( bscDelay > (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*2*FPS_RATIO || ( userInput->pressed[kb_backspace] && !userInput->released[kb_backspace] ) )
                    {
                        bscDelay = 0;
                        if( !isReadOnly)
                        {
                            bscDelay = 0;
                            if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos)
                            {
                                delete_selection();
                            }
                            else if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                            {
                                lineToEdit = listOfStrings[cursorYPos];
                                int prevSize = (int)lineToEdit.size();
                                if( prevSize>0)
                                {
                                    if( cursorXPos > prevSize )
                                    {
                                        cursorXPos = prevSize;
                                    }
                                }
                                else
                                {
                                    cursorXPos = 0;
                                }
                                if( cursorXPos>0 && cursorXPos <= (int)lineToEdit.size() )
                                {
                                    textInputString = get_substring(lineToEdit,0,cursorXPos);
                                    std::string rightSide = get_substring(lineToEdit,cursorXPos);
                                    if( cursorXPos >= (int)lineToEdit.size() )
                                    {
                                        textInputString = get_substring(lineToEdit,0);
                                        rightSide = "";
                                    }
                                    int trailingSpaces = get_trailing_space_count(textInputString);
                                    int tabsToCheckCount = get_tab_space_count();
                                    if( trailingSpaces >= tabsToCheckCount )
                                    {
                                        cursorXPos -= tabsToCheckCount;
                                        textInputString = get_substring(textInputString,0,cursorXPos);
                                    }
                                    else
                                    {
                                        cursorXPos -=1;
                                        textInputString = get_substring(textInputString,0,cursorXPos);
                                    }

                                    textInputString+=rightSide;
                                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                                    if( cursorYPos>=0)
                                    {
                                        listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                                    }
                                    else
                                    {
                                        listOfStrings.push_back(textInputString);
                                    }
                                    log_editable_action();
                                }
                                else if( cursorYPos>=1)
                                {
                                    log_editable_action();
                                    textInputString = lineToEdit;
                                    std::string prevString = listOfStrings.at(cursorYPos-1);
                                    cursorXPos = prevString.size();
                                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                                    cursorYPos -=1;
                                    if( cursorYPos < lineStartYPos && cursorYPos>=0)
                                    {
                                        lineStartYPos-=1;
                                    }
                                    textInputString = listOfStrings[cursorYPos]+lineToEdit;
                                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                                    listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                                    log_editable_action();
                                }
                            }
                            bscDelay = 0;
                            showCursor = true;
                            cursorTimer = 0;
                            scroll_to_cursor();
                        }
                        codeBeingSuggested = false;
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm  = NULL;

                    }
                    else if( delDelay >= (MAIN_GUI_SETTINGS->textAreaDelayTime+1)*2*FPS_RATIO  || ( userInput->pressed[kb_delete] && !userInput->released[kb_delete] ) )
                    {
                        delDelay = 0;
                        if(!isReadOnly)
                        {
                            log_editable_action();
                            if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos)
                            {
                                delete_selection();
                            }
                            else if( cursorYPos >=0 && cursorYPos < (int)listOfStrings.size() )
                            {
                                lineToEdit = listOfStrings[cursorYPos];
                                int prevSize = (int)lineToEdit.size();
                                if( prevSize>0)
                                {
                                    if( cursorXPos > prevSize )
                                    {
                                        cursorXPos = prevSize;
                                    }
                                }
                                else
                                {
                                    cursorXPos = 0;
                                }
                                if( cursorXPos>=0 && cursorXPos < (int)lineToEdit.size() )
                                {
                                    textInputString = get_substring(lineToEdit,0,cursorXPos);
                                    std::string rightSide = get_substring(lineToEdit,cursorXPos+1);
                                    if( cursorXPos >= (int)lineToEdit.size() )
                                    {
                                        textInputString = get_substring(lineToEdit,0);
                                        rightSide = "";
                                    }

                                    textInputString+=rightSide;
                                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                                    if( cursorYPos>=0)
                                    {
                                        listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                                    }
                                    else
                                    {
                                        listOfStrings.push_back(textInputString);
                                    }
                                    log_editable_action();
                                }
                                else if( cursorYPos>=0 && cursorXPos>=(int)lineToEdit.size() && cursorYPos < (int)listOfStrings.size()-1 )
                                {
                                    log_editable_action();
                                    textInputString = lineToEdit;
                                    std::string prevString = listOfStrings.at(cursorYPos+1);
                                    cursorXPos = lineToEdit.size();
                                    textInputString = lineToEdit+prevString;
                                    listOfStrings.erase(listOfStrings.begin()+cursorYPos+1);
                                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                                    listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                                    log_editable_action();
                                }
                            }
                            delDelay = 0;
                            showCursor = true;
                            cursorTimer = 0;
                            scroll_to_cursor();
                        }
                        codeBeingSuggested = false;
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm  = NULL;

                    }
                    else if( tabDelay > (MAIN_GUI_SETTINGS->normalInputDelayTime+1)*2*FPS_RATIO || ( !userInput->pressed[kb_tab] && userInput->released[kb_tab] ) )
                    {
                        tabDelay = 0;
                        if( !isReadOnly)
                        {
                            int tabStartYPos = 0;
                            int tabEndYPos = 0;
                            if( selectionCursorYPos>selectionEndCursorYPos)
                            {
                                tabEndYPos = selectionCursorYPos;
                                tabStartYPos = selectionEndCursorYPos;
                            }
                            else
                            {
                                tabStartYPos = selectionCursorYPos;
                                tabEndYPos = selectionEndCursorYPos;
                            }

                            int tabCharCount = get_tab_space_count();
                            if( userInput->shiftKeyIsPressed)
                            {
                                std::string strToUnTab = "";
                                if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos )
                                {
                                    for( int iTabPos = tabStartYPos; iTabPos <= tabEndYPos; iTabPos++)
                                    {
                                        strToUnTab = listOfStrings[iTabPos];
                                        if( has_early_tab(strToUnTab) )
                                        {
                                            strToUnTab = untab_string(strToUnTab);
                                            listOfStrings[iTabPos] = strToUnTab;
                                            if( iTabPos ==selectionCursorYPos && selectionCursorYPos==selectionEndCursorYPos )
                                            {
                                                if( selectionCursorXPos>selectionEndCursorXPos)
                                                {
                                                    selectionCursorXPos-=tabCharCount;
                                                }
                                                else
                                                {
                                                    selectionEndCursorXPos-=tabCharCount;
                                                }
                                            }
                                            else if(iTabPos ==selectionEndCursorYPos  )
                                            {
                                                if( selectionCursorYPos>selectionEndCursorYPos)
                                                {
                                                    selectionCursorXPos-=tabCharCount;
                                                }
                                                else
                                                {
                                                    selectionEndCursorXPos-=tabCharCount;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                std::string tabAddition = generate_tabs(1);
                                if( selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos )
                                {
                                    for( int iTabPos = tabStartYPos; iTabPos <= tabEndYPos; iTabPos++)
                                    {
                                        listOfStrings[iTabPos] = tabAddition+listOfStrings[iTabPos];
                                    }
                                    if( selectionCursorYPos==selectionEndCursorYPos)
                                    {
                                        if( selectionCursorXPos>selectionEndCursorXPos)
                                        {
                                            selectionCursorXPos+=tabCharCount;
                                        }
                                        else
                                        {
                                            selectionEndCursorXPos+=tabCharCount;
                                        }
                                    }
                                    else
                                    {
                                        if( selectionCursorYPos>selectionEndCursorYPos)
                                        {
                                            selectionCursorXPos+=tabCharCount;
                                        }
                                        else
                                        {
                                            selectionEndCursorXPos+=tabCharCount;
                                        }
                                    }
                                }
                                else
                                {
                                    delete_selection();
                                    textInputString = get_substring(lineToEdit,0,cursorXPos);
                                    textInputString+=tabAddition;
                                    textInputString+=get_substring(lineToEdit,cursorXPos);
                                    cursorXPos+=tabCharCount;
                                    userInput->inkeys = "";
                                    listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                                    listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                                    scroll_to_cursor();
                                }

                                scroll_to_pos(lineStartYPos, cursorXPos+tabCharCount );
                            }
                            save_edit();
                        }
                        showCursor = true;
                        cursorTimer = 0;
                        codeBeingSuggested = false;
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                        tabDelay= 0;
                    }
                    else if( (int)userInput->inkeys.size()>0 && !isReadOnly )
                    {
                        //Type input into textarea
                        delete_selection();
                        log_editable_action();
                        textInputString = get_substring(lineToEdit,0,cursorXPos);
                        std::string preInputString = string_replace_all(textInputString," ","");
                        textInputString+=userInput->inkeys;
                        listOfStrings.erase(listOfStrings.begin()+cursorYPos);
                        std::string restofLine = get_substring(lineToEdit,cursorXPos);
                        if( userInput->inkeys=="{" && (int)restofLine.size()==0 && (int)preInputString.size()==0 )
                        {
                            int numbOfSpaces =  get_leading_space_count(lineToEdit);
                            cursorXPos = 0;
                            std::string nextString = "";
                            if( numbOfSpaces > 0)
                            {
                                for(int i= 0; i < numbOfSpaces; i++)
                                {
                                    nextString=" "+nextString;
                                }
                                cursorXPos = numbOfSpaces;
                            }
                            std::string bracketString = nextString+"}";
                            nextString="    "+nextString;
                            cursorXPos+=4;

                            textInputString+=restofLine;
                            listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);
                            listOfStrings.insert(listOfStrings.begin()+cursorYPos+1,nextString);
                            listOfStrings.insert(listOfStrings.begin()+cursorYPos+2,bracketString);
                            cursorYPos+=1;
                            scroll_to_pos(cursorYPos+1,cursorXPos);
                            userInput->inkeys = "";
                            save_edit();
                        }
                        else
                        {
                            log_editable_action();
                            cursorXPos+=(int)userInput->inkeys.size();
                            if( userInput->inkeys=="[" )
                            {
                                textInputString+="]";
                            }
                            else if( userInput->inkeys=="{" )
                            {
                                textInputString+="}";
                            }
                            else if( userInput->inkeys=="(" )
                            {
                                textInputString+=")";
                            }
                            textInputString+=restofLine;
                            listOfStrings.insert(listOfStrings.begin()+cursorYPos,textInputString);

                            userInput->inkeys = "";
                            if( isCodeEditor)
                            find_suggested_text();
                            scroll_to_cursor();
                            GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                        }
                        userInput->inkeys = "";
                    }
                    else if( userInput->check_keyboard_released(kb_esc) )
                    {
                        MAIN_SEARCH_CONTROLLER->close_finder();
                        codeBeingSuggested = false;
                        GPE_MAIN_HIGHLIGHTER->highlightedTerm  = NULL;
                    }
                }
            }

            parseForErrorsTimerPos++;
            if( parseForErrorsTimerPos >=parseForErrorsTimerGoal)
            {
                if( isCodeEditor && codeEditorType==0)
                {
                    //parse_code_javascript(viewedSpace,cam);
                }
                parseForErrorsTimerPos = 0;
            }
        }
        else
        {
            hasScrollControl = false;
            hasArrowkeyControl = false;
        }

        if( isHovered)
        {
            if( userInput->mouseScrollingUp > 0)
            {
                if( userInput->down[kb_ctrl])
                {
                    move_left(charactersWithinView/8);
                    GPE_MAIN_HIGHLIGHTER->highlightedTerm  = NULL;
                }
                else
                {
                    move_up( 3 );
                    GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                }
            }
            else if( userInput->mouseScrollingDown > 0)
            {
                if( userInput->down[kb_ctrl])
                {
                    move_right(charactersWithinView/8);
                    GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                }
                else
                {
                    move_down( 3 );
                    GPE_MAIN_HIGHLIGHTER->highlightedTerm = NULL;
                }
            }
            hasScrollControl= true;
        }

        if( lineStartXPos < 0)
        {
            lineStartXPos = 0;
        }
        if( lineStartYPos < 0)
        {
            lineStartYPos = 0;
        }
    }

    MAIN_GUI_SETTINGS->textAreaFindBox.x = barBox.x+lineCountBoxWidth;
    //if( showXScroll && textXScroll!=NULL)
    {
        //MAIN_GUI_SETTINGS->textAreaFindBox.y = barBox.y+textEditorButtonBar->get_height()+renderBox.h+textXScroll->barBox.h;
    }
    //else
    {
        MAIN_GUI_SETTINGS->textAreaFindBox.y = barBox.y+textEditorButtonBar->get_height()+renderBox.h;
    }
    MAIN_GUI_SETTINGS->textAreaFindBox.w = barBox.w-lineCountBoxWidth;

    int findAllResult = 0;
    switch(MAIN_SEARCH_CONTROLLER->textSearchMode )
    {
        //find
        case 1:
            if( MAIN_SEARCH_CONTROLLER->findTextStringBox->has_content() )
            {
                if( MAIN_SEARCH_CONTROLLER->findTextStringBox->was_submitted() || MAIN_SEARCH_CONTROLLER->findButton->is_clicked() )
                {
                    if( find_string(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(),MAIN_SEARCH_CONTROLLER->findMatchCase->is_clicked(),false)==false )
                    {
                        cursorXPos = 0;
                        cursorYPos = 0;
                        lineStartXPos = 0;
                        lineStartYPos = 0;
                        if( find_string(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(),true,MAIN_SEARCH_CONTROLLER->findMatchCase->is_clicked(),false)==false)
                        {
                            MAIN_OVERLAY->update_temporary_message("Searched for","["+MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string()+"]","Unable to Find String");
                        }
                    }
                    MAIN_SEARCH_CONTROLLER->showFindAllResults = false;
                }
                /*
                else if( MAIN_SEARCH_CONTROLLER->findAllButton->is_clicked() )
                {
                    findAllResult = find_all_strings(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(),MAIN_SEARCH_CONTROLLER->findMatchCase->is_clicked() );
                    displayMessageTitle = "Substring Search";
                    displayMessageSubtitle = MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string();

                    if( findAllResult > 0)
                    {
                        displayMessageString = "Found "+int_to_string(findAllResult)+" results";
                        MAIN_SEARCH_CONTROLLER->showFindAllResults = true;
                    }
                    else
                    {
                        displayMessageString ="No matches found";
                        MAIN_SEARCH_CONTROLLER->showFindAllResults = false;
                    }
                    display_user_messaage();
                    MAIN_OVERLAY->update_temporary_message(displayMessageTitle,displayMessageSubtitle,displayMessageString,5);
                }
                */
            }
        break;

        //goto line
        case 2:
            //MAIN_SEARCH_CONTROLLER->goToLineStringBox->set_string("1");

            if( (int)listOfStrings.size() > 0)
            {
                MAIN_SEARCH_CONTROLLER->goToLineStringBox->descriptionText = "Go To Line: 1 - "+int_to_string( get_line_count() ) ;
            }
            else
            {
                MAIN_SEARCH_CONTROLLER->goToLineStringBox->descriptionText = "Go To Line: ";
            }

            if( ( MAIN_SEARCH_CONTROLLER->goToLineStringBox->was_submitted() || MAIN_SEARCH_CONTROLLER->goToButton->is_clicked() ) &&  MAIN_SEARCH_CONTROLLER->goToLineStringBox->is_valid() )
            {
                scroll_to_pos(MAIN_SEARCH_CONTROLLER->goToLineStringBox->get_held_number()-1 ,0);
            }
        break;

        //find/replace
        case 3:
            if( !isReadOnly)
            {
                if( MAIN_SEARCH_CONTROLLER->findTextStringBox->has_content() )
                {
                    if( MAIN_SEARCH_CONTROLLER->findTextStringBox->was_submitted() || MAIN_SEARCH_CONTROLLER->findButton->is_clicked() )
                    {
                        if( find_string(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(),true,MAIN_SEARCH_CONTROLLER->findMatchCase->is_clicked(),false)==false )
                        {
                            cursorXPos = 0;
                            cursorYPos = 0;
                            lineStartXPos = 0;
                            lineStartYPos = 0;
                            if( find_string(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(),true,MAIN_SEARCH_CONTROLLER->findMatchCase->is_clicked(),false)==false)
                            {
                                MAIN_OVERLAY->update_temporary_message("Searched for","["+MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string()+"]","Unable to Find String");
                            }
                        }
                        MAIN_SEARCH_CONTROLLER->showFindAllResults = false;
                    }
                    /*
                    else if( MAIN_SEARCH_CONTROLLER->findAllButton->is_clicked() )
                    {
                        findAllResult = find_all_strings(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(),MAIN_SEARCH_CONTROLLER->findMatchCase->is_clicked() );
                        displayMessageTitle = "Substring Search";
                        displayMessageSubtitle = MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string();

                        if( findAllResult > 0)
                        {
                            displayMessageString = "Found "+int_to_string(findAllResult)+" results";
                            MAIN_SEARCH_CONTROLLER->showFindAllResults = true;
                        }
                        else
                        {
                            displayMessageString ="No matches found";
                            MAIN_SEARCH_CONTROLLER->showFindAllResults = false;
                        }
                        display_user_messaage();
                        MAIN_OVERLAY->update_temporary_message(displayMessageTitle,displayMessageSubtitle,displayMessageString,15);
                    }
                    */
                    else if( MAIN_SEARCH_CONTROLLER->replaceTextStringBox->has_content() )
                    {
                        if( MAIN_SEARCH_CONTROLLER->replaceTextStringBox->was_submitted() || MAIN_SEARCH_CONTROLLER->replaceButton->is_clicked() )
                        {
                            MAIN_SEARCH_CONTROLLER->showFindAllResults = false;
                        }
                        else if( MAIN_SEARCH_CONTROLLER->replaceAllButton->is_clicked() )
                        {
                            if( display_get_prompt("Warning!","All copies of the text will be replaced. Are you sure you want to continue this operation?")==DISPLAY_QUERY_YES )
                            {
                                findAllResult = find_all_strings(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(),true);
                                displayMessageTitle = "Replacing Substring";
                                displayMessageSubtitle = MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string();

                                if( findAllResult > 0)
                                {
                                    displayMessageString = "Replaced "+int_to_string(replace_all_found(MAIN_SEARCH_CONTROLLER->findTextStringBox->get_string(), MAIN_SEARCH_CONTROLLER->replaceTextStringBox->get_string() ) )+" copies.";;
                                    MAIN_SEARCH_CONTROLLER->showFindAllResults = true;
                                }
                                else
                                {
                                    displayMessageString ="No matches found";
                                    MAIN_SEARCH_CONTROLLER->showFindAllResults = false;
                                }
                                display_user_messaage();
                                MAIN_OVERLAY->update_temporary_message(displayMessageTitle,displayMessageSubtitle,displayMessageString,1);
                            }
                        }
                    }
                }
            }
        break;

        default:

        break;
    }

    if( !isReadOnly && pasteCommandGiven && SDL_HasClipboardText()==SDL_TRUE )
    {
        delete_selection();
        paste_clipboard();
        codeBeingSuggested = false;
        userInput->reset_all_input();
        process_self( viewedSpace,cam );
    }

    if( undoableActionOccurred)
    {
        time_t currentTimeNow;
        time(&currentTimeNow);
        if( difftime(currentTimeNow,lastUndoableActionTime ) >=4 )
        {
            save_edit();
        }
    }
}

void GPE_TextAreaInputBasic::redo_edit()
{
    if( can_redo() )
    {
        if( currentPositionInHistory >=0 && currentPositionInHistory+1 < (int)savedHistory.size() )
        {
            GPE_TextAreaInputBasic * tempPlace = savedHistory.at(currentPositionInHistory+1);
            if( tempPlace!=NULL)
            {
                copy_source(tempPlace,true);
                currentPositionInHistory++;
                showCursor = true;
                cursorTimer = 0;
            }
        }
    }
}

void GPE_TextAreaInputBasic::render_code_css(GPE_Renderer * cRender ,GPE_Rect * viewedSpace, GPE_Rect * cam )
{
    viewedSpace = GPE_find_camera(viewedSpace);
    cam = GPE_find_camera(cam);

    if( viewedSpace!=NULL && cam!=NULL && textEditorButtonBar!=NULL)
    {
        renderBox.x = barBox.x-cam->x;
        renderBox.y = barBox.y-cam->y+textEditorButtonBar->get_height();
        renderBox.w = barBox.w;

        if(showYScroll)
        {
            renderBox.w-=16;
        }
        renderBox.h = barBox.h-textEditorButtonBar->get_height()-32;

        int mostCharactersOfText = get_most_characters_used();
        if( mostCharactersOfText > charactersWithinView && showYScroll )
        {
            mostCharactersOfText-=2;
        }
        int i = 0;
        std::string currStringToRender = "";
        std::string currentLineInView = "";
        //Processes the sythax to re-render each one
        std::string foundSyntaxString = "";
        std::string foundGPEKeyTag= "";
        std::string foundGPEProperty = "";
        int tempSynStringSize = 0;
        int currPosToParse = 0, lineEnd = 0;
        int textRenderXPos = 0, textRenderYPos = 0;
        GPE_Color * color = NULL;
        bool isInBlockCommentMode = false;
        bool isInDoubleQuoteMode = false;
        bool isInSingleQuoteMode = false;
        int minLineToRender = std::max(lineStartYPos-50 ,0);
        int maxLineToRender = std::min(lineStartYPos+linesWithinView ,(int)listOfStrings.size()-1 );
        int endBlockCommentPos = 0;
        int endDQuoteCommentPos = 0;
        int endSQuoteCommentPos = 0;
        bool commentFoundInSymbols = false;
        GPE_ParsedText * mLineComment = new GPE_ParsedText(-1, -1);
        GPE_ParsedText * dqLineComment = new GPE_ParsedText(-1, -1);
        GPE_ParsedText * sqLineComment = new GPE_ParsedText(-1, -1);
        GPE_ParsedText * tempParseTextToAdd = new GPE_ParsedText(-1, -1);

        //Finds the previous mode of  the editor up to 20 lines to the current lineStartYPos
        for( i=minLineToRender; i < lineStartYPos && i < (int)listOfStrings.size(); i++)
        {
            currStringToRender = listOfStrings[i];
            currPosToParse = 0;
            lineEnd = (int)currStringToRender.size();
            while (currPosToParse < lineEnd)
            {
                if( isInBlockCommentMode==false && isInDoubleQuoteMode==false && isInSingleQuoteMode==false)
                {
                    if (currPosToParse < lineEnd)
                    {
                        if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currPosToParse + 1 < lineEnd && currStringToRender[currPosToParse + 1] == '/' )
                        {
                            currPosToParse = lineEnd;
                        }
                        else if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currStringToRender[currPosToParse + 1] == '*' )
                        {
                            isInBlockCommentMode = true;
                            currPosToParse+=2;
                        }
                        else if(currStringToRender[currPosToParse] == '"')
                        {
                            isInDoubleQuoteMode = true;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '\'')
                        {
                            isInSingleQuoteMode = true;
                            currPosToParse++;
                        }
                        else
                        {
                            currPosToParse++;
                        }
                    }
                }

                if( isInBlockCommentMode)
                {
                    endBlockCommentPos = currStringToRender.find("*/");
                    if( endBlockCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endBlockCommentPos+2;
                        isInBlockCommentMode = false;
                    }
                }
                else if( isInDoubleQuoteMode)
                {
                    endDQuoteCommentPos = currStringToRender.find('"',currPosToParse);
                    if( endDQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endDQuoteCommentPos+1;
                        isInDoubleQuoteMode = false;
                    }
                }
                else if( isInSingleQuoteMode)
                {
                    endSQuoteCommentPos = currStringToRender.find("'",currPosToParse);
                    if( endSQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endSQuoteCommentPos+1;
                        isInSingleQuoteMode = false;
                    }
                }
            }
        }

        for( i=lineStartYPos; i <= maxLineToRender; i++)
        {
            //resets highlight boxes and such
            if( commentLineText!=NULL)
            {
                commentLineText->reset_self();
            }
            if( datatypeLineText!=NULL)
            {
                datatypeLineText->reset_self();
            }
            if( dQuoteLineText!=NULL)
            {
                dQuoteLineText->reset_self();
            }
            if( functionLineText!=NULL)
            {
                functionLineText->reset_self();
            }
            if( keywordLineText!=NULL)
            {
                keywordLineText->reset_self();
            }
            if( normalLineText!=NULL)
            {
                normalLineText->reset_self();
            }

            if( numberLineText!=NULL)
            {
                numberLineText->reset_self();
            }

            if( sQuoteLineText!=NULL)
            {
                sQuoteLineText->reset_self();
            }

            if( symbolLineText!=NULL)
            {
                symbolLineText->reset_self();
            };

            currStringToRender = listOfStrings[i];
            currPosToParse = 0;

            lineEnd = (int)currStringToRender.size();

            endBlockCommentPos=(int)std::string::npos;
            endDQuoteCommentPos=(int)std::string::npos;
            endSQuoteCommentPos=(int)std::string::npos;

            foundGPEKeyTag = "";
            foundGPEProperty = "";
            mLineComment->textStart = -1;
            mLineComment->textEnd = -1;
            tempParseTextToAdd->textStart = -1;
            tempParseTextToAdd->textEnd = -1;

            while (currPosToParse < lineEnd)
            {
                if( isInBlockCommentMode==false && isInDoubleQuoteMode==false && isInSingleQuoteMode==false)
                {
                    while (currPosToParse < lineEnd && currStringToRender[currPosToParse]==' ')
                    {
                        currPosToParse++;
                    }
                    if (currPosToParse < lineEnd)
                    {
                        if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currPosToParse + 1 < lineEnd && currStringToRender[currPosToParse + 1] == '/' )
                        {
                            commentLineText->foundParses.push_back( new GPE_ParsedText(currPosToParse, lineEnd));
                            currPosToParse = lineEnd;
                        }
                        else if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currStringToRender[currPosToParse + 1] == '*' )
                        {
                            isInBlockCommentMode = true;
                            mLineComment->textStart = currPosToParse;
                            currPosToParse+=2;
                        }
                        else if(currStringToRender[currPosToParse] == '"')
                        {
                            isInDoubleQuoteMode = true;
                            dqLineComment->textStart = currPosToParse;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '\'')
                        {
                            isInSingleQuoteMode = true;
                            sqLineComment->textStart = currPosToParse;
                            currPosToParse++;
                        }
                        else if (isdigit(currStringToRender[currPosToParse]))
                        {
                            tempParseTextToAdd->textStart = currPosToParse;
                            currPosToParse++;
                            while( (currPosToParse < lineEnd && isdigit( currStringToRender[currPosToParse] )  ) || currStringToRender[currPosToParse] ==' ')
                            {
                                currPosToParse++;
                            }
                            tempParseTextToAdd->textEnd = currPosToParse;
                            numberLineText->foundParses.push_back(tempParseTextToAdd);
                            tempParseTextToAdd = new GPE_ParsedText(0, -1);
                        }
                        else if (GPE_MAIN_HIGHLIGHTER->charIsSymbol(currStringToRender[currPosToParse]))
                        {
                            tempParseTextToAdd->textStart = currPosToParse;
                            currPosToParse++;
                            commentFoundInSymbols = false;
                            while( ( commentFoundInSymbols==false && currPosToParse < lineEnd && GPE_MAIN_HIGHLIGHTER->charIsSymbol(currStringToRender[currPosToParse] ) )|| currStringToRender[currPosToParse] ==' ')
                            {
                                if( lineEnd > currPosToParse+1)
                                {
                                    if( currStringToRender[currPosToParse] == '/' && (currStringToRender[currPosToParse + 1] == '/' || currStringToRender[currPosToParse + 1] == '*' ) )
                                    {
                                        commentFoundInSymbols = true;
                                    }
                                    else if (currStringToRender[currPosToParse] == '*' && currStringToRender[currPosToParse + 1] == '/' )
                                    {
                                        commentFoundInSymbols = true;
                                    }
                                    else
                                    {
                                        currPosToParse++;
                                    }
                                }
                                else
                                {
                                    currPosToParse++;
                                }
                            }
                            tempParseTextToAdd->textEnd = currPosToParse;
                            symbolLineText->foundParses.push_back(tempParseTextToAdd);
                            tempParseTextToAdd = new GPE_ParsedText(0, -1);
                        }
                        else
                        {
                            if (char_is_alpha(currStringToRender[currPosToParse],false,true) )
                            {
                                //color = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;
                                tempParseTextToAdd->textStart = currPosToParse;
                                currPosToParse++;
                                while (currPosToParse < lineEnd && char_is_alnum(currStringToRender[currPosToParse],false,true) )
                                {
                                    currPosToParse++;
                                }
                                tempParseTextToAdd->textEnd = currPosToParse;
                                normalLineText->foundParses.push_back(tempParseTextToAdd);
                                tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                            }
                            // add new cases here:
                            // else if (...)
                            // {
                            //     ...
                            // }
                            else
                            {
                                //color = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;
                                //anything else is just regular text as well...
                                tempParseTextToAdd->textStart = currPosToParse;
                                tempParseTextToAdd->textEnd = currPosToParse+1;
                                normalLineText->foundParses.push_back(tempParseTextToAdd);
                                tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                                currPosToParse++;
                            }
                        }
                    }
                }
                if( isInBlockCommentMode)
                {
                    endBlockCommentPos = currStringToRender.find("*/");
                    if( endBlockCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endBlockCommentPos+2;
                        isInBlockCommentMode = false;
                    }
                    mLineComment->textEnd = currPosToParse;
                    commentLineText->foundParses.push_back(mLineComment);
                    mLineComment = new GPE_ParsedText(0, -1);
                }
                else if( isInDoubleQuoteMode)
                {
                    endDQuoteCommentPos = currStringToRender.find('"',currPosToParse);
                    if( endDQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endDQuoteCommentPos+1;
                        isInDoubleQuoteMode = false;
                    }
                    dqLineComment->textEnd = currPosToParse;
                    dQuoteLineText->foundParses.push_back(dqLineComment);
                    dqLineComment = new GPE_ParsedText(0, -1);
                }
                else if( isInSingleQuoteMode)
                {
                    endSQuoteCommentPos = currStringToRender.find("'",currPosToParse);
                    if( endSQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endSQuoteCommentPos+1;
                        isInSingleQuoteMode = false;
                    }
                    sqLineComment->textEnd = currPosToParse;
                    sQuoteLineText->foundParses.push_back(sqLineComment);
                    sqLineComment = new GPE_ParsedText(0, -1);
                }
            }

            if ( i >=lineStartYPos  )
            {
                textRenderXPos = renderBox.x+lineCountBoxWidth+2;
                textRenderYPos = renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4;

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Color;
                normalLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Number_Color;
                numberLineText->render_tokens(cRender,FONT_TEXTINPUT_NUMBER,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color,true );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Symbols_Color;
                symbolLineText->render_tokens(cRender,FONT_TEXTINPUT_SYMBOL,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                //
                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Function_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Function_Color;
                }
                functionLineText->render_tokens(cRender,FONT_TEXTINPUT_FUNCTION,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                //
                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Keyword_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Keyword_Color;
                }
                keywordLineText->render_tokens(cRender,FONT_TEXTINPUT_KEYWORD,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Keyword_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Keyword_Color;
                }
                projectKeywordLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Function_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Function_Color;
                }
                projectFunctionLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );


                color = GPE_MAIN_TEMPLATE->Text_Box_Font_DataType_Color;
                datatypeLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_DataType_Color;
                datatypeLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_SQuote_Color;
                sQuoteLineText->render_tokens(cRender,FONT_TEXTINPUT_QUOTE,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_DQuote_Color;
                dQuoteLineText->render_tokens(cRender,FONT_TEXTINPUT_QUOTE,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Comment_Color;
                commentLineText->render_tokens(cRender,FONT_TEXTINPUT_COMMENT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );
            }

        }

        if( mLineComment!=NULL)
        {
            delete mLineComment;
            mLineComment = NULL;
        }
        if( dqLineComment!=NULL)
        {
            delete dqLineComment;
            dqLineComment = NULL;
        }
        if( sqLineComment!=NULL)
        {
            delete sqLineComment;
            sqLineComment = NULL;
        }
        if( tempParseTextToAdd!=NULL)
        {
            delete tempParseTextToAdd;
            tempParseTextToAdd = NULL;
        }
    }
}

void GPE_TextAreaInputBasic::render_code_javascript(GPE_Renderer * cRender ,GPE_Rect * viewedSpace, GPE_Rect * cam )
{
    viewedSpace = GPE_find_camera(viewedSpace);
    cam = GPE_find_camera(cam);
    if( viewedSpace!=NULL && cam!=NULL && textEditorButtonBar!=NULL && has_content() )
    {
        renderBox.x = barBox.x-cam->x;
        renderBox.y = barBox.y-cam->y+textEditorButtonBar->get_height();
        renderBox.w = barBox.w;

        if(showYScroll)
        {
            renderBox.w-=16;
        }
        renderBox.h = barBox.h-textEditorButtonBar->get_height()-32;

        int mostCharactersOfText = get_most_characters_used();
        if( mostCharactersOfText > charactersWithinView && showYScroll )
        {
            mostCharactersOfText-=2;
        }
        int i = 0, j = 0;
        int parsedTokensCount = 0;
        std::string currStringToRender = "";
        std::string currentLineInView = "";
        //Processes the sythax to re-render each one
        std::string foundGPEDataType = "";
        std::string foundGPEFunction = "";
        std::string foundGPEVariable = "";
        std::string foundGPEKeyword = "";
        std::string foundGPEProjectFunction = "";
        std::string foundGPEProjectKeyword = "";
        std::string foundSyntaxString = "";
        int tempSynStringSize = 0;
        int currPosToParse = 0, lineEnd = 0;
        GPE_Color *color = NULL;
        int textRenderXPos = 0, textRenderYPos = 0;
        bool isInBlockCommentMode = false;
        bool isInDoubleQuoteMode = false;
        bool isInSingleQuoteMode = false;
        int minLineToRender = std::max(lineStartYPos-20 ,0);
        int maxLineToRender = std::min(lineStartYPos+linesWithinView ,(int)listOfStrings.size()-1);
        int endBlockCommentPos = 0;
        int endDQuoteCommentPos = 0;
        int endSQuoteCommentPos = 0;
        bool commentFoundInSymbols = false;
        GPE_ParsedText * mLineComment = new GPE_ParsedText(-1, -1);
        GPE_ParsedText * dqLineComment = new GPE_ParsedText(-1, -1);
        GPE_ParsedText * sqLineComment = new GPE_ParsedText(-1, -1);
        GPE_ParsedText * tempParseTextToAdd = new GPE_ParsedText(-1, -1);

        //Finds the previous mode of  the editor up to 20 lines to the current lineStartYPos
        for( i=minLineToRender; i < lineStartYPos && i < (int)listOfStrings.size(); i++)
        {
            currStringToRender = listOfStrings[i];
            currPosToParse = 0;
            lineEnd = (int)currStringToRender.size();
            while (currPosToParse < lineEnd)
            {
                if( isInBlockCommentMode==false && isInDoubleQuoteMode==false && isInSingleQuoteMode==false)
                {
                    if (currPosToParse < lineEnd)
                    {
                        if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currPosToParse + 1 < lineEnd && currStringToRender[currPosToParse + 1] == '/' )
                        {
                            currPosToParse = lineEnd;
                        }
                        else if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currStringToRender[currPosToParse + 1] == '*' )
                        {
                            isInBlockCommentMode = true;
                            currPosToParse+=2;
                        }
                        else if(currStringToRender[currPosToParse] == '"')
                        {
                            isInDoubleQuoteMode = true;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '\'')
                        {
                            isInSingleQuoteMode = true;
                            currPosToParse++;
                        }
                        else
                        {
                            currPosToParse++;
                        }
                    }
                }

                if( isInBlockCommentMode)
                {
                    endBlockCommentPos = currStringToRender.find("*/");
                    if( endBlockCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endBlockCommentPos+2;
                        isInBlockCommentMode = false;
                    }
                }
                else if( isInDoubleQuoteMode)
                {
                    endDQuoteCommentPos = currStringToRender.find('"',currPosToParse);
                    if( endDQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endDQuoteCommentPos+1;
                        isInDoubleQuoteMode = false;
                    }
                }
                else if( isInSingleQuoteMode)
                {
                    endSQuoteCommentPos = currStringToRender.find("'",currPosToParse);
                    if( endSQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endSQuoteCommentPos+1;
                        isInSingleQuoteMode = false;
                    }
                }
            }
        }

        for( i=lineStartYPos; i <= maxLineToRender; i++)
        {
            //resets highlight boxes and such
            if( commentLineText!=NULL)
            {
                commentLineText->reset_self();
            }
            if( datatypeLineText!=NULL)
            {
                datatypeLineText->reset_self();
            }
            if( dQuoteLineText!=NULL)
            {
                dQuoteLineText->reset_self();
            }
            if( functionLineText!=NULL)
            {
                functionLineText->reset_self();
            }
            if( keywordLineText!=NULL)
            {
                keywordLineText->reset_self();
            }
            if( variableLineText!=NULL)
            {
                variableLineText->reset_self();
            }
            if( normalLineText!=NULL)
            {
                normalLineText->reset_self();
            }

            if( numberLineText!=NULL)
            {
                numberLineText->reset_self();
            }

            if( sQuoteLineText!=NULL)
            {
                sQuoteLineText->reset_self();
            }

            if( symbolLineText!=NULL)
            {
                symbolLineText->reset_self();
            }

            if( projectFunctionLineText!=NULL)
            {
                projectFunctionLineText->reset_self();
            }

            if( projectKeywordLineText!=NULL)
            {
                projectKeywordLineText->reset_self();
            }

            currStringToRender = listOfStrings[i];
            currPosToParse = 0;

            lineEnd = (int)currStringToRender.size();

            endBlockCommentPos=(int)std::string::npos;
            endDQuoteCommentPos=(int)std::string::npos;
            endSQuoteCommentPos=(int)std::string::npos;

            foundGPEKeyword = "";
            foundGPEVariable = "";
            foundGPEDataType = "";
            foundGPEProjectFunction = "";
            foundGPEProjectKeyword = "";
            mLineComment->textStart = 0;
            mLineComment->textEnd = -1;
            tempParseTextToAdd->textStart = 0;
            tempParseTextToAdd->textEnd = -1;

            while (currPosToParse < lineEnd)
            {
                while (currPosToParse < lineEnd && currStringToRender[currPosToParse]==' ')
                {
                    currPosToParse++;
                }
                if( isInBlockCommentMode==false && isInDoubleQuoteMode==false && isInSingleQuoteMode==false)
                {
                    /*
                    while (currPosToParse < lineEnd && currStringToRender[currPosToParse]==' ')
                    {
                        currPosToParse++;
                    }*/
                    if (currPosToParse < lineEnd)
                    {
                        if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currPosToParse + 1 < lineEnd && currStringToRender[currPosToParse + 1] == '/' )
                        {
                            commentLineText->foundParses.push_back( new GPE_ParsedText(currPosToParse, lineEnd));
                            currPosToParse = lineEnd;
                        }
                        else if (currPosToParse+1<lineEnd && currStringToRender[currPosToParse] == '/' && currStringToRender[currPosToParse + 1] == '*' )
                        {
                            isInBlockCommentMode = true;
                            mLineComment->textStart = currPosToParse;
                            currPosToParse+=2;
                        }
                        else if(currStringToRender[currPosToParse] == '"')
                        {
                            isInDoubleQuoteMode = true;
                            dqLineComment->textStart = currPosToParse;
                            currPosToParse++;
                        }
                        else if(currStringToRender[currPosToParse] == '\'')
                        {
                            isInSingleQuoteMode = true;
                            sqLineComment->textStart = currPosToParse;
                            currPosToParse++;
                        }
                        else if (isdigit(currStringToRender[currPosToParse]))
                        {
                            tempParseTextToAdd->textStart = currPosToParse;
                            currPosToParse++;
                            while( (currPosToParse < lineEnd && isdigit( currStringToRender[currPosToParse] )  ) || currStringToRender[currPosToParse] ==' ')
                            {
                                currPosToParse++;
                            }
                            tempParseTextToAdd->textEnd = currPosToParse;
                            numberLineText->foundParses.push_back(tempParseTextToAdd);
                            tempParseTextToAdd = new GPE_ParsedText(0, -1);
                        }
                        else if( GPE_MAIN_HIGHLIGHTER->charIsSymbol(currStringToRender[currPosToParse] ))
                        {
                            tempParseTextToAdd->textStart = currPosToParse;
                            currPosToParse++;
                            commentFoundInSymbols = false;
                            while( ( commentFoundInSymbols==false && currPosToParse < lineEnd && GPE_MAIN_HIGHLIGHTER->charIsSymbol(currStringToRender[currPosToParse] ) )|| currStringToRender[currPosToParse] ==' ')
                            {
                                if( lineEnd > currPosToParse+1)
                                {
                                    if( currStringToRender[currPosToParse] == '/' && (currStringToRender[currPosToParse + 1] == '/' || currStringToRender[currPosToParse + 1] == '*' ) )
                                    {
                                        commentFoundInSymbols = true;
                                    }
                                    else if (currStringToRender[currPosToParse] == '*' && currStringToRender[currPosToParse + 1] == '/' )
                                    {
                                        commentFoundInSymbols = true;
                                    }
                                    else
                                    {
                                        currPosToParse++;
                                    }
                                }
                                else
                                {
                                    currPosToParse++;
                                }
                            }
                            tempParseTextToAdd->textEnd = currPosToParse;
                            symbolLineText->foundParses.push_back(tempParseTextToAdd);
                            tempParseTextToAdd = new GPE_ParsedText(0, -1);
                        }
                        else
                        {
                            if( GPE_MAIN_HIGHLIGHTER!=NULL)
                            {
                                foundGPEProjectFunction = GPE_MAIN_HIGHLIGHTER->find_project_function(currStringToRender,currPosToParse);
                                foundGPEProjectKeyword = GPE_MAIN_HIGHLIGHTER->find_project_keyword(currStringToRender,currPosToParse);
                            }
                            if( (foundGPEProjectFunction )!="")
                            {
                                tempParseTextToAdd->textStart = currPosToParse;
                                while (currPosToParse < lineEnd && foundGPEProjectFunction !="")
                                {
                                    if(foundGPEProjectFunction!="" )
                                    {
                                        currPosToParse+=(int)foundGPEProjectFunction.size();
                                    }
                                    else
                                    {
                                        currPosToParse++;
                                    }
                                    foundGPEProjectFunction= GPE_MAIN_HIGHLIGHTER->find_project_function(currStringToRender,currPosToParse);
                                }
                                tempParseTextToAdd->textEnd = currPosToParse;
                                projectFunctionLineText->foundParses.push_back(tempParseTextToAdd);
                                tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                            }
                            else if( (foundGPEProjectKeyword )!="")
                            {
                                tempParseTextToAdd->textStart = currPosToParse;
                                while (currPosToParse < lineEnd && foundGPEProjectKeyword !="")
                                {
                                    if(foundGPEProjectKeyword!="" )
                                    {
                                        currPosToParse+=(int)foundGPEProjectKeyword.size();
                                    }
                                    else
                                    {
                                        currPosToParse++;
                                    }
                                    foundGPEProjectKeyword= GPE_MAIN_HIGHLIGHTER->find_project_keyword(currStringToRender,currPosToParse);
                                }
                                tempParseTextToAdd->textEnd = currPosToParse;
                                projectKeywordLineText->foundParses.push_back(tempParseTextToAdd);
                                tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                            }
                            else
                            {
                                foundGPEDataType= GPE_MAIN_HIGHLIGHTER->find_gpe_datatype(currStringToRender,currPosToParse);
                                if( (foundGPEDataType )!="")
                                {
                                    tempParseTextToAdd->textStart = currPosToParse;
                                    while (currPosToParse < lineEnd && foundGPEDataType !="")
                                    {
                                        if(foundGPEDataType!="" )
                                        {
                                            currPosToParse+=(int)foundGPEDataType.size();
                                        }
                                        else
                                        {
                                            currPosToParse++;
                                        }
                                        foundGPEDataType= GPE_MAIN_HIGHLIGHTER->find_gpe_datatype(currStringToRender,currPosToParse);
                                    }
                                    tempParseTextToAdd->textEnd = currPosToParse;
                                    datatypeLineText->foundParses.push_back(tempParseTextToAdd);
                                    tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                                }
                                else
                                {
                                    foundGPEFunction =GPE_MAIN_HIGHLIGHTER->find_gpe_function(currStringToRender,currPosToParse);
                                    if( (foundGPEFunction )!="")
                                    {
                                        tempParseTextToAdd->textStart = currPosToParse;
                                        while (currPosToParse < lineEnd && foundGPEFunction !="")
                                        {
                                            if(foundGPEFunction!="" )
                                            {
                                                currPosToParse+=(int)foundGPEFunction.size();
                                            }
                                            else
                                            {
                                                currPosToParse++;
                                            }
                                            foundGPEFunction= GPE_MAIN_HIGHLIGHTER->find_gpe_function(currStringToRender,currPosToParse);
                                        }
                                        tempParseTextToAdd->textEnd = currPosToParse;
                                        functionLineText->foundParses.push_back(tempParseTextToAdd);
                                        tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                                    }
                                    else
                                    {
                                        foundGPEVariable = GPE_MAIN_HIGHLIGHTER->find_gpe_variable(currStringToRender,currPosToParse);
                                        if( (foundGPEVariable )!="")
                                        {
                                            tempParseTextToAdd->textStart = currPosToParse;
                                            while (currPosToParse < lineEnd && foundGPEVariable !="")
                                            {
                                                if(foundGPEVariable!="" )
                                                {
                                                    currPosToParse+=(int)foundGPEVariable.size();
                                                }
                                                else
                                                {
                                                    currPosToParse++;
                                                }
                                                foundGPEVariable = GPE_MAIN_HIGHLIGHTER->find_gpe_variable(currStringToRender,currPosToParse);
                                            }
                                            tempParseTextToAdd->textEnd = currPosToParse;
                                            variableLineText->foundParses.push_back(tempParseTextToAdd);
                                            tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                                        }
                                        else
                                        {
                                            foundGPEKeyword = GPE_MAIN_HIGHLIGHTER->find_gpe_keyword(currStringToRender,currPosToParse);
                                            if( (foundGPEKeyword )!="")
                                            {
                                                tempParseTextToAdd->textStart = currPosToParse;
                                                while (currPosToParse < lineEnd && foundGPEKeyword !="")
                                                {
                                                    if(foundGPEKeyword!="" )
                                                    {
                                                        currPosToParse+=(int)foundGPEKeyword.size();
                                                    }
                                                    else
                                                    {
                                                        currPosToParse++;
                                                    }
                                                    foundGPEKeyword = GPE_MAIN_HIGHLIGHTER->find_gpe_keyword(currStringToRender,currPosToParse);
                                                }
                                                tempParseTextToAdd->textEnd = currPosToParse;
                                                keywordLineText->foundParses.push_back(tempParseTextToAdd);
                                                tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                                            }
                                            else if (char_is_alpha(currStringToRender[currPosToParse],false,true) )
                                            {
                                                //color = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;
                                                tempParseTextToAdd->textStart = currPosToParse;
                                                currPosToParse++;
                                                while (currPosToParse < lineEnd && char_is_alnum(currStringToRender[currPosToParse],false,true) )
                                                {
                                                    currPosToParse++;
                                                }
                                                tempParseTextToAdd->textEnd = currPosToParse;
                                                normalLineText->foundParses.push_back(tempParseTextToAdd);
                                                tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                                            }
                                            else
                                            {
                                                if(currStringToRender[currPosToParse]!=' ')
                                                {
                                                    //color = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;
                                                    //anything else is just regular text as well...
                                                    tempParseTextToAdd->textStart = currPosToParse;
                                                    tempParseTextToAdd->textEnd = currPosToParse+1;
                                                    normalLineText->foundParses.push_back(tempParseTextToAdd);
                                                }
                                                tempParseTextToAdd = new GPE_ParsedText(-1, -1);
                                                currPosToParse++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if( isInBlockCommentMode)
                {
                    endBlockCommentPos = currStringToRender.find("*/");
                    if( endBlockCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endBlockCommentPos+2;
                        isInBlockCommentMode = false;
                    }
                    mLineComment->textEnd = currPosToParse;
                    commentLineText->foundParses.push_back(mLineComment);
                    mLineComment = new GPE_ParsedText(0, -1);
                }
                else if( isInDoubleQuoteMode)
                {
                    endDQuoteCommentPos = currStringToRender.find('"',currPosToParse);
                    if( endDQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endDQuoteCommentPos+1;
                        isInDoubleQuoteMode = false;
                    }
                    dqLineComment->textEnd = currPosToParse;
                    dQuoteLineText->foundParses.push_back(dqLineComment);
                    dqLineComment = new GPE_ParsedText(0, -1);
                }
                else if( isInSingleQuoteMode)
                {
                    endSQuoteCommentPos = currStringToRender.find("'",currPosToParse);
                    if( endSQuoteCommentPos==(int)std::string::npos)
                    {
                        currPosToParse = lineEnd;
                    }
                    else
                    {
                        currPosToParse = endSQuoteCommentPos+1;
                        isInSingleQuoteMode = false;
                    }
                    sqLineComment->textEnd = currPosToParse;
                    sQuoteLineText->foundParses.push_back(sqLineComment);
                    sqLineComment = new GPE_ParsedText(0, -1);
                }
            }

            if ( i >=lineStartYPos  )
            {
                textRenderXPos = renderBox.x+lineCountBoxWidth+2;
                textRenderYPos = renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4;

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Color;
                normalLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Number_Color;
                numberLineText->render_tokens(cRender,FONT_TEXTINPUT_NUMBER,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color,true );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Symbols_Color;
                symbolLineText->render_tokens(cRender,FONT_TEXTINPUT_SYMBOL,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                //
                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Function_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Function_Color;
                }
                functionLineText->render_tokens(cRender,FONT_TEXTINPUT_FUNCTION,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                //
                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Keyword_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Keyword_Color;
                }
                keywordLineText->render_tokens(cRender,FONT_TEXTINPUT_KEYWORD,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Keyword_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Keyword_Color;
                }
                projectKeywordLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Function_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Project_Function_Color;
                }
                projectFunctionLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );



                if( USE_COLORBLINDMODE)
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Variable_Alt_Color;
                }
                else
                {
                    color = GPE_MAIN_TEMPLATE->Text_Box_Font_Variable_Color;
                }
                variableLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_DataType_Color;
                datatypeLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_DataType_Color;
                datatypeLineText->render_tokens(cRender,FONT_TEXTINPUT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_SQuote_Color;
                sQuoteLineText->render_tokens(cRender,FONT_TEXTINPUT_QUOTE,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_DQuote_Color;
                dQuoteLineText->render_tokens(cRender,FONT_TEXTINPUT_QUOTE,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );

                color = GPE_MAIN_TEMPLATE->Text_Box_Font_Comment_Color;
                commentLineText->render_tokens(cRender,FONT_TEXTINPUT_COMMENT,currStringToRender,textRenderXPos,textRenderYPos,lineStartXPos,lineStartXPos+charactersWithinView,color );
            }
        }

        if( mLineComment!=NULL)
        {
            delete mLineComment;
            mLineComment = NULL;
        }
        if( dqLineComment!=NULL)
        {
            delete dqLineComment;
            dqLineComment = NULL;
        }
        if( sqLineComment!=NULL)
        {
            delete sqLineComment;
            sqLineComment = NULL;
        }
        if( tempParseTextToAdd!=NULL)
        {
            delete tempParseTextToAdd;
            tempParseTextToAdd = NULL;
        }
    }
}

void GPE_TextAreaInputBasic::render_self(GPE_Renderer * cRender ,GPE_Rect * viewedSpace, GPE_Rect * cam,bool forceRedraw )
{
    viewedSpace = GPE_find_camera(viewedSpace);
    cam = GPE_find_camera(cam);

    if( viewedSpace!=NULL &&  cam!=NULL && textEditorButtonBar!=NULL)
    {
        int subCopyStartPos = 0;
        if( (int)listOfStrings.size()==0)
        {
            listOfStrings.push_back("");
            reset_self();
        }
        renderBox.x = barBox.x-cam->x;
        renderBox.y = barBox.y-cam->y+textEditorButtonBar->get_height();
        renderBox.w = barBox.w;

        if(showYScroll)
        {
            renderBox.w-=16;
        }
        renderBox.h = get_renderbox_height();

        int mostCharactersOfText = get_most_characters_used();
        if( mostCharactersOfText > charactersWithinView && showYScroll )
        {
            mostCharactersOfText-=2;
        }
        if( forceRedraw)
        {
            int i = 0;

            std::string currentLineInView = "";
            redrawDelay++;
            //if( redrawDelay >= redrawDelayMax)
            {
                redrawDelay = 0;
            }
            render_rectangle(cRender,barBox.x-cam->x,barBox.y-cam->y,barBox.x+barBox.w-cam->x,barBox.y+barBox.h-cam->y,GPE_MAIN_TEMPLATE->Text_Box_Color,false);

            if( has_content() )
            {
                //Calculates and highlights the symbols
                find_connected_symbols();
                if( symbolCursorXPos >= lineStartXPos && symbolCursorYPos >=lineStartYPos )
                {
                    render_rectangle(cRender,
                                     renderBox.x+lineCountBoxWidth+2+( std::min(mostCharactersOfText,symbolCursorXPos)-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                                     renderBox.y+(symbolCursorYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                     renderBox.x+lineCountBoxWidth+2+( std::min(mostCharactersOfText,symbolCursorXPos)-lineStartXPos+1)*TEXTBOX_FONT_SIZE_WIDTH,
                                     renderBox.y+(symbolCursorYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                     GPE_MAIN_TEMPLATE->Text_Box_Font_Comment_Color,false,64);
                }
                if( symbolEndCursorXPos >= lineStartXPos && symbolEndCursorYPos >=lineStartYPos )
                {
                    render_rectangle(cRender,
                                     renderBox.x+lineCountBoxWidth+2+( std::min(mostCharactersOfText,symbolEndCursorXPos)-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                                     renderBox.y+(symbolEndCursorYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                     renderBox.x+lineCountBoxWidth+2+( std::min(mostCharactersOfText,symbolEndCursorXPos)-lineStartXPos+1)*TEXTBOX_FONT_SIZE_WIDTH,
                                     renderBox.y+(symbolEndCursorYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                     GPE_MAIN_TEMPLATE->Text_Box_Font_Comment_Color,false,64);
                }

                //Renders the text highlights
                if(selectionCursorXPos!=selectionEndCursorXPos || selectionCursorYPos!=selectionEndCursorYPos)
                {
                    int minHighlightXPos = 0, maxHighlightXPos = 0;
                    int minHighlightYPos = std::min(selectionCursorYPos, selectionEndCursorYPos);
                    int maxHighlightYPos = std::max(selectionCursorYPos, selectionEndCursorYPos);

                    if( selectionCursorYPos > selectionEndCursorYPos)
                    {
                        minHighlightXPos = selectionEndCursorXPos;
                        maxHighlightXPos = selectionCursorXPos;
                    }
                    else
                    {
                        maxHighlightXPos = selectionEndCursorXPos;
                        minHighlightXPos = selectionCursorXPos;
                    }
                    if(minHighlightYPos !=maxHighlightYPos)
                    {
                        if( (int)listOfStrings.size() > minHighlightYPos && minHighlightYPos>=lineStartYPos && minHighlightYPos < lineStartYPos+linesWithinView )
                        {
                            if( (int)listOfStrings.at(minHighlightYPos).size() > lineStartXPos && ( minHighlightXPos <= lineStartXPos+charactersWithinView) )
                            {
                                render_rectangle(cRender,
                                                 renderBox.x+lineCountBoxWidth+2+std::max(0,minHighlightXPos-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                                                 renderBox.y+(minHighlightYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                                 renderBox.x+lineCountBoxWidth+2+( std::min(mostCharactersOfText,(int)listOfStrings.at(minHighlightYPos).size() )-lineStartXPos+1)*TEXTBOX_FONT_SIZE_WIDTH,
                                                 renderBox.y+(minHighlightYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                                 GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);
                            }
                            else
                            {
                                render_rectangle(cRender,
                                renderBox.x+lineCountBoxWidth+2,
                                renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                renderBox.x+lineCountBoxWidth+2+TEXTBOX_FONT_SIZE_WIDTH,
                                renderBox.y+(i-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);

                            }
                        }

                        if( maxHighlightYPos-minHighlightYPos > 1)
                        {
                            for( i = minHighlightYPos+1; i <=maxHighlightYPos-1 && i < (int)listOfStrings.size() && i <= lineStartYPos+linesWithinView; i++ )
                            {
                                if( i >=lineStartYPos  && minHighlightYPos < lineStartYPos+linesWithinView)
                                {
                                    if( (int)listOfStrings[i].size() > lineStartXPos )
                                    {
                                            render_rectangle(cRender,
                                                    renderBox.x+lineCountBoxWidth+2,
                                                    renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                                    renderBox.x+lineCountBoxWidth+2+( std::min( mostCharactersOfText,(int)listOfStrings[i].size() )-lineStartXPos )*TEXTBOX_FONT_SIZE_WIDTH,
                                                    renderBox.y+(i-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);
                                    }
                                    else
                                    {
                                        render_rectangle(cRender,
                                                    renderBox.x+lineCountBoxWidth+2,
                                                    renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                                    renderBox.x+lineCountBoxWidth+2+TEXTBOX_FONT_SIZE_WIDTH,
                                                    renderBox.y+(i-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);
                                    }
                                }
                            }
                        }

                        if( (int)listOfStrings.size() > maxHighlightYPos && maxHighlightYPos>=lineStartYPos  && maxHighlightYPos < lineStartYPos+linesWithinView )
                        {
                            std::string lastStrToHighlight = listOfStrings.at(maxHighlightYPos);
                            if( (int)lastStrToHighlight.size() > lineStartXPos && maxHighlightXPos >= lineStartXPos )
                            {
                                render_rectangle(cRender,
                                                 renderBox.x+lineCountBoxWidth+2,
                                                 renderBox.y+(maxHighlightYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                                 renderBox.x+lineCountBoxWidth+2+( std::min(mostCharactersOfText,maxHighlightXPos)-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                                                 renderBox.y+(maxHighlightYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                                 GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);
                            }
                            else
                            {
                                render_rectangle(cRender,
                                            renderBox.x+lineCountBoxWidth+2,
                                            renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                            renderBox.x+lineCountBoxWidth+2+TEXTBOX_FONT_SIZE_WIDTH,
                                            renderBox.y+(i-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);
                            }
                        }
                    }
                    else if( maxHighlightXPos >= lineStartXPos && maxHighlightYPos>=lineStartYPos && maxHighlightYPos < lineStartYPos+linesWithinView)
                    {
                        minHighlightXPos = std::min(mostCharactersOfText,minHighlightXPos);
                        maxHighlightXPos = std::min(mostCharactersOfText,maxHighlightXPos);

                        if( minHighlightXPos==maxHighlightXPos)
                        {
                            maxHighlightXPos++;
                        }
                        render_rectangle(cRender,
                                         renderBox.x+lineCountBoxWidth+2+( minHighlightXPos-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                                         renderBox.y+(maxHighlightYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                         renderBox.x+lineCountBoxWidth+2+( maxHighlightXPos-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                                         renderBox.y+(maxHighlightYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                         GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);
                    }
                }

                //Renders the texts
                std::string currStringToRender = "";
                if( MAIN_GUI_SETTINGS->showTextEditorSyntaxHightlight && isCodeEditor)
                {
                    //CSS Codes
                    if( codeEditorType==1)
                    {
                        render_code_css(cRender,viewedSpace,cam);
                    }
                    else
                    {
                        //JavaScript Codes
                        render_code_javascript(cRender,viewedSpace,cam);
                    }
                }
                else
                {
                    GPE_Color * textColor = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;
                    int foundSpecialLogPos = 0;
                    for( i=lineStartYPos; i <= lineStartYPos+linesWithinView && i < (int)listOfStrings.size(); i++)
                    {
                        currStringToRender = listOfStrings[i];
                        if( (int)currStringToRender.size() > lineStartXPos)
                        {
                            subCopyStartPos = 0;
                            if( isTextLog)
                            {
                                textColor = GPE_MAIN_TEMPLATE->Main_Box_Font_Color;;
                                foundSpecialLogPos = currStringToRender.find("Error:");
                                if( foundSpecialLogPos!=(int)std::string::npos)
                                {
                                    textColor = GPE_MAIN_TEMPLATE->Input_Error_Box_Color;
                                    subCopyStartPos =7;
                                }
                                else
                                {
                                    foundSpecialLogPos = currStringToRender.find("Warning:");
                                    if( foundSpecialLogPos!=(int)std::string::npos)
                                    {
                                        textColor = GPE_MAIN_TEMPLATE->Text_Box_Font_Keyword_Color;
                                        subCopyStartPos =8;
                                    }
                                    else
                                    {
                                        foundSpecialLogPos = currStringToRender.find("Comment:");
                                        if( foundSpecialLogPos!=(int)std::string::npos)
                                        {
                                            textColor = GPE_MAIN_TEMPLATE->Text_Box_Font_Comment_Color;
                                            subCopyStartPos =8;
                                        }
                                    }
                                }
                            }
                            currStringToRender = get_substring(currStringToRender,lineStartXPos,charactersWithinView );

                            render_new_text(cRender,renderBox.x+lineCountBoxWidth+2,renderBox.y+4+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                                            currStringToRender,textColor,FONT_TEXTINPUT,FA_LEFT,FA_TOP,255 );
                        }
                    }
                }

                //Renders the scrollbars
                if( showXScroll && textXScroll!=NULL)
                {
                    textXScroll->render_self(cRender,viewedSpace,cam);
                }
                if( showYScroll && textYScroll!=NULL)
                {
                    textYScroll->render_self(cRender,viewedSpace,cam);
                }

                //attempt to draw the cursor
                if( cursorYPos < (int) listOfStrings.size() )
                {
                    currentLineInView = listOfStrings[cursorYPos];
                }
            }

            //draws the line count box
            if( lineCountBoxWidth>0 && MAIN_GUI_SETTINGS->showTextEditorLineCount)
            {
                render_rectangle(cRender,barBox.x-cam->x,renderBox.y,barBox.x+lineCountBoxWidth-cam->x,barBox.y+barBox.h-cam->y,GPE_MAIN_TEMPLATE->Text_Box_Outer_Color,false);
                for( i=lineStartYPos; i <= lineStartYPos+linesWithinView && i < (int)listOfStrings.size(); i++)
                {
                    if( i == cursorYPos)
                    {
                        render_rectangle(cRender,renderBox.x,renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,renderBox.x+lineCountBoxWidth,renderBox.y+(i-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,GPE_MAIN_TEMPLATE->Text_Box_Highlight_Color,false);
                    }
                    render_bitmap_text(cRender,renderBox.x+lineCountBoxWidth/2,renderBox.y+(i-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,int_to_string(1+i),GPE_MAIN_TEMPLATE->Main_Box_Font_Color,FONT_TEXTINPUT,FA_CENTER,FA_TOP,255);
                }
                render_rectangle(cRender,barBox.x-cam->x,renderBox.y,barBox.x+lineCountBoxWidth-cam->x,barBox.y+barBox.h-cam->y,GPE_MAIN_TEMPLATE->Text_Box_Outline_Color,true);
            }

            render_rectangle(cRender,renderBox.x,renderBox.y,renderBox.x+renderBox.w,barBox.y+barBox.h-cam->y,GPE_MAIN_TEMPLATE->Text_Box_Outline_Color,true);
            //render_horizontal_line_color(cRender,renderBox.y+renderBox.h+GENERAL_GPE_PADDING,renderBox.x+lineCountBoxWidth,renderBox.x+renderBox.w,GPE_MAIN_TEMPLATE->Main_Border_Color);



            if( !isReadOnly )
            {
                render_rectangle(cRender,textEditorButtonBar->get_xpos()-cam->x,textEditorButtonBar->get_ypos()-cam->y,textEditorButtonBar->get_x2pos()-cam->x,textEditorButtonBar->get_y2pos()-cam->y,GPE_MAIN_TEMPLATE->Text_Box_Outer_Color,false);
                textEditorButtonBar->render_self(cRender,viewedSpace,cam);
            }
        }

        if( isInUse && (prevCursorXPos >=lineStartXPos && prevCursorXPos <= lineStartXPos+charactersWithinView) &&  ( prevCursorYPos >=lineStartYPos && prevCursorYPos <= lineStartYPos+linesWithinView ) )
        {
            if( prevCursorXPos!=cursorXPos || prevCursorYPos!=cursorYPos )
            {
                render_vertical_line_color(cRender,renderBox.x+lineCountBoxWidth+2+(prevCursorXPos-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                        renderBox.y+(prevCursorYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                        renderBox.y+(prevCursorYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                        GPE_MAIN_TEMPLATE->Text_Box_Color);
            }
        }

        //renders the cursor blinking effect
        if( isInUse && (cursorXPos >=lineStartXPos && cursorXPos <= lineStartXPos+charactersWithinView) &&  ( cursorYPos >=lineStartYPos && cursorYPos <= lineStartYPos+linesWithinView ) )
        {
            if( showCursor)
            {
                render_vertical_line_color(cRender,renderBox.x+lineCountBoxWidth+2+(cursorXPos-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                    renderBox.y+(cursorYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                    renderBox.y+(cursorYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT-GENERAL_GPE_PADDING/4,
                    GPE_MAIN_TEMPLATE->Main_Box_Font_Color);
            }
            else
            {
                render_vertical_line_color(cRender,renderBox.x+lineCountBoxWidth+2+(cursorXPos-lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH,
                        renderBox.y+(cursorYPos-lineStartYPos)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                        renderBox.y+(cursorYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT+GENERAL_GPE_PADDING/4,
                        GPE_MAIN_TEMPLATE->Text_Box_Color);
            }
        }

        if( isInUse)
        {
            render_rectangle(cRender,barBox.x-cam->x,barBox.y-cam->y,barBox.x+barBox.w-cam->x,barBox.y+barBox.h-cam->y,GPE_MAIN_TEMPLATE->Input_Highlight_Outline_Color,true);
            if( !isReadOnly)
            {
                std::string editorFeedbackLine = "Line: "+int_to_string(cursorYPos+1)+", Column: "+int_to_string(cursorXPos+1);
                if( GPE_Main_Statusbar!=NULL)
                {
                    GPE_Main_Statusbar->set_codestring(editorFeedbackLine);
                }
            }
        }

        if( forceRedraw)
        {
            cRender->reset_viewpoint();
            cRender->reset_viewpoint();
            int iRendSuggestion = 0;
            GPE_Compiler_Term * cTerm = NULL;
            std::string fullPhraseToRender = "";
            if( codeBeingSuggested && (int)suggestedCompilerTerms.size() > 0 )
            {
                int suggestionRenderYPos = barBox.y+viewedSpace->y;
                if( cursorYPos >= lineStartYPos)
                {
                    if( cursorYPos+suggestedTextMaxInViewCount <= lineStartYPos+linesWithinView && suggestedTextMaxInViewCount < linesWithinView )
                    {
                        suggestionRenderYPos +=(cursorYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT;
                        suggestionRenderYPos+=textEditorButtonBar->get_height();
                    }
                    else if( suggestedTextMaxInViewCount >= (int)suggestedCompilerTerms.size() )
                    {
                        suggestionRenderYPos += (cursorYPos-lineStartYPos-suggestedTextMaxInViewCount)*GPE_AVERAGE_LINE_HEIGHT;
                        suggestionRenderYPos+=textEditorButtonBar->get_height();
                    }
                    else
                    {
                        suggestionRenderYPos+=(cursorYPos-lineStartYPos-(int)suggestedCompilerTerms.size() )*GPE_AVERAGE_LINE_HEIGHT;
                        suggestionRenderYPos+=textEditorButtonBar->get_height();
                    }

                    int iSuggestedEntry = 0;
                    for( int iSuggestedEntry = iSuggestedStartPos;iSuggestedEntry < (int)suggestedCompilerTerms.size() && iSuggestedEntry <  iSuggestedStartPos+suggestedTextMaxInViewCount;iSuggestedEntry++ )
                    {
                        cTerm = suggestedCompilerTerms[iSuggestedEntry];
                        if( cTerm!=NULL)
                        {
                            if( cTerm->termType==CTERM_FUNCTION)
                            {
                                if( (int)cTerm->termScope.size() > 0 && cTerm->termScope!="User Global" )
                                {
                                    fullPhraseToRender = cTerm->termFunctionReturnType+" "+cTerm->termScope+"."+cTerm->termString+"("+cTerm->get_parameters()+")";
                                }
                                else
                                {
                                    fullPhraseToRender = cTerm->termFunctionReturnType+" "+cTerm->termString+"("+cTerm->get_parameters()+")";
                                }
                            }
                            else if( (int)cTerm->termScope.size() > 0 && cTerm->termScope!="User Global" )
                            {
                                fullPhraseToRender = cTerm->termScope+"."+cTerm->termString;
                            }
                            else
                            {
                                fullPhraseToRender = cTerm->termString;
                            }
                            if( iSuggestedEntry==iSuggestionPos)
                            {
                                render_rectangle(cRender, barBox.x+viewedSpace->x, suggestionRenderYPos+GPE_AVERAGE_LINE_HEIGHT*iRendSuggestion,barBox.x+viewedSpace->x+maxSuggestedTextWidth, suggestionRenderYPos+GPE_AVERAGE_LINE_HEIGHT*(iRendSuggestion+1),GPE_MAIN_TEMPLATE->PopUp_Box_Highlight_Color,false);
                                render_new_text(cRender,barBox.x+viewedSpace->x+32, suggestionRenderYPos+GPE_AVERAGE_LINE_HEIGHT*iRendSuggestion,fullPhraseToRender,GPE_MAIN_TEMPLATE->PopUp_Box_Highlight_Font_Color,FONT_TEXTINPUT,FA_LEFT,FA_TOP,255 );
                            }
                            else
                            {
                                render_rectangle(cRender, barBox.x+viewedSpace->x, suggestionRenderYPos+GPE_AVERAGE_LINE_HEIGHT*iRendSuggestion,barBox.x+viewedSpace->x+maxSuggestedTextWidth, suggestionRenderYPos+GPE_AVERAGE_LINE_HEIGHT*(iRendSuggestion+1),GPE_MAIN_TEMPLATE->PopUp_Box_Color,false);
                                render_new_text(cRender,barBox.x+viewedSpace->x+32, suggestionRenderYPos+GPE_AVERAGE_LINE_HEIGHT*iRendSuggestion,fullPhraseToRender,GPE_MAIN_TEMPLATE->PopUp_Box_Font_Color,FONT_TEXTINPUT,FA_LEFT,FA_TOP,255 );
                            }
                            iRendSuggestion++;
                        }
                    }
                    render_rectangle(cRender, barBox.x+viewedSpace->x, suggestionRenderYPos,barBox.x+viewedSpace->x+maxSuggestedTextWidth, suggestionRenderYPos+GPE_AVERAGE_LINE_HEIGHT*(iRendSuggestion+1),GPE_MAIN_TEMPLATE->PopUp_Box_Border_Color,true);

                }
                else
                {
                    codeBeingSuggested = false;
                    suggestedCompilerTerms.clear();
                }
            }
            else if( isCodeEditor && GPE_MAIN_HIGHLIGHTER->highlightedTerm!=NULL && highlightYPos >=lineStartYPos && highlightYPos <= lineStartYPos+linesWithinView+3 )
            {
                std::string fullTermDescription = "";
                //GPE_MAIN_HIGHLIGHTER->highlightedTerm = highlightedTerm;

                GPE_MAIN_HIGHLIGHTER->highlightedTermXPos = renderBox.x+viewedSpace->x+lineCountBoxWidth+( (highlightXPos -lineStartXPos)*TEXTBOX_FONT_SIZE_WIDTH);
                int suggestionRenderYPos = 0;

                if( highlightYPos > lineStartYPos+1)
                {
                    if( highlightYPos+3 <= lineStartYPos+linesWithinView)
                    {
                        suggestionRenderYPos = (highlightYPos-lineStartYPos+1)*GPE_AVERAGE_LINE_HEIGHT;
                    }
                    else
                    {
                        suggestionRenderYPos = (highlightYPos-lineStartYPos-4 )*GPE_AVERAGE_LINE_HEIGHT;
                    }
                }
                else
                {
                    suggestionRenderYPos=(highlightYPos-lineStartYPos+3)*GPE_AVERAGE_LINE_HEIGHT;
                }
                GPE_MAIN_HIGHLIGHTER->highlightedTermYPos = renderBox.y+viewedSpace->y+suggestionRenderYPos;
            }
            cRender->set_viewpoint( viewedSpace );
        }
    }
}

int GPE_TextAreaInputBasic::replace_all_found(std::string strToReplace, std::string newString)
{
    GPE_TextAnchor * cAnchor = NULL;
    std::string tempLine = "";
    std::string changedLine = "";
    int copiesDeleted = 0;
    export_text_anchors(APP_DIRECTORY_NAME+"replace_test.txt");
    for( int iReplace = (int)anchorPositions.size()-1; iReplace >=0;iReplace--)
    {
        cAnchor = anchorPositions.at( iReplace);
        if( cAnchor!=NULL)
        {
            if( (int)listOfStrings.size() > cAnchor->lineNumber )
            {
                tempLine = listOfStrings.at( cAnchor->lineNumber);
                if( (int)tempLine.size() >= cAnchor->characterNumber+(int)strToReplace.size() )
                {
                    changedLine = tempLine.substr(0,cAnchor->characterNumber)+newString+tempLine.substr(cAnchor->characterNumber+(int)strToReplace.size() );
                    listOfStrings[cAnchor->lineNumber] = changedLine;
                    copiesDeleted++;
                }
            }
        }
    }
    showCursor = true;
    cursorTimer = 0;
    return copiesDeleted;
}

void GPE_TextAreaInputBasic::reset_selection(int resetDirection)
{
    if( resetDirection < 0)
    {
        if(selectionCursorXPos!=selectionEndCursorXPos  || selectionCursorYPos!=selectionEndCursorYPos )
        {
            if( selectionCursorYPos==selectionEndCursorYPos)
            {
                cursorXPos = std::min(selectionCursorXPos, selectionEndCursorXPos);
                cursorYPos = selectionCursorYPos;
            }
            else if( selectionCursorYPos > selectionEndCursorYPos)
            {
                cursorXPos = selectionEndCursorXPos;
                cursorYPos = selectionEndCursorYPos;
            }
            else
            {
                cursorXPos = selectionCursorXPos;
                cursorYPos = selectionCursorYPos;
            }
        }

    }
    if(  resetDirection > 0)
    {
        if(selectionCursorXPos!=selectionEndCursorXPos  || selectionCursorYPos!=selectionEndCursorYPos )
        {
            if( selectionCursorYPos==selectionEndCursorYPos)
            {
                cursorXPos = std::max(selectionCursorXPos, selectionEndCursorXPos);
                cursorYPos = selectionCursorYPos;
            }
            else if( selectionCursorYPos > selectionEndCursorYPos)
            {
                cursorXPos = selectionCursorXPos;
                cursorYPos = selectionCursorYPos;
            }
            else
            {
                cursorXPos = selectionEndCursorXPos;
                cursorYPos = selectionEndCursorYPos;
            }
        }
    }
    selectionCursorXPos = 0;
    selectionCursorYPos = 0;
    selectionEndCursorXPos = 0;
    selectionEndCursorYPos = 0;
    if( listOfStrings.size() <=0)
    {
        listOfStrings.push_back("");
        cursorXPos = 0;
        cursorYPos = 0;
    }
    if( cursorYPos >= (int)listOfStrings.size() )
    {

        cursorYPos= (int)listOfStrings.size() - 1;
        lineToEdit = listOfStrings[cursorYPos];
        cursorXPos = (int)lineToEdit.size();
    }
    else if( cursorXPos > (int)listOfStrings[cursorYPos].size() )
    {
        cursorXPos = (int)listOfStrings[cursorYPos].size();
    }
    showCursor = true;
    cursorTimer = 0;
}

void GPE_TextAreaInputBasic::reset_self()
{
    cursorXPos = 0;
    cursorYPos = 0;
    selectionCursorXPos = 0;
    selectionCursorYPos = 0;
    selectionEndCursorXPos = 0;
    selectionEndCursorYPos = 0;
    bscDelay = 0;
    delDelay = 0;
    enterDelay = 0;
    upDelay = 0;
    downDelay = 0;
    leftDelay = 0;
    rightDelay = 0;
    tabDelay=0;
    showCursor = true;
    cursorTimer = 0;
}

void GPE_TextAreaInputBasic::revise_edit(int editId)
{
    if( editId >=0 && editId < (int)savedHistory.size() )
    {
        GPE_TextAreaInputBasic * tempPlace = savedHistory.at(editId);
        if( tempPlace!=NULL)
        {
            save_edit();
            copy_source(tempPlace,true);
        }
    }
}

void GPE_TextAreaInputBasic::save_edit()
{
    bool currentContentChanged = true;
    bool prevContentChanged = true;
    bool nextContentChanged = true;
    GPE_TextAreaInputBasic * fTextArea = NULL;
    if( currentPositionInHistory > 0 && (int)savedHistory.size() > currentPositionInHistory-1 )
    {
        fTextArea = savedHistory.at(currentPositionInHistory-1);
        if( fTextArea!=NULL)
        {
            if( compare_with(fTextArea)==1)
            {
                prevContentChanged = false;
            }
        }
    }

    if( currentPositionInHistory >= 0 && (int)savedHistory.size() > currentPositionInHistory )
    {
        fTextArea = savedHistory.at(currentPositionInHistory);
        if( fTextArea!=NULL)
        {
            if( compare_with(fTextArea)==1)
            {
                currentContentChanged = false;
            }
        }
    }

    if( currentPositionInHistory >= 0 && (int)savedHistory.size() > currentPositionInHistory+1 )
    {
        fTextArea = savedHistory.at(currentPositionInHistory+1);
        if( fTextArea!=NULL)
        {
            if( compare_with(fTextArea)==1)
            {
                nextContentChanged = false;
            }
        }
    }

    if( currentContentChanged && prevContentChanged && nextContentChanged)
    {
        //int prevSavePos = currentPositionInHistory;
        if( (int)savedHistory.size() >= 128 )
        {
            if( currentPositionInHistory < 32)
            {
                //remove from right
                savedHistory.erase(savedHistory.end());
            }
            else if( currentPositionInHistory > 96)
            {
                //remove from left
                savedHistory.erase(savedHistory.begin());
                currentPositionInHistory--;
            }
            else
            {
                if( currentPositionInHistory>=64)
                {
                    savedHistory.erase(savedHistory.begin());
                    currentPositionInHistory--;
                }
                else
                {
                    savedHistory.erase(savedHistory.end());
                }
            }
        }

        GPE_TextAreaInputBasic * savedText = new GPE_TextAreaInputBasic(false);
        savedText->copy_source(this,true);
        if( currentPositionInHistory >=0 && currentPositionInHistory < (int)savedHistory.size() )
        {
            savedHistory.insert(savedHistory.begin()+currentPositionInHistory+1,savedText);
            currentPositionInHistory++;
        }
        else
        {
            savedHistory.push_back(savedText);
            currentPositionInHistory = savedHistory.size()-1;
        }
    }
    undoableActionOccurred = false;
}

void GPE_TextAreaInputBasic::select_all()
{
    cursorXPos = 0;
    cursorYPos = 0;
    selectionCursorXPos = 0;
    selectionCursorYPos = 0;
    selectionEndCursorXPos = 0;
    selectionEndCursorYPos = 0;
    int listSize = (int)listOfStrings.size() ;
    if( listSize > 0)
    {
        std::string tempStr = listOfStrings.back();
        selectionEndCursorYPos = listSize - 1;
        if( (int)tempStr.size() > 0)
        {
            selectionEndCursorXPos = tempStr.size();
        }
    }
    showCursor = true;
    cursorTimer = 0;
}

void GPE_TextAreaInputBasic::scroll_to_pos(int lineNumberIn, int characterNumberIn)
{
    if( showYScroll )
    {
        showYScroll = true;
        lineStartYPos = lineNumberIn;
        if( lineStartYPos+linesWithinView >= (int)listOfStrings.size() )
        {
            lineStartYPos =  (int)listOfStrings.size() - linesWithinView;
        }
        if( lineStartYPos < 0)
        {
            lineStartYPos = 0;
        }

    }
    if( showXScroll )
    {
        if( characterNumberIn > lineStartXPos+charactersWithinView)
        {
            lineStartXPos = characterNumberIn-charactersWithinView;
        }
        else if( characterNumberIn < lineStartXPos )
        {
            lineStartXPos = characterNumberIn;
        }

        if( lineStartXPos+charactersWithinView > get_most_characters_used() )
        {
            lineStartXPos =  get_most_characters_used() - charactersWithinView;
        }
        if( lineStartXPos < 0)
        {
            lineStartXPos = 0;
        }
    }
    else
    {
        lineStartXPos = 0;
    }
    showCursor = true;
    cursorTimer = 0;
}

void GPE_TextAreaInputBasic::scroll_to_cursor()
{
    if( cursorYPos >= lineStartYPos && cursorYPos <= lineStartYPos+linesWithinView && cursorYPos < (int)listOfStrings.size() )
    {
        if( cursorXPos < lineStartXPos || cursorXPos > lineStartXPos+charactersWithinView)
        {
            scroll_to_pos(lineStartYPos,cursorXPos);
        }
        else
        {
            scroll_to_pos(lineStartYPos, lineStartXPos);
        }
    }
    else
    {
        if( cursorXPos < lineStartXPos ||  cursorXPos > lineStartXPos+charactersWithinView)
        {
            scroll_to_pos(cursorYPos,cursorXPos);
        }
        else
        {
            scroll_to_pos(cursorYPos, lineStartXPos);
        }
    }
}

void GPE_TextAreaInputBasic::scroll_to_selection()
{
    scroll_to_pos( selectionCursorYPos, selectionCursorXPos);
}

void GPE_TextAreaInputBasic::set_read_only()
{
    isReadOnly = true;
    textEditorButtonBar->set_height(0);
}

void GPE_TextAreaInputBasic::set_writeable()
{
    isReadOnly = true;
    textEditorButtonBar->set_height(32);
}

void GPE_TextAreaInputBasic::set_string(std::string newString)
{

}

void GPE_TextAreaInputBasic::set_placeholder(std::string newString)
{

}

void GPE_TextAreaInputBasic::set_xcursor(int newPos)
{
    cursorXPos = newPos;
    std::string cLine = listOfStrings[cursorYPos];
    if( cursorXPos < 0 || cursorXPos < (int)cLine.size() )
    {
        cursorXPos = 0;
    }
    showCursor = true;
    cursorTimer = 0;
}

void GPE_TextAreaInputBasic::set_ycursor(int newPos)
{
    if( newPos >=0 && newPos < (int)listOfStrings.size() )
    {
        cursorYPos = newPos;
        std::string cLine = listOfStrings.at(newPos);
        if( cursorXPos < 0 || cursorXPos < (int)cLine.size() )
        {
            cursorXPos = 0;
        }
    }
    else
    {
        cursorYPos = 0;
        cursorXPos = 0;
    }
    showCursor = true;
    cursorTimer = 0;
}

void GPE_TextAreaInputBasic::undo_edit()
{
    if( can_undo() )
    {
        int editId = currentPositionInHistory;
        /*
        if( undoableActionOccurred)
        {
            save_edit();
        }
        if( currentPositionInHistory > editId)
        {
            currentPositionInHistory--;
        }
        */
        GPE_TextAreaInputBasic * tempPlace = NULL;
        if( currentPositionInHistory-1 >=0 && currentPositionInHistory-1 < (int)savedHistory.size() )
        {
            tempPlace = savedHistory.at(currentPositionInHistory-1);
            if( tempPlace!=NULL)
            {
                copy_source(tempPlace,true);
                currentPositionInHistory--;
            }
        }
        else if( editId==(int)savedHistory.size() && (int)savedHistory.size()>0)
        {
            save_edit();
        }
        showCursor = true;
        cursorTimer = 0;
    }
}

void GPE_TextAreaInputBasic::update_cursor_to_mouse(GPE_Rect * viewedSpace, GPE_Rect * cam )
{
    viewedSpace = GPE_find_camera(viewedSpace);
    cam = GPE_find_camera(cam);
    find_mouse_cursor(&cursorXPos, &cursorYPos, viewedSpace, cam);
    lineToEdit = listOfStrings[cursorYPos];
    showCursor = true;
    cursorTimer = 0;
    adjust_fortabs();
}

bool GPE_TextAreaInputBasic::write_data_into_file(std::ofstream * fileTarget, int leftTabAmount, bool useNewLines, bool useLastNewLine )
{
    if( fileTarget!=NULL && leftTabAmount >=0)
    {
        std::string nestedTabsStr = generate_tabs( leftTabAmount  );
        if( fileTarget->is_open() )
        {
            int strSize = (int)listOfStrings.size();

            for( int i = 0; i < strSize-1; i++)
            {
                if( useNewLines)
                {
                    *fileTarget << nestedTabsStr+listOfStrings[i] << "\n";
                }
                else
                {
                    *fileTarget <<nestedTabsStr+listOfStrings[i] << " ";
                }
            }
            if( useNewLines)
            {
                if( useLastNewLine)
                {
                    *fileTarget << nestedTabsStr+listOfStrings[strSize-1] << "\n";
                }
                else
                {
                    *fileTarget << nestedTabsStr+listOfStrings[strSize-1];
                }
            }
            else
            {
                *fileTarget <<nestedTabsStr+listOfStrings[strSize-1] << " ";
            }
            return true;
        }
    }
    return false;
}

bool GPE_TextAreaInputBasic::write_short_data_into_file(std::ofstream * fileTarget, int leftTabAmount, bool useNewLines, bool useLastNewLine )
{
    if( fileTarget!=NULL && leftTabAmount >=0)
    {
        std::string nestedTabsStr = generate_tabs( leftTabAmount  );
        if( fileTarget->is_open() )
        {
            int strSize = (int)listOfStrings.size();
            std::string currentLineToExport = "";
            for( int i = 0; i < strSize-1; i++)
            {
                currentLineToExport= listOfStrings[i];
                if( (int)currentLineToExport.size() > 0)
                {
                    if( useNewLines)
                    {
                        *fileTarget << nestedTabsStr+currentLineToExport << "\n";
                    }
                    else
                    {
                        *fileTarget <<nestedTabsStr+currentLineToExport << " ";
                    }
                }
            }
            if( useNewLines)
            {
                if( useLastNewLine)
                {
                    *fileTarget << nestedTabsStr+listOfStrings[strSize-1] << "\n";
                }
                else
                {
                    *fileTarget << nestedTabsStr+listOfStrings[strSize-1];
                }
            }
            else
            {
                *fileTarget <<nestedTabsStr+listOfStrings[strSize-1] << " ";
            }
            return true;
        }
    }
    return false;
}

GPE_WrappedTextArea::GPE_WrappedTextArea()
{
    guiListTypeName = "wrappedtextarea";
    heldTextArea = new GPE_TextAreaInputBasic();
    heldTextArea->set_read_only();
    heldTextArea->isCodeEditor = false;
    barBox.w = 640;
    barBox.h = 480;
    paragraphText = "";
    hasLineBreak = true;
}

GPE_WrappedTextArea::~GPE_WrappedTextArea()
{
    if( heldTextArea!=NULL)
    {
        delete heldTextArea;
        heldTextArea = NULL;
    }
}

void GPE_WrappedTextArea::process_self(GPE_Rect * viewedSpace, GPE_Rect * cam )
{
    heldTextArea->set_coords(barBox.x,barBox.y);
    heldTextArea->process_self(viewedSpace,cam);
}

void GPE_WrappedTextArea::render_self(GPE_Renderer * cRender,GPE_Rect * viewedSpace, GPE_Rect *cam, bool forceRedraw )
{
    heldTextArea->set_coords(barBox.x,barBox.y);
    heldTextArea->render_self(cRender,viewedSpace,cam, forceRedraw);
}

void GPE_WrappedTextArea::set_string( std::string strIn)
{
    if( paragraphText!=strIn)
    {
        paragraphText = strIn;
        update_paragraph();
    }
}

void GPE_WrappedTextArea::set_width(int newWidth)
{
    if( barBox.w!=newWidth)
    {
        barBox.w = newWidth;
        heldTextArea->set_width( barBox.w );
        update_paragraph();
    }
}

void GPE_WrappedTextArea::set_height( int newHeight)
{
    if( barBox.h!=newHeight)
    {
        barBox.h = newHeight;
        heldTextArea->set_height( barBox.h );
        update_paragraph();
    }
}

void GPE_WrappedTextArea::set_max_width( int nMW)
{
    if( barBox.w!=nMW )
    {
        barBox.w = nMW;
        heldTextArea->set_width( barBox.w );
        update_paragraph();
    }
}

void GPE_WrappedTextArea::set_max_height( int nMH)
{
    if( barBox.h!=nMH )
    {
        barBox.h = nMH;
        heldTextArea->set_height( barBox.h );
        update_paragraph();
    }
}

void GPE_WrappedTextArea::update_paragraph(int foundMaxWidth )
{
    if( heldTextArea!=NULL && barBox.w > 0 )
    {
        heldTextArea->reset_self();
        heldTextArea->clear_all_lines();
        if( (int)paragraphText.size() > 0)
        {
            int maxMessageWidth = 0;
            //int maxMessageHeight = 0;
            int defaultFontWidth = 0;;
            int defaultFontHeight = 0;
            int iSubMessage = 0;
            if( FONT_TEXTINPUT!=NULL)
            {
                FONT_TEXTINPUT->get_metrics("A",&defaultFontWidth, &defaultFontHeight);
                FONT_TEXTINPUT->clear_cache();
            }

            std::vector < std::string > messageSubTitles;

            if( defaultFontWidth > 0 && defaultFontHeight > 0)
            {
                maxMessageWidth = ( barBox.w -GENERAL_GPE_PADDING)/ defaultFontWidth;

                if( (int)paragraphText.size() > 0)
                {
                    wrap_string(paragraphText,messageSubTitles,maxMessageWidth,-1);
                }

                maxMessageWidth = 0;
                if( messageSubTitles.size() <= 0)
                {
                    heldTextArea->add_line("");
                }
                else
                {
                    for( iSubMessage = 0; iSubMessage < (int)messageSubTitles.size(); iSubMessage++)
                    {
                        heldTextArea->add_line( messageSubTitles.at(iSubMessage) );
                    }
                }
            }
        }
        else
        {
            heldTextArea->add_line("");
        }
    }
}
