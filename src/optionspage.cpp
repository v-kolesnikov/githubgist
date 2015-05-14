#include "optionspage.h"
#include "ui_optionspage.h"
#include "gistpluginconstants.h"

#include <coreplugin/icore.h>

#include <QDesktopServices>
#include <QUrl>

namespace GitHubGist {
namespace Internal {

OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::OptionsWidget)
{
    m_ui->setupUi(this);
    m_ui->footerLabel->setPixmap(QPixmap(QLatin1String(":/images/octocat.png")));

    connect(m_ui->signUpButton, &QPushButton::clicked, this, &OptionsWidget::openGitHubSignUp);
    connect(m_ui->tokensButton, &QPushButton::clicked, this, &OptionsWidget::openGitHubTokens);
}

OptionsWidget::~OptionsWidget()
{
    delete m_ui;
}

void OptionsWidget::setSettings(const Settings &settings)
{
    m_ui->userEdit->setText(settings.username);
    m_ui->tokenEdit->setText(settings.token);
    m_ui->copyLinkBox->setChecked(settings.autoCopyLink);
}

Settings OptionsWidget::settings()
{
    Settings settings;
    settings.username = m_ui->userEdit->text();
    settings.token = m_ui->tokenEdit->text();
    settings.autoCopyLink = m_ui->copyLinkBox->isChecked();
    return settings;
}

void OptionsWidget::openGitHubSignUp()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/join")));
}

void OptionsWidget::openGitHubTokens()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://github.com/settings/tokens")));
}

OptionsPage::OptionsPage(const QSharedPointer<Settings> &settings, QObject *parent) :
    IOptionsPage(parent),
    m_settings(settings),
    m_widget(0)
{
    setId("GistsSettings");
    setDisplayName(tr("General"));
    setCategory(Constants::GIST_SETTINGS_CATEGORY);
    setDisplayCategory(tr(Constants::GIST_SETTINGS_TR_CATEGORY));
    setCategoryIcon(QLatin1String(Constants::GIST_SETTINGS_CATEGORY_ICON));
}

OptionsPage::~OptionsPage()
{

}

QWidget *OptionsPage::widget()
{
    if (!m_widget) {
        m_widget = new OptionsWidget;
        m_widget->setSettings(*m_settings);
    }
    return m_widget;
}

void OptionsPage::apply()
{
    if (!m_widget) // page was never shown
        return;
    const Settings newSettings = m_widget->settings();
    if (newSettings != *m_settings) {
        *m_settings = newSettings;
        m_settings->save(Core::ICore::settings());
    }
}

void OptionsPage::finish()
{
    delete m_widget;
}

} // namespace Internal
} // namespace GitHubGist
