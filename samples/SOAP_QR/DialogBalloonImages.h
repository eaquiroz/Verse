#ifndef UI_DialogBallonImages_h
#define UI_DialogBallonImages_h

#include <Core/DisplayObject.h>
#include <UI/DialogBalloon.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include <UI/Draw2D.h>
#include <UI/FreeType.h>
#include <UI/TextField.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>


class DialogBalloonImages : public UI::DialogBalloon {
    public:
        DialogBalloonImages(freetype::font_data* f, freetype::font_data* ftext);
        void draw(int selection=0);

};

#endif
