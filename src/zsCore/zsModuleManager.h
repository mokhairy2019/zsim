//
// Created by Mokhairy on 8/11/2020.
//

#ifndef ZSIM_ZSMODULEMANAGER_H
#define ZSIM_ZSMODULEMANAGER_H
#include "zsExportModule.h"

namespace zsim {
    template <class M>
    class ZSIM_EXPORT zsModuleManager {


    public:
    /**
   * Creates new instance of module.
   * @param name Name of module.
   * @param n Number associated with module.
   * @param emodel Engineering model which receiver belongs to.
   */
        virtual std::unique_ptr<M> CreateModule(const char *name, int n, zsEngngModel *emodel) = 0;
        /**
         * Instanciates the receiver from input record. Called from instanciateYourself to initialize yourself
         * from corresponding record. Should be called before instanciateYourself.
         */
        virtual void initializeFrom(zsInputRecord &ir) = 0;

        /// Returns class name of the receiver.
        virtual const char *giveClassName() const = 0;

    };

}
#endif //ZSIM_ZSMODULEMANAGER_H
