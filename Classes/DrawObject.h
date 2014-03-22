#ifndef __DRAW_OBJECT_H__
#define __DRAW_OBJECT_H__

#include "cocos2d.h"
#include <functional>

using namespace std;

USING_NS_CC;

class DrawObject : public cocos2d::Node
{
private:
	function<void()> m_on_draw;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void draw();
    
    // implement the "static create()" method manually
    CREATE_FUNC(DrawObject);

	void setOnDraw(const function<void()>& onDraw);
};

#endif // __DRAW_OBJECT_H__
