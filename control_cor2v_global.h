#ifndef CONTROL_COR2V_GLOBAL_H
#define CONTROL_COR2V_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONTROL_COR2V_LIBRARY)
#  define CONTROL_COR2VSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONTROL_COR2VSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONTROL_COR2V_GLOBAL_H
