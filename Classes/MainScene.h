//
//  MainScene.h
//  Flow
//
//  Created by Tsubo on 2015/03/13.
//
//

#ifndef __Flow__MainScene__
#define __Flow__MainScene__

#include <stdio.h>
#include <Box2d.h>
#include <GLES-Render.h>
#include "json11.hpp"

#define PTM_RATIO 32.0

USING_NS_CC;
using namespace json11;

class MainScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    
    CREATE_FUNC(MainScene);
    
protected:
    EventListenerTouchOneByOne* _touchListener;
    
private:
    b2World* world;
    GLESDebugDraw* debugDraw;

    int currentStage = 0;
    Json stageDatas;
    
    virtual bool init();
    
    void loadStage(int stageNumber = 0);
    void initWorldPhysics();
    void initFrames();
    void initCharacters();
    void initInputs();
    
    void setFrame(std::vector<Vec2> points);
    
    void update(float delta);
    
};


#endif /* defined(__Flow__MainScene__) */
