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

#include "CocoControlButton.h"

NS_CC_EXT_BEGIN

CocoControlButton::CocoControlButton():
m_pNormalBackGround(NULL),
m_pPressedBackGround(NULL),
m_pDisabledBackGround(NULL),
m_pNormalTitle(NULL),
m_pPressedTitle(NULL),
m_pDisabledTitle(NULL),
m_bZoomOnTouchDown(true)
{
    
}

CocoControlButton::~CocoControlButton()
{
    
}

CocoControlButton* CocoControlButton::create()
{
    CocoControlButton* widget = new CocoControlButton();
    if (widget && widget->init()) {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool CocoControlButton::init()
{
    if (CocoWidget::init())
    {
        this->m_pCCRenderNode->addChild(this->m_pNormalBackGround);
        this->m_pCCRenderNode->addChild(this->m_pPressedBackGround);
        this->m_pCCRenderNode->addChild(this->m_pDisabledBackGround);
        this->m_pCCRenderNode->addChild(this->m_pNormalTitle);
        this->m_pCCRenderNode->addChild(this->m_pPressedTitle);
        this->m_pCCRenderNode->addChild(this->m_pDisabledTitle);
        this->setPressState(WidgetStateNormal);
        return true;
    }
    return false;
}

void CocoControlButton::initNodes()
{
    CocoWidget::initNodes();
    this->m_pNormalTitle = cocos2d::CCLabelTTF::create();
    this->m_pPressedTitle = cocos2d::CCLabelTTF::create();
    this->m_pDisabledTitle = cocos2d::CCLabelTTF::create();

    this->m_pNormalBackGround = cocos2d::extension::CCScale9Sprite::create();
    this->m_pPressedBackGround = cocos2d::extension::CCScale9Sprite::create();
    this->m_pDisabledBackGround = cocos2d::extension::CCScale9Sprite::create();
}

void CocoControlButton::setTextures(const char* backgroundNormal,const char* backgroundPressed,const char* backgroundDisabled)
{
    this->m_pNormalBackGround->initWithFile(backgroundNormal);
    this->m_pPressedBackGround->initWithFile(backgroundPressed);
    this->m_pDisabledBackGround->initWithFile(backgroundDisabled);
    
    m_pNormalBackGround->setContentSize(cocos2d::CCSize(this->m_pNormalTitle->boundingBox().size.width+8*2,this->m_pNormalTitle->boundingBox().size.height+2*2));
    m_pPressedBackGround->setContentSize(cocos2d::CCSize(this->m_pPressedTitle->boundingBox().size.width+8*2,this->m_pPressedTitle->boundingBox().size.height+2*2));
    m_pDisabledBackGround->setContentSize(cocos2d::CCSize(this->m_pDisabledTitle->boundingBox().size.width+8*2,this->m_pDisabledTitle->boundingBox().size.height+2*2));
}

void CocoControlButton::setTitle(const char* titleNormal,const char* titlePressed,const char* titleDisabled)
{
    this->m_pNormalTitle->setString(titleNormal);
    this->m_pPressedTitle->setString(titlePressed);
    this->m_pDisabledTitle->setString(titleDisabled);
    
    m_pNormalBackGround->setContentSize(cocos2d::CCSize(this->m_pNormalTitle->boundingBox().size.width+8*2,this->m_pNormalTitle->boundingBox().size.height+2*2));
    m_pPressedBackGround->setContentSize(cocos2d::CCSize(this->m_pPressedTitle->boundingBox().size.width+8*2,this->m_pPressedTitle->boundingBox().size.height+2*2));
    m_pDisabledBackGround->setContentSize(cocos2d::CCSize(this->m_pDisabledTitle->boundingBox().size.width+8*2,this->m_pDisabledTitle->boundingBox().size.height+2*2));
}

void CocoControlButton::onPressStateChangedToNormal()
{
    if (!m_bZoomOnTouchDown)
    {
        return;
    }
    cocos2d::CCAction *zoomAction = cocos2d::CCScaleTo::create(0.05f, 1.0f);
    runAction(zoomAction);
}

void CocoControlButton::onPressStateChangedToPressed()
{
    if (!m_bZoomOnTouchDown)
    {
        return;
    }
    cocos2d::CCAction *zoomAction = cocos2d::CCScaleTo::create(0.05f, 1.1f);
    runAction(zoomAction);
}

void CocoControlButton::onPressStateChangedToDisabled()
{
    
}

cocos2d::CCNode* CocoControlButton::getValidNode()
{
    cocos2d::CCNode* validNode = NULL;
    switch (this->m_nCurPressState)
    {
        case WidgetStateNormal:
            validNode = m_pNormalBackGround;
            break;
        case WidgetStateSelected:
            validNode = m_pPressedBackGround;
            break;
        case WidgetStateDisabled:
            validNode = m_pDisabledBackGround;
            break;
        default:
            break;
    }
    return validNode;
}

void CocoControlButton::setAnchorPoint(const cocos2d::CCPoint &pt)
{
    CocoWidget::setAnchorPoint(pt);
    m_pNormalBackGround->setAnchorPoint(pt);
    m_pPressedBackGround->setAnchorPoint(pt);
    m_pDisabledBackGround->setAnchorPoint(pt);
}

void CocoControlButton::setColor(int r,int g,int b)
{
    
}

void CocoControlButton::setOpacity(int opcity)
{
    
}

void CocoControlButton::setFlipX(bool flipX)
{
    
}

void CocoControlButton::setFlipY(bool flipY)
{
    
}

void CocoControlButton::setNormalTitle(const char *title)
{
    m_pNormalTitle->setString(title);
}

void CocoControlButton::setPressedTitle(const char *title)
{
    m_pPressedTitle->setString(title);
}

void CocoControlButton::setDisabledTitle(const char *title)
{
    m_pDisabledTitle->setString(title);
}

void CocoControlButton::setNormalFontName(const char *name)
{
    m_pNormalTitle->setFontName(name);
}

void CocoControlButton::setPressedFontName(const char *name)
{
    m_pPressedTitle->setFontName(name);
}

void CocoControlButton::setDisabledFontName(const char *name)
{
    m_pDisabledTitle->setFontName(name);
}

void CocoControlButton::setNormalFontSize(float size)
{
    m_pNormalTitle->setFontSize(size);
}

void CocoControlButton::setPressedFontSize(float size)
{
    m_pPressedTitle->setFontSize(size);
}

void CocoControlButton::setDisabledFontSize(float size)
{
    m_pDisabledTitle->setFontSize(size);
}

void CocoControlButton::setNormalFontColor(const cocos2d::ccColor3B &color)
{
    m_pNormalTitle->setColor(color);
}

void CocoControlButton::setPressedFontColor(const cocos2d::ccColor3B &color)
{
    m_pPressedTitle->setColor(color);
}

void CocoControlButton::setDisalbedFontColor(const cocos2d::ccColor3B &color)
{
    m_pDisabledTitle->setColor(color);
}

void CocoControlButton::setLabelAnchorPoint(const cocos2d::CCPoint &labelAnchorPoint)
{
    m_pNormalTitle->setAnchorPoint(labelAnchorPoint);
    m_pPressedTitle->setAnchorPoint(labelAnchorPoint);
    m_pDisabledTitle->setAnchorPoint(labelAnchorPoint);
}

void CocoControlButton::setPreferredSize(const cocos2d::CCSize &size)
{
    m_pNormalBackGround->setPreferredSize(size);
    m_pPressedBackGround->setPreferredSize(size);
    m_pDisabledBackGround->setPreferredSize(size);
}

void CocoControlButton::setNormalBackgroundSpriteFrame(cocos2d::CCSpriteFrame *spriteFrame)
{
    m_pNormalBackGround->setSpriteFrame(spriteFrame);
}

void CocoControlButton::setPressedBackgroundSpriteFrame(cocos2d::CCSpriteFrame *spriteFrame)
{
    m_pPressedBackGround->setSpriteFrame(spriteFrame);
}

void CocoControlButton::setDisabledBackgroundSpriteFrame(cocos2d::CCSpriteFrame *spriteFrame)
{
    m_pDisabledBackGround->setSpriteFrame(spriteFrame);
}

NS_CC_EXT_END

