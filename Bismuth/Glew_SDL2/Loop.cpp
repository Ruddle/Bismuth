#include "Loop.h"



Loop::Loop() : mFrame(0), mContinue(true), mFps(1.0), mElapsedTime(1.0)
{
	mCfg = readConfig(); 
	mScene = new Scene_SDL(mCfg->ResolutionX, mCfg->ResolutionY, mCfg->FullScreen);
	mCamera = new Camera(70.0, (float)mCfg->ResolutionX / mCfg->ResolutionY, 0.3, 100.0);
	mResourcesManager = new ResourcesManager();
	mEntityManager =new EntityManager();
	mRenderSystem = new RenderSystem(*mCfg, mResourcesManager);
	mInput =new Input();

}


Loop::~Loop()
{
	delete mCfg;
	delete mResourcesManager;
	delete mEntityManager;
	delete mRenderSystem;
	delete mCamera;
	delete mScene;
}

void Loop::insertInLoop(std::vector<Updatable*> &toUpdate)
{

	mContinue = !mInput->end();
	mFrame++;
	mFps = (mScene->waitForFps(30) + 2 * mFps) / 3.0;
	mElapsedTime = 1000.0 / mFps;
	//if (time % 10 == 0)	cout << mFps << endl;
	mInput->update();
	

	float numIterPhys = 10;
	for (int i = 0; i < numIterPhys; i++)
	{
		for (int i = 0; i < toUpdate.size(); i++)
			toUpdate[i]->update(float(mElapsedTime / numIterPhys));

		mEntityManager->update(float(mElapsedTime / numIterPhys));
		mEntityManager->collision();
		mEntityManager->collisionResponse(mElapsedTime / numIterPhys);
	}


	mRenderSystem->draw(mEntityManager->getEntities(), *mCamera, mFrame, *mInput, float(mFps));
	if (mInput->getKey(SDL_SCANCODE_C))
	mRenderSystem->draw2D(getVisualCollision(mResourcesManager, mEntityManager->getEntities(), *mCamera));
	mRenderSystem->draw2D(mEntityManager->getEntities2D());
	mScene->flip();
}
