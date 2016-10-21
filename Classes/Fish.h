//
//  Fish.h
//  Flow
//
//  Created by Tsubo on 2015/03/13.
//
//

#ifndef __Flow__Fish__
#define __Flow__Fish__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class  Fish : public cocos2d::Sprite
{
public:
    static Fish* create(const std::string& filename, const Rect& rect);
    static Fish* create(const std::string& filename);
};

#endif /* defined(__Flow__Fish__) */
