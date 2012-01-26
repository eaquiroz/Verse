/* 
 * File:   GLBaseApp.h
 * Author: damiles
 *
 * Created on 23 de enero de 2012, 21:40
 */

#ifndef GLBASEAPP_H
#define	GLBASEAPP_H

#include <Core/DisplayObject.h>
#include <Events/MouseEvent.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


namespace UI {

class GLBaseApp: public Core::DisplayObject  {
public:
    GLBaseApp();
    GLBaseApp(const GLBaseApp& orig);
    virtual ~GLBaseApp();
    void render();
    void selection(Events::MouseEvent e);

private:
    
};
}
#endif	/* GLBASEAPP_H */

