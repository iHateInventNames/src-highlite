#include <iostream>

#include "asserttestexit.h"
#include "srcuntabifier.h"

using namespace std;

int main() {
    Untabifier untabifier(4);

    string orig = "\twith\t\ttabs";

    cout << "orig     : " << orig << endl;

    string preformat = untabifier.preformat(orig);

    cout << "preformat: " << preformat << endl;

    assertEquals("    with        tabs", preformat);

    Untabifier untabifier2(4);

    preformat = untabifier2.preformat(orig);

    cout << "preformat: " << preformat << endl;
    
    //assertEquals("   with        tabs", preformat);

    preformat = untabifier2.preformat("\n");
    preformat = untabifier2.preformat("\tsecond line");

    cout << "preformat: " << preformat << endl;
    
    assertEquals("    second line", preformat);

    cout << "test_untabifier: SUCCESS" << endl;

    return 0;
}
