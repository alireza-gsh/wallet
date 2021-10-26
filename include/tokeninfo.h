#ifndef TOKENINFO_H
#define TOKENINFO_H

#include <QString>
#include <QVariant>

class TokenInfo : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString name READ get_name NOTIFY tokenChange)
	Q_PROPERTY(QString value READ get_value NOTIFY tokenChange)
	Q_PROPERTY(QString network READ get_network NOTIFY tokenChange)

public:
	TokenInfo(QString name, QString value, QString network);

	QString get_name();
	QString get_value();
	QString get_network();

signals:
	void tokenChange();

private:
	QString name;
	QString value;
	QString network;
};

#endif // TOKENINFO_H
