#ifndef HTML_H
#define HTML_H

#include <QString>

/// Add HTML flavor to a string
class Html
{
public:
    /// Make text gray
    static QString gray(QString str);

    /// Make text white
    static QString white(QString str);

    /// Make text italic
    static QString italic(QString str);

    /// Make text strong
    static QString strong(QString str);

    /// Make text to be link
    static QString link(QString str);
};

#endif // HTML_H
