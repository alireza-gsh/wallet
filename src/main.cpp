#include <chrono>
#include <thread>

#include <QFile>
#include <QFileInfo>
#include <QGuiApplication>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "backend.h"

int main(int argc, char* argv[])
{

	// run darkfid daemon
	// TODO: this need to change to work with other platfroms
	QProcess check_darkfid;
	QStringList arguments;
	arguments << "darkfid";

	check_darkfid.start("which", arguments);

	check_darkfid.setReadChannel(QProcess::ProcessChannel::StandardOutput);

	if (!check_darkfid.waitForFinished())
		return 0;

	QString darkfid_path(check_darkfid.readAll());

	darkfid_path = darkfid_path.trimmed();

	QFile path(darkfid_path);
	QFileInfo check_path(path);

	if (!check_path.exists() && !check_path.isFile()) {
		std::cout << "Darkfid is  not installed"
				  << "\n";

		check_darkfid.close();
		return 0;
	}

	QProcess* darkfid_daemon = new QProcess();
	QStringList s = QStringList();
	darkfid_daemon->start(darkfid_path, s, QIODevice::ReadOnly);

	boost::asio::io_context io_context;

	rpc::RpcClient* rpc_client
		= new rpc::RpcClient("127.0.0.1", 8000, io_context);

	int c = 0;

	// try to connect to darkfid
	while (c < 5) {

		auto error = rpc_client->connect();

		if (!error) {
			std::cout << "CONNECTION: "
					  << "The connection established."
					  << "\n";
			break;
		} else {
			std::cerr << "CONNECTION: " << error.message() << "\n";
		}

		++c;
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreated, &app,
		[url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);

	Backend* backend = new Backend(rpc_client);

	// update the tokens list
	backend->update();

	engine.rootContext()->setContextProperty("backend", backend);

	// load qml
	engine.load(url);

	app.exec();

	// close daemon
	darkfid_daemon->close();

	return 0;
}
