#ifndef GISTPLUGIN_H
#define GISTPLUGIN_H

#include "gistplugin_global.h"
#include "settings.h"

#include <extensionsystem/iplugin.h>

#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

namespace ProjectExplorer {
class Node;
}

namespace GitHubGist {
namespace Internal {

class GistManager;
class OptionsPage;

class GistPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "GitHubGist.json")

public:
    GistPlugin();
    ~GistPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    void createGistFromText();
    void createGistFromNode();

private:
    void initMenus();
    void initOptionsPage();
    void showMessage(const QString &message) const;
    void gistCreated(const QString &name, const QString &url) const;
    QStringList nodeFiles(const ProjectExplorer::Node *node) const;

    const QSharedPointer<Settings> m_settings;
    GistManager *m_gistManager;
    OptionsPage *m_optionsPage;
};

} // namespace Internal
} // namespace GitHubGist

#endif // GISTPLUGIN_H

