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
        out << "(" << obj.x << ", " << obj.y << ")";
        return out;
    }
};

int determinant(coords A, coords B, coords C){
    int val = (B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : -1;
}

void convexHull(vector<coords> _coords){
    if (_coords.size() < 3)
        return;

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
            if (determinant(_coords[p], _coords[i], _coords[q]) == -1)
                q = i;
        }
        p = q;
    } while(p != l);

    for (auto x : Hull){
        cout << x << endl;
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

    convexHull(_coords);

    return 0;
}
