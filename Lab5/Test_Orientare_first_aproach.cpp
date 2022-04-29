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
};

void direction(coords A, coords B, coords C){
    int val = (A.x - B.x)*(B.y - C.y) - (A.y - B.y)*(B.x - C.x);
    if (val == 0) cout << "TOUCH" << endl;
    if (val < 0) cout << "RIGHT" << endl; 
    else cout << "LEFT" << endl;
}

int main()
{
    int t;
    cin >> t;

    coords P, Q, R;

    for (int i = 0; i < t; i++){
        cin >> P >> Q >> R;
        direction(P, Q, R);
    }
    
    return 0;
}
