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
subItemMap(std::ostream &o, const Indent &prefix,
           const StrMap &m, bool isVector=false)
{
    for (const auto &it : m) {
        if (isVector)
            o << prefix.elem();
        else
            o << prefix;
        o << it.first << ": " << it.second << "\n";
        isVector = false;
    }
}

void
subVectorMap(std::ostream &o, const Indent &prefix, const std::vector<StrMap> &m)
{
    for (const auto &it : m) {
        subItemMap(o, prefix, it, true);
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

    o << "**** using Indent()\n";
    Indent i0, i1 = i0.indent(), i2 = i1.indent();
    o << i0 << "level0.1:\n"
        << i1 << "level1.1:\n";
    subItemMap(o, i2, {{"a", "1"}, {"b", "2"}});
    o << i1 << "level1.2:\n";
    subItemMap(o, i2, {{"a", "4"}, {"b", "5"}});
    o << i0 << "level0.2:\n";
    o << i1.elem() << "k1: v1\n"
        << i1 << "k2: v2\n"
        << i1.elem() << "k1: v1\n"
        << i1 << "k2: v2\n";

    o << "**** using Indent() and scopes\n";
    o << i0 << "level0.1:\n";
    {
        auto i1=i0.indent();
        o << i1 << "level1.1:\n";
        subItemMap(o, i1.indent(), {{"a", "1"}, {"b", "2"}});
        o << i1 << "level1.2:\n";
        subItemMap(o, i1.indent(), {{"a", "4"}, {"b", "5"}});
    }
    o << i0 << "level0.2:\n";
    {
        auto i1 = i0.indent();
        subVectorMap(o, i1.indent(), {
            {{"k1", "v1"}, {"k2", "v2"}},
            {{"k1", "v1"}, {"k2", "v2"}}
        });
    }

    return 0;
}