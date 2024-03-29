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
class Moon : public CelestialBody
{
    string orbitingPlanet;

public:
    void setMoon(string _name, long double _mass, long double _radius, long double _x, long double _y, long double _z, string _orbitingPlanet)
        {
            setCelestialBody(_name, _mass, _radius, _x, _y, _z);
            orbitingPlanet=_orbitingPlanet; 
        }

    void displayInfo() override
    {
        CelestialBody::displayInfo();
        cout << "Orbiting planet: " << orbitingPlanet << endl;
    }
};
int main()
{
    fstream f;
    Moon m1, m2, m3, m4, m5;
    m1.setMoon("Luna", 7.35e22, 1737.5, 0, 0, 0, "Earth");
    m2.setMoon("Phobos", 1.08e16, 11.2667, 0, 0, 0, "Mars");
    m3.setMoon("Io", 8.9319e22, 1821.6, 0, 0, 0, "Jupiter");
    m4.setMoon("Europa", 4.8e22, 1560.8, 0, 0, 0, "Jupiter");
    m5.setMoon("Titan", 1.3452e23, 2575, 0, 0, 0, "Saturn");
    f.open("moon.txt",ios::out|ios::binary);
    f.write((char *)&m1,sizeof(m1));
    f.write((char *)&m2,sizeof(m2));
    f.write((char *)&m3,sizeof(m3));
    f.write((char *)&m4,sizeof(m4));
    f.write((char *)&m5,sizeof(m5));
    f.close();
    Moon m;
    f.open("moon.txt",ios::in|ios::binary);
    while(f.read((char *)&m,sizeof(m))){
        m.displayInfo();
    }
    f.close();
}