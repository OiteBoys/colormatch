//
//  Ball.h
//  ColorMatch
//
//  Created by damingdan on 14-6-5.
//
//

#ifndef ColorMatch_Ball_h
#define ColorMatch_Ball_h
#include"cocos2d.h"
using namespace cocos2d;
using namespace std;

class Ball : public Sprite {
public:
    Ball* getComponentRoot();
    void setComponentRoot(Ball* componentRoot);
    int componentCount;
    bool init();
    CREATE_FUNC(Ball);
    
    bool onTouchBegan(Touch* touches, Event* event);
    
    bool isTouchInBall(Point location);
private:
    static Ball* ball();
    Ball *componentRoot;
    Ball *componentParent;
};


#endif
