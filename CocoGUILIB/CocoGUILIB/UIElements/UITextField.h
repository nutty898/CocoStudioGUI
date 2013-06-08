/*
 * Copyright (c) 2012 Chukong Technologies, Inc.
 *
 * http://www.sweetpome.com
 * http://tools.cocoachina.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __CocoGUI__UITextField__
#define __CocoGUI__UITextField__

#include "UIElement.h"

namespace cs {
    class UITextField : public UIElement
    {
    public:
        UITextField();
        virtual ~UITextField();
        virtual void init();
        void openIME();
        void closeIME();
        void setPlaceHolder(const char* value);
        void setStringValue(const char* value);
        void setSize(float width,float height);
        void setTextColor(int r,int g,int b);
        void setFontSize(int size);
        const char* getStringValue();
        void setCharacterLength(int length);
        void setIsPassWord(bool isPassword);
        
        bool getAttachWithIME();
        void setAttachWithIME(bool attach);
        bool getDetachWithIME();
        void setDetachWithIME(bool detach);
        bool getInsertText();
        void setInsertText(bool insertText);
        bool getDeleteBackward();
        void setDeleteBackward(bool deleteBackward);
    protected:
    };
}

#endif /* defined(__CocoGUI__UITextField__) */