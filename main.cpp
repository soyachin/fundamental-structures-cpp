#include <iostream>
#include "include/Hash.h"

int main() {
    
    Hash<string, int> mihash;

    mihash.insert("Free Tea", 2);
    mihash.insert("Inka Cola", 3);

    cout << mihash.get("Inka Cola") << endl;

    return 0;
}
