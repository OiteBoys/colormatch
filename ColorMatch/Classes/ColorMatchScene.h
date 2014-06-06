//
//  ColorMatchScene.h
//  ColorMatch
//
//  Created by damingdan on 14-6-5.
//
//

#ifndef ColorMatch_ColorMatchScene_h
#define ColorMatch_ColorMatchScene_h
#include "cocos2d.h"
#include "Ball.h"
using namespace cocos2d;
using namespace std;

class ColorMatchScene : public Scene {
public:
    void removeBall(Ball* ball);
    bool init();
    CREATE_FUNC(ColorMatchScene);
    void onEnter();
    
    bool onContactBegin(PhysicsContact& contact);
    
    void update(float delta);
private:
    Sprite* background;
    Sprite* foreground;
    Node* physics;
    Vector<Ball*> balls;
    int ticks;
    Rect boundRect;
};


#endif
