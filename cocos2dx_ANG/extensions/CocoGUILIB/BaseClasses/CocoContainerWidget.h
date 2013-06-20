/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CCCONTAINERWIDGET_H__
#define __CCCONTAINERWIDGET_H__

#include "CocoWidget.h"

NS_CC_EXT_BEGIN
    
typedef enum
{
    RENDER_TYPE_LAYERCOLOR,
    RENDER_TYPE_LAYERGRADIENT
}RenderType;


class CocoContainerWidget : public CocoWidget
{
public:
    CocoContainerWidget();
    virtual ~CocoContainerWidget();
    static CocoContainerWidget* create();
    //Only containerWidget can use the LayoutParameter for doing layout to child widget
    virtual void setLayoutParameter(/*LayoutParameter * parmeter*/);
    virtual bool init();
    virtual void initNodes();
    virtual bool addChild(CocoWidget* child);
    virtual void setClipAble(bool able);
    virtual void setClipRect(const cocos2d::CCRect &rect);
    virtual void updateWidth();
    virtual void updateHeight();
    virtual void setSize(const cocos2d::CCSize &size);
    virtual void setWidth(float width);
    virtual float getWidth();
    virtual void setHeight(float height);
    virtual float getHeight();
    virtual bool getClipAble();
    virtual bool hitTest(cocos2d::CCNode*node, cocos2d::CCPoint &pt);
    virtual void updateClipSize();
    virtual void onScaleDirtyChanged();
    virtual void onScaleXDirtyChanged();
    virtual void onScaleYDirtyChanged();        
protected:
    float m_fWidth;
    float m_fHeight;
    bool m_bClipAble;
    RenderType m_renderType;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__CocoContainerWidget__) */
