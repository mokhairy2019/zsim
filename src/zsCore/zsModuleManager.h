//
// Created by Mokhairy on 8/11/2020.
//

#ifndef ZSIM_ZSMODULEMANAGER_H
#define ZSIM_ZSMODULEMANAGER_H

#include "zsForwardDeclarations.h"
#include "zsInputRecord.h"
#include "zsDataReader.h"

namespace zsim {
    class zsEngngModel;

    /**
     * Class representing and implementing ModuleManager. It is attribute of EngngModel.
     * It manages the modules of given type.
     */
    template <class M>
    class ZSIM_EXPORT zsModuleManager {
    protected:
        /// Module list
        std::vector<std::unique_ptr<M>> moduleList;
        ///Number of modules
        index_t numberOfModules;
        /// Associated Engineering Model
        zsEngngModel *emodel;

    public:
        zsModuleManager(zsEngngModel *emodel){
            this->emodel = emodel;
            numberOfModules = 0;
        }
        virtual ~zsModuleManager(){ }
        zsModuleManager(const zsModuleManager &) = delete;
        zsModuleManager & operator= (const zsModuleManager &) = delete;
        /**
 * Creates new instance of module.
 * @param name Name of module.
 * @param n Number associated with module.
 * @param emodel Engineering model which receiver belongs to.
 */
        virtual std::unique_ptr<M> CreateModule(const char *name, index_t n, zsEngngModel *emodel) = 0;

        /**
 * Instanciates the receiver from input record. Called from instanciateYourself to initialize yourself
 * from corresponding record. Should be called before instanciateYourself.
 */
        virtual void initializeFrom(zsInputRecord &ir) = 0;
        /**
    *
    * Reads receiver description from input stream and creates corresponding modules components accordingly.
    * It scans input file, each line is assumed to be single record describing particular module.
    * The record line is converted to lowercase letters.
    * After new output module object is created, its initializeForm member function is
    * called with its record as parameter.
    * @param dr Data reader for input records.
    * @param ir Record for receiver.
    * @return Nonzero if o.k.
    */
        virtual index_t instanciateYourself(zsDataReader &dr, zsInputRecord &ir) {
            std :: string name;

            // read modules
            moduleList.reserve(numberOfModules);
            for ( index_t i = 0; i < numberOfModules; i++ ) {
                //auto &mir = dr.giveInputRecord(zsDataReader :: IR_expModuleRec, i + 1);
                //mir.giveRecordKeywordField(name);

                // read type of module
                std :: unique_ptr< M > module = this->CreateModule(name.c_str(), i, emodel);
                if ( !module ) {
                    // TODO:: error module should be modified
                    //ZSIM_ERROR("unknown module (%s)", name.c_str());
                }

                //module->initializeFrom(mir);
                //registerModule(module);
        }
#  ifdef VERBOSE
            VERBOSE_PRINT0("Instanciated output modules ", numberOfModules)
#  endif
            return 1;
        }

        /**
         * Stores a module in moduleList. Useful when
         * adding modules externally, e.g. from Python
         */

        virtual void registerModule (std::unique_ptr< M > &module){
            moduleList.push_back(std::move(module));
        }


        /// Returns class name of the receiver.
        virtual const char *giveClassName() const = 0;

        /**
    * Returns the required module.
    * @param num Module number.
    */
        M *giveModule(index_t num) {
            M *elem = NULL;

            if ( num >= 1 && num <= (index_t)moduleList.size() ) {
                elem = moduleList[num-1].get();
            } else {
                // TODO:: error module should be modified
                //ZSIM_ERROR("No module no. %d defined", num);
            }

            return elem;
        }

        index_t giveNumberOfModules() const { return (index_t)moduleList.size(); }
    }; // End of calss zsModuleManager
} // End of namespace zsim
#endif //ZSIM_ZSMODULEMANAGER_H
