#include <iostream>

#include "sourcehighlight.h"
#include "textstyleformatter.h"
#include "my_sstream.h"
#include "asserttestexit.h"
#include "ioexception.h"
#include "docgenerator.h"
#include "parserexception.h"

using namespace std;

int main() {
    istringstream input;
    ostringstream output;

    // test with error in the style file
    try {
        SourceHighlight sourcehighlight("html.outlang");
        sourcehighlight.setDataDir(BASEDIR);
        sourcehighlight.setStyleFile("nonexistent.style");
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_var.lang");
        assertTrue(false); // must not get here
    } catch (IOException &e) {
        //cout << "expected exception: " << e << endl;
        assertEqualsException("cannot open " BASEDIR "/nonexistent.style.", e);
    }

    try {
        SourceHighlight sourcehighlight("html.outlang");
        sourcehighlight.setDataDir(BASEDIR);
        sourcehighlight.setStyleFile(TESTSDIR "/wrong_already_defined.style");
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_var.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        //cout << "expected exception: " << es.str() << endl;
        assertEqualsException(TESTSDIR "/wrong_already_defined.style:3: already defined date", e);
    }

    try {
        SourceHighlight sourcehighlight("html.outlang");
        sourcehighlight.setDataDir(BASEDIR);
        sourcehighlight.setStyleCssFile("nonexistent.style");
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_var.lang");
        assertTrue(false); // must not get here
    } catch (IOException &e) {
        //cout << "expected exception: " << e << endl;
        assertEqualsException("cannot open " BASEDIR "/nonexistent.style.", e);
    }

    try {
        SourceHighlight sourcehighlight("html.outlang");
        sourcehighlight.setDataDir(BASEDIR);
        sourcehighlight.setStyleCssFile(TESTSDIR "/wrong_already_defined_css.css");
        sourcehighlight.highlight(BASEDIR "../doc/Hello.java", "Hello.java.html", TESTSDIR "wrong_var.lang");
        assertTrue(false); // must not get here
    } catch (ParserException &e) {
        //cout << "expected exception: " << es.str() << endl;
        assertEqualsException(TESTSDIR "/wrong_already_defined_css.css:5: already defined keyword", e);
    }

    cout << "test_style_errors: SUCCESS" << endl;

    return 0;
}
