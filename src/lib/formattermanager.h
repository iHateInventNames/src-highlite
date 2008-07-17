//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2008
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FORMATTERMANAGER_H_
#define FORMATTERMANAGER_H_

#include <string>
#include <map>

#include "formatter.h"

typedef std::map<std::string, FormatterPtr> FormatterMap;

/**
 * Associates to an element name the corresponding formatter.
 * This class is the owner of each stored formatter
 */
class FormatterManager {
    /// the map associating to each element name a formatter
    mutable FormatterMap formatterMap;

    /// the default formatter, i.e., the one that is used when there's no
    /// formatter associated to an element name
    FormatterPtr defaultFormatter;
public:
    FormatterManager(FormatterPtr _defaultFormatter);
    ~FormatterManager();

    /**
     * Returns the formatter for the specific element (this function always returns
     * a valid pointer, since if no formatter is found for the specified element, it will
     * return the default formatter)
     * @param elem
     * @return the formatter for the specific element
     */
    FormatterPtr getFormatter(const std::string &elem) const;

    FormatterPtr getDefaultFormatter() const {
        return defaultFormatter;
    }

    void setDefaultFormatter(FormatterPtr def) {
        defaultFormatter = def;
    }

    /**
     * Returns the formatter for the specific element or an empty pointer if there's
     * no such formatter
     * @param elem
     * @return the formatter for the specific element or an empty pointer
     */
    FormatterPtr hasFormatter(const std::string &elem) const;

    /**
     * Associates the formatter to the element name (possible previous associated formatter
     * is discarded).
     * @param elem
     * @param formatter
     */
    void addFormatter(const std::string &elem, FormatterPtr formatter);
};

#endif /*FORMATTERMANAGER_H_*/
