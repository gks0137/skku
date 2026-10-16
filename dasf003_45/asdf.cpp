#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main() {
    // ifstream instream("a.txt");
    // ofstream outstream("b.txt");
    ifstream instream;
    ofstream outstream;
    instream.open("a.txt");
    outstream.open("b.txt");

    string line;
    while (!instream.eof()) {\
        char c;
        instream.get(c);
        outstream << c << ' ';
    }

    
}