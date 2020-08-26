//
// Created by Mokhairy on 7/22/2020.
//

#ifndef ZSIM_ZSEXPORTMODULE_H
#define ZSIM_ZSEXPORTMODULE_H


#include "zsIntArray.h"
#include "zsCore/zsExport.h"
/*#include "inputrecord.h"
#include "range.h"
#include "set.h"*/

#include <list>

///@name Input fields for export module
//@{
#define _IFT_ExportModule_tstepall "tstep_all"
#define _IFT_ExportModule_tstepstep "tstep_step"
#define _IFT_ExportModule_tstepsout "tsteps_out"
#define _IFT_ExportModule_subtstepsout "subtsteps_out"
#define _IFT_ExportModule_domainall "domain_all"
#define _IFT_ExportModule_domainmask "domain_mask"
#define _IFT_ExportModule_regionsets "regionsets"
#define _IFT_ExportModule_timescale "timescale"
#define _IFT_ExportModule_pythonexport "pythonexport"
//@}

namespace zsim  {
    class zsEngngModel;
    class zsTimeStep;

/**
 * Represents export output module - a base class for all output modules. ExportModule is an abstraction
 * for module performing some specific kind of output. The modules can declare necessary component
 * services using the interface concept. The basic class declares the basic services (the general
 * interface) and implements the services intended to filter output to certain time steps.
 * The output modules are maintained by ExportModuleManager.
 * The output for given time step is done only if this step is selected by one of above
 * described method.
 */
    class ZSIM_EXPORT zsExportModule {

    };

}


#endif //ZSIM_ZSEXPORTMODULE_H
