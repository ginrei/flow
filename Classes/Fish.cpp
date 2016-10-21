//
//  Fish.cpp
//  Flow
//
//  Created by Tsubo on 2015/03/13.
//
//

#include "Fish.h"

USING_NS_CC;

Fish* Fish::create(const std::string& filename)
{
    Fish *sprite = new (std::nothrow) Fish();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Fish* Fish::create(const std::string& filename, const Rect& rect)
{
    Fish *sprite = new (std::nothrow) Fish();
    if (sprite && sprite->initWithFile(filename, rect))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}