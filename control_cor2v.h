#ifndef CONTROL_COR2V_H
#define CONTROL_COR2V_H

#include "control_cor2v_global.h"

class CONTROL_COR2VSHARED_EXPORT Control_cor2v
{

public:
    Control_cor2v();
    double * decision (double ** Cor_Car);
};

#endif // CONTROL_COR2V_H
