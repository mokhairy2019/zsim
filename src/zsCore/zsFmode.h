//
// Created by Mokhairy on 7/20/2020.
//

#ifndef ZSIM_ZSFMODE_H
#define ZSIM_ZSFMODE_H
namespace zsim {
    /**
   * Type representing the type of formulation (total or updated) of non-linear computation.
   */
    enum zsFMode {
        UNKNOWN = 0, ///< Unknown.
        TL = 1,      ///< Total Lagrange.
        AL = 2,      ///< Updated Lagrange.
    };
}
#endif //ZSIM_ZSFMODE_H
