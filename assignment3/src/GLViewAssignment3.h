#pragma once

#include "GLView.h"

namespace Aftr
{
   class Camera;

/**
   \class GLViewAssignment3
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewAssignment3 : public GLView
{
public:
   static GLViewAssignment3* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewAssignment3();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createAssignment3WayPoints();
   virtual void onResizeWindow( GLsizei width, GLsizei height );
   virtual void onMouseDown( const SDL_MouseButtonEvent& e );
   virtual void onMouseUp( const SDL_MouseButtonEvent& e );
   virtual void onMouseMove( const SDL_MouseMotionEvent& e );
   virtual void onKeyDown( const SDL_KeyboardEvent& key );
   virtual void onKeyUp( const SDL_KeyboardEvent& key );

   WO* cube; 

   float LocalX = 0.0;
   float LocalY = 0.0;
   float LocalZ = 0.0;
   float GlobalX = 0.0;
   float GlobalY = 0.0;
   float GlobalZ = 0.0;
   float MoveX = 0.0;
   float MoveY = 0.0;
   float MoveZ = 0.0;

   bool nightmode = false;



protected:
   GLViewAssignment3( const std::vector< std::string >& args );
   virtual void onCreate();   
};

/** \} */

} //namespace Aftr
