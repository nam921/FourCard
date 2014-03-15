#ifndef __GAME_QUEUE_SCENE_H__
#define __GAME_QUEUE_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include <list>
#include <thread>
#include <string>
#include "FourCard.h"
#include "Dialog.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class GameQueueScene : public cocos2d::LayerColor
{
private:
	LabelTTF* label_time;

	int32_t m_queue_type;
	list<string> m_queue_user_list;

	float m_queue_time;
	bool m_queue_packet_received;
	int32_t m_queue_status;
	int32_t m_queue_id;
	string m_queue_error_message;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int32_t queue_type, const list<string>& queue_user_list);
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameQueueScene);
};

#endif // __GAME_QUEUE_SCENE_H__