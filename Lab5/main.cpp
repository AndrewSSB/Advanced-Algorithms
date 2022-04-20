#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#define OUT 0
#define IN 1
#define COL 2

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

int IsPointInPolygon(coords p, vector<coords> polygon )
{
    int minX = polygon[ 0 ].x;
    int maxX = polygon[ 0 ].x;
    int minY = polygon[ 0 ].y;
    int maxY = polygon[ 0 ].y;
    for ( int i = 1 ; i < (int)polygon.size() ; i++ )
    {
        coords q = polygon[ i ];
        minX = min( q.x, minX );
        maxX = max( q.x, maxX );
        minY = min( q.y, minY );
        maxY = max( q.y, maxY );
    }

    if ( p.x < minX || p.x > maxX || p.y < minY || p.y > maxY )
    {
        return OUT;
    }

    // https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
    bool inside = false;
    for ( int i = 0, j = (int)polygon.size() - 1 ; i < (int)polygon.size() ; j = i++ )
    {
        if ( ( polygon[ i ].y > p.y ) != ( polygon[ j ].y > p.y ) &&
             p.x < ( polygon[ j ].x - polygon[ i ].x ) * ( p.y - polygon[ i ].y ) / ( polygon[ j ].y - polygon[ i ].y ) + polygon[ i ].x )
        {
            inside = !inside;
        }
        else{
            int val = determinant(polygon[i], polygon[i+1], p);
            if (val == 0)
                return COL;
        }
    }

    return (inside) ? IN : OUT;
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
    }
    fin.close();

    for (auto x : points){
        int val = IsPointInPolygon(x, _coords);
        if (val == IN)
            cout << "INSIDE\n";
        if (val == OUT)
            cout << "OUTSIDE\n";
        if (val == COL)
            cout << "BOUNDARY\n";
    }

    return 0;
}
