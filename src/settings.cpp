#include "settings.h"

#include <QSettings>

namespace GitHubGist {
namespace Internal {

QLatin1String SETTINGS_GROUP("GitHubGist");
QLatin1String USER_NAME("UserName");
QLatin1String OAUTH_TOKEN("OAuthToken");
QLatin1String AUTO_COPY_LINK("AutoCopyLink");

Settings::Settings() :
    autoCopyLink(true)
{
}

void Settings::save(QSettings *settings) const
{
    settings->beginGroup(SETTINGS_GROUP);
    settings->setValue(USER_NAME, username);
    settings->setValue(OAUTH_TOKEN, token);
    settings->setValue(AUTO_COPY_LINK, autoCopyLink);
    settings->endGroup();
}

void Settings::load(QSettings *settings)
{
    const QString rootKey = SETTINGS_GROUP + QLatin1Char('/');
    username = settings->value(rootKey + USER_NAME, QString()).toString();
    token = settings->value(rootKey + OAUTH_TOKEN, QString()).toString();
    autoCopyLink = settings->value(rootKey + AUTO_COPY_LINK, true).toBool();
}

bool Settings::equals(const Settings &rhs) const
{
    return (username == rhs.username
            && token == rhs.token
            && autoCopyLink == rhs.autoCopyLink);
}

bool Settings::isAnonymous() const
{
    return (username.isEmpty()
            || token.isEmpty());
}

} // namespaceGists
} // namespace Internal
