#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using std::fstream;
using std::cerr;
using std::endl;
using std::string;

int main()
{
    // open for input and output and preposition file pointers to end-of-file
    // file mode argument see § 8.4 (p. 319)
    fstream inOut("copyOut.txt", fstream::ate | fstream::in | fstream::out);

    if (!inOut) {
        cerr << "Unable to open file!" << endl;
        return EXIT_FAILURE; // EXIT_FAILURE see § 6.3.2 (p. 227)
    }

    // inOut is opened in ate mode, so it starts out positioned at the end
    fstream::pos_type end_mark = inOut.tellg();// remember original end-of-file position
    inOut.seekg(0, fstream::beg); // reposition to the start of the file
    size_t cnt = 0; // accumulator for the byte count
    string line; // hold each line of input

    // while we haven't hit an error and are still reading the original data
    while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) { // and can get another line of input
        cnt += line.size() + 1; // add 1 to account for the newline
        auto mark = inOut.tellg(); // remember the read position
        inOut.seekp(0, fstream::end); // set the write marker to the end
        inOut << cnt; // write the accumulated length
        // print a separator if this is not the last line
        if (mark != end_mark) inOut << " ";
        inOut.seekg(mark); // restore the read position
    }

    inOut.seekp(0, fstream::end); // seek to the end
    inOut << "\n"; // write a newline at end-offile
    return 0;
}

// copyOut.txt:
// abcd
// efg
// hi
// j
// #1 Compile in Win7 with gcc version 8.1.0, the result:
// abcd
// efg
// hi
// j
// 5 6 7 8
// #2 Compile in Ubuntu 12.04.5 LTS with gcc version 4.6.3, the result:
// abcd
// efg
// hi
// j
// 5 9 12 14
