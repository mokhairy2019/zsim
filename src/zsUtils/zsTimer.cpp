//
// Created by Mokhairy on 7/20/2020.
//

#include "zsTimer.h"

std::ostream &zsim::formatTime(std::ostream &os, double sec)  {
    int flo = (int)(sec);
    sec -= flo;
    int hh = flo / 3600;
    flo = flo  % 3600;
    int mm = flo / 60;
    double ss = (flo % 60) + sec;
    if (hh > 0) os << hh << "h ";
    if (mm > 0) os << mm << "m ";
    std::streamsize prec = os.precision();
    os.precision(2);
    os << ss << " s";
    os.precision(prec);
    return os;
}
