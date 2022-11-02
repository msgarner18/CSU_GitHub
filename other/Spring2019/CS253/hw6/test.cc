#include "Gallery.h"
#include <cassert>
#include <iostream>
#include <string>

//Enemy[size_t] -A zero argument to [] does not necessarily return the first key/value pair read. The exact order is unspecified, but all pairs must be represented. 



using namespace std;

void show(const Enemy &e) {
    for (size_t i=0; i<e.size(); i++) {
        pair<string,string> p = e[i];
        assert(e[p.first] == p.second);
        cout << p.first << ": " << p.second << '\n';
    }
}

void show(const Gallery &g) {
    for (size_t i=0; i<g.size(); i++) {
        if (i>0)
            cout << '\n';
        show(g[i]);
    }
}

int main() {

    Gallery vacant("pokekeys", "/dev/null");
	//Gallery vacant("pokekeys", "pokemon");
    const Gallery monsters("pokemon", "pokekeys");

    assert(!vacant);
    assert(monsters);
    assert(monsters[0]);

    assert(monsters[0] == monsters[0]);
    assert(monsters[1] == monsters[1]);
    assert(!(monsters[1] == monsters[0]));
    assert(!(monsters[0] == monsters[1]));

    assert(!(monsters[0] != monsters[0]));
    assert(!(monsters[1] != monsters[1]));
    assert(monsters[1] != monsters[0]);
    assert(monsters[0] != monsters[1]);

    show(vacant);
    show(monsters);

    return 0;
}
