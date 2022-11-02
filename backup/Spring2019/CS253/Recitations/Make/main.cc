#include <iostream>

using namespace std;

#include "foo.h"

int main() {
    cout << "Hi from " << __func__ << " at " __FILE__ ":" << __LINE__ << '\n';
    foo();
    return 0;
}
