#include <string>

#include "qvector.h"
#include "gadgetfinder.h"
#include "binaryfile.h"
#include "headermatch.h"
#include "headers/sectionheader.h"

#include <iostream>

using namespace std;

qvector<HeaderMatch<SectionHeader>> GadgetFinder::FindGadget(BinaryFile fileInfo, string gadget) {
    auto result = qvector<HeaderMatch<SectionHeader>>();

    auto headers = fileInfo.section_headers
        .where([] (auto header) { return header.type == SECT_PROGRAM; })
        .where([] (auto header) { return header.flags & SECT_EXECUTE; })
        .where([&gadget] (auto header) { return header.contents.find(gadget) != string::npos; });

    for (auto header: headers) {
        auto contents = string(header.contents);
        long index = 0;

        while ((index = contents.find(gadget)) != string::npos) {
            result.push_back(HeaderMatch<SectionHeader>(header, header.address + index));
            contents = contents.substr(index+1);
        }
    }

    return result;
}
