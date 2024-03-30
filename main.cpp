#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

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
        cout << "-------------------------------------------------------------\n";
        cout << "Name                   : " << name << endl;
        cout << "Mass                   : " << mass << " kg" << endl;
        cout << "Radius                 : " << radius << " km" << endl;
        cout << "Coordinates (x, y, z)  : (" << x << ", " << y << ", " << z << ")" << endl;
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
        cout << "Type                   : " << type << endl;
    }
};
class Planet : public CelestialBody
{
    long double distanceFromStar;

public:
    void setPlanet(string _name, long double _mass, long double _radius, long double _x, long double _y, long double _z, long double _distanceFromStar)
    {
        setCelestialBody(_name, _mass, _radius, _x, _y, _z);
        distanceFromStar = _distanceFromStar;
    }

    void displayInfo() override
    {
        CelestialBody::displayInfo();
        cout << "Distance from star     : " << distanceFromStar << " AU" << endl;
    }
};

class Moon : public CelestialBody
{
    string orbitingPlanet;

public:
    void setMoon(string _name, long double _mass, long double _radius, long double _x, long double _y, long double _z, string _orbitingPlanet)
    {
        setCelestialBody(_name, _mass, _radius, _x, _y, _z);
        orbitingPlanet = _orbitingPlanet;
    }

    void displayInfo() override
    {
        CelestialBody::displayInfo();
        cout << "Orbiting planet        : " << orbitingPlanet << endl;
    }
};

long double calculateDistance(const CelestialBody &body1, const CelestialBody &body2)
{
    long double distance = sqrt(pow(body2.getX() - body1.getX(), 2) +
                                pow(body2.getY() - body1.getY(), 2) +
                                pow(body2.getZ() - body1.getZ(), 2));
    return distance;
}

class Spaceship
{
    int fuel;
    CelestialBody currentPlanet;
    long double speed;

public:
    friend long double calculateDistance(const CelestialBody &body1, const CelestialBody &body2);

    Spaceship(int _fuel, const CelestialBody &_currentPlanet, long double _speed)
        : fuel(_fuel), currentPlanet(_currentPlanet), speed(_speed) {}

    int getFuel() const
    {
        return fuel;
    }
    string getCurrentPlanet() const
    {
        return currentPlanet.name;
    }

    void travelTo(const CelestialBody &destinationPlanet)
    {
        long double distance = calculateDistance(currentPlanet, destinationPlanet);
        long double fuelRequired = speed * distance;
        long double timeTaken = distance / speed;

        cout << "Traveling from " << currentPlanet.name << " to " << destinationPlanet.name << "..." << endl;

        fuel -= fuelRequired;
        currentPlanet = destinationPlanet;
        cout << "Arrived at " << currentPlanet.name << ". Fuel remaining: " << fuel << endl;
        cout << "Time taken to travel: " << timeTaken << " hours" << endl;
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
    f.open("star.txt", ios::out | ios::binary);
    f.write((char *)&s1, sizeof(s1));
    f.write((char *)&s2, sizeof(s2));
    f.write((char *)&s3, sizeof(s3));
    f.write((char *)&s4, sizeof(s4));
    f.write((char *)&s5, sizeof(s5));
    f.close();
    Moon m1, m2, m3, m4, m5;
    m1.setMoon("Luna", 7.35e22, 1737.5, 0, 0, 0, "Earth");
    m2.setMoon("Phobos", 1.08e16, 11.2667, 0, 0, 0, "Mars");
    m3.setMoon("Io", 8.9319e22, 1821.6, 0, 0, 0, "Jupiter");
    m4.setMoon("Europa", 4.8e22, 1560.8, 0, 0, 0, "Jupiter");
    m5.setMoon("Titan", 1.3452e23, 2575, 0, 0, 0, "Saturn");
    f.open("moon.txt", ios::out | ios::binary);
    f.write((char *)&m1, sizeof(m1));
    f.write((char *)&m2, sizeof(m2));
    f.write((char *)&m3, sizeof(m3));
    f.write((char *)&m4, sizeof(m4));
    f.write((char *)&m5, sizeof(m5));
    f.close();
    Planet p1, p2, p3, p4, p5;
    p1.setPlanet("Mercury", 3.285e23, 2439.7, 0, 0, 0, 0.39);
    p2.setPlanet("Venus", 4.867e24, 6051.8, 0, 0, 0, 0.72);
    p3.setPlanet("Earth", 5.972e24, 6371, 0, 0, 0, 1);
    p4.setPlanet("Mars", 6.39e23, 3389.5, 0, 0, 0, 1.52);
    p5.setPlanet("Jupiter", 1.898e27, 69911, 0, 0, 0, 5.2);
    f.open("planet.txt", ios::out | ios::binary);
    f.write((char *)&p1, sizeof(p1));
    f.write((char *)&p2, sizeof(p2));
    f.write((char *)&p3, sizeof(p3));
    f.write((char *)&p4, sizeof(p4));
    f.write((char *)&p5, sizeof(p5));
    f.close();
    int ch;
    do
    {
        cout << "-------------------------------------------------------------\n";
        cout << "|" << setw(10) << "NO    |"
             << "|" << setw(50) << "        Choice                      |\n";
        cout << "-------------------------------------------------------------\n";
        cout << "|" << setw(10) << "1     |"
             << "|" << setw(50) << "Information of All Stars                      |\n";
        cout << "|" << setw(10) << "2     |"
             << "|" << setw(50) << "Information of All Moons                      |\n";
        cout << "|" << setw(10) << "3     |"
             << "|" << setw(50) << "Information of All Planets                    |\n";
        cout << "|" << setw(10) << "4     |"
             << "|" << setw(50) << "Information of Star                           |\n";
        cout << "|" << setw(10) << "5     |"
             << "|" << setw(50) << "Information of Moon                           |\n";
        cout << "|" << setw(10) << "6     |"
             << "|" << setw(50) << "Information of Planet                         |\n";
        cout << "|" << setw(10) << "7     |"
             << "|" << setw(50) << "Add Star                                      |\n";
        cout << "|" << setw(10) << "8     |"
             << "|" << setw(50) << "Add Moon                                      |\n";
        cout << "|" << setw(10) << "9     |"
             << "|" << setw(50) << "Add planet                                    |\n";
        cout << "|" << setw(10) << "10     |"
             << "|" << setw(50) << "Calculate Distance Between Two Celestial Body |\n";
        cout << "|" << setw(10) << "11     |"
             << "|" << setw(50) << "SpaceShip's fuel Details                      |\n";
        cout << "-------------------------------------------------------------\n";
        cout << "Enter your Choice : ";
        cin >> ch;
        Star s;
        Planet p;
        Moon m;
        switch (ch)
        {
        case 1:
            f.open("star.txt", ios::in | ios::binary);
            while (f.read((char *)(&s), sizeof(s)))
            {
                s.displayInfo();
                cout << "-------------------------------------------------------------\n";
            }
            f.close();

            break;
        case 2:
            f.open("moon.txt", ios::in | ios::binary);
            while (f.read((char *)&m, sizeof(m)))
            {
                m.displayInfo();
                cout << "-------------------------------------------------------------\n";
            }
            f.close();
            break;

        case 3:
            f.open("planet.txt", ios::in | ios::binary);
            while (f.read((char *)&p, sizeof(p)))
            {
                p.displayInfo();
                cout << "-------------------------------------------------------------\n";
            }
            f.close();
            break;
        }

    } while (ch < 12);
}