#include "Gallery.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int main() {

	Gallery g("keys", "gold-odd");
	Enemy* enp = g.get(0)->link("Henchman");
	cout << enp << '\n';
/*
    Gallery g("bond-villains", "keys", "/dev/null");
    assert(g.size() == 2);
    g.read("jaws", "keys");
    cout << g << "———–—––—–——–———–\n";
    assert(g.size() == 3);
    assert(!g.empty());
    g.clear();
    assert(g.size() == 0);
    assert(g.empty());

    const Gallery go("keys", "gold-odd");
    for (size_t i=0; i<go.size(); i++) {
        const Enemy *e = go.get(i);
        try {
            const Enemy *h = e->link("Henchman");   // might throw error
            cout << e->field("Name") << "’s henchman is "
                 << h->field("Name") << '\n';
        }
        catch (...) {
            cout << e->field("Name") << "’s boss is "
                 << e->link("Boss")->field("Name") << '\n';
        }
    }
*/
    return 0;
}
/*
try
{
	Gallery g("bond-villains", "keys");
	g.read("jaws", "keys");
    	cout << g << "———–—––—–——–———–\n";
}
catch(const exception &err)
{
	cout << err.what() << '\n';
}
catch(...)
{
	cout << "I don't know what error this is!" << '\n';
}*/
