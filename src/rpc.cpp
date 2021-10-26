#include <rpc.h>

rpc::RpcClient::RpcClient(
	std::string url, int port, boost::asio::io_context& io_context)
	: url(url)
	, socket(io_context)
	, endpoint(boost::asio::ip::tcp::endpoint(
		  boost::asio::ip::make_address(url), port))
{
}

boost::system::error_code rpc::RpcClient::connect()
{
	socket.connect(endpoint, error);
	return error;
};

rpc::RpcClient::~RpcClient() { socket.close(); }

std::optional<boost::json::object> rpc::RpcClient::send_request(
	RpcMethods method, boost::json::array params)
{

	response = {};

	boost::json::object msg {};

	switch (method) {
	case RpcMethods::say_hello:
		msg = pack_msg("say_hello", params);
		break;
	case RpcMethods::get_key:
		msg = pack_msg("get_key", params);
		break;
	case RpcMethods::networks:
		msg = pack_msg("features", params);
		break;
	case RpcMethods::transfer:
		msg = pack_msg("transfer", params);
		break;
	case RpcMethods::deposit:
		msg = pack_msg("deposit", params);
		break;
	case RpcMethods::withdraw:
		msg = pack_msg("withdraw", params);
		break;
	case RpcMethods::balances:
		msg = pack_msg("get_balances", params);
		break;
	default:
		std::cerr << "DEBUG RPC ERROR: "
				  << "Unknow method"
				  << "\n";
		return {};
	}

	std::cout << "DEBUG RPC SEND: " << msg << "\n";

	socket.send(boost::asio::buffer(boost::json::serialize(msg)), 0, error);

	socket.receive(boost::asio::buffer(response), 0, error);

	if (!error) {

		std::string data = response.data();

		boost::json::object ob = boost::json::parse(data).as_object();

		std::cout << "DEBUG RPC RESPONSE:  " << ob << "\n";

		return ob;

	} else {
		std::cerr << "ERROR:  " << error.message() << "\n";
		return {};
	}
}

boost::json::object rpc::RpcClient::pack_msg(
	const char* msg, boost::json::array params)
{
	std::srand(std::time(nullptr));
	int id = std::rand();

	boost::json::object request;
	request.emplace("jsonrpc", "2.0");
	request.emplace("method", msg);
	request.emplace("id", id);
	request.emplace("params", params);

	return request;
};
