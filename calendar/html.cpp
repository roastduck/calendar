#include "html.h"

QString Html::gray(QString str)
{
    return "<p style='color: gray'>" + str + "</p>";
}

QString Html::italic(QString str)
{
    return "<i>" + str + "</i>";
}

QString Html::strong(QString str)
{
    return "<strong>" + str + "</strong>";
}
