#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "FourCard.h"
#include "GameQueueScene.h"

USING_NS_CC;

class MainScene : public cocos2d::LayerColor
{
private:
	Layer *layer_menu;
	Menu *menu_menu;
	MenuItemImage *menuItem_menu_main, *menuItem_menu_rank, *menuItem_menu_help, *menuItem_menu_setting, *menuItem_menu_info;
	MenuItemImage *menuItem_menu_current;
	LayerMultiplex *layer_content;
	Layer *layer_content_main, *layer_content_rank, *layer_content_help, *layer_content_setting, *layer_content_info;
	Layer *layer_game_start;
	Menu* menu_game_start;
	MenuItemImage* menuItem_game_start;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

	void changeContent(MenuItemImage* menuItem, int index);
};

#endif // __MAIN_SCENE_H__
