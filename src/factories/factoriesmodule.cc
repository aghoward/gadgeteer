#include <functional>
#include <memory>

#include "cdif/cdif.h"
#include "factories/elfheaderfactory.h"
#include "factories/factoriesmodule.h"
#include "factories/programheaderfactory.h"
#include "factories/sectionheaderfactory.h"
#include "files/filereader.h"

void FactoriesModule::Load(cdif::Container & ctx) {
    std::function<std::unique_ptr<SectionHeaderFactory> (std::shared_ptr<FileReader>)> shff = 
        [] (auto fr) { return std::make_unique<SectionHeaderFactory>(fr); };
    ctx.RegisterFactory<
        std::unique_ptr<SectionHeaderFactory>,
        std::shared_ptr<FileReader>>(shff);

    std::function<std::unique_ptr<ProgramHeaderFactory> (std::shared_ptr<FileReader>)> phff =
        [] (auto fr) { return std::make_unique<ProgramHeaderFactory>(fr); };
    ctx.RegisterFactory<
        std::unique_ptr<ProgramHeaderFactory>,
        std::shared_ptr<FileReader>>(phff);

    std::function<std::unique_ptr<ElfHeaderFactory> (std::shared_ptr<FileReader>)> ehff =
        [] (auto fr) { return std::make_unique<ElfHeaderFactory>(fr); };
    ctx.RegisterFactory<
        std::unique_ptr<ElfHeaderFactory>,
        std::shared_ptr<FileReader>>(ehff);
}
