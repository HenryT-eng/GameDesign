#pragma once

#include "GLView.h"

#include "NetMsgCreateRawWO.h"
#include "NetMessengerClient.h"
#include "NetMsgCreateWO.h"

#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultErrorCallback.h"
#include "extensions/PxDefaultAllocator.h"
#include "common/PxTolerancesScale.h"
#include "PxRigidActor.h"
#include "PxRigidActor.h"

#include "irrKlang.h"

using namespace irrklang;

namespace Aftr
{
   class Camera;

/**
   \class GLViewAssignment7
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewAssignment7 : public GLView
{
public:
   static GLViewAssignment7* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewAssignment7();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createAssignment7WayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );

   bool wflag = false;
   bool sflag = false;
   bool aflag = false;
   bool dflag = false;

   float MoveX = 0.0;
   float MoveY = 0.0;
   float MoveZ = 0.0;



   bool showaxes = true;

   float volumeslider = 0.0;
   bool mutesound = false;

   ISoundEngine* engine = createIrrKlangDevice();
   ISound* s;

   //NetMessengerClient* client;
   WO* cube1;
   physx::PxShape* cube1px = nullptr;
   physx::PxRigidDynamic* cube1act;

   WO* cube2;
   physx::PxShape* cube2px = nullptr;
   physx::PxRigidDynamic* cube2act;

   WO* cube3;
   physx::PxShape* cube3px = nullptr;
   physx::PxRigidDynamic* cube3act;

   WO* cube4;
   physx::PxShape* cube4px = nullptr;
   physx::PxRigidDynamic* cube4act;

   WO* cube5;
   physx::PxShape* cube5px = nullptr;
   physx::PxRigidDynamic* cube5act;

   WO* cube6;
   physx::PxShape* cube6px = nullptr;
   physx::PxRigidDynamic* cube6act;

   //---------------------------------

   WO* cubepx;
   physx::PxShape* boxpx = nullptr;
   physx::PxRigidDynamic* boxact;

   WO* cubepx2;
   physx::PxShape* boxpx2 = nullptr;
   physx::PxRigidStatic* boxact2;

   WO* cubepx3;
   physx::PxShape* boxpx3 = nullptr;
   physx::PxRigidDynamic* boxact3;
   
   WO* pew;
   physx::PxShape* pewpx = nullptr;
   physx::PxRigidDynamic* pewact;

   physx::PxDefaultAllocator a;
   physx::PxDefaultErrorCallback e;
   physx::PxFoundation* f;// = PxCreateFoundation(PX_PHYSICS_VERSION, a, e);
   physx::PxPhysics* p;// = PxCreatePhysics(PX_PHYSICS_VERSION, *f, physx::PxTolerancesScale(), true, NULL);
   //physx::PxSceneDesc sc(p -> getTolerancesScale());
   physx::PxScene* scene; //  = p->createScene(sc);
   //scene -> setFlag(physx::PxSceneFlag::eENABLE_ACTIVE_ACTORS, true);

   physx::PxMaterial* gMaterial;


protected:
   GLViewAssignment7( const std::vector< std::string >& args );
   virtual void onCreate();   

};

/** \} */

} //namespace Aftr
