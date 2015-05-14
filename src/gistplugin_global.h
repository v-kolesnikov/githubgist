#ifndef GISTPLUGIN_GLOBAL_H
#define GISTPLUGIN_GLOBAL_H

#include <QtGlobal>

#if defined(GITHUBGIST_LIBRARY)
#  define GITHUBGISTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GITHUBGISTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GISTPLUGIN_GLOBAL_H

