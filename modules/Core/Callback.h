#ifndef Core_Callback_h
#define Core_Callback_h

#include <iostream>

#include <Events/Event.h>

namespace Core {


class Callback
{
    public:
        virtual void Execute(Events::Event *Param) const =0;
};


template <class cInstance>
class TCallback : public Callback
{
    public:
        TCallback()    // constructor
        {
            pFunction = 0;
        }

        typedef void (cInstance::*tFunction)(Events::Event *Param);
        
        virtual void Execute(Events::Event *Param) const 
        {
            if (pFunction) (cInst->*pFunction)(Param);
            else std::cout << "ERROR : the callback function has not been defined !!!!";
        }

        void SetCallback (cInstance  *cInstancePointer, 
                          tFunction   pFunctionPointer)
        {
            cInst     = cInstancePointer;
            pFunction = pFunctionPointer;
        }

    private:
        cInstance  *cInst;
        tFunction  pFunction;
};

}
#endif;
