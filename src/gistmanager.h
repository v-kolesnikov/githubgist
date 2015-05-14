#ifndef GISTSMANAGER_H
#define GISTSMANAGER_H

#include "settings.h"

#include <QObject>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class QNetworkAccessManager;
class QNetworkRequest;
QT_END_NAMESPACE

namespace Gists {
namespace Internal {

class GistManager : public QObject
{
    Q_OBJECT
public:
    explicit GistManager(const QSharedPointer<Settings> &settings, QObject *parent = 0);

    void postGist(const QString &text, const QString &gistName,
                  const QString &fileName, bool publicFlag = false);

    void setUserName(const QString &name);
    void setOAuthToken(const QString &token);

signals:
    void gistPosted(const QString &name, const QString &url);
    void apiError(const QString &error);

private:
    void setAuthHeader(QNetworkRequest *request);
    void apiResponse();

    QNetworkAccessManager *m_nam;
    const QSharedPointer<Settings> m_settings;
};

} // namespace Internal
} // namespace Gists

#endif // GISTSMANAGER_H
