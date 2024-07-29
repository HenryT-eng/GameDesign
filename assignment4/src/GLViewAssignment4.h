#pragma once
#include "irrKlang.h"
#include "GLView.h"

using namespace irrklang;

namespace Aftr
{
   class Camera;

/**
   \class GLViewAssignment4
   \author Scott Nykl 
   \brief A child of an abstract GLView. This class is the top-most manager of the module.

   Read \see GLView for important constructor and init information.

   \see GLView

    \{
*/

class GLViewAssignment4 : public GLView
{
public:
   static GLViewAssignment4* New( const std::vector< std::string >& outArgs );
   virtual ~GLViewAssignment4();
   virtual void updateWorld(); ///< Called once per frame
   virtual void loadMap(); ///< Called once at startup to build this module's scene
   virtual void createAssignment4WayPoints();
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
   bool showaxes = true;

   float volumeslider = 0.0;
   bool mutesound = false;

   ISoundEngine* engine = createIrrKlangDevice();
   ISound* s;


protected:
   GLViewAssignment4( const std::vector< std::string >& args );
   virtual void onCreate();   
};

/** \} */

} //namespace Aftr
