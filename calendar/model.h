#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QStandardItemModel>

class Model : public QObject
{
    Q_OBJECT

public:
    Model();
    ~Model();

    QStandardItemModel* getModel() const { return mModel; }

protected:
    QStandardItemModel *mModel;
};

#endif // MODEL_H
