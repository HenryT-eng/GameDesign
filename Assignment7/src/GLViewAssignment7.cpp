#include "GLViewAssignment7.h"

#include "WorldList.h" //This is where we place all of our WOs
#include "ManagerOpenGLState.h" //We can change OpenGL State attributes with this
#include "Axes.h" //We can set Axes to on/off with this
#include "PhysicsEngineODE.h"

//Different WO used by this module
#include "WO.h"
#include "WOStatic.h"
#include "WOStaticPlane.h"
#include "WOStaticTrimesh.h"
#include "WOTrimesh.h"
#include "WOHumanCyborg.h"
#include "WOHumanCal3DPaladin.h"
#include "WOWayPointSpherical.h"
#include "WOLight.h"
#include "WOSkyBox.h"
#include "WOCar1970sBeater.h"
#include "Camera.h"
#include "CameraStandard.h"
#include "CameraChaseActorSmooth.h"
#include "CameraChaseActorAbsNormal.h"
#include "CameraChaseActorRelNormal.h"
#include "Model.h"
#include "ModelDataShared.h"
#include "ModelMesh.h"
#include "ModelMeshDataShared.h"
#include "ModelMeshSkin.h"
#include "WONVStaticPlane.h"
#include "WONVPhysX.h"
#include "WONVDynSphere.h"
#include "WOImGui.h" //GUI Demos also need to #include "AftrImGuiIncludes.h"
#include "AftrImGuiIncludes.h"
#include "AftrGLRendererBase.h"

#include "NetMsgCreateRawWO.h"
#include "NetMessengerClient.h"
#include "NetMsgCreateWO.h"

#include "PxPhysicsAPI.h"
#include "extensions/PxDefaultErrorCallback.h"
#include "extensions/PxDefaultAllocator.h"
#include "common/PxTolerancesScale.h"
#include "foundation/PxTransform.h"
#include "PxRigidActor.h"
#include "foundation/PxPreprocessor.h"
#include "PxForceMode.h"

#include "irrKlang.h"

using namespace Aftr;

GLViewAssignment7* GLViewAssignment7::New( const std::vector< std::string >& args )
{
   GLViewAssignment7* glv = new GLViewAssignment7( args );
   glv->init( Aftr::GRAVITY, Vector( 0, 0, -1.0f ), "aftr.conf", PHYSICS_ENGINE_TYPE::petODE ); //-1.0
   glv->onCreate();
   return glv;
}


GLViewAssignment7::GLViewAssignment7( const std::vector< std::string >& args ) : GLView( args )
{
   //Initialize any member variables that need to be used inside of LoadMap() here.
   //Note: At this point, the Managers are not yet initialized. The Engine initialization
   //occurs immediately after this method returns (see GLViewAssignment7::New() for
   //reference). Then the engine invoke's GLView::loadMap() for this module.
   //After loadMap() returns, GLView::onCreate is finally invoked.

   //The order of execution of a module startup:
   //GLView::New() is invoked:
   //    calls GLView::init()
   //       calls GLView::loadMap() (as well as initializing the engine's Managers)
   //    calls GLView::onCreate()

   //GLViewAssignment7::onCreate() is invoked after this module's LoadMap() is completed.
}


void GLViewAssignment7::onCreate()
{
   //GLViewAssignment7::onCreate() is invoked after this module's LoadMap() is completed.
   //At this point, all the managers are initialized. That is, the engine is fully initialized.

   if( this->pe != NULL )
   {
      //optionally, change gravity direction and magnitude here
      //The user could load these values from the module's aftr.conf
      this->pe->setGravityNormalizedVector( Vector( 0,0,-1.0f ) );//-1.0
      this->pe->setGravityScalar( Aftr::GRAVITY );
   }
   this->setActorChaseType( STANDARDEZNAV ); //Default is STANDARDEZNAV mode
   //this->setNumPhysicsStepsPerRender( 0 ); //pause physics engine on start up; will remain paused till set to 1
}


GLViewAssignment7::~GLViewAssignment7()
{
   //Implicitly calls GLView::~GLView()
}


void GLViewAssignment7::updateWorld()
{
   GLView::updateWorld(); //Just call the parent's update world first.
                          //If you want to add additional functionality, do it after
                          //this call.
   scene -> simulate(0.01); //.01
   //scene -> setGravity(physx::PxVec3(0, 0, -9.81));
   
   physx::PxU32 errorState = 0;
   scene->fetchResults(true);

   //cubepx2->setPosition(Vector(MoveX, MoveY, MoveZ));
   //physx::PxTransform t({ MoveX, MoveY, MoveZ });
   //boxact = p->createRigidDynamic(t);

   cubepx->setPosition(Vector(boxact->getGlobalPose().p.x, boxact->getGlobalPose().p.y, boxact->getGlobalPose().p.z));
   cubepx3->setPosition(Vector(boxact3->getGlobalPose().p.x, boxact3->getGlobalPose().p.y, boxact3->getGlobalPose().p.z));

   cube1->setPosition(Vector(cube1act->getGlobalPose().p.x, cube1act->getGlobalPose().p.y, cube1act->getGlobalPose().p.z));
   cube2->setPosition(Vector(cube2act->getGlobalPose().p.x, cube2act->getGlobalPose().p.y, cube2act->getGlobalPose().p.z));
   cube3->setPosition(Vector(cube3act->getGlobalPose().p.x, cube3act->getGlobalPose().p.y, cube3act->getGlobalPose().p.z));
   cube4->setPosition(Vector(cube4act->getGlobalPose().p.x, cube4act->getGlobalPose().p.y, cube4act->getGlobalPose().p.z));
   cube5->setPosition(Vector(cube5act->getGlobalPose().p.x, cube5act->getGlobalPose().p.y, cube5act->getGlobalPose().p.z));
   cube6->setPosition(Vector(cube6act->getGlobalPose().p.x, cube6act->getGlobalPose().p.y, cube6act->getGlobalPose().p.z));
   //pew->setPosition(Vector(pewact->getGlobalPose().p.x, pewact->getGlobalPose().p.y, pewact->getGlobalPose().p.z));

   engine->setSoundVolume(volumeslider);
   engine->setListenerPosition(vec3df(cam->getPosition().x, cam->getPosition().y, cam->getPosition().z),
       vec3df(cam->getLookDirection().x, cam->getLookDirection().y, cam->getLookDirection().z),
       vec3df(0, 0, 0), vec3df(0, 1, 0));
   
   if (wflag == true) {
       cam->moveInLookDirection();
   }
   else if (sflag == true) {
       cam->moveOppositeLookDirection();
   }
   else if (aflag == true) {
       cam->moveLeft();
   }
   else if (dflag == true) {
       cam->moveRight();
   }
   else if (showaxes == true)
   {
       Axes::isVisible = true;
   }
   else if (showaxes == false)
   {
       Axes::isVisible = false;
   }
}


void GLViewAssignment7::onResizeWindow( GLsizei width, GLsizei height )
{
   GLView::onResizeWindow( width, height ); //call parent's resize method.
}


void GLViewAssignment7::onMouseDown( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseDown( e );
}


void GLViewAssignment7::onMouseUp( const SDL_MouseButtonEvent& e )
{
   GLView::onMouseUp( e );
}


void GLViewAssignment7::onMouseMove( const SDL_MouseMotionEvent& e )
{
   GLView::onMouseMove( e );
}


void GLViewAssignment7::onKeyDown( const SDL_KeyboardEvent& key )
{
   GLView::onKeyDown( key );
   if( key.keysym.sym == SDLK_0 )
      this->setNumPhysicsStepsPerRender( 1 );

   if( key.keysym.sym == SDLK_1 )
   {
       s = engine->play3D("../../../shared/mm/sounds/sound5.wav", vec3df(1, 1, 1), true);
   }
   else if (key.keysym.sym == SDLK_w)
   {
       cam->moveInLookDirection();
       wflag = true;
   }
   else if (key.keysym.sym == SDLK_s)
   {
       cam->moveOppositeLookDirection();
       sflag = true;
   }
   else if (key.keysym.sym == SDLK_a)
   {
       cam->moveLeft();
       aflag = true;
   }
   else if (key.keysym.sym == SDLK_d)
   {
       cam->moveRight();
       dflag = true;
   }
   else if (key.keysym.sym == SDLK_x)
   {
       //spawn cube at camera position forced in look direction
       //std::string shinyRedPlasticCube(ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl");
       //pew = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
       //pew->setPosition(Vector(cam->getPosition().x, cam->getPosition().y, cam->getPosition().z));
       //pew->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
       //pew->setLabel("pew");
       //worldLst->push_back(pew);

       //gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

       //pewpx = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
       //physx::PxTransform t({ cam->getPosition().x,cam->getPosition().y,cam->getPosition().z });
       //pewact = p->createRigidDynamic(t);
       //pewact->attachShape(*pewpx);
       //scene->addActor(*pewact);

       //cube1act->addForce(physx::PxVec3(cam->getLookDirection().x * 10, cam->getLookDirection().y * 10, cam->getLookDirection().z) * 10);
      
       boxact->addForce(physx::PxVec3(0,-50,0));
   }
   else if (key.keysym.sym == SDLK_z)
   {
       boxact->addForce(physx::PxVec3(50, 0, 0));
   }
   else if (key.keysym.sym == SDLK_c)
   {
       boxact->addForce(physx::PxVec3(-50, 0, 0));
   }
   else if (key.keysym.sym == SDLK_v)
   {
       boxact->addForce(physx::PxVec3(0, 0, 50));
   }

   else if (key.keysym.sym == SDLK_o)
   {
       boxact3->addForce(physx::PxVec3(0, -100, 0));
   }
   else if (key.keysym.sym == SDLK_p)
   {
       boxact3->addForce(physx::PxVec3(-100, 0, 0));
   }
   else if (key.keysym.sym == SDLK_i)
   {
       boxact3->addForce(physx::PxVec3(100, 0, 0));
   }
   else if (key.keysym.sym == SDLK_l)
   {
       boxact3->addForce(physx::PxVec3(0, 100, 0));
   }
   else if (key.keysym.sym == SDLK_k)
   {
       boxact3->addForce(physx::PxVec3(0, 0, 50));
   }
}


void GLViewAssignment7::onKeyUp( const SDL_KeyboardEvent& key )
{
   GLView::onKeyUp( key );
   if (key.keysym.sym == SDLK_w)
   {
       wflag = false;
   }
   else if (key.keysym.sym == SDLK_s)
   {
       sflag = false;
   }
   else if (key.keysym.sym == SDLK_a)
   {
       aflag = false;
   }
   else if (key.keysym.sym == SDLK_d)
   {
       dflag = false;
   }
}


void Aftr::GLViewAssignment7::loadMap()
{
    this->worldLst = new WorldList(); //WorldList is a 'smart' vector that is used to store WO*'s
    this->actorLst = new WorldList();
    this->netLst = new WorldList();

    f = PxCreateFoundation(PX_PHYSICS_VERSION, a, e);
    p = PxCreatePhysics(PX_PHYSICS_VERSION, *f, physx::PxTolerancesScale(), true, NULL);
    physx::PxSceneDesc sc(p->getTolerancesScale());
    sc.filterShader = physx::PxDefaultSimulationFilterShader;
    sc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    scene = p->createScene(sc);
    scene->setFlag(physx::PxSceneFlag::eENABLE_ACTIVE_ACTORS, true);

    scene->setGravity(physx::PxVec3(0, 0, -1));

    //client = NetMessengerClient::New("127.0.0.1", "12865");

    ManagerOpenGLState::GL_CLIPPING_PLANE = 1000.0;
    ManagerOpenGLState::GL_NEAR_PLANE = 0.1f;
    ManagerOpenGLState::enableFrustumCulling = false;
    Axes::isVisible = true;
    this->glRenderer->isUsingShadowMapping(false); //set to TRUE to enable shadow mapping, must be using GL 3.2+

    this->cam->setPosition(15, 15, 10);

    std::string shinyRedPlasticCube(ManagerEnvironmentConfiguration::getSMM() + "/models/cube4x4x4redShinyPlastic_pp.wrl");
    std::string wheeledCar(ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl");
    std::string grass(ManagerEnvironmentConfiguration::getSMM() + "/models/grassFloor400x400_pp.wrl");
    std::string human(ManagerEnvironmentConfiguration::getSMM() + "/models/human_chest.wrl");

    //SkyBox Textures readily available
    std::vector< std::string > skyBoxImageNames; //vector to store texture paths
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_water+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_dust+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_mountains+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_winter+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/early_morning+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_afternoon+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_cloudy3+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_day2+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_deepsun+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_evening+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_morning2+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_noon+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/sky_warp+6.jpg" );
    skyBoxImageNames.push_back(ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_Hubble_Nebula+6.jpg");
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_gray_matter+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_easter+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_hot_nebula+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_ice_field+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_lemon_lime+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_milk_chocolate+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_solar_bloom+6.jpg" );
    //skyBoxImageNames.push_back( ManagerEnvironmentConfiguration::getSMM() + "/images/skyboxes/space_thick_rb+6.jpg" );

    {
        //Create a light
        float ga = 0.1f; //Global Ambient Light level for this module
        ManagerLight::setGlobalAmbientLight(aftrColor4f(ga, ga, ga, 1.0f));
        WOLight* light = WOLight::New();
        light->isDirectionalLight(true);
        light->setPosition(Vector(0, 0, 100));
        //Set the light's display matrix such that it casts light in a direction parallel to the -z axis (ie, downwards as though it was "high noon")
        //for shadow mapping to work, this->glRenderer->isUsingShadowMapping( true ), must be invoked.
        light->getModel()->setDisplayMatrix(Mat4::rotateIdentityMat({ 0, 1, 0 }, 90.0f * Aftr::DEGtoRAD));
        light->setLabel("Light");
        worldLst->push_back(light);
    }

    {
        //Create the SkyBox
        WO* wo = WOSkyBox::New(skyBoxImageNames.at(0), this->getCameraPtrPtr());
        wo->setPosition(Vector(0, 0, 0));
        wo->setLabel("Sky Box");
        wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        worldLst->push_back(wo);
    }

    {
        ////Create the infinite grass plane (the floor)
        WO* wo = WO::New(grass, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        wo->setPosition(Vector(0, 0, 0));
        wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        wo->upon_async_model_loaded([wo]()
            {
                ModelMeshSkin& grassSkin = wo->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0);
        grassSkin.getMultiTextureSet().at(0).setTexRepeats(5.0f);
        grassSkin.setAmbient(aftrColor4f(0.4f, 0.4f, 0.4f, 1.0f)); //Color of object when it is not in any light
        grassSkin.setDiffuse(aftrColor4f(1.0f, 1.0f, 1.0f, 1.0f)); //Diffuse color components (ie, matte shading color of this object)
        grassSkin.setSpecular(aftrColor4f(0.4f, 0.4f, 0.4f, 1.0f)); //Specular color component (ie, how "shiney" it is)
        grassSkin.setSpecularCoefficient(10); // How "sharp" are the specular highlights (bigger is sharper, 1000 is very sharp, 10 is very dull)
            });
        wo->setLabel("Grass");
        worldLst->push_back(wo);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);
        //physx::PxActor* groundPlane = PxCreatePlane(*p, physx::PxPlane(0, 0, 1, 0), *gMaterial);
        physx::PxRigidStatic* groundPlane = PxCreatePlane(*p, physx::PxPlane(0, 0, 1, 0), *gMaterial);//good for the grass
        scene->addActor(*groundPlane);

    }

    {
        cubepx = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        //cubepx->setPosition(Vector(0, 0, 40));
        cubepx->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cubepx->setLabel("cubepx");
        worldLst->push_back(cubepx);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        boxpx = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ 17.5,18,4 });
        boxact = p->createRigidDynamic(t);
        boxact->attachShape(*boxpx);
        scene->addActor(*boxact);
    }
    {
        cubepx3 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        //cubepx->setPosition(Vector(0, 0, 40));
        cubepx3->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cubepx3->setLabel("cubepx3");
        worldLst->push_back(cubepx3);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        boxpx3 = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ -20,8,4 });
        boxact3 = p->createRigidDynamic(t);
        boxact3->attachShape(*boxpx3);
        scene->addActor(*boxact3);
    }
    //-----------------------------------------

    {
        cubepx2 = WO::New(shinyRedPlasticCube, Vector(1, 1, 5), MESH_SHADING_TYPE::mstFLAT);
        cubepx2->setPosition(Vector(-20, -20, 5));
        cubepx2->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cubepx2->setLabel("cubepx2");
        worldLst->push_back(cubepx2);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        boxpx2 = p->createShape(physx::PxBoxGeometry(2, 2, 10), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ -20,-20,5 });
        boxact2 = p->createRigidStatic(t);
        boxact2->attachShape(*boxpx2);
        scene->addActor(*boxact2);
    }

    {
        cube1 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        cube1->setPosition(Vector(20, 2, 6));
        cube1->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cube1->setLabel("cube1");
        worldLst->push_back(cube1);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        cube1px = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ 20,2,6 });
        cube1act = p->createRigidDynamic(t);
        cube1act->attachShape(*cube1px);
        scene->addActor(*cube1act);
    }
    {
        cube2 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        cube2->setPosition(Vector(15, 2, 6));
        cube2->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cube2->setLabel("cube2");
        worldLst->push_back(cube2);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        cube2px = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ 15,2,6 });
        cube2act = p->createRigidDynamic(t);
        cube2act->attachShape(*cube2px);
        scene->addActor(*cube2act);
    }
    {
        cube3 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        cube3->setPosition(Vector(17.5, 2, 10));
        cube3->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cube3->setLabel("cube3");
        worldLst->push_back(cube3);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        cube3px = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ 17.5,2,10 });
        cube3act = p->createRigidDynamic(t);
        cube3act->attachShape(*cube3px);
        scene->addActor(*cube3act);
    }
    {
        cube4 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        cube4->setPosition(Vector(12.5, 2, 2));
        cube4->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cube4->setLabel("cube4");
        worldLst->push_back(cube4);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        cube4px = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ 12.5,2,2 });
        cube4act = p->createRigidDynamic(t);
        cube4act->attachShape(*cube4px);
        scene->addActor(*cube4act);
    }
    {
        cube5 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        cube5->setPosition(Vector(17.5, 2, 2));
        cube5->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cube5->setLabel("cube5");
        worldLst->push_back(cube5);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        cube5px = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ 17.5,2,2 });
        cube5act = p->createRigidDynamic(t);
        cube5act->attachShape(*cube5px);
        scene->addActor(*cube5act);
    }
    {
        cube6 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
        cube6->setPosition(Vector(22.5, 2, 2));
        cube6->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
        cube6->setLabel("cube6");
        worldLst->push_back(cube6);

        gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

        cube6px = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
        physx::PxTransform t({ 22.5,2,2 });
        cube6act = p->createRigidDynamic(t);
        cube6act->attachShape(*cube6px);
        scene->addActor(*cube6act);
    }

   //{
   //    cubepx3 = WO::New(shinyRedPlasticCube, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
   //    cubepx3->setPosition(Vector(0, 0, 30));
   //    cubepx3->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //    cubepx3->setLabel("cubepx3");
   //    worldLst->push_back(cubepx3);

   //    gMaterial = p->createMaterial(0.5f, 0.5f, 0.6f);

   //    boxpx3 = p->createShape(physx::PxBoxGeometry(2, 2, 2), *gMaterial);//good for the shiny red plastic cube
   //    physx::PxTransform t({ 0,0,20 });
   //    boxact3 = p->createRigidDynamic(t);
   //    boxact3->attachShape(*boxpx3);
   //    scene->addActor(*boxact3);
   //}

   //{
   //   //Create the infinite grass plane that uses the Open Dynamics Engine (ODE)
   //   WO* wo = WOStatic::New( grass, Vector(1,1,1), MESH_SHADING_TYPE::mstFLAT );
   //   ((WOStatic*)wo)->setODEPrimType( ODE_PRIM_TYPE::PLANE );
   //   wo->setPosition( Vector(0,0,0) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->getModel()->getModelDataShared()->getModelMeshes().at(0)->getSkins().at(0).getMultiTextureSet().at(0)->setTextureRepeats( 5.0f );
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   //Create the infinite grass plane that uses NVIDIAPhysX(the floor)
   //   WO* wo = WONVStaticPlane::New( grass, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
   //   wo->setPosition( Vector( 0, 0, 0 ) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->getModel()->getModelDataShared()->getModelMeshes().at( 0 )->getSkins().at( 0 ).getMultiTextureSet().at( 0 )->setTextureRepeats( 5.0f );
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   //Create the infinite grass plane (the floor)
   //   WO* wo = WONVPhysX::New( shinyRedPlasticCube, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
   //   wo->setPosition( Vector( 0, 0, 50.0f ) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   WO* wo = WONVPhysX::New( shinyRedPlasticCube, Vector( 1, 1, 1 ), MESH_SHADING_TYPE::mstFLAT );
   //   wo->setPosition( Vector( 0, 0.5f, 75.0f ) );
   //   wo->renderOrderType = RENDER_ORDER_TYPE::roOPAQUE;
   //   wo->setLabel( "Grass" );
   //   worldLst->push_back( wo );
   //}

   //{
   //   WO* wo = WONVDynSphere::New( ManagerEnvironmentConfiguration::getVariableValue( "sharedmultimediapath" ) + "/models/sphereRp5.wrl", Vector( 1.0f, 1.0f, 1.0f ), mstSMOOTH );
   //   wo->setPosition( 0, 0, 100.0f );
   //   wo->setLabel( "Sphere" );
   //   this->worldLst->push_back( wo );
   //}

   //{
   //   WO* wo = WOHumanCal3DPaladin::New( Vector( .5, 1, 1 ), 100 );
   //   ((WOHumanCal3DPaladin*)wo)->rayIsDrawn = false; //hide the "leg ray"
   //   ((WOHumanCal3DPaladin*)wo)->isVisible = false; //hide the Bounding Shell
   //   wo->setPosition( Vector( 20, 20, 20 ) );
   //   wo->setLabel( "Paladin" );
   //   worldLst->push_back( wo );
   //   actorLst->push_back( wo );
   //   netLst->push_back( wo );
   //   this->setActor( wo );
   //}
   //
   //{
   //   WO* wo = WOHumanCyborg::New( Vector( .5, 1.25, 1 ), 100 );
   //   wo->setPosition( Vector( 20, 10, 20 ) );
   //   wo->isVisible = false; //hide the WOHuman's bounding box
   //   ((WOHuman*)wo)->rayIsDrawn = false; //show the 'leg' ray
   //   wo->setLabel( "Human Cyborg" );
   //   worldLst->push_back( wo );
   //   actorLst->push_back( wo ); //Push the WOHuman as an actor
   //   netLst->push_back( wo );
   //   this->setActor( wo ); //Start module where human is the actor
   //}

   //{
   //   //Create and insert the WOWheeledVehicle
   //   std::vector< std::string > wheels;
   //   std::string wheelStr( "../../../shared/mm/models/WOCar1970sBeaterTire.wrl" );
   //   wheels.push_back( wheelStr );
   //   wheels.push_back( wheelStr );
   //   wheels.push_back( wheelStr );
   //   wheels.push_back( wheelStr );
   //   WO* wo = WOCar1970sBeater::New( "../../../shared/mm/models/WOCar1970sBeater.wrl", wheels );
   //   wo->setPosition( Vector( 5, -15, 20 ) );
   //   wo->setLabel( "Car 1970s Beater" );
   //   ((WOODE*)wo)->mass = 200;
   //   worldLst->push_back( wo );
   //   actorLst->push_back( wo );
   //   this->setActor( wo );
   //   netLst->push_back( wo );
   //}
   
   //Make a Dear Im Gui instance via the WOImGui in the engine... This calls
   //the default Dear ImGui demo that shows all the features... To create your own,
   //inherit from WOImGui and override WOImGui::drawImGui_for_this_frame(...) (among any others you need).
   WOImGui* gui = WOImGui::New( nullptr );
   gui->setLabel( "My Gui" );
   gui->subscribe_drawImGuiWidget(
      [this, gui]() //this is a lambda, the capture clause is in [], the input argument list is in (), and the body is in {}
      {
         //ImGui::ShowDemoWindow(); //Displays the default ImGui demo from C:/repos/aburn/engine/src/imgui_implot/implot_demo.cpp
         //WOImGui::draw_AftrImGui_Demo( gui ); //Displays a small Aftr Demo from C:/repos/aburn/engine/src/aftr/WOImGui.cpp
         //ImPlot::ShowDemoWindow(); //Displays the ImPlot demo using ImGui from C:/repos/aburn/engine/src/imgui_implot/implot_demo.cpp
         ImGui::Begin("Control");
         ImGui::Text("Translation");
         ImGui::SliderFloat("Move X", &MoveX, 0.0f, 50.0f);//takes a float and bounds
         ImGui::SliderFloat("Move Y", &MoveY, 0.0f, 50.0f);//takes a float and bounds
         ImGui::SliderFloat("Move Z", &MoveZ, 0.0f, 50.0f);//takes a float and bounds
         ImGui::Text("Sound Control");
         ImGui::SliderFloat("Volume", &volumeslider, 0.0f, 1.0f);
         //ImGui::Checkbox("Mute", &mutesound);
         ImGui::Separator();
         ImGui::Checkbox("Show Axes", &showaxes);
         ImGui::End();
       } );
   this->worldLst->push_back( gui );

   createAssignment7WayPoints();
}


void GLViewAssignment7::createAssignment7WayPoints()
{
   // Create a waypoint with a radius of 3, a frequency of 5 seconds, activated by GLView's camera, and is visible.
   WayPointParametersBase params(this);
   params.frequency = 5000;
   params.useCamera = true;
   params.visible = true;
   WOWayPointSpherical* wayPt = WOWayPointSpherical::New( params, 3 );
   wayPt->setPosition( Vector( 50, 0, 3 ) );
   worldLst->push_back( wayPt );
}
