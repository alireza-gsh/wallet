#ifndef RPC_H
#define RPC_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <optional>
#include <string>

#include <boost/asio.hpp>
#include <boost/json.hpp>

namespace rpc {

enum class RpcMethods {
	say_hello,
	balances,
	get_key,
	networks,
	transfer,
	deposit,
	withdraw
};

class RpcClient {
public:
	RpcClient(std::string url, int port, boost::asio::io_context& io_context);
	~RpcClient();

	std::optional<boost::json::object> send_request(
		RpcMethods method, boost::json::array params);

	boost::system::error_code connect();

private:
	boost::json::object pack_msg(const char* msg, boost::json::array params);

	std::string url;
	boost::system::error_code error;
	boost::asio::ip::tcp::socket socket;
	std::array<char, 2048> response;
	boost::asio::ip::tcp::endpoint endpoint;
};
}

#endif // RPC_H
