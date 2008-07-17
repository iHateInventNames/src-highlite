//
// C++ Interface: parsestyles
//
// Description: declaration of function for parsing style files
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004-2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef PARSESTYLES_H
#define PARSESTYLES_H

class TextStyleFormatterFactory;

/// for style files
void parseStyles(const std::string &path, const std::string &name,
        TextStyleFormatterFactory *formatterFactory, std::string &bodyBgColor);
void parseStyleError(const std::string &error);

/// for css style files
void parseCssStyles(const std::string &path, const std::string &name,
        TextStyleFormatterFactory *formatterFactory, std::string &bodyBgColor);

#endif
