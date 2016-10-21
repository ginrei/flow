//
//  MainScene.cpp
//  Flow
//
//  Created by Tsubo on 2015/03/13.
//
//

#include "MainScene.h"
#include "Fish.h"
#include <iostream>


USING_NS_CC;
using namespace json11;

cocos2d::Scene* MainScene::createScene() {
    
    auto scene = Scene::create();
    
    auto mainScene = MainScene::create();
    //auto bg = LayerColor::create(Color4B(255, 101, 103));
    auto bg = LayerColor::create(Color4B(73, 230, 188, 255));
    
    scene->addChild(bg);
    scene->addChild(mainScene);
    
    return scene;
}

bool MainScene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Load Stage File
    auto jsonStageDataString = FileUtils::getInstance()->getStringFromFile("stages.json");
    std::string err;
    stageDatas = Json::parse(jsonStageDataString, err);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    
    srand(time(NULL));
    
    initWorldPhysics();
    
    initFrames();
    
    initCharacters();
    
    initInputs();
    
    this->scheduleUpdate();
    
    return true;
}

void MainScene::initWorldPhysics() {
    // Define the gravity vector.
    b2Vec2 gravity;
    gravity.Set(0.0f, -1.0f);//No gravity
    
    // Do we want to let bodies sleep?
    bool doSleep = true;
    
    // create a world object, which will hold and simulate the rigid bodies.
    world = new b2World(gravity);
    
    debugDraw = new GLESDebugDraw(PTM_RATIO);
    world->SetDebugDraw(debugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    debugDraw->SetFlags(flags);
    
    // Example box2d object to confirm debugDraw works
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(200/PTM_RATIO, 300/PTM_RATIO);
//    b2Body *body = world->CreateBody(&bodyDef);
//    
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(50/PTM_RATIO, 50/PTM_RATIO);
//    
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &dynamicBox;
//    fixtureDef.density = 1.0f;
//    body->CreateFixture(&fixtureDef);

    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(330/PTM_RATIO, 420/PTM_RATIO);
    b2Body *body = world->CreateBody(&bodyDef);
    
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = 5/PTM_RATIO;
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);
    body->SetGravityScale(10);
    
}

void MainScene::initFrames() {
    
    auto frameDatas = stageDatas[0]["frames"].array_items();
    
    int tag = 0;
    std::vector<Vec2> points;
    for (auto &frameData : frameDatas) {
        auto pointDatas = frameData["points"].array_items();
        for(auto &pointData : pointDatas) {
            points.push_back(Vec2(pointData["x"].number_value(), pointData["y"].number_value()));
        }
        setFrame(points);
        points.clear();
        tag++;
    }
}

void MainScene::initCharacters() {
    
    Vec2 sceneSize = this->getContentSize();
    
    auto water = Sprite::create("res/water.png");
    water->setPosition(Vec2(0, -100));
    //this->addChild(water);
    
    auto fish = Fish::create("res/fishes.png", Rect(0, 0, 64, 64));
    fish->setPosition(Vec2(sceneSize.x / 2, sceneSize.y / 2 ));
    this->addChild(fish);
    
    auto waterMask = ClippingNode::create();
    auto maskNode = Node::create();
    auto waterMaskShape = Sprite::create("res/water.png");
//    auto fishMaskShape = Fish::create("res/fishes.png", Rect(0, 0, 64, 64));
//    fishMaskShape->setPosition(Vec2(0, -180));
//    waterMask->setPosition(Vec2(sceneSize.x / 2, sceneSize.y / 2 ));
//    
//    maskNode->addChild(waterMaskShape);
//    maskNode->addChild(fishMaskShape);
//
//    waterMask->setStencil(maskNode);
//
//    waterMask->setInverted(false);
//    waterMask->setAlphaThreshold(0.0f);
//
//    waterMask->addChild(water);
//   
//    this->addChild(waterMask);

    
    
    auto tanks = Sprite::create("res/stage0.png");
    tanks->setPosition(Vec2(sceneSize.x / 2, sceneSize.y / 2 ));
    this->addChild(tanks);
    
    //
    //    BlendFunc blend;
    //    blend.src = GL_ZERO;
    //    blend.dst = GL_SRC_COLOR;
    //    water->setBlendFunc(blend);
    //
}

void MainScene::initInputs() {
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(MainScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

bool MainScene::onTouchBegan(Touch* touch, Event* event) {
    
}
void MainScene::onTouchMoved(Touch* touch, Event* event) {
    
}
void MainScene::onTouchEnded(Touch* touch, Event* event) {
    
}
void MainScene::onTouchCancelled(Touch* touch, Event* event) {
    
}

void MainScene::setFrame(std::vector<Vec2> points) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0, 0);
    b2Body* body = world->CreateBody(&bodyDef);
    
    for (int i=1;i<points.size();i++)
    {
        
        b2Vec2 start = b2Vec2(points.at(i-1).x/PTM_RATIO, points.at(i-1).y/PTM_RATIO);
        b2Vec2 end = b2Vec2(points.at(i).x/PTM_RATIO, points.at(i).y/PTM_RATIO);
        
        b2EdgeShape shape; //b2ChainShapeでもよい
        shape.Set(start, end);
        body->CreateFixture(&shape, 0.0f);
    }
}

void MainScene::update(float delta) {
    int positionIterations = 10;
    int velocityIterations = 10;
    
    float deltaTime = delta;
    world->Step(delta, velocityIterations, positionIterations);
    
    for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext()) {
        if (body->GetUserData())
        {
            
        }
    }

}

void MainScene::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformUpdated) {
    Layer::draw(renderer, transform, transformUpdated);
    Director* director = Director::getInstance();
    
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    world->DrawDebugData();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}