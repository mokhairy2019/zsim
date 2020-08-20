//
// Created by Mokhairy on 7/20/2020.
//

#ifndef ZSIM_ZSMONITORMANAGER_H
#define ZSIM_ZSMONITORMANAGER_H

#include "zsModuleManager.h"
#include "zsMonitor.h"

namespace zsim {
    /**
 * Class representing and implementing MonitorManager. It is attribute of EngngModel.
 * It manages individual monitors, which perform monitor - specific output operations.
 * Monitors can be called at user specific events, such as time step termination, etc.
 * The event type is preopagated to each monitor.
 */
    class ZSIM_EXPORT zsMonitorManager : public zsModuleManager< zsMonitor >{

    public:
        zsMonitorManager(zsEngngModel * emodel);
        virtual ~zsMonitorManager();

        void initializeFrom(zsInputRecord &ir) override;


        std::unique_ptr<zsMonitor> CreateModule(const char *name, int num, zsEngngModel *emodel) override;
        /**
         * Writes the output. Loops over all modules and calls corresponding doOutput module service.
         * @param tStep Time step.
         * @param substepFlag is set to true, only the modules with substepFlag set to true will be processed.
         */
        
        void update(zsTimeStep *tStep, zsMonitor::zsMonitorEvent event);

        const char *giveClassName() const override { return "MonitorManager"; }
    };

}


#endif //ZSIM_ZSMONITORMANAGER_H
