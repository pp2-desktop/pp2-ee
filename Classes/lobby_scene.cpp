#include "lobby_scene.h"
#include "ui/CocosGUI.h"
#include "lobby_multi_scene.h"

using namespace ui;

Scene* lobby_scene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = lobby_scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool lobby_scene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    center_ = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(lobby_scene::menuCloseCallback, this));
    closeItem->setScale(2.0f, 2.0f);
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2-20, origin.y + closeItem->getContentSize().height/2+15));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 
    auto background = Sprite::create("background/lobby_scene.jpg");
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background, 0);

   // 싱글 버튼 추가
    auto single_button = Button::create("ui/normal_btn.png", "ui/pressed_btn.png", "ui/disabled_btn.png");
    single_button->setTitleText("SinglePlay");
    single_button->setTitleFontSize(24);
    single_button->setScale(2.0f, 2.0f);
    single_button->setPosition(Vec2(center_.x+425, center_.y+260));
    single_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
	  {
	  case ui::Widget::TouchEventType::BEGAN:
	    break;
	  case ui::Widget::TouchEventType::ENDED:
	    //std::cout << "Button 1 clicked" << std::endl;
	    break;
	  default:
	    break;
	  }
      });
    this->addChild(single_button);

    // 멀티 버튼 추가
    auto multi_button = Button::create("ui/normal_btn.png", "ui/pressed_btn.png", "ui/disabled_btn.png");
    multi_button->setTitleText("MultiPlay");
    multi_button->setTitleFontSize(24);
    multi_button->setScale(2.0f, 2.0f);
    multi_button->setPosition(Vec2(center_.x+425, center_.y+150));
    multi_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
	auto scene = lobby_multi_scene::createScene();

        switch (type)
	  {
	  case ui::Widget::TouchEventType::BEGAN:
	    break;
	  case ui::Widget::TouchEventType::ENDED:
	    Director::getInstance()->replaceScene(TransitionFade::create(1, scene, Color3B(0,255,255)));
	    //std::cout << "Button 1 clicked" << std::endl;
	    break;
	  default:
	    break;
	  }
      });
    this->addChild(multi_button);



  
    this->scheduleUpdate();
    
    return true;
}

void lobby_scene::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void lobby_scene::update(float dt) {
  //CCLOG("update");
}
