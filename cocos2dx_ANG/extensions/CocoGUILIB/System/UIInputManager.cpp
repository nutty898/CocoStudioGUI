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

#include "UIInputManager.h"
#include "UISystem.h"

NS_CC_EXT_BEGIN

UIInputManager::UIInputManager():
m_manageredWidget(NULL),
m_pCurSelectedWidget(NULL),
m_bWidgetBeSorted(false),
m_bTouchDown(false),
m_fLongClickTime(0.0),
m_fLongClickRecordTime(0.0),
checkedDoubleClickWidget(NULL)
{
    this->m_manageredWidget = cocos2d::CCArray::create();
    this->m_manageredWidget->retain();
    this->checkedDoubleClickWidget = cocos2d::CCArray::create();
    this->checkedDoubleClickWidget->retain();
}

UIInputManager::~UIInputManager()
{
    
}

void UIInputManager::registWidget(CocoWidget* widget)
{
    if (!widget){
        return;
    }
    if (this->m_manageredWidget->containsObject(widget))
    {
        return;
    }
    this->m_manageredWidget->addObject(widget);
}

void UIInputManager::uiSceneHasChanged()
{
    this->m_bWidgetBeSorted = false;
}

void UIInputManager::sortWidgets()
{

    this->m_manageredWidget->removeAllObjects();
    this->sortRootWidgets(COCOUISYSTEM->getCurScene()->getRootWidget());
    this->m_bWidgetBeSorted = true;
}

void UIInputManager::sortRootWidgets(CocoWidget *root)
{
    for (int i=root->getChildren()->count()-1; i >= 0; i--)
    {
        CocoWidget* widget = (CocoWidget*)(root->getChildren()->objectAtIndex(i));
        this->sortRootWidgets(widget);
    }
    if (root->getBeTouchAble())
    {
        this->registWidget(root);
    }
}

void UIInputManager::removeManageredWidget(CocoWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (!this->m_manageredWidget->containsObject(widget))
    {
        return;
    }
    this->m_manageredWidget->removeObject(widget);
}

CocoWidget* UIInputManager::checkEventWidget(cocos2d::CCPoint &touchPoint)
{
    if (!this->m_bWidgetBeSorted)
    {
        this->sortWidgets();
    }
    
    for (int i=0;i<this->m_manageredWidget->count();i++)
    {
        CocoWidget* widget = (CocoWidget*)(this->m_manageredWidget->objectAtIndex(i));
        
        if(widget->pointAtSelfBody(touchPoint))
        {
            if (!widget->checkVisibleDependParent(touchPoint))
            {
                continue;
            }
            if (i != this->m_manageredWidget->count()-1){
                int j = i+1;
                for (;j < this->m_manageredWidget->count();j++)
                {
                    CocoWidget* wid = (CocoWidget*)(m_manageredWidget->objectAtIndex(j));
                    wid->didNotSelectSelf();
                }
            }
            return widget;
        }
        else
        {
            widget->didNotSelectSelf();
        }
    }
    return NULL;
}

void UIInputManager::addCheckedDoubleClickWidget(CocoWidget* widget)
{
    if (this->checkedDoubleClickWidget->containsObject(widget))
    {
        return;
    }
    this->checkedDoubleClickWidget->addObject(widget);
}

void UIInputManager::update(float dt)
{
    if (this->m_bTouchDown)
    {
        this->m_fLongClickRecordTime += dt;
        if (this->m_fLongClickRecordTime >= this->m_fLongClickTime)
        {
            this->m_fLongClickRecordTime = 0;
            this->m_bTouchDown = false;
            this->m_pCurSelectedWidget->onTouchLongClicked(this->touchBeganedPoint);
        }
    }
    for (int i=0;i<this->checkedDoubleClickWidget->count();i++)
    {
        CocoWidget* widget = (CocoWidget*)(this->checkedDoubleClickWidget->objectAtIndex(i));
        if (!widget->getVisible())
        {
            continue;
        }
    }
}

bool UIInputManager::onTouchPressed(cocos2d::CCTouch* touch)
{
    this->touchBeganedPoint.x = touch->getLocation().x;
    this->touchBeganedPoint.y = touch->getLocation().y;
    CocoWidget* hitWidget = this->checkEventWidget(this->touchBeganedPoint);
    if (!hitWidget || !hitWidget->getActive())
    {
        this->m_pCurSelectedWidget = NULL;
        return false;
    }
    this->m_pCurSelectedWidget = hitWidget;
    hitWidget->onTouchPressed(this->touchBeganedPoint);
    this->m_bTouchDown = true;
    return true;
}

bool UIInputManager::onTouchMoved(cocos2d::CCTouch* touch)
{
    CocoWidget* hitWidget = this->m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->getActive())
    {
        return false;
    }
    this->touchMovedPoint.x = touch->getLocation().x;
    this->touchMovedPoint.y = touch->getLocation().y;
    hitWidget->onTouchMoved(this->touchMovedPoint);
    if (this->m_bTouchDown)
    {
        this->m_fLongClickRecordTime = 0;
        this->m_bTouchDown = false;
    }
    return true;
}

bool UIInputManager::onTouchReleased(cocos2d::CCTouch* touch)
{
    this->m_bTouchDown = false;
    CocoWidget* hitWidget = this->m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->getActive())
    {
        return false;
    }
    this->touchEndedPoint.x = touch->getLocation().x;
    this->touchEndedPoint.y = touch->getLocation().y;
    hitWidget->onTouchReleased(this->touchEndedPoint);
    this->m_pCurSelectedWidget = NULL;
    hitWidget = NULL;
    return true;
}

bool UIInputManager::onTouchCanceled(cocos2d::CCTouch* touch)
{
    this->m_bTouchDown = false;
    CocoWidget* hitWidget = this->m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->getActive())
    {
        return false;
    }
    this->touchEndedPoint.x = touch->getLocation().x;
    this->touchEndedPoint.y = touch->getLocation().y;
    hitWidget->onTouchReleased(this->touchEndedPoint);
    this->m_pCurSelectedWidget = NULL;
    hitWidget = NULL;
    return true;
}

bool UIInputManager::onTouchPressed(float x,float y)
{
    this->touchBeganedPoint.x = x;
    this->touchBeganedPoint.y = y;
    CocoWidget* hitWidget = this->checkEventWidget(this->touchBeganedPoint);
    if (!hitWidget || !hitWidget->getActive())
    {
        this->m_pCurSelectedWidget = NULL;
        return false;
    }
    this->m_pCurSelectedWidget = hitWidget;
    hitWidget->onTouchPressed(this->touchBeganedPoint);
    this->m_bTouchDown = true;
    return true;
}

bool UIInputManager::onTouchMoved(float x,float y)
{
    CocoWidget* hitWidget = this->m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->getActive())
    {
        return false;
    }
    this->touchMovedPoint.x = x;
    this->touchMovedPoint.y = y;
    hitWidget->onTouchMoved(this->touchMovedPoint);
    if (this->m_bTouchDown)
    {
        this->m_fLongClickRecordTime = 0;
        this->m_bTouchDown = false;
    }
    return true;
}

bool UIInputManager::onTouchReleased(float x,float y)
{
    this->m_bTouchDown = false;
    CocoWidget* hitWidget = this->m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->getActive())
    {
        return false;
    }
    this->touchEndedPoint.x = x;
    this->touchEndedPoint.y = y;
    hitWidget->onTouchReleased(this->touchEndedPoint);
    this->m_pCurSelectedWidget = NULL;
    hitWidget = NULL;
    return true;
}

bool UIInputManager::onTouchCanceled(float x,float y)
{
    this->m_bTouchDown = false;
    CocoWidget* hitWidget = this->m_pCurSelectedWidget;
    if (!hitWidget || !hitWidget->getActive())
    {
        return false;
    }
    this->touchEndedPoint.x = x;
    this->touchEndedPoint.y = y;
    hitWidget->onTouchReleased(this->touchEndedPoint);
    this->m_pCurSelectedWidget = NULL;
    hitWidget = NULL;
    return true;
}

NS_CC_EXT_END