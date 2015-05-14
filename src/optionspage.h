#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include "settings.h"

#include <coreplugin/dialogs/ioptionspage.h>

#include <QWidget>
#include <QPointer>

namespace Ui {
class OptionsWidget;
}

namespace GitHubGist {
namespace Internal {

/*!
 * \brief The OptionsWidget class
 */

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();

    void setSettings(const Settings &settings);
    Settings settings();

private:
    Ui::OptionsWidget *m_ui;
};

/*!
 * \brief The SettingsPage class
 */

class OptionsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    explicit OptionsPage(const QSharedPointer<Settings> &settings,
                         QObject *parent = 0);
    ~OptionsPage();

    QWidget *widget() override;
    void apply() override;
    void finish()  override;

private:
    const QSharedPointer<Settings> m_settings;
    QPointer<OptionsWidget> m_widget;
};

} // namespace Internal
} // namespace GitHubGist

#endif // SETTINGSPAGE_H
