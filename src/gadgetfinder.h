#ifndef GadgetFinder_H
#define GadgetFinder_H

#include "headermatch.h"
#include "qvector.h"
#include "binaryfile.h"
#include "headers/sectionheader.h"

class GadgetFinder {
    public:
        static qvector<HeaderMatch<SectionHeader *>> FindGadget(BinaryFile fileInfo, string gadget);
        static qvector<HeaderMatch<SectionHeader *>> FindAllGadgets(BinaryFile fileInfo, qvector<string> gadgets);
};


#endif
