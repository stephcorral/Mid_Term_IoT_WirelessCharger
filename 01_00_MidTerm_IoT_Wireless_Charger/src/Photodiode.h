#ifndef _PHOTODIODE_H_
#define _PHOTODIODE_H_

class Photodiode{

    int _photodiode;
    bool _isOn;

    public:
        Photodiode(int photodiode){
            _photodiode = photodiode;
            pinMode(_photodiode, INPUT);
            
        }

        int inputValue(){
            return analogRead(_photodiode);
        }

        bool isOn(){
            if(analogRead(_photodiode)<3900){
                //photodiode is in the dark meaning something is covering the light that is going into it
                return _isOn = TRUE;
            }
            //photodiode is not being covered
            return _isOn = FALSE;

        }


};

#endif