#pragma once

#include <functional>
#include <memory>
#include <string>

#include "cdif/cdif.h"
#include "files/filereader.h"

class FilesModule : public cdif::IModule {
    public:
        void Load(cdif::Container & ctx);
};
