#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class QSettings;

namespace GitHubGist {
namespace Internal {

class Settings
{
public:
    Settings();
    void save(QSettings *settings) const;
    void load(QSettings *settings);
    bool equals(const Settings &rhs) const;
    bool isAnonymous() const;

    QString username;
    QString token;
    bool autoCopyLink;
};


inline bool operator==(const Settings &s1, const Settings &s2)
{
    return s1.equals(s2);
}

inline bool operator!=(const Settings &s1, const Settings &s2)
{
    return !s1.equals(s2);
}

} // namespaceGists
} // namespace Internal
#endif // SETTINGS_H
