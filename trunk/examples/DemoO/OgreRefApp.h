/*
This file is mostly stolen from Ogre's ExampleRefAppApplication.h, so
we're including the credits/licensing from that file below.
 -OpenGUI Project-
*/

/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2005 The OGRE Team
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------
Filename:    ExampleApplication.h
Description: Base class for all the OGRE ReferenceApplication examples
-----------------------------------------------------------------------------
*/

#ifndef __OgreRefApp_H__
#define __OgreRefApp_H__

#include <OpenGUI.h>
#include <OgreFusion.h>
#include <Ogre.h>



#include "OgreConfigFile.h"


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#    include <SDL.h>
#endif

using namespace Ogre;

class OgreRefFrameListener : public Ogre::FrameListener
{
public:
	OgreRefFrameListener() {}
	virtual ~OgreRefFrameListener() {}
	virtual bool frameStarted (const FrameEvent &evt) {}
	virtual bool frameEnded (const FrameEvent &evt) {}
};

/** Base class which manages the standard startup of an Ogre application
    based on the ReferenceApplication layer.
    Designed to be subclassed for specific examples if required.
*/
class OgreRefApp
{
public:
    /// Standard constructor
    OgreRefApp()
    {
        mFrameListener = 0;
        mRoot = 0;
		mCamera = 0;
		mSceneMgr = 0;
		mWindow = 0;

		ogRenderer = 0;
		ogResourceProvider = 0;
		ogSystem = 0;
    }
    /// Standard destructor
    virtual ~OgreRefApp()
    {
		destroyOpenGUI();

        if (mFrameListener)
            delete mFrameListener;
        if (mRoot)
            delete mRoot;
    }

    /// Start the example
    virtual void go(void)
    {
		if(!mRoot){
			if (!setup())
				return;
		}

        mRoot->startRendering();
    }

	// These internal methods package up the stages in the startup process
	/** Sets up the application - returns false if the user chooses to abandon configuration. */
	virtual bool setup(void)
	{
		//cannot setup twice
		if(mRoot) return false;

		mRoot = new Root();

		setupResources();

		bool carryOn = configure();
		if (!carryOn) return false;

		chooseSceneManager();
		createCamera();
		createViewports();

		// Set default mipmap level (NB some APIs ignore this)
		TextureManager::getSingleton().setDefaultNumMipmaps(5);

		createOpenGUI(); //this looks like a good spot for OpenGUI to jump in

		// Create any resource listeners (for loading screens)
		createResourceListener();
		// Load resources
		loadResources();

		// Create the scene
		createScene();

		createFrameListener();

		return true;

	}

protected:
    Root *mRoot;
	Camera* mCamera;
    SceneManager* mSceneMgr;
    FrameListener* mFrameListener;
    RenderWindow* mWindow;

	OpenGUI::OgreRenderer* ogRenderer;
	OpenGUI::OgreResourceProvider* ogResourceProvider;
	OpenGUI::System* ogSystem;

    
    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure(void)
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(mRoot->showConfigDialog())
        {
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mWindow = mRoot->initialise(true);
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual void chooseSceneManager(void)
    {
        // Get the SceneManager, in this case a generic one
        mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "RefAppSMInstance");
    }
    virtual void createCamera(void)
    {
        // Create the camera
		mCamera = mSceneMgr->createCamera("PlayerCam");

        // Position it at 500 in Z direction
        mCamera->setPosition(Vector3(0,0,500));
        // Look back along -Z
        mCamera->lookAt(Vector3(0,0,-300));
        mCamera->setNearClipDistance(5);

    }
    virtual void createFrameListener(void)
    {
       // Fill me in if you want a frame listener
    }

	virtual void createScene(void)
	{
		//nothing in the default scene.
	}

    virtual void createViewports(void)
    {
        // Create one viewport, entire window
       Viewport* vp = mWindow->addViewport(mCamera);
       vp->setBackgroundColour(ColourValue(0,0,0));
    }

	virtual void destroyOpenGUI(void)
	{
		if(ogSystem)
			delete ogSystem;
		if(ogResourceProvider)
			delete ogResourceProvider;
		if(ogRenderer)
			delete ogRenderer;
		ogSystem = 0;
		ogResourceProvider = 0;
		ogRenderer = 0;
	}
	virtual void createOpenGUI(void)
	{
		ogRenderer = new OpenGUI::OgreRenderer(mWindow, mSceneMgr);
		ogResourceProvider = new OpenGUI::OgreResourceProvider();
		ogSystem = new OpenGUI::System(ogRenderer, ogResourceProvider);
	}

    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources(void)
    {
        // Load resource paths from config file
        ConfigFile cf;
        cf.load("resources.cfg");

        // Go through all sections & settings in the file
        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
                ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
            }
        }
    }
 
	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener(void)
	{

	}

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources(void)
	{
		// Initialise, parse scripts etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}



};


#endif
