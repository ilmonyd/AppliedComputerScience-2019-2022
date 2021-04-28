#include <iostream>
#include "arraylist.h"

//
//  Created by Oleg Semenov on 29.10.2020
//

using namespace std;

void help() {
    cout << "f - push_front()" << endl;
    cout << "b - push_back()" << endl;
    cout << "F - pop_front" << endl;
    cout << "B - pop_back" << endl;
    cout << "l - ArrayList front" << endl;
    cout << "L - ArrayList back" << endl;
    cout << "p - print ArrayList" << endl;
    cout << "s - number of elements in ArrayList" << endl;
    cout << "e - empty check" << endl;
    cout << "E - full check" << endl;
    cout << "i - get chosen element's index" << endl;
    cout << "S - sort the ArrayList" << endl;
    cout << "r - reverse the ArrayList" << endl;
    cout << "m - merge" << endl;
    cout << "c - clear" << endl;
    cout << "h - help" << endl;
}


int main() {
    int s;
    cout << "Enter ArrayList size" << endl;
    cin >> s;

    ArrayList<int> arr = ArrayList<int>(s);
    ArrayList<int> arr2 = ArrayList<int>(s);
    char opt;
    string temp;
    help();

    while (cin >> opt) {
        switch(opt) {
            case 'f':
                if(!arr.full()) {
                    cin >> temp;
                    int n = stoi(temp);
                    arr.push_front(n);
                    cout << "Current state: " << arr << endl;
                } else {
                    cout << "ArrayList is full, can't add more elements" << endl;
                }
                break;
            case 'b':
                if(!arr.full()) {
                    cin >> temp;
                    int n = stoi(temp);
                    arr.push_back(n);
                    cout << "Current state: " << arr << endl;
                } else {
                    cout << "ArrayList is full, can't add more elements" << endl;
                }
                break;
            case 'F':
                if(!arr.empty()) {
                    arr.pop_front();
                    cout << "Current state: " << arr << endl;
                } else {
                    cout << "ArrayList has no elements to pop" << endl;
                }
                break;
            case 'B':
                if(!arr.empty()) {
                    arr.pop_back();
                    cout << "Current state: " << arr << endl;
                } else {
                    cout << "ArrayList has no elements to pop" << endl;
                }
                break;
            case 'l':
                if(!arr.empty()) {
                    cout << arr.front() << endl;
                } else {
                    cout << "ArrayList is empty" << endl;
                }
                break;
            case 'L':
                if(!arr.empty()) {
                    cout << arr.back() << endl;
                } else {
                    cout << "ArrayList is empty" << endl;
                }
                break;
            case 's':
                cout << "ArrayList currently holds " << arr.size() << " elements" << endl;
                break;
            case 'P':
                cout << arr << endl;
                break;
            case 'e':
                if(arr.empty()){
                    cout << "ArrayList is empty" << endl;
                } else {
                    cout << "ArrayList is not empty" << endl;
                }
                break;
            case 'E':
                if(arr.full()){
                    cout << "ArrayList is full" << endl;
                } else {
                    cout << "ArrayList is not full" << endl;
                }
                break;
            case 'i':
                if(!arr.empty()) {
                    cin >> temp;
                    int pos;
                    if((pos = arr.find(stoi(temp))) != -1) {
                        cout << pos << endl;
                    } else {
                        cout << "Element is not in ArrayList" << endl;
                    }
                } else {
                    cout << "ArrayList has no elements in it" << endl;
                }
                break;
            case 'S':
                if(!arr.empty()) {
                    arr.sort();
                    cout << "Current state: " << arr << endl;
                } else {
                    cout << "ArrayList has no elements to sort" << endl;
                }
                break;
            case 'R':
                if(!arr.empty()) {
                    arr.reverse();
                    cout << "Current state: " << arr << endl;
                } else {
                    cout << "ArrayList is empty" << endl;
                }
                break;
            case 'm':
                cout << "the size of mergeable array is the same as the first one created" << endl;
                cout << "enter number of elements for ArrayList" << endl;
                int i;
                int tempval;
                cin >> i;
                for (int j = 0; j < i; j++) {
                    cout << "enter value" << endl;
                    cin >> tempval;
                    arr2.push_back(tempval);
                }
                arr.merge(arr2);
                arr.sort();
                cout << "merged ArrayList: " << arr << endl;
                break;
            case 'c':
                if(!arr.empty()) {
                    arr.clear();
                    cout << "Current state: " << arr << endl;
                } else {
                    cout << "ArrayList is already empty" << endl;
                }
                break;
            case 'h':
                help();
                break;
            default:
                break;
        }
    }

    return 0;
}
