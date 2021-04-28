#include <iostream>
#include "singlelist.h"

//
//  Created by Oleg Semenov on 15.11.2020
//

using namespace std;


int main() {
    SingleList<int> arr;
    arr.push_front(10);
    arr.push_back(11);
    arr.push_front(12);
    arr.reverse();
    if (arr.empty()) {
        cout << "SingleList is empty.\n";
    }
    else {cout << "SingleList has some elements.\n";}
    cout << "The SingleList has a size of: " << arr.size() << endl;
    arr.display();
    SingleList<int> arr_copy(arr);
    arr_copy.display();
    arr_copy.insert(2, 15);
    if (!arr_copy.empty()) {
        cout << arr_copy[0] << endl;
    }
    arr_copy.display();
    arr_copy.push_back(move(20));
    arr_copy.display();
    cout << arr_copy.back() << endl;
    arr_copy.clear();
    arr_copy.display();
    return 0;
}
