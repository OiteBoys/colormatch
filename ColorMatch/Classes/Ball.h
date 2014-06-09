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

enum BALL_TAG {
	TAG_RED,
	TAG_ORANGE,
	TAG_YELLOW,
	TAG_GREEN,
    TAG_BLUE,
    TAG_VIOLET
};

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
    Ball *componentParent;
    void markBallCorlor(string color);
};


#endif
