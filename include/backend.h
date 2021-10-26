#ifndef BALANCES_H
#define BALANCES_H

#include "rpc.h"
#include "tokeninfo.h"

class Backend : public QObject {
	Q_OBJECT
	Q_PROPERTY(
		QVariant tokens_info_list READ get_tokens_info_list NOTIFY on_update)
	Q_PROPERTY(QVariantList own_tokens READ get_own_tokens NOTIFY on_update)
	Q_PROPERTY(QVariantList networks READ get_networks NOTIFY on_update)

	Q_PROPERTY(QVariantList supported_deposit_tokens READ
			get_supported_deposit_tokens NOTIFY on_change_network)

	Q_PROPERTY(QVariantList supported_withdraw_tokens READ
			get_supported_withdraw_tokens NOTIFY on_change_network)

	Q_PROPERTY(QString wallet_address READ get_address NOTIFY on_update)

	Q_PROPERTY(
		QString notification READ get_notification NOTIFY send_notification)

public:
	Backend(rpc::RpcClient* rpc_client);
	~Backend();
	QVariant get_tokens_info_list();
	QVariantList get_own_tokens();
	QVariantList get_networks();
	QVariantList get_supported_deposit_tokens();
	QVariantList get_supported_withdraw_tokens();
	QString get_address();
	QString get_notification();

public slots:
	void update();
	void on_select_network(QString network);
	void on_deposit(QString token);
	void on_transfer(QString token, QString address, QString amount);
	void on_withdraw(QString token, QString token_address, QString amount);

signals:
	void on_update();
	void on_change_network();
	void send_notification();

private:
	QList<TokenInfo*> tokens_info_list;
	QVariantList own_tokens;
	QVariantList networks;
	QMap<QString, QVariantList> supported_deposit_tokens;
	rpc::RpcClient* rpc_client;
	QString selected_network;
	QString wallet_address;
	QString notification;

	bool handle_error(boost::json::object& obj);
};

#endif // BALANCES_H
