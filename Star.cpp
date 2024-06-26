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
class Star : public CelestialBody
{
    string type;

public:
    Star() {}
    void setStar(string _name, long double _mass, long double _radius, long double _x, long double _y, long double _z, string _type)
    {
        setCelestialBody(_name, _mass, _radius, _x, _y, _z);
        type = _type;
    }

    void displayInfo() override
    {
        CelestialBody::displayInfo();
        cout << "Type: " << type << endl;
    }
};
int main()
{
    fstream f;
    Star s1, s2, s3, s4, s5;
    s1.setStar("Sun", 1.989e30, 696340, 0, 0, 0, "G-type main-sequence star");
    s2.setStar("Sirius", 2.063e30, 1.711e6, 8.6, 0, 0, "A-type main-sequence star");
    s3.setStar("Betelgeuse", 7.7e31, 9.04e5, 0, 0, 643, "Red supergiant");
    s4.setStar("Vega", 2.1e30, 2.17e6, -7.6, 0, 0, "A-type main-sequence star");
    s5.setStar("Rigel", 2.5e31, 7.6e5, 0, 0, -860, "Blue supergiant");
    f.open("star.txt", ios::out|ios::binary);
    f.write((char *)&s1, sizeof(s1));
    f.write((char *)&s2, sizeof(s2));
    f.write((char *)&s3, sizeof(s3));
    f.write((char *)&s4, sizeof(s4));
    f.write((char *)&s5, sizeof(s5));
    f.close();
    Star p;
    f.open("star.txt", ios::in|ios::binary);
    while (f.read((char *)(&p), sizeof(Star)))
    {
        p.displayInfo();
    }
    f.close();
}