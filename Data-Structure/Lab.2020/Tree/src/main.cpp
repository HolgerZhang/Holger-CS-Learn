#include "console.h"

using namespace std;

int main() {
    Console session;
    session.initialize();
    return session.exec();
}
