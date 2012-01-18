#ifndef Utils_UrlLoader_h
#define Utils_UrlLoader_h

#include <Core/EventDispatcher.h>



namespace Utils {

class UrlLoader : public Core::EventDispatcher {

 public:

    virtual int loadString(void  url);

 public:
    int dataFormat;
    int data;
};

} /* End of namespace Utils */

#endif // Utils_UrlLoader_h
