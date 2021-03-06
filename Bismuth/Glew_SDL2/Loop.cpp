#include "Loop.h"



Loop::Loop() : mFrame(0), mContinue(true), mFps(1.0), mPhysicsDelay(0.0f), mTimeStep((1000.0/60.0)/10.0), mElapsedTime(0.0f), mTimeFactor(1.0f)
{
	mCfg = readConfig(); 
	mScene = new Scene_SDL(mCfg->ResolutionX, mCfg->ResolutionY, mCfg->FullScreen);
	mCamera = new Camera(70, (float)mCfg->ResolutionX / mCfg->ResolutionY, 0.3, 1000.0);
	mResourcesManager = new ResourcesManager();
	mEntityManager =new EntityManager();
	mRenderSystem = new RenderSystem(mCfg, mResourcesManager);
	mInput =new Input(mCfg->ResolutionX, mCfg->ResolutionY);

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
	mRenderSystem->draw(mEntityManager->getWorld(), *mCamera, float(mFrame), *mInput, float(mFps));

	mContinue = !mInput->end();
	mFrame++;
	mFps = mScene->waitForFps(30);
	mElapsedTime = 1000.0 / mFps; // ATTENTION EN MS

	double timeToCompute = mTimeFactor * mElapsedTime + mPhysicsDelay;
	mNbSteps = int(floor(timeToCompute / mTimeStep));
	mPhysicsDelay = timeToCompute - mNbSteps*mTimeStep;
	//if (time % 10 == 0)	cout << mFps << endl;
	mInput->update();

	int signTF = (mTimeFactor > 0) - (mTimeFactor < 0);

	if(mTimeFactor != 0.0)
	for (int i = 0; i < abs(mNbSteps); i++)
	{
		for (int i = 0; i < toUpdate.size(); i++)
			toUpdate[i]->update( float(mTimeStep /1000) ); // CONVERSION EN S

		mEntityManager->update(signTF *  float(mTimeStep / 1000));
		mEntityManager->collision();
		mEntityManager->singleCollisionResponse(signTF *  float(mTimeStep / 1000));
		mEntityManager->systemCollisionResponse(signTF * float(mTimeStep / 1000));
		mEntityManager->doResponseCollision();


		if (mCfg->DrawCollision)
			mRenderSystem->draw2D(getVisualCollision(mResourcesManager, mEntityManager->getIM(), *mCamera));
	}

	mRenderSystem->draw2D(mEntityManager->getEntities2D());
	mScene->flip();
}

void Loop::setTimeFactor(double timeFactor)
{
	//if (timeFactor > 0)
		mTimeFactor = timeFactor;
}
