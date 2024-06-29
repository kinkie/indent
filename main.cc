#include "Indent.h"
#include <iostream>
#include <map>

using StrMap=std::map<std::string, std::string>;

/* desired output:
---
level0.1:
  level1.1:
    a: 1
    b: 2
  level1.2:
    a: 4
    b: 5
level0.2:
  - k1: v1
    k2: v2
  - k1: v1
    k2: v2
 */

void
subItemMap(std::ostream &o, const std::string &prefix,
           const StrMap &m)
{
    for (const auto &it: m) {
        o << prefix << it.first << ": " << it.second << "\n";
    }
}
void
subItemMap(std::ostream &o, Indent &prefix,
           const StrMap &m)
{
    for (const auto &it : m) {
        o << prefix << it.first << ": " << it.second << "\n";
    }
}

int main()
{
    std::ostream& o=std::cout;

    o << "**** using spaces()\n"
        << "level0.1:\n"
        << spaces(2) << "level1.1:\n"
        << spaces(4) << "a: 1\n"
        << spaces(4) << "b: 2\n"
        << spaces(2) << "level1.2:\n"
        << spaces(4) << "a: 4\n"
        << spaces(4) << "b: 5\n"
        << "level0.2:\n"
        << spaces(2) << "- k1: v1\n"
        << spaces(4) << "k2: v2\n"
        << spaces(2) << "- k1: v1\n"
        << spaces(4) << "k2: v2\n";

    Indent i0;
    o << "**** using Indent()\n";
    o << i0 << "level0.1:\n";
    {
        auto i1=i0.indent();
        o << i1 << "level1.1:\n";
        {
            auto i2=i1.indent();
            StrMap m{{"a", "1"}, {"b", "2"}};
            subItemMap(o, i2, m);
        }
        o << i1 << "level1.2:\n";
        {
            auto i2=i1.indent();
            StrMap m{{"a", "4"}, {"b", "5"}};
            subItemMap(o, i2, m);
        }
    }
    o << i0 << "level0.2:\n";
    {
        auto i1=i0.indent();
        o << i1.elem() << "k1: v1\n"
            << i1 << "k2: v2\n"
            << i1.elem() << "k1: v1\n"
            << i1 << "k2: v2\n";

    }

    return 0;
}