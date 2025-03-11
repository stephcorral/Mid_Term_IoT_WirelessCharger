#ifndef _NEOPIXELS_H
#define _NEOPIXELS_H

#

class Neopixels{

    int _neopixels;
    bool _sleepingColor;
    bool _chargingColor;

    public:
        Neopixels(int neopixels){
            _neopixels = neopixels;
            pinMode(D2, OUTPUT);
        }

        

        
        

};

#endif