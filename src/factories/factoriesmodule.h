#pragma once

#include <functional>
#include <memory>

#include "cdif/cdif.h"
#include "factories/elfheaderfactory.h"
#include "factories/programheaderfactory.h"
#include "factories/sectionheaderfactory.h"
#include "files/filereader.h"

class FactoriesModule : cdif::IModule {
    public:
        void Load(cdif::Container & ctx);
};
