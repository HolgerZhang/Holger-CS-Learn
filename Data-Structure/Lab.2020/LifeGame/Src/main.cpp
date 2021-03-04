#include "life.h"
#include "console_runtime.h"

using namespace std;


int main(int argc, const char **argv) {
    cout << "Life Game (Oct. 10 2020) By Holger Zhang\n" << endl;
    cout << Life::introduction << endl;
    Life life;

    // initialize
    string file_name = "<stdin>";
    ifstream fin;
    streambuf *backup;
    if (argc >= 2) {
        file_name = argv[argc - 1];
        fin.open(file_name);
        if (!fin.is_open()) {
            cerr << "Invalid file path: " << file_name << endl;
            exit(-1);
        }
        cout << "Reading configuration from file_name '" << file_name << "'" << endl;
        backup = cin.rdbuf();
        cin.rdbuf(fin.rdbuf()); // Input redirection -> file
    } else {
        cout << "Please input a configuration, multi-line rectangular text consisting of character ' ' and 'x', "
                "and end up with '#' in the new line: " << endl;
    }
    try { life.initialize(cin); }
    catch (std::exception &e) {
        console_runtime::show_error(e, "Setup configuration", file_name, true, -2);
    }
    if (argc >= 2) {
        cout << "Got configuration: " << endl;
        life.show();
        cin.rdbuf(backup);  // Input redirection -> standard input
        fin.close();
    }

    cout << "Now let's begin!" << endl;
    cout << console_runtime::MENU << endl;
    for (;;) {
        try { console_runtime::execute(life, console_runtime::wait_user("Input Command")); }
        catch (std::exception &e) {
            console_runtime::show_error(e, "Executing command");
        }
    }
}
