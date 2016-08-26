#include "html.h"

QString Html::gray(QString str)
{
    return "<p style='color: gray'>" + str + "</p>";
}

QString Html::white(QString str)
{
    return "<p style='color: white'>" + str + "</p>";
}

QString Html::italic(QString str)
{
    return "<i>" + str + "</i>";
}

QString Html::strong(QString str)
{
    return "<strong>" + str + "</strong>";
}

QString Html::link(QString str)
{
    return "<a href='#'>" + str + "</a>";
}
