//
//  GUINodeRGBA.h
//  TestColorNode
//
//  Created by cai wenzhi on 13-5-9.
//
//

#ifndef __TestColorNode__GUINodeRGBA__
#define __TestColorNode__GUINodeRGBA__

#include "cocos2d.h"

namespace cs {

class GUINodeRGBA  : public cocos2d::CCNodeRGBA{

public:
    static GUINodeRGBA * create(void);
    bool init();
    virtual void addChild(CCNode * child);
    virtual void setColor(const cocos2d::ccColor3B& color3);
    virtual void setOpacity(GLubyte opacity);
    virtual void setOpacityModifyRGB(bool modify){};
    virtual bool isOpacityModifyRGB(void){return false;};
};
}

#endif /* defined(__TestColorNode__GUINodeRGBA__) */
