#ifndef zsExportModuleManager_h
#define zsExportModuleManager_h


#include "zsExportModule.h"
#include "zsInputRecord.h"
#include "zsModuleManager.h"

namespace zsim {
    class zsEngngModel;


/**
 * Class representing and implementing ExportModuleManager. It is attribute of EngngModel.
 * It manages the export output modules, which perform module - specific output operations.
 */

    class ZSIM_EXPORT  zsExportModuleManager : public zsModuleManager< zsExportModule >
{
    public:
    zsExportModuleManager(zsEngngModel * emodel);

    virtual ~zsExportModuleManager();

    void initializeFrom(zsInputRecord &ir) override;

    std::unique_ptr<zsExportModule> CreateModule(const char *name, int num, zsEngngModel *emodel) override;


/**
     * Writes the output. Loops over all modules and calls corresponding doOutput module service.
     * @param tStep Time step.
     * @param substepFlag is set to true, only the modules with substepFlag set to true will be processed.
     */

    void doOutput(zsTimeStep *tStep, bool substepFlag = false);

/**
     * Initializes output manager. The corresponding initialize module services are called.
     */

    void initialize();

/**
     * Terminates the receiver, the corresponding terminate module services are called.
     */

    void terminate();
    const char *giveClassName() const override { return "zsExportModuleManager"; }
};
} // end namespace zsim
#endif // zsExportModuleManager_h

