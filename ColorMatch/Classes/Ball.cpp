//
//  Ball.cpp
//  ColorMatch
//
//  Created by damingdan on 14-6-5.
//
//

#include "Ball.h"
#include "ColorMatchScene.h"



bool Ball::init() {
    string colors[] = {"red", "orange", "yellow", "green", "blue", "violet"};
    string color = colors[rand()%6];
    if (Sprite::initWithFile("Ball_" + color + "-hd.png")) {
        // Give the balls some variation in size.
        this->setScale(0.5 + 0.15*CCRANDOM_MINUS1_1());
        
        // Estimate the ball's radius using half of the sprite's width.
        float padding = 5.0f;
        float radius = 0.5f*(this->getContentSize().width*this->getScale() - padding);
        
        // Bodies default to a mass of 1.0. We want bigger balls to weight more.
		// Setting the density is an easy way to accomplish that.
		// Keep in mind that if you resize the object the mass is kept constant and the density will change.
        auto material = PhysicsMaterial(1.0, 0, 0.5);
        
        // First we need to create a physics body with a circle shape.
        auto body = PhysicsBody::createCircle(radius, material);
        body->setCollisionBitmask(0x01);
        body->setCategoryBitmask(0x01);
        body->setContactTestBitmask(0x01);
        
        // make the sprite have the physical feature
        this->setPhysicsBody(body);
        
        // mark this ball's color
        this->markBallCorlor(color);
        
        // set the touch listener, when you touch the ball, the ball will expored
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(Ball::onTouchBegan, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        // A the first, the ball' componentRoot is it's self
        //this->componentParent = this;
        //this->componentCount = 0;
        return true;
    }else {
        return false;
    }
}

void Ball::markBallCorlor(string color) {
    if(color == "red") {
        this->setTag(TAG_RED);
    }else if(color == "orange") {
        this->setTag(TAG_ORANGE);
    }else if(color == "yellow") {
        this->setTag(TAG_YELLOW);
    }else if(color == "green") {
        this->setTag(TAG_GREEN);
    }else if(color == "blue") {
        this->setTag(TAG_BLUE);
    }else if(color == "violet") {
        this->setTag(TAG_VIOLET);
    }
}

bool Ball::onTouchBegan(Touch* touche, cocos2d::Event *event) {
    auto location = touche->getLocation();
    if(this->isTouchInBall(location)) {
        ColorMatchScene *scene = (ColorMatchScene*)this->getScene();
        scene->removeBall(this);
    }
    return true;
}

bool Ball::isTouchInBall(Point location) {
    float radius = this->getContentSize().width*this->getScale()*0.5;
    float maxX = this->getPositionX() + radius;
    float minX = this->getPositionX() - radius;
    float maxY = this->getPositionY() + radius;
    float minY = this->getPositionY() - radius;
    bool xMatch = (minX < location.x && location.x < maxX);
    bool yMatch = (minY < location.y && location.y < maxY);
    return xMatch&&yMatch;
}

Ball* Ball::ball() {
    return Ball::create();
}

Ball* Ball::getComponentRoot() {
    if(this->componentParent != this) {
        // Path compression.
		// Make the next lookup quicker by caching the parent's root.
        this->componentParent = this->componentParent->getComponentRoot();
    }
    return componentParent;
}

void Ball::setComponentRoot(Ball *componentRoot) {
    if(componentRoot == this) {
        this->componentParent = this;
    }else {
        this->componentParent = componentRoot->getComponentRoot();
    }
}