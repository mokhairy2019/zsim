/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2013   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


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

    class  zsExportModuleManager : public zsModuleManager< zsExportModule >
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

