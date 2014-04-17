//
//  Coordinate.h
//  CAL Project One
//
//  MIEIC 2013/2014
//  Eduardo Almeida, Joao Almeida and Joao de Figueiredo
//

#ifndef calProjectOne_Coordinate_h
#define calProjectOne_Coordinate_h

#include <math.h>

static double degreesToRadians = 0.0174532925;

class Coordinate {
    double _latitude;
    double _longitude;
    
public:
    Coordinate(double lat, double lng) : _latitude(lat), _longitude(lng) {}
    
    bool operator==(const Coordinate &cmp) const {
        return (_latitude == cmp._latitude && _longitude == cmp._longitude);
    }
    
    double getLatitude() {
        return _latitude;
    }
    
    double getLongitude() {
        return _longitude;
    }
    
    double distanceTo(const Coordinate &crd) const {
        double dlong = (crd._longitude - _longitude) * degreesToRadians;
        double dlat = (crd._latitude - _latitude) * degreesToRadians;
        double a = pow(sin(dlat/2.0), 2) + cos(_latitude * degreesToRadians) * cos(crd._latitude * degreesToRadians) * pow(sin(dlong/2.0), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        double d = 6367 * c;
        
        return d;
    }
};

#endif
