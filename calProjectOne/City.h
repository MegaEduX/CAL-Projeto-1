//
//  City.h
//  CAL Project One
//
//  MIEIC 2013/2014
//  Eduardo Almeida, Joao Almeida and Joao de Figueiredo
//

#ifndef calProjectOne_City_h
#define calProjectOne_City_h

#include "Coordinate.h"

static int NOT_CALCULATED = -1;

class City {
    std::string _name;
    
    Coordinate _coordinates;
    
    bool _healthCenter = false;
    
    bool _needsHealthCenter = true;
    
    //  Step One Variables
    
    double _viableCount;
    
    //  Step Two Variables
    
    double _population;
    
    double _maxPopulationServed = NOT_CALCULATED;
    
public:
    City(std::string name, Coordinate crd, int popl = -1) : _name(name), _coordinates(crd), _population(popl) {}
    
    std::string getName() {
        return _name;
    }
    
    Coordinate getCoordinates() {
        return _coordinates;
    }
    
    double distanceTo(const City &city) const {
        return _coordinates.distanceTo(city._coordinates);
    }
    
    void setContainsHealthCenter(bool contains) {
        _healthCenter = contains;
    }
    
    bool getContainsHealthCenter() {
        return _healthCenter;
    }
    
    void setNeedsHealthCenter(bool needs) {
        _needsHealthCenter = needs;
    }
    
    bool getNeedsHealthCenter() {
        return _needsHealthCenter;
    }
    
    void setHealthCenterViableCount(double count) {
        _viableCount = count;
    }
    
    double getHealthCareViableCount() {
        return _viableCount;
    }
    
    void setPopulation(int pop) {
        _population = pop;
    }
    
    int getPopulation() {
        return _population;
    }
    
    void setMaxPopulationServed(int maxPop) {
        _maxPopulationServed = maxPop;
    }
    
    int getMaxPopulationServed() {
        return _maxPopulationServed;
    }
    
    bool operator==(const City &cmp) const {
        return (_name == cmp._name && _coordinates == cmp._coordinates);
    }
};

#endif
