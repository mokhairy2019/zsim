//
// Created by Mokhairy on 8/14/2020.
//

#ifndef ZSIM_ZSMONITOR_H
#define ZSIM_ZSMONITOR_H

#include "zsCore/zsExport.h"

namespace zsim {
    class zsEngngModel;
    class zsTimeStep;
    class zsInputRecord;
///@name Input fields for Monitor
//@{
#define _IFT_DummyMonitor_Name "dummymonitor"

/**
 * Class representing monitor, an abstract class inplementing solution monitor.
 * Monitors are managed by MonitorManager and are invoked at user controlled events, such as solution step termoination.
 * Derived classes can perform specific actions (updating model, plotting proogress, etc)
 */
    class ZSIM_EXPORT zsMonitor {
    protected:
        index_t number;

    public:

        enum zsMonitorEvent {
            TimeStepTermination
        };

    public:
        zsMonitor(index_t n) : number(n) {}

        virtual ~zsMonitor() { };

        /// Initializes receiver according to object description stored in input record.
        virtual void initializeFrom(zsInputRecord &ir) = 0;

        /**
        * updates the monitor state. This can also mean updating received eModel state.
        * @param eModel instance of EngngModel
        * @param tStep time step
        * @param event event type
        */
        virtual void update(zsEngngModel* eModel, zsTimeStep *tStep, zsMonitorEvent event) = 0;

        /// Returns class name of the receiver.
        virtual const char *giveClassName() const = 0;

    };

}


#endif //ZSIM_ZSMONITOR_H
