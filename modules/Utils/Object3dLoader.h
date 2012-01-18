#ifndef Utils_Object3dLoader_h
#define Utils_Object3dLoader_h

#include <Core/EventDispatcher.h>



namespace Utils {

class Object3dLoader : public Core::EventDispatcher {

 public:

    virtual int loadObject();
};

} /* End of namespace Utils */

#endif // Utils_Object3dLoader_h
