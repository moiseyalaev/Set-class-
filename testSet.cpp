#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Set x;
    Set y;
    assert(y.size() == 0 && x.size() == 0);

    assert(x.insert("hello") && x.insert("hi") && !x.insert("hi") && x.size() == 2);

    assert(y.insert("animal") && y.insert("goat") && y.insert("man") && y.insert("happy") && y.insert("zebra") && y.insert("banana"));

    assert(x.erase("hello") && x.erase("hi") && !x.erase("hi") && x.size() == 0);

    assert(y.erase("goat") && y.erase("animal") && y.erase("zebra") && y.erase("happy") && y.erase("man") && y.size() == 1);

    assert(x.insert("heyyoo") && x.insert("waddup") && x.insert("apple"));

    // assert(x.erase("heyyoo") && x.erase("apple") && !x.erase("apple") && x.erase("waddup"));

    cout << "x is: ";
    x.dump();
    cout << "y is: ";
    y.dump();

    y = x;

    cout << (y.size() == 3) << endl;
    // // string test = "moisey";
    // // assert(x.get(0, test));
    // // cout << test << endl;
    
    // Set z = x;
    // cout << "========================\n";

    // cout << "x is: ";
    // x.dump();
    // cout << "y is: ";
    // y.dump();
    // cout << "z is: ";
    // z.dump();

    // z.swap(y);

    // cout << "x is: ";
    // x.dump();
    // cout << "y is: ";
    // y.dump();
    // cout << "z is: ";
    // z.dump();


    // assert(x.contains("apple") && x.contains("waddup") && !x.contains("jackfrost"));

    // //assert(z.size() == 4);


//=================TESTING UNITE() AND SUBTRACT()==========================

    Set s1;
    s1.insert("king-kong");
    s1.insert("YES");
    s1.insert("lobster");
    s1.insert("hey");

    Set s2;
    s2.insert("yogurt");
    s2.insert("king-kong");
    s2.insert("lobster");
    s2.insert("lamp");
    s2.insert("hey");

    Set result;
    result.insert("cool");
    result.insert("chill");
    result.insert("kewl");

    unite(s1, s2, result);

    cout << "s1 is: ";
    s1.dump();
    cout << "s2 is: ";
    s2.dump();
    cout << "result is: ";
    result.dump();
}
