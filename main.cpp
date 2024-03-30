#include <iostream>
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
    string getName()
    {
        return name;
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

    void setSpaceship(int _fuel, const CelestialBody &_currentPlanet, long double _speed)
    {
        fuel = _fuel;
        currentPlanet = _currentPlanet;
        speed = _speed;
    }

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
        cout << "Arrived at " << currentPlanet.name << ". \nFuel remaining             : " << fuel << endl;
        cout << "Time taken to travel       : " << timeTaken << " hours" << endl;
        cout << "-------------------------------------------------------------\n";
    }

    void displayInfo(CelestialBody ob)
    {
        cout << "-------------------------------------------------------------\n";
        cout << "Current Planet       : " << currentPlanet.getName() << endl;
        cout << "Fuel                 : " << fuel << endl;
        travelTo(ob);
    }
};

CelestialBody getCelestialBody(string str, vector<Star> s, vector<Moon> m, vector<Planet> p, int &flag)
{
    flag = 0;
    CelestialBody celestialBody;
    for (Star &obj : s)
    {
        if (!str.compare(obj.getName()))
        {
            flag = 1;
            celestialBody = obj;
            break;
        }
    }
    if (!flag)
    {
        for (Moon &obj : m)
        {
            if (!str.compare(obj.getName()))
            {
                flag = 1;
                celestialBody = obj;
                break;
            }
        }
    }
    if (!flag)
    {
        for (Planet &obj : p)
        {
            if (!str.compare(obj.getName()))
            {
                flag = 1;
                celestialBody = obj;
                break;
            }
        }
    }
    return celestialBody;
}
int main()
{
    vector<Star> s;
    Star s1, s2, s3, s4, s5;
    s1.setStar("Sun", 1.989e30, 696340, 0, 0, 0, "G-type main-sequence star");
    s2.setStar("Sirius", 2.063e30, 1.711e6, 8.6, 0, 0, "A-type main-sequence star");
    s3.setStar("Betelgeuse", 7.7e31, 9.04e5, 0, 0, 643, "Red supergiant");
    s4.setStar("Vega", 2.1e30, 2.17e6, -7.6, 0, 0, "A-type main-sequence star");
    s5.setStar("Rigel", 2.5e31, 7.6e5, 0, 0, -860, "Blue supergiant");
    s.push_back(s1);
    s.push_back(s2);
    s.push_back(s3);
    s.push_back(s4);
    s.push_back(s5);

    vector<Moon> m;
    Moon m1, m2, m3, m4, m5;
    m1.setMoon("Luna", 7.35e22, 1737.5, 0, 0, 0, "Earth");
    m2.setMoon("Phobos", 1.08e16, 11.2667, 0, 0, 0, "Mars");
    m3.setMoon("Io", 8.9319e22, 1821.6, 0, 0, 0, "Jupiter");
    m4.setMoon("Europa", 4.8e22, 1560.8, 0, 0, 0, "Jupiter");
    m5.setMoon("Titan", 1.3452e23, 2575, 10, 10, 0, "Saturn");
    m.push_back(m1);
    m.push_back(m2);
    m.push_back(m3);
    m.push_back(m4);
    m.push_back(m5);

    vector<Planet> p;
    Planet p1, p2, p3, p4, p5;
    p1.setPlanet("Mercury", 3.285e23, 2439.7, 0, 0, 0, 0.39);
    p2.setPlanet("Venus", 4.867e24, 6051.8, 0, 0, 0, 0.72);
    p3.setPlanet("Earth", 5.972e24, 6371, 5, 10, 9, 1);
    p4.setPlanet("Mars", 6.39e23, 3389.5, 0, 0, 0, 1.52);
    p5.setPlanet("Jupiter", 1.898e27, 69911, 0, 0, 0, 5.2);
    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);
    p.push_back(p5);

    Spaceship sp;
    int ch;
    while (1)
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
        cout << "|" << setw(10) << "12     |"
             << "|" << setw(50) << "Exit                                          |\n";
        cout << "-------------------------------------------------------------\n";
        cout << "Enter your Choice : ";
        cin >> ch;
        if (ch >= 1 && ch <= 12)
        {
            string star, moon, planet, name, type, orbitingPlanet, celestialBody1, celestialBody2;
            long double mass, radius, x, y, z, distanceFromStar, speed;
            int fuel;
            Star obS;
            Planet obP;
            Moon obM;
            CelestialBody c1, c2;
            int flag;
            switch (ch)
            {
            case 1:
                for (Star &obj : s)
                {
                    obj.displayInfo();
                    cout << "-------------------------------------------------------------\n";
                }
                break;
            case 2:
                for (Moon &obj : m)
                {
                    obj.displayInfo();
                    cout << "-------------------------------------------------------------\n";
                }
                break;

            case 3:
                for (Planet &obj : p)
                {
                    obj.displayInfo();
                    cout << "-------------------------------------------------------------\n";
                }
                break;

            case 4:
                cout << "Enter Star's Name : ";
                flag = 0;
                cin >> star;
                for (Star &obj : s)
                {
                    if (!star.compare(obj.getName()))
                    {
                        flag = 1;
                        obj.displayInfo();
                        cout << "-------------------------------------------------------------\n";
                        break;
                    }
                }
                if (!flag)
                {
                    cout << "Not Found!\n";
                }
                break;

            case 5:
                cout << "Enter Moon's Name : ";
                flag = 0;
                cin >> moon;
                for (Moon &obj : m)
                {
                    if (!moon.compare(obj.getName()))
                    {
                        flag = 1;
                        obj.displayInfo();
                        cout << "-------------------------------------------------------------\n";
                        break;
                    }
                }
                if (!flag)
                {
                    cout << "Not Found!\n";
                }
                break;

            case 6:
                cout << "Enter Planet's Name : ";
                flag = 0;
                cin >> planet;
                for (Planet &obj : p)
                {
                    if (!planet.compare(obj.getName()))
                    {
                        flag = 1;
                        obj.displayInfo();
                        cout << "-------------------------------------------------------------\n";
                        break;
                    }
                }
                if (!flag)
                {
                    cout << "Not Found!\n";
                }
                break;

            case 7:
                cout << "-------------------------------------------------------------\n";
                cout << "Enter Star's Information\n";
                cout << "-------------------------------------------------------------\n";
                cout << "Name                 : ";
                cin >> name;
                cout << "Mass                 : ";
                cin >> mass;
                cout << "Radius               : ";
                cin >> radius;
                cout << "Coordinates(x,y,z)   : ";
                cin >> x >> y >> z;
                cout << "Type                 : ";
                cin >> type;
                cout << "-------------------------------------------------------------\n";
                obS.setStar(name, mass, radius, x, y, z, type);
                s.push_back(obS);
                cout << "Added Successfully!\n";
                break;

            case 8:
                cout << "-------------------------------------------------------------\n";
                cout << "Enter Moon's Information\n";
                cout << "-------------------------------------------------------------\n";
                cout << "Name                 : ";
                cin >> name;
                cout << "Mass                 : ";
                cin >> mass;
                cout << "Radius               : ";
                cin >> radius;
                cout << "Coordinates(x,y,z)   : ";
                cin >> x >> y >> z;
                cout << "Orbiting Planet      : ";
                cin >> orbitingPlanet;
                cout << "-------------------------------------------------------------\n";
                obM.setMoon(name, mass, radius, x, y, z, orbitingPlanet);
                m.push_back(obM);
                cout << "Added Successfully!\n";
                break;

            case 9:
                cout << "-------------------------------------------------------------\n";
                cout << "Enter Planet's Information\n";
                cout << "-------------------------------------------------------------\n";
                cout << "Name                 : ";
                cin >> name;
                cout << "Mass                 : ";
                cin >> mass;
                cout << "Radius               : ";
                cin >> radius;
                cout << "Coordinates(x,y,z)   : ";
                cin >> x >> y >> z;
                cout << "Distance From Star   : ";
                cin >> distanceFromStar;
                cout << "-------------------------------------------------------------\n";
                obP.setPlanet(name, mass, radius, x, y, z, distanceFromStar);
                p.push_back(obP);
                cout << "Added Successfully!\n";
                break;

            case 10:
                cout << "-------------------------------------------------------------\n";
                cout << "Enter first Celestial Body             : ";
                cin >> celestialBody1;
                cout << "Enter Second Celestial Body            : ";
                cin >> celestialBody2;
                cout << "-------------------------------------------------------------\n";
                c1 = getCelestialBody(celestialBody1, s, m, p, flag);
                c2 = getCelestialBody(celestialBody2, s, m, p, flag);
                if (!flag)
                {
                    cout << "Entered Celestial Body is not found!\n";
                }
                else
                {
                    cout << "Distance between " << celestialBody1 << " and " << celestialBody2 << "       : " << calculateDistance(c1, c2) << " Km" << endl;
                    cout << "-------------------------------------------------------------\n";
                }
                break;

            case 11:
                cout << "-------------------------------------------------------------\n";
                cout << "Enter Spaceship's Information\n";
                cout << "Fuel                       : ";
                cin >> fuel;
                cout << "Current Planet Name        : ";
                cin >> celestialBody1;
                cout << "Destination Planet Name    : ";
                cin >> celestialBody2;
                cout << "Speed                      : ";
                cin >> speed;
                cout << "-------------------------------------------------------------\n";
                flag = 0;
                for (Planet &obj : p)
                {
                    if (!celestialBody1.compare(obj.getName()))
                    {
                        flag = 1;
                        c1 = obj;
                        break;
                    }
                }
                for (Planet &obj : p)
                {
                    if (!celestialBody2.compare(obj.getName()))
                    {
                        flag = 1;
                        c2 = obj;
                        break;
                    }
                }
                if (!flag)
                {
                    cout << "Entered Celestial Body is not found!\n";
                }
                else
                {
                    sp.setSpaceship(fuel, c1, speed);
                    sp.displayInfo(c2);
                }
                break;
            }
        }
        else if (ch == 12)
        {
            break;
        }
        else
        {
            cout << "Enter valid choice!\n";
        }
    }
}