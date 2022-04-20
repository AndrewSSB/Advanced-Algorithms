#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

struct coords{
    int x;
    int y;

    void setCoords(int _x, int _y){
        this->x = _x;
        this->y = _y;
    }

    friend istream&operator>>(istream& in, coords & obj){
        in >> obj.x;
        in >> obj.y;
        return in;
    }

    friend ostream&operator<<(ostream& out, const coords & obj){
        out << "(" << obj.x << ", " << obj.y << ")";
        return out;
    }
};

int determinant(coords A, coords B, coords C){
    return (A.x - B.x)*(B.y - C.y) - (A.y - B.y)*(B.x - C.x);
}

vector<coords> convexHull(vector<coords> _coords){
    if (_coords.size() < 3)
        return _coords;

    vector<coords> Hull;

    int l = 0;
    for (int i = 1; i < (int)_coords.size(); i++)
        if (_coords[i].x < _coords[l].x)
            l = i; //cel mai stang punct


    int p = l, q;
    do {
        Hull.push_back(_coords[p]);

        q = (p+1)%_coords.size();

        for (int i = 0; i < (int)_coords.size(); i++){
            if (determinant(_coords[p], _coords[i], _coords[q]) < 0)
                q = i;
        }
        p = q;
    } while(p != l);

    return Hull;
}

void pointInPolygon(vector<coords> polygon, coords A){
    polygon.push_back(polygon.front());

    for (int i = 0; i < int(polygon.size()) - 1; i++){
        int value = determinant(polygon[i], polygon[i+1], A);
        if (value > 0){
            continue;
        }
        if (value < 0){
            cout << "OUTSIDE\n";
            return;
        }
        if (value == 0){
            cout << "BOUNDARY\n";
            return;
        }
    }

    cout << "INSIDE\n";
    return;
}

int main()
{
    int _size;
    ifstream fin("date.in");
    fin >> _size;

    vector<coords> _coords(_size);
    for (coords &x : _coords){
        fin >> x;
    }

    fin >> _size;
    vector<coords> points(_size);
    for (coords &x : points){
        fin >> x;
        pointInPolygon(_coords, x);
    }
    fin.close();

    return 0;
}
