class Elevator {
    int id;
    double price;
public:
    Elevator(int a, int b) : id(a), price(b) { }
};

class pElevator : virtual public Elevator {
    double passenger_load;
public:
    pElevator(int a, int b, int c) : Elevator(a, b), passenger_load(c) { }
};

class cElevator : virtual public Elevator {
    double cargo_load;
public:
    cElevator(int a, int b, int c) : Elevator(a, b), cargo_load(c) { }
};

class dElevator : public pElevator, public cElevator {
public:
    dElevator(int a, int b, int c, int d) :
        Elevator(a, b), pElevator(a, b, c), cElevator(a, b, d) { }
};

int main() {

    return 0;
}
