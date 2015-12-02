#include "Loop.h"



Loop::Loop() : mFrame(0), mContinue(true), mFps(1.0), mPhysicsDelay(0.0f), mTimeStep(2.0f), mElapsedTime(0.0f), mTimeFactor(1.0f)
{
	mCfg = readConfig(); 
	mScene = new Scene_SDL(mCfg->ResolutionX, mCfg->ResolutionY, mCfg->FullScreen);
	mCamera = new Camera(70.0, (float)mCfg->ResolutionX / mCfg->ResolutionY, 0.3, 1000.0);
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
	mFps = mScene->waitForFps(30);
	mElapsedTime = 1000.0 / mFps;

	double timeToCompute = mTimeFactor * mElapsedTime + mPhysicsDelay;
	mNbSteps = floor(timeToCompute / mTimeStep);
	mPhysicsDelay = timeToCompute - floor(timeToCompute / mTimeStep);
	//if (time % 10 == 0)	cout << mFps << endl;
	mInput->update();

	for (int i = 0; i < mNbSteps; i++)
	{
		for (int i = 0; i < toUpdate.size(); i++)
			toUpdate[i]->update(mTimeStep);

		mEntityManager->update(mTimeStep);
		mEntityManager->collision();
		mEntityManager->collisionResponse(mTimeStep);
	}


	mRenderSystem->draw(mEntityManager->getEntities(), *mCamera, mFrame, *mInput, float(mFps));
	if (mInput->getKey(SDL_SCANCODE_C))
	mRenderSystem->draw2D(getVisualCollision(mResourcesManager, mEntityManager->getEntities(), *mCamera));
	mRenderSystem->draw2D(mEntityManager->getEntities2D());
	mScene->flip();
}

void Loop::setTimeFactor(double timeFactor)
{
	if (timeFactor > 0)
		mTimeFactor = timeFactor;
}
