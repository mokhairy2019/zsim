//
// Created by Mokhairy on 7/20/2020.
//

#include "zsMonitorManager.h"
#include "zsMonitor.h"

namespace zsim {
    zsMonitorManager::zsMonitorManager(zsEngngModel *emodel) : zsModuleManager<zsMonitor> (emodel) { }

    zsMonitorManager::~zsMonitorManager() { }

    void zsMonitorManager::initializeFrom(zsInputRecord &ir) {
        this->numberOfModules = 0;
        //TODO: Reactivate this
        //IR_GIVE_OPTIONAL_FIELD(ir, numberOfModules, "nmonitors");

    }

   std::unique_ptr<zsMonitor> zsMonitorManager::CreateModule(const char *name, int num, zsEngngModel *emodel) {
       return 0;
   }


}
