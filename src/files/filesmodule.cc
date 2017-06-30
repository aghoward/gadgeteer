#include <functional>
#include <memory>
#include <string>

#include "cdif/cdif.h"
#include "files/filesmodule.h"
#include "files/filereader.h"

void FilesModule::Load(cdif::Container & ctx) {
    std::function<std::shared_ptr<FileReader> (std::string)> factory =
        [] (auto filename) { return std::make_shared<FileReader>(filename); };
    ctx.RegisterFactory<std::shared_ptr<FileReader>, std::string>(factory);
}
