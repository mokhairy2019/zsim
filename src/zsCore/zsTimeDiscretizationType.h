//
// Created by Mokhairy on 8/16/2020.
//

#ifndef ZSIM_ZSTIMEDISCRETIZATIONTYPE_H
#define ZSIM_ZSTIMEDISCRETIZATIONTYPE_H


namespace zsim {
    enum zsTimeDiscretizationType {
        TD_Unspecified         = -1,     ///< Unspecified
        TD_ThreePointBackward  =  0,     ///< Three-point Backward Euler method
        TD_TwoPointBackward    =  1,     ///< Two-point Backward Euler method
        TD_Newmark             =  2,     ///< Newmark-beta method
        TD_Wilson              =  3,     ///< Wilson-theta method
        TD_Explicit            =  4,     ///< Central difference
    };

}


#endif //ZSIM_ZSTIMEDISCRETIZATIONTYPE_H
