#include "tokeninfo.h"

TokenInfo::TokenInfo(QString name, QString value, QString network)
	: name(name)
	, value(value)
	, network(network) {};

QString TokenInfo::get_name() { return name; };

QString TokenInfo::get_value() { return value; };

QString TokenInfo::get_network() { return network; };
