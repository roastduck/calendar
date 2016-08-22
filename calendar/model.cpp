#include "model.h"

Model::Model()
{
    mModel = new QStandardItemModel();
}

Model::~Model()
{
    delete mModel;
}
