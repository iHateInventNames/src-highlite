//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef CTAGSCOLLECTOR_H_
#define CTAGSCOLLECTOR_H_

#include <string>
#include <list>

#include "refposition.h"
#include "readtags.h"

class FormatterParams;

/**
 * Information about a tag.  This structure is used to
 * return collected information.
 */
struct CTagsInfo {
    /// the filename of a tag
    std::string fileName;

    /// the line number
    std::string lineNumber;

    /// where the reference should be positioned (only valid if !isAnchor)
    RefPosition refposition;

    /// whether the information concerns an anchor and not a reference
    bool isAnchor;

    CTagsInfo(const std::string &_fileName, const std::string &_lineNumber,
            RefPosition _refposition, bool _isAnchor) :
        fileName(_fileName), lineNumber(_lineNumber),
                refposition(_refposition), isAnchor(_isAnchor) {

    }
};

/**
 * The collection of information about a tag.
 */
typedef std::list<CTagsInfo> CTagsInfos;

/**
 * Collects the tags information generated by the ctags program for
 * a given word
 */
class CTagsCollector {
    /// where references should be positioned
    RefPosition refposition;

    /// the ctags file
    tagFile *ctags_file;

    /// information about the ctags being examined (not really used)
    tagFileInfo info;

public:
    /**
     * @param ctags_file_name the name of the ctags file
     * @param pos where the reference should be generated
     * @throws IOException if the file cannot be opened
     */
    CTagsCollector(const std::string &ctags_file_name, RefPosition pos);
    ~CTagsCollector();

    /**
     * Collects the tag information about the specified word and stores them
     * into the passed collection
     * @param word the word to collect tag information about
     * @param infos where to store the information
     * @param fileInfo information about the word being processed
     * @return false whether we did not find any information about the passed word
     */
    bool collectTags(const std::string &word, CTagsInfos &infos,
            const FormatterParams *fileInfo);

    void setRefPosition(RefPosition r) {
        refposition = r;
    }
};

#endif /*CTAGSCOLLECTOR_H_*/
