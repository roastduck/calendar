#ifndef HTML_H
#define HTML_H

#include <QString>

/// Add HTML flavor to a string
class Html
{
public:
    static QString gray(QString str);
    static QString white(QString str);
    static QString italic(QString str);
    static QString strong(QString str);
};

#endif // HTML_H
