/**
 * Basic header/include file for PromptOverlay.cpp.
 *
 * @author GabuEx, dawnmew
 * @since 1.0
 *
 * Licensed under the MIT License.
 *
 * Copyright (c) 2014 Equestrian Dreamers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PROMPTOVERLAY_H
#define PROMPTOVERLAY_H

#include "../EasingFunctions.h"
#include "../LocalizableContent.h"
#include "../MLIFont.h"
#include "../Vector2.h"
#include <deque>

using namespace std;

class PromptButton : public ILocalizableTextOwner
{
public:
    static void Initialize(MLIFont *pTextFont);

    PromptButton(Vector2 position, const string &textId)
    {
        this->position = position;
        this->textId = textId;

        this->isMouseOver = false;
        this->isMouseDown = false;
        this->isClicked = false;
        this->isEnabled = true;

        ReloadLocalizableText();
    }

    virtual ~PromptButton() {}

    bool GetIsClicked() { return this->isClicked; }
    string GetText() { return this->text; }

    void SetIsEnabled(bool isEnabled)
    {
        this->isEnabled = isEnabled;

        if (!isEnabled)
        {
            this->isMouseOver = false;
            this->isMouseDown = false;
            this->isClicked = false;
        }
    }

    static string GetClickSoundEffect() { return "ButtonClick3"; }

    void Update(int delta);
    void Draw(double opacity);
    void Reset();

    void ReloadLocalizableText() override;

private:
    static MLIFont *pTextFont;

    Vector2 position;
    string textId;
    string text;

    bool isMouseOver;
    bool isMouseDown;
    bool isClicked;
    bool isEnabled;
};

class PromptOverlay : public ILocalizableTextOwner
{
public:
    static void Initialize(MLIFont *pTextFont, MLIFont *pTextEntryFont, Image *pDarkeningImage);

    PromptOverlay(const string &headerTextId, bool allowsTextEntry);
    virtual ~PromptOverlay();

    bool GetIsShowing() { return this->isShowing; }

    void SetHeaderTextId(const string &headerTextId);
    void SetHeaderText(const string &headerText);

    void AddButton(const string &textId);
    void FinalizeButtons();

    void Begin(const string &initialText = "");
    void Update(int delta);
    void Draw();
    void Reset();

    void SetMaxPixelWidth(int pixelWidth, MLIFont *pFontToCheckAgainst) { this->maxPixelWidth = pixelWidth; this->pFontToCheckAgainst = pFontToCheckAgainst; }
    void KeepOpen();

    void ReloadLocalizableText() override;

private:
    static MLIFont *pTextFont;
    static MLIFont *pTextEntryFont;
    static Image *pDarkeningImage;

    string headerTextId;
    string headerText;
    deque<string> headerTextLines;

    bool allowsTextEntry;
    string textEntered;
    vector<string> buttonTextIdList;
    vector<string> finalizedButtonTextIdList;
    vector<PromptButton *> buttonList;

    EasingFunction *pFadeInEase;
    EasingFunction *pFadeOutEase;

    double fadeOpacity;
    bool isShowing;

    int maxPixelWidth;
    MLIFont *pFontToCheckAgainst;

    double yOffset;
};

#endif
