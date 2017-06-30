#pragma once

#include <functional>
#include <memory>
#include <string>

#include "cdif/cdif.h"
#include "files/filereader.h"
#include "factories/elfheaderfactory.h"
#include "factories/factoriesmodule.h"
#include "factories/programheaderfactory.h"
#include "factories/sectionheaderfactory.h"
#include "fileparser.h"
#include "files/filesmodule.h"

class GadgeteerModule : cdif::IModule {
    private:
        void RegisterModules(cdif::Container &);

    public:
        void Load(cdif::Container &);
};
