#ifndef EORM_GLOBAL_H
#define EORM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EORM_LIBRARY)
#  define EORMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EORMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EORM_GLOBAL_H
