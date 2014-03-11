#ifndef __MAIN_CONTENT_LAYERS_H__
#define __MAIN_CONTENT_LAYERS_H__

#include "cocos2d.h"

USING_NS_CC;

class MainContentMainLayer : public cocos2d::LayerColor
{
private:
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainContentMainLayer);
};

class MainContentRankLayer : public cocos2d::LayerColor
{
private:
	LayerMultiplex *layer_rank_current;
	Layer *layer_rank_recent, *layer_rank_winrate, *layer_rank_win, *layer_rank_lose, *layer_rank_total;

	Menu *menu_category;
	MenuItemLabel *menuItem_category_current;
	MenuItemLabel *menuItem_category_recent, *menuItem_category_winrate, *menuItem_category_win, *menuItem_category_lose, *menuItem_category_total;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainContentRankLayer);

	void changeLayer(MenuItemLabel* menuItem, int index);
};

class MainContentHelpLayer : public cocos2d::LayerColor
{
private:
	int page_index;

	Layer* layer_page;
	Menu* menu_index;
	MenuItemImage* menuItem_page_current;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainContentHelpLayer);

	void changeIndex(Layer* layer_page, int index);
};

class MainContentSettingLayer : public cocos2d::LayerColor
{
private:
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainContentSettingLayer);
};

class MainContentInfoLayer : public cocos2d::LayerColor
{
private:
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainContentInfoLayer);
};

#endif // __MAIN_CONTENT_LAYERS_H__
