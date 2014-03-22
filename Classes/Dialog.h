#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DrawObject.h"
#include "FourCard.h"
#include <functional>

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class Dialog : public cocos2d::LayerColor
{
private:
	string m_title, m_message;
	Layer* m_layer;
	list<pair<string, function<void()>>> m_list_button;

	Layer* m_dialog;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Dialog);

	void setTitle(const char* title);
	void setMessage(const char* message);
	void setLayer(Layer* layer);
	void addButton(const char* name, const function<void()>& listener);

	void clearLayout();
	void updateLayout();
};

#endif // __DIALOG_H__
