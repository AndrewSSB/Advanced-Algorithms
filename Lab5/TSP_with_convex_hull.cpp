#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <climits>

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

struct container{
    float dist;
    coords point;
    int id;

    void setContainer(float dist, coords point, int id){
        this->dist = dist;
        this->point = point;
        this->id = id;
    }
};

vector<coords> convexHull_v2(vector<coords> _coords){
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

    return points;
}

float calc_distance(coords p1, coords p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

float distance1(coords p1, vector<coords> _coords, int pos){
    float ans = calc_distance(_coords[pos], p1) + calc_distance(p1, _coords[(pos+1) % _coords.size()]);
    ans /= calc_distance(_coords[pos], _coords[(pos + 1) % _coords.size()]);
    return ans;
}

float distance2(coords p1, vector<coords> _coords, int pos){
        float ans = calc_distance(_coords[pos], p1) + calc_distance(p1, _coords[(pos+1) % _coords.size()]);
    ans -= calc_distance(_coords[pos], _coords[(pos + 1) % _coords.size()]);
    return ans;
}

void TSP_with_convex_hull(vector<coords> _coords){
    vector<coords> points = convexHull_v2(_coords);
    vector<coords> leftPoints = _coords;
    coords point; //am nevoie de una goala
    for (auto x : points)
        leftPoints.erase(remove(leftPoints.begin(), leftPoints.end(), x), leftPoints.end());

    while (!leftPoints.empty()){
        container best;
        best.setContainer(INT_MAX, point, 0);

        for (auto x : leftPoints){
            int id = 0;
            int best_dist = INT_MAX;

            for (int i = 0; i<(int)points.size(); i++){
                float d_act = distance1(x, points, i);
                if (d_act < best_dist){
                    best_dist = d_act;
                    id = i;
                }
            }

            float rap_act = distance2(x, points, id);
            if (rap_act < best.dist){
                best.dist = rap_act;
                best.point = x;
                best.id = id;
            }
        }

        leftPoints.erase(remove(leftPoints.begin(), leftPoints.end(), best.point), leftPoints.end());
        points.insert(points.begin()+best.id, best.point);
    }

    sort(points.begin(), points.end(), [&](coords p1, coords p2){return p1.x < p2.x;});
    points.push_back(points.front());
    for (auto x : points)
        cout << x << "\n";
}

int main()
{
    int _size;
    cin >> _size;

    vector<coords> _coords(_size);
    for (coords &x : _coords){
        cin >> x;
    }

    //convexHull(_coords);
    //convexHull_v2(_coords);
    TSP_with_convex_hull(_coords);
    return 0;
}
