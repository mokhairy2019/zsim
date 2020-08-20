//
// Created by Mokhairy on 7/21/2020.
//

#ifndef ZSIM_ZSINITMODULEMANAGER_H
#define ZSIM_ZSINITMODULEMANAGER_H

#include "zsCore/zsExport.h"
#include "zsInitModule.h"
#include "zsModuleManager.h"

namespace zsim{
    class zsEngngModel;
    /**
 * Class representing and implementing InitModuleManager. It is attribute of EngngModel.
 * It manages the init modules, which perform module - specific init oprations.
 */
    class ZSIM_EXPORT zsInitModuleManager : public zsModuleManager<zsInitModule> {
    public:
        zsInitModuleManager(zsEngngModel * emodel);
        virtual ~zsInitModuleManager ();

        std::unique_ptr<zsInitModule> CreateModule(const char *name, int n, zsEngngModel *emodel) override;

        /**
    * Performs the initialization of individual modules.
    * Loops over all modules and calls corresponding doInit module service.
    */
        void doInit();

        void initializeFrom(zsInputRecord &ir) override;

        const char *giveClassName() const override { return "InitModuleManager"; }

    };
}



#endif //ZSIM_ZSINITMODULEMANAGER_H
