#ifndef PINCODEDLL_GLOBAL_H
#define PINCODEDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PINCODEDLL_LIBRARY)
#  define PINCODEDLLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PINCODEDLLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PINCODEDLL_GLOBAL_H

