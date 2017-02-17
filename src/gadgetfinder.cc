#include <memory>
#include <string>

#include "queryalgorithms.h"
#include "gadgetfinder.h"
#include "binaryfile.h"
#include "headermatch.h"
#include "headers/sectionheader.h"

#include <iostream>

using namespace std;

vector<HeaderMatch<shared_ptr<SectionHeader>>> GadgetFinder::FindGadget(shared_ptr<BinaryFile> fileInfo, string gadget) {
    auto result = vector<HeaderMatch<shared_ptr<SectionHeader>>>();

    auto executableHeaders = filter(fileInfo->section_headers, [] (auto header) { return header->flags & SECT_EXECUTE && header->type == SECT_PROGRAM; });
    auto headers = filter(executableHeaders, [&gadget] (auto header) { return header->contents.find(gadget) != string::npos; });

    for (auto header: headers) {
        auto contents = string(header->contents);
        long index = 0;

        while ((index = contents.find(gadget)) != string::npos) {
            result.push_back(HeaderMatch<shared_ptr<SectionHeader>>(header, header->address + index));
            contents = contents.substr(index+1);
        }
    }

    return result;
}

vector<HeaderMatch<shared_ptr<SectionHeader>>> GadgetFinder::FindAllGadgets(shared_ptr<BinaryFile> fileInfo, vector<string> gadgets) {
    auto ret = vector<HeaderMatch<shared_ptr<SectionHeader>>>();

    for (auto gadget : gadgets) {
        auto newGadgets = FindGadget(fileInfo, gadget);
        ret.insert(ret.end(), newGadgets.begin(), newGadgets.end());
    }

    return ret;
}
