//
//  ColorMatchScene.cpp
//  ColorMatch
//
//  Created by damingdan on 14-6-5.
//
//

#include "ColorMatchScene.h"

enum Z_ORDER {
	Z_BACKGROUND,
	Z_BALLS,
	Z_PARTICLES,
	Z_FOREGROUND,
};


bool ColorMatchScene::init(){
    if(Scene::initWithPhysics()) {
        //this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        this->getPhysicsWorld()->setGravity(Point(0, -250));
        this->balls = Vector<Ball*>(10);
        
        
        this->ticks = 0;
        //this->scheduleUpdate();
        return true;
    } else {
        return false;
    }
}

void ColorMatchScene::onEnter() {
    Scene::onEnter();
    
    this->background = Sprite::create("Background-hd.png");
    this->background->setAnchorPoint(Point::ZERO);
    this->addChild(this->background, Z_BACKGROUND);
    
    this->foreground = Sprite::create("Foreground-hd.png");
    this->foreground->setAnchorPoint(Point::ZERO);
    this->addChild(this->foreground, Z_FOREGROUND);
    
    // create a border
    auto border = Node::create();
    // make the border 3 in order to avoid cross
    this->boundRect = Rect(68*2, 34*2, 430*2, 500*2);
    auto boundBody = PhysicsBody::createEdgeBox(boundRect.size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    border->setPosition(boundRect.origin.x + boundRect.size.width/2, boundRect.origin.y + boundRect.size.height/2);
    border->setPhysicsBody(boundBody);
    this->addChild(border);
    
    // dispatch contact listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(ColorMatchScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool ColorMatchScene::onContactBegin(cocos2d::PhysicsContact &contact) {
    return true;
}


void ColorMatchScene::removeBall(Ball *ball) {
    // Draw the confetti particles whenever a ball is removed.
    auto particleSystem = ParticleSystemQuad::create("pop.plist");
    //particleSystem->setSpeed(100);
    //particleSystem->setTexture(ball->getTexture());
    particleSystem->setPosition(ball->getPosition());
    particleSystem->setAutoRemoveOnFinish(true);
    this->addChild(particleSystem, Z_PARTICLES);
    
    
    this->balls.erase(this->balls.getIndex(ball));
    ball->removeFromParent();
}

void ColorMatchScene::update(float delta) {
    Scene::update(delta);
    if(ticks%6 == 0 && this->balls.size() < 100) {
        auto ball = Ball::create();
        
        float xmin = this->boundRect.getMinX();
        float ymax = this->boundRect.getMaxY();
        float varies = 0.8*CCRANDOM_MINUS1_1();
        ball->setPosition(abs((xmin + ymax)/2.0 - (xmin - ymax)/2.0*varies), this->boundRect.size.height*0.9);
        ball->getPhysicsBody()->setVelocity(Point(100.0*CCRANDOM_MINUS1_1(), 0));
        ball->getPhysicsBody()->setAngularVelocity(5.0*CCRANDOM_MINUS1_1());
        
        this->balls.pushBack(ball);
        this->addChild(ball, Z_BALLS);
    }
    ticks ++;
}

















