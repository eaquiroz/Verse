#ifndef _SerialDevice_h
#define _SerialDevice_h

namespace Devices {

    class SerialDevice : public Device {
                    
    public:
        
        /* Constructor */
        Serial (std::string baudrate, std::string port);
        
        /* read from the serial stream to the data char pointer, each block of data is of (size) size and 
         there are (count) block of data to read. Method returns the number of byte read in total.*/
        int read (char *data, int size, int count) throw (int);
        
        /* Write to the serial stream with data from the char pointer, each block of data is of (size) size and 
         there are (count) block of data to write. The methods return the number of bytes written */
        int write (char *data, int size, int count) throw (int);
                        
    private:
        /* rx and tx stream */
        std::iostream *rx;
        std::iostream *tx;
        
        std::string baudrate;
        std::string port;
        
    }
    
}


#endif
