#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct coords{
    int x;
    int y;

    friend istream&operator>>(istream& in, coords & obj){
        in >> obj.x;
        in >> obj.y;
        return in;
    }

    friend ostream&operator<<(ostream& out, const coords & obj){
        out << obj.x << " " << obj.y;
        return out;
    }

    coords&operator=(const coords &obj){
        if (this != &obj){
            x = obj.x;
            y = obj.y;
        }
        return *this;
    }

    coords(const coords &obj){
        x = obj.x;
        y = obj.y;
    }

    coords(){
        x = 0;
        y = 0;
    }

    bool operator==(const coords &obj){
        return x == obj.x && y == obj.y;
    }

    bool operator!=(const coords &obj){
        return x != obj.x && y != obj.y;
    }
};

int determinant(coords A, coords B, coords C){
    int val = (B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : -1;
}

void convexHull_v2(vector<coords> _coords){
    vector<coords> points;
    coords leftMostPoint = _coords[0];
    for (int i = 1; i < (int)_coords.size(); i++)
        if (_coords[i].x <= leftMostPoint.x)
            leftMostPoint = _coords[i];

    int i = 0;
    coords nextPoint;
    do {
        points.push_back(leftMostPoint);
        nextPoint = _coords[0];
        for (int j = 0; j < (int)_coords.size(); j++){
            if ((nextPoint == leftMostPoint) || (determinant(points[i], nextPoint, _coords[j]) == -1))
                nextPoint = _coords[j];
        }
        i++;
        leftMostPoint = nextPoint;
    }while(nextPoint != points[0]);

    cout << points.size() << "\n";
    for (auto x : points){
        cout << x << "\n";
    }
}

//Test Orientare


int main()
{
    int _size;
    cin >> _size;

    vector<coords> _coords(_size);
    for (coords &x : _coords){
        cin >> x;
    }

    //convexHull(_coords);
    convexHull_v2(_coords);
    return 0;
}
