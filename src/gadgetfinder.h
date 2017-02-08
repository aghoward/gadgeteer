#ifndef GadgetFinder_H
#define GadgetFinder_H

#include <memory>

#include "headermatch.h"
#include "qvector.h"
#include "binaryfile.h"
#include "headers/sectionheader.h"

using namespace std;

class GadgetFinder {
    public:
        static qvector<HeaderMatch<shared_ptr<SectionHeader>>> FindGadget(shared_ptr<BinaryFile> fileInfo, string gadget);
        static qvector<HeaderMatch<shared_ptr<SectionHeader>>> FindAllGadgets(shared_ptr<BinaryFile> fileInfo, qvector<string> gadgets);
};


#endif
