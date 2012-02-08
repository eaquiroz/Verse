/* 
 * File:   QREvent.h
 * Author: damiles
 *
 * Created on 8 de febrero de 2012, 19:47
 */

#ifndef QREVENT_H
#define	QREVENT_H

#include "Event.h"
#include <string>

namespace Events {

class QREvent : public Event  {
public:
    QREvent();
    std::string data;
    float x,y;
    static const std::string QR_DETECTED;
    static const std::string QR_NO_DETECTED;
    
private:

};
}
#endif	/* QREVENT_H */

