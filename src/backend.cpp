#include "backend.h"

Backend::Backend(rpc::RpcClient* rpc_client)
	: rpc_client(rpc_client)
{
	// this hardcoded but it should get it from rpc function
	QVariantList solana_tokens { "SOL", "BTC", "USDC" };
	QVariantList bitcoin_tokens { "BTC" };
	supported_deposit_tokens.insert("solana", solana_tokens);
	supported_deposit_tokens.insert("bitcoin", bitcoin_tokens);

	// update address
	std::optional<boost::json::object> data
		= rpc_client->send_request(rpc::RpcMethods::get_key, {});

	if (data.has_value()) {
		boost::json::object obj = data.value();

		if (handle_error(obj)) {
			return;
		}

		QString result = obj["result"].as_string().c_str();

		wallet_address = result;
	}
}

Backend::~Backend() { delete rpc_client; }

bool Backend::handle_error(boost::json::object& obj)
{
	if (obj["result"].is_null()) {
		std::cerr << "BACKEND ERROR: " << obj["error"] << "\n";
		notification = "ERROR: ";

		notification.push_back(
			obj["error"].as_object()["message"].as_string().c_str());

		emit send_notification();
		return true;
	}

	return false;
}

void Backend::update()
{

	// update tokens_info_list
	std::optional<boost::json::object> data
		= rpc_client->send_request(rpc::RpcMethods::balances, {});

	if (data.has_value()) {
		boost::json::object obj = data.value();

		if (handle_error(obj)) {
			return;
		}

		tokens_info_list = {};
		own_tokens = {};

		boost::json::object result = obj["result"].as_object();

		for (auto tkn : result) {
			QString name(tkn.key().to_string().c_str());
			auto val = tkn.value().as_array();
			QString value(val[0].as_string().c_str());
			QString network(val[1].as_string().c_str());

			TokenInfo* token = new TokenInfo(name, value, network);

			tokens_info_list.append(token);
			own_tokens.append(name);
		}
	}

	// update networks
	data = rpc_client->send_request(rpc::RpcMethods::networks, {});

	if (data.has_value()) {
		boost::json::object obj = data.value();

		if (handle_error(obj)) {
			return;
		}

		networks = {};

		boost::json::object result = obj["result"].as_object();
		boost::json::array nets = result["networks"].as_array();

		for (auto net : nets) {
			for (auto n_obj : net.as_object()) {
				QString n(n_obj.key().to_string().c_str());
				networks.append(n);
			}
		}
	}

	notification = "";
	emit send_notification();
	emit on_update();
}

void Backend::on_select_network(QString network)
{
	selected_network = network;
	emit on_change_network();
}

void Backend::on_withdraw(QString token, QString token_address, QString amount)
{
	boost::json::array params {};

	params.push_back(boost::json::value_from(selected_network.toStdString()));
	params.push_back(boost::json::value_from(token.toStdString()));
	params.push_back(boost::json::value_from(token_address.toStdString()));
	// should be the amount
	params.push_back(boost::json::value_from(amount.toStdString()));

	std::optional<boost::json::object> data
		= rpc_client->send_request(rpc::RpcMethods::withdraw, params);

	if (data.has_value()) {
		boost::json::object obj = data.value();

		if (handle_error(obj)) {
			return;
		}

		notification = "Withdraw: ";
		notification.push_back(obj["result"].as_string().c_str());
	}

	emit send_notification();
}
void Backend::on_deposit(QString token)
{
	boost::json::array params {};

	params.push_back(boost::json::value_from(selected_network.toStdString()));
	params.push_back(boost::json::value_from(token.toStdString()));

	std::optional<boost::json::object> data
		= rpc_client->send_request(rpc::RpcMethods::deposit, params);

	if (data.has_value()) {
		boost::json::object obj = data.value();

		if (handle_error(obj)) {
			return;
		}

		notification = "Deposit Address: ";
		notification.push_back(obj["result"].as_string().c_str());
	}

	emit send_notification();
}

void Backend::on_transfer(QString token, QString address, QString amount)
{
	boost::json::array params {};

	params.push_back(boost::json::value_from(token.toStdString()));
	params.push_back(boost::json::value_from(address.toStdString()));
	params.push_back(boost::json::value_from(amount.toStdString()));

	std::optional<boost::json::object> data
		= rpc_client->send_request(rpc::RpcMethods::transfer, params);

	if (data.has_value()) {
		boost::json::object obj = data.value();

		if (handle_error(obj)) {
			return;
		}

		notification = "Transfer: ";
		notification.push_back(obj["result"].as_string().c_str());
	}

	emit send_notification();
}

