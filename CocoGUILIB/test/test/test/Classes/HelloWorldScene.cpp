#include "HelloWorldScene.h"
#include "CCEditBox.h"
using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    COCOUISYSTEM->resetSystem(this);
    
//    COCOUISYSTEM->replaceUISceneWithFile(this, "UIRES/CocoGUISample.json", 1, true,true,true);
    
    COCOUISYSTEM->getCurScene()->addWidget(COCOUISYSTEM->createWidgetFromFileWithAdapt_json("UIRES/CocoGUISample.json", true, true));
    
    cs::CocoScrollView* sc = (cs::CocoScrollView*)(COCOUISYSTEM->getWidgetByName("scrollview"));
    sc->setUpdateEnable(true);
    sc->setMoveMode(cs::SCROLLVIEW_MOVE_MODE_ACTION);
    cs::CocoTextButton* bt = (cs::CocoTextButton*)(COCOUISYSTEM->getWidgetByName("backtotopbutton"));
    bt->addReleaseEvent(this, coco_releaseselector(HelloWorld::backToTop));
    cs::CocoSlider* sld = (cs::CocoSlider*)(COCOUISYSTEM->getWidgetByName("slider"));
    sld->addPercentChangedEvent(this, coco_percentchangedselector(HelloWorld::sliderPercentChanged));
    cs::CocoButton* anib = (cs::CocoButton*)(COCOUISYSTEM->getWidgetByName("animationbutton"));
    anib->addReleaseEvent(this, coco_releaseselector(HelloWorld::playUIAnimation));
    cs::CocoTextField* tfd = dynamic_cast<cs::CocoTextField*>(COCOUISYSTEM->getWidgetByName("textfield"));
    tfd->setCharacterLength(4);
    tfd->setIsPassWord(true);
    cs::CocoButton* exit = (cs::CocoButton*)(COCOUISYSTEM->getWidgetByName("exitbutton"));
    exit->addReleaseEvent(this, coco_releaseselector(HelloWorld::menuCloseCallback));
    exit->addCancelEvent(this, coco_cancelselector(HelloWorld::cancelTouch));
    
    
    cs::CocoLabel* cleanUI = cs::CocoLabel::create();
    cleanUI->setTouchScaleChangeAble(true);
    cleanUI->setPosition(ccp(200, 40));
    cleanUI->setText("Click to clean UI Scene!");
    cleanUI->setBeTouchAble(true);
    cleanUI->addReleaseEvent(this, coco_releaseselector(HelloWorld::cleanUIWidgets));
    COCOUISYSTEM->getCurScene()->addWidget(cleanUI);
    
    cs::CocoNodeContainer* container = cs::CocoNodeContainer::create();
    extension::CCEditBox* eb = extension::CCEditBox::create(CCSizeMake(200, 50), extension::CCScale9Sprite::create("UIRES/sliderballnormal.png"));
    eb->setText("I'm a EditBox");
    container->addCCNode(eb);
    container->setPosition(ccp(330, 150));
    COCOUISYSTEM->getCurScene()->addWidget(container);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::backToTop(cocos2d::CCObject *pSender)
{
    cs::CocoScrollView* sc = (cs::CocoScrollView*)(COCOUISYSTEM->getWidgetByName("scrollview"));
    sc->scrollToTop();
}

void HelloWorld::sliderPercentChanged(cocos2d::CCObject *pSender)
{
    cs::CocoLoadingBar* lb = (cs::CocoLoadingBar*)(COCOUISYSTEM->getWidgetByName("loadingbar"));
    cs::CocoSlider* sld = (cs::CocoSlider*)pSender;
    int percent = sld->getPercent();
    lb->setPercent(percent);
}

void HelloWorld::playUIAnimation(cocos2d::CCObject *pSender)
{
    cs::CocoWidget* widget = (cs::CocoWidget*)pSender;
    widget->stopAllActions();
    widget->setColor(0, 0, 255);
    CCTintTo* tt = CCTintTo::create(0.5f, 0, 255, 0);
    CCTintTo* tt2 = CCTintTo::create(0.5f, 255, 255, 255);
    CCFadeOut* fo = CCFadeOut::create(0.5f);
    CCFadeIn* fi = CCFadeIn::create(0.5f);
    CCSequence* seq = CCSequence::create(CCMoveTo::create(1.0, ccp(300, 300)),CCScaleTo::create(1, 0.5),CCMoveTo::create(1.0, ccp(127, 96)),CCScaleTo::create(1.0, 1.0),CCRotateTo::create(0.5, 720),CCRotateTo::create(0.5, 0),tt,tt2,fo,fi,NULL);
    widget->runAction(seq);
}

void HelloWorld::cancelTouch(cocos2d::CCObject *pSender)
{
    CCLOG("cancel touch");
}

void HelloWorld::cleanUIWidgets(cocos2d::CCObject *pSender)
{
    COCOUISYSTEM->getCurScene()->getRootWidget()->removeAllChildrenAndCleanUp(true);
//    cs::CocoControlButton* cb = cs::CocoControlButton::create();
//    cb->setTexture("CloseNormal.png");
//    cb->setTitle("ControlButton");
//    cb->setPosition(ccp(100, 100));
//    cb->setBeTouchAble(true);
//    COCOUISYSTEM->getCurScene()->addWidget(cb);
//    
//    CCLabelTTF* lttf = CCLabelTTF::create();
//    lttf->setString("ControlButton");
//    extension::CCControlButton* cbc = extension::CCControlButton::create(lttf, extension::CCScale9Sprite::create("CloseNormal.png"));
//    this->addChild(cbc);
//    cbc->setPosition(ccp(200, 200));
//    
//    CCLabelBMFont* lbbmf = CCLabelBMFont::create("dasjio", "arial-14.fnt");
//    lbbmf->setPosition(ccp(300, 300));
//    this->addChild(lbbmf);
//
    cs::CocoLabelBMFont* lb = cs::CocoLabelBMFont::create();
    lb->setFntFile("arial-14.fnt");
    lb->setText("abcd");
    lb->setPosition(ccp(100, 100));
    COCOUISYSTEM->getCurScene()->addWidget(lb);
    
    return;
    COCOUISYSTEM->resetSystem(this);
    cs::CocoPanel* p = cs::CocoPanel::create();
    p->setSize(100, 100);
    p->setBackGroundColorEnable(true);
    p->setColor(0, 255, 0);
    p->setOpacity(255);
    COCOUISYSTEM->getCurScene()->addWidget(p);
    p->setBackGroundColorEnable(false);
}
