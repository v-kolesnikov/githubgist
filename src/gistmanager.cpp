#include "gistmanager.h"

#include <utils/networkaccessmanager.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace GitHubGist::Internal;

QLatin1String API_BASE_URL("https://api.github.com");
QLatin1String API_GIST("/gists");
QLatin1String API_GIST_PUBLIC("/gists/public");
QLatin1String API_USER_INFO("/user");

QLatin1String JSON_CONTENT("content");
QLatin1String JSON_DESCR("description");
QLatin1String JSON_FILES("files");
QLatin1String JSON_HTML_URL("html_url");
QLatin1String JSON_MESSAGE("message");
QLatin1String JSON_PUBLIC("public");

GistManager::GistManager(const QSharedPointer<Settings> &settings, QObject *parent) :
    QObject(parent),
    m_nam(Utils::NetworkAccessManager::instance()),
    m_settings(settings)
{
}

void GistManager::postGist(const QString &text, const QString &gistName,
                           const QString &fileName, bool publicFlag)
{
    QNetworkRequest request(QUrl(API_BASE_URL + API_GIST));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QByteArray("application/json"));

    if (!m_settings->isAnonymous()) {
        setAuthHeader(&request);
    }

    QJsonObject file;
    file.insert(JSON_CONTENT, text);

    QJsonObject files;
    files.insert(fileName, file);

    QJsonObject postData;
    postData.insert(JSON_FILES, files);
    postData.insert(JSON_DESCR, gistName);
    postData.insert(JSON_PUBLIC, publicFlag);

    QNetworkReply *reply = m_nam->post(request, QJsonDocument(postData).toJson());

    connect(reply, &QNetworkReply::finished, this, &GistManager::apiResponse);
}

/*!
 * \brief GistManager::makeAuthRequest
 *
 * HTTP Basic authentication:
 * header name: "Authorization"
 * header value: "Basic + base64(username:password)"
 */

void GistManager::setAuthHeader(QNetworkRequest *request)
{
    QByteArray headerData = QByteArray("Basic ")
            + QString(QLatin1String("%1:%2"))
            .arg(m_settings->username)
            .arg(m_settings->token)
            .toLocal8Bit()
            .toBase64();
    request->setRawHeader("Authorization", headerData);
}

void GistManager::apiResponse()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    quint32 httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    QJsonDocument jsonReply = QJsonDocument::fromJson(reply->readAll());

    switch (httpStatusCode) {
    case 200:   //! 200 OK
        break;
    case 201: { //! 201 Created
        QString name = jsonReply.object().value(JSON_DESCR).toString();
        QString url = jsonReply.object().value(JSON_HTML_URL).toString();
        emit gistPosted(name, url);
        break;
    }
    default:
        QString error = jsonReply.object().value(JSON_MESSAGE).toString();
        emit apiError(tr("Gist API ERROR: ") + error);
        break;
    }

    reply->deleteLater();
}

