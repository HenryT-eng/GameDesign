#pragma once
#include "NetMsgCreateRawWO.h"
#include "GLView.h"

namespace Aftr
{
   class Camera;

   class NetMessengerClient;

/**
   \class GLViewAssignment6
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewAssignment6 : public GLView
{
public:
   static GLViewAssignment6* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewAssignment6();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createAssignment6WayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );

   NetMessengerClient* client;

   WO* cube;

   float MoveX = 0.0;
   float MoveY = 0.0;
   float MoveZ = 0.0;

protected:
   GLViewAssignment6( const std::vector< std::string >& args );
   virtual void onCreate();   
};

/** \} */

} //namespace Aftr
