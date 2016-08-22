#ifndef MONTHMODEL_H
#define MONTHMODEL_H

#include "model.h"

class MonthModel : public Model
{
    Q_OBJECT

public:
    MonthModel(int year, int month);
};

#endif // MONTHMODEL_H
