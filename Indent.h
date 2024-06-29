/*
 * Copyright (C) 1996-2023 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

#ifndef SQUID_SRC_BASE_INDENT_H
#define SQUID_SRC_BASE_INDENT_H

#include <ostream>

class Indent {
    public:
        static const size_t STEP = 2;

        Indent indent() const {
            Indent rv(*this);
            rv.addSpaces(STEP);
            return rv;
        }

        void print(std::ostream &os) {
            os << spaces << (isVector ? VectorSuffix : Suffix);
            isVector = false;
        }

        auto& elem() {
            isVector = true;
            return *this;
        }

    private:
        void addSpaces(uint8_t howmuch) {
            spaces.append(howmuch, ' ');
        }

        // does not include the last two spaces, due to arrays
        std::string spaces;
        static const std::string Suffix,  // rely that STEP==2
            VectorSuffix;
        bool isVector = false;
};

const std::string Indent::Suffix("  "), Indent::VectorSuffix("- ");

std::string spaces(uint8_t howmuch, char c=' ') {
    return std::string(howmuch,' ');
}

std::ostream& operator<<(std::ostream& os, Indent& indent) {
    indent.print(os);
    return os;
}

#endif /* SQUID_SRC_BASE_INDENT_H */
