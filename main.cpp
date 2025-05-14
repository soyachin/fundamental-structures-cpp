#include <iostream>
#include "include/Hash.h"
#include <string>

int main() {
    
    Hash<string, int> mihash;

    mihash.insert("Hola", 1);
    mihash.insert("Chau", 0);

    cout << mihash.get("Hola") << endl;

    return 0;
}
