#include <iostream>
#include "doublelist.h"

//
//  Created by Oleg Semenov on 20.11.2020
//

using namespace std;


int main() {
    DoubleList<int> arr;
    arr.push_front(10);
    arr.push_back(11);
    arr.push_front(12);
    if (arr.empty()) {
        cout << "DoubleList is empty.\n";
    }
    else {cout << "DoubleList has some elements.\n";}
    cout << "The DoubleList has a size of: " << arr.size() << endl;
    arr.display();
    DoubleList<int> arr_copy(arr);
    arr_copy.display();
    arr_copy.display_reversed();
    arr_copy.push_back(move(20));
    arr_copy.display();
    cout << arr_copy.back() << endl;
    arr_copy.clear();
    arr_copy.display();
    return 0;
}
