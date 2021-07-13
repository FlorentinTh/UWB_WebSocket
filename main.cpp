#include <QCoreApplication>
#include <QtSerialPort/QSerialPortInfo>
#include "websocketserver.h"
#include "uwbradar.h"

static const quint16 noveldaId = 0x03EB;
static const quint16 x4m200Id = 0x6124;
static const unsigned short int webSocketServerPort = 9002;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Starting WebSocket server on port: " <<
                 webSocketServerPort << "..." << std::endl;

    WebSocketServer *webSocketServer = new WebSocketServer(webSocketServerPort);
    webSocketServer->start();

    const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    std::cout << "Scanning serial ports..." << std::endl;

    if (serialPortInfos.count() > 0)
    {
        for (const QSerialPortInfo &serialPortInfo : serialPortInfos)
        {
            if (serialPortInfo.vendorIdentifier() == noveldaId &&
                    serialPortInfo.productIdentifier() == x4m200Id)
            {
                std::string serialPort = serialPortInfo.systemLocation().toStdString();

                std::cout << "* Found X4M200 radar on port: " << serialPort << std::endl;

                UWBRadar *xethrurRadar = new UWBRadar(serialPort, webSocketServer);
                xethrurRadar->start();
            }
        }
    } else {
        std::cout << "No serial port being used at the moment" << std::endl;
    }

    std::cout << "Waiting for clients to open connections..." << std::endl;

    return a.exec();
}
