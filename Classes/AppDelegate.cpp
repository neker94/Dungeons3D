#include "AppDelegate.h"
#include "MainMenuScene.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Dungeons3D");
		
        director->setOpenGLView(glview);
    }

	auto fileUtils = FileUtils::getInstance();
	std::vector<std::string> resDirOrders;
	resDirOrders.push_back("resources");

	glview->setFrameSize(800,600);
	glview->setDesignResolutionSize(800,600, ResolutionPolicy::EXACT_FIT);

	fileUtils->setSearchPaths(resDirOrders);

    // turn on display FPS
    director->setDisplayStats(false);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = MainMenuScene::createScene();

    // run
    director->runWithScene(scene);

	

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
