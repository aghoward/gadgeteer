#include <functional>
#include <memory>
#include <string>

#include "cdif/cdif.h"
#include "fileparser.h"
#include "files/filereader.h"
#include "factories/elfheaderfactory.h"
#include "factories/factoriesmodule.h"
#include "factories/programheaderfactory.h"
#include "factories/sectionheaderfactory.h"
#include "fileparser.h"
#include "files/filesmodule.h"
#include "gadgeteermodule.h"

void GadgeteerModule::Load(cdif::Container & ctx) {
    RegisterModules(ctx);

    ctx.Register<FileParser,
        std::function<std::shared_ptr<FileReader> (std::string)>,
        std::function<std::unique_ptr<ElfHeaderFactory> (std::shared_ptr<FileReader>)>,
        std::function<std::unique_ptr<ProgramHeaderFactory> (std::shared_ptr<FileReader>)>,
        std::function<std::unique_ptr<SectionHeaderFactory> (std::shared_ptr<FileReader>)>>();
}

void GadgeteerModule::RegisterModules(cdif::Container & ctx) {
    ctx.RegisterModule<FactoriesModule>();
    ctx.RegisterModule<FilesModule>();
}
