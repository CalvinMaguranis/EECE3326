#include "carddeck.h"

using namespace std;

int main() {
    try {
        deck d;
        cout << d;
    } catch (rangeError &ex) {
        cout << ex.what() << endl;
        exit(0);
    } catch ( ... ) {
        cout << "unhandled exception found!" << endl;
        exit(0);
    }

    return 1;
}
