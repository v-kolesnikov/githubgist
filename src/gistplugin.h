#ifndef GISTPLUGIN_H
#define GISTPLUGIN_H

#include "gistplugin_global.h"

#include <extensionsystem/iplugin.h>

namespace GistPlugin {
namespace Internal {

class GistPluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "GistPlugin.json")

public:
    GistPluginPlugin();
    ~GistPluginPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void triggerAction();
};

} // namespace Internal
} // namespace GistPlugin

#endif // GISTPLUGIN_H

