#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

class CelestialBody
{
protected:
    string name;
    long double mass;
    long double radius;
    long double x, y, z;

public:
    void setCelestialBody(string _name, long double _mass, long double _radius, long double _x, long double _y, long double _z)
    {
        name = _name;
        mass = _mass;
        radius = _radius;
        x = _x;
        y = _y;
        z = _z;
    }

    virtual void displayInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Mass: " << mass << " kg" << endl;
        cout << "Radius: " << radius << " km" << endl;
        cout << "Coordinates (x, y, z): (" << x << ", " << y << ", " << z << ")" << endl;
    }

    long double getX() const
    {
        return x;
    }
    long double getY() const
    {
        return y;
    }
    long double getZ() const
    {
        return z;
    }
    friend class Spaceship;
};
class Planet : public CelestialBody
{
    long double distanceFromStar;

public:
    void setPlanet(string _name, long double _mass, long double _radius, long double _x, long double _y, long double _z, long double _distanceFromStar)
        {
            setCelestialBody(_name, _mass, _radius, _x, _y, _z);
            distanceFromStar=_distanceFromStar;
        }

    void displayInfo() override
    {
        CelestialBody::displayInfo();
        cout << "Distance from star: " << distanceFromStar << " AU" << endl;
    }
    
};
int main()
{
    fstream f;
    Planet p1, p2, p3, p4, p5;
    p1.setPlanet("Mercury", 3.285e23, 2439.7, 0, 0, 0, 0.39);
    p2.setPlanet("Venus", 4.867e24, 6051.8, 0, 0, 0, 0.72);
    p3.setPlanet("Earth", 5.972e24, 6371, 0, 0, 0, 1);
    p4.setPlanet("Mars", 6.39e23, 3389.5, 0, 0, 0, 1.52);
    p5.setPlanet("Jupiter", 1.898e27, 69911, 0, 0, 0, 5.2);
    f.open("planet.txt",ios::out|ios::binary);
    f.write((char *)&p1,sizeof(p1));
    f.write((char *)&p2,sizeof(p2));
    f.write((char *)&p3,sizeof(p3));
    f.write((char *)&p4,sizeof(p4));
    f.write((char *)&p5,sizeof(p5));
    f.close();
    f.open("planet.txt",ios::in|ios::binary);
    Planet p;
    while(f.read((char *)&p,sizeof(p)))
    {
        p.displayInfo();
    }
    f.close();
}