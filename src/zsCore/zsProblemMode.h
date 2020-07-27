//
// Created by Mokhairy on 7/20/2020.
//

#ifndef ZSIM_ZSPROBLEMMODE_H
#define ZSIM_ZSPROBLEMMODE_H

namespace zsim{
    enum zsProblemMode {
        _processor,
        _postProcessor
    };

}

/// Corresponds to macro- and micro-problem in multiscale simulations.
enum problemScale{
    macroScale,
    microScale
};


#endif //ZSIM_ZSPROBLEMMODE_H
