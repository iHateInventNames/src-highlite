//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef SOURCEHIGHLIGHT_H_
#define SOURCEHIGHLIGHT_H_

#include <string>
#include <istream>
#include <ostream>

#include "textstyleformattercollection.h"
#include "verbose.h"

class FormatterManager;
class PreFormatter;
class LangDefManager;
class BufferedOutput;
class LineNumGenerator;
class DocGenerator;
class CharTranslator;
class HighlightEventListener;
class CTagsManager;
class CTagsFormatter;

/**
 * The main class performing highlighting of a file
 */
class SourceHighlight : public Verbose {
    /// the output language file name
    std::string outputLang;

    /// path for several configuration files
    std::string dataDir;

    /// the background color
    std::string backgroundColor;

    /// the style file
    std::string styleFile;

    /// the css style file
    std::string styleCssFile;

    /// the style defaults file
    std::string styleDefaultFile;

    /// the prefix for all the output lines
    std::string linePrefix;

    /// the title for the output document (defaults to the source file name)
    std::string title;

    /// the value for the css
    std::string css;

    /// the file name of the header
    std::string headerFileName;

    /// the file name of the footer
    std::string footerFileName;

    /// the file extension for output files
    std::string outputFileExtension;

    /// the directory for output files
    std::string outputFileDir;

    /// the formatter manager
    FormatterManager *formatterManager;

    /// the preformatter
    PreFormatter *preFormatter;

    /// all the formatters that are created
    TextStyleFormatterCollection formatterCollection;

    /// for loading language definitions
    LangDefManager *langDefManager;

    /// the generator for line numbers
    LineNumGenerator *lineNumGenerator;

    /**
     * the generator of the start and end of the output document 
     */
    DocGenerator *docGenerator;

    /**
     * the generator of the start and end of the output document when NOT generating
     * an entire document
     */
    DocGenerator *noDocGenerator;

    /**
     * The listener for highlight events
     */
    HighlightEventListener *highlightEventListener;

    /// the CTagsManager for creating CTagsFormatters
    CTagsManager *ctagsManager;

    /// the CTagsFormatter for formatting references and anchors
    CTagsFormatter *ctagsFormatter;

    /**
     * Whether to optmize output (e.g., adiacent text parts belonging
     * to the same element will be buffered and generated as a single text part)
     */
    bool optimize;

    /// whether to generate line numbers
    bool generateLineNumbers;

    /// whether to generate line numbers with references
    bool generateLineNumberRefs;

    /// the prefix for the line number anchors
    std::string lineNumberAnchorPrefix;

    /// the line number padding char (default '0')
    char lineNumberPad;

    /// whether to generate an entire document (default false)
    bool generateEntireDoc;

    /// whether to generate the program version in the output file (default=true)
    bool generateVersion;

    /// whether we can use stdout for generating the output (default true)
    bool canUseStdOut;

    /**
     * If greater than 0 it means that tabs will be replaced by tabSpaces
     * blank characters
     */
    unsigned int tabSpaces;

    /**
     * Sets the specified buffered output to all the formatters
     * @param output
     */
    void updateBufferedOutput(BufferedOutput *output);

public:
    SourceHighlight(const std::string &outputLang);
    ~SourceHighlight();

    /**
     * performs initialization of fields, if not already initialized.
     * There's no need to call it directly, since the highlight functions always
     * check initialization.
     */
    void initialize();

    /**
     * Highlights the contents of the input file into the output file, using
     * the specified inputLang definition
     * @param input the input file name, if empty stdin will be used
     * @param output the output file name, if empty (or equal to STDOUT) the stdout will be used
     * @param inputLang the language definition file
     */
    void highlight(const std::string &input, const std::string &output,
            const std::string &inputLang);

    /**
     * Highlights the contents of the input stream into the output stream, using
     * the specified inputLang definition
     * @param input the input stream
     * @param output the output stream
     * @param inputLang the language definition file
     * @param inputFileName the input file name
     */
    void highlight(std::istream &input, std::ostream &output,
            const std::string &inputLang, const std::string &inputFileName = "");

    /**
     * Only check the validity of the language definition file.
     * If the language definition is valid it simply returns, otherwise,
     * it throws an exception (with the details of the problems found)
     * @param langFile
     * @throws HighlightBuilderException
     */
    void checkLangDef(const std::string &langFile);

    /**
     * Only check the validity of the out language definition file.
     * If the language definition is valid it simply returns, otherwise,
     * it throws an exception (with the details of the problems found)
     * @param langFile
     * @throws ParserException
     */
    void checkOutLangDef(const std::string &langFile);

    /**
     * Prints the HighlightState corresponding to the language definition file.
     * If the language definition is valid it simply prints the state and returns, otherwise,
     * it throws an exception (with the details of the problems found)
     * @param langFile
     * @param os where to print the highlight state
     * @throws HighlightBuilderException
     */
    void printHighlightState(const std::string &langFile, std::ostream &os);

    /**
     * Prints the language elements corresponding to the language definition file.
     * If the language definition is valid it simply prints the state and returns, otherwise,
     * it throws an exception (with the details of the problems found)
     * @param langFile
     * @param os where to print the highlight state
     * @throws HighlightBuilderException
     */
    void printLangElems(const std::string &langFile, std::ostream &os);

    /**
     * Given the input file name creates an output file name.
     * 
     * @return the output file name
     */
    const std::string createOutputFileName(const std::string &inputFile);
    
    void setDataDir(const std::string &_datadir) {
        dataDir = _datadir;
    }

    void setStyleFile(const std::string &_styleFile) {
        styleFile = _styleFile;
    }

    void setStyleCssFile(const std::string &_styleFile) {
        styleCssFile = _styleFile;
    }

    void setStyleDefaultFile(const std::string &_styleDefaultFile) {
        styleDefaultFile = _styleDefaultFile;
    }

    void setTitle(const std::string &_title) {
        title = _title;
    }

    void setCss(const std::string &_css) {
        css = _css;
    }

    void setHeaderFileName(const std::string &h) {
        headerFileName = h;
    }

    void setFooterFileName(const std::string &f) {
        footerFileName = f;
    }

    void setOutputDir(const std::string &_outputDir) {
        outputFileDir = _outputDir;
    }

    const TextStyleFormatterCollection &getFormatterCollection() const {
        return formatterCollection;
    }

    void setOptimize(bool b = true) {
        optimize = b;
    }

    void setGenerateLineNumbers(bool b = true) {
        generateLineNumbers = b;
    }

    void setGenerateLineNumberRefs(bool b = true) {
        generateLineNumberRefs = b;
    }

    void setLineNumberPad(char c) {
        lineNumberPad = c;
    }

    void setLineNumberAnchorPrefix(const std::string &_prefix) {
        lineNumberAnchorPrefix = _prefix;
    }

    void setGenerateEntireDoc(bool b = true) {
        generateEntireDoc = b;
    }

    void setGenerateVersion(bool b = true) {
        generateVersion = b;
    }

    void setCanUseStdOut(bool b = true) {
        canUseStdOut = b;
    }

    void setHighlightEventListener(HighlightEventListener *l) {
        highlightEventListener = l;
    }

    DocGenerator *getDocGenerator() const {
        return docGenerator;
    }

    DocGenerator *getNoDocGenerator() const {
        return noDocGenerator;
    }

    void setCTagsManager(CTagsManager *m) {
        ctagsManager = m;
    }

    void setTabSpaces(unsigned int i) {
        tabSpaces = i;
    }
};

#endif /*SOURCEHIGHLIGHT_H_*/
