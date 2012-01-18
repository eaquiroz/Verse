#ifndef Core_DisplayObject_h
#define Core_DisplayObject_h

#include "EventDispatcher.h"
#include <Devices/Platform.h>

#include <vector>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace Core {

class DisplayObject : public EventDispatcher {

 public:
	DisplayObject(Devices::Platform *p);
    virtual int hitTestObject();
    virtual int hitTestPoint();
    virtual void draw();
    void render();
	void addChild(DisplayObject *object);
	void removeChild(DisplayObject *object);
	void setOrthographicProjection();
  	void restorePerspectiveProjection();
	void setBackgroundColor(int r, int g, int b);
	void setColor(int r, int g, int b);
 public:
    int visible;
    int x;
    int y;
    int width;
    int height;
    int z;
    int scalex;
    int scaley;
    int scalez;
    int rotationx;
    int rotationy;
    int rotationz;
    int rotion;
    float red,green, blue;
    float fred,fgreen, fblue;
    int alpha;
    int blendMode;
    Devices::Platform* platform;
    
  private:
  	std::vector<DisplayObject*> childs;
};

} /* End of namespace Core */

#endif // Core_DisplayObject_h
