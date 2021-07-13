#include "uwbradar.h"
#include <QtSerialPort/QSerialPortInfo>
#include <ctime>
#include <sstream>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

UWBRadar::UWBRadar(std::string port, WebSocketServer *webSocketServer) :
    _moduleConnector(port, 0)
{
    dac_min = 949;
    dac_max = 1100;
    iteration = 16;
    pps = 100;
    fps = 50.0;
    offset = 0.18;
    dc = 1;
    frame_area_min = 0.4;
    frame_area_max = 9.8;
    bins = 0;

    _x4m200 = &_moduleConnector.get_x4m200();
    _xep = &_moduleConnector.get_xep();

    _webSockerServer = webSocketServer;

    _init();
    _configure();
}

UWBRadar::~UWBRadar()
{
    delete _xep;
    delete _x4m200;
    delete _webSockerServer;
}

bool UWBRadar::_init()
{
    std::string *orderCode = new std::string;
    std::string *serialNumber = new std::string;

    _x4m200->get_system_info(XTID_SSIC_ORDERCODE, orderCode);
    _x4m200->get_system_info(XTID_SSIC_SERIALNUMBER, serialNumber);

    unsigned int pong = 0;
    if (_x4m200->ping(&pong) != 0)
    {
        return false;
    }

    _serialNumber = *serialNumber;

    delete orderCode;
    delete serialNumber;

    return true;
}

bool UWBRadar::_configure()
{
    _x4m200->set_sensor_mode(XTID_SM_STOP, 0);
    _x4m200->set_sensor_mode(XTID_SM_MANUAL, 0);

    _xep->x4driver_set_dac_min(dac_min);
    _xep->x4driver_set_dac_max(dac_max);
    _xep->x4driver_set_iterations(iteration);
    _xep->x4driver_set_pulses_per_step(pps);
    _xep->x4driver_set_fps(fps);
    _xep->x4driver_set_frame_area_offset(offset);
    _xep->x4driver_set_downconversion(dc);
    _xep->x4driver_set_frame_area(frame_area_min, frame_area_max);

    uint32_t bin = 0;
    _xep->x4driver_get_frame_bin_count(&bin);

    return true;
}

void UWBRadar::run()
{
    XeThru::DataFloat data;

    while (!isInterruptionRequested())
    {
        if (_xep->peek_message_data_float())
        {
            if (!_xep->read_message_data_float(&data))
            {
                std::time_t time = std::time(0);
                std::stringstream timeStringStream;
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

                writer.StartObject();

                writer.Key("serial_number");
                writer.String(this->_serialNumber.c_str());

                timeStringStream << time;
                writer.Key("timestamp");
                writer.Uint(std::stoi(timeStringStream.str(), nullptr, 0));

                writer.Key("data");
                writer.StartArray();
                for (uint32_t i = 0; i < data.data.size(); i++)
                {
                    writer.Double(static_cast<double>(data.data[i]));
                }
                writer.EndArray();
                writer.EndObject();

                _webSockerServer->sendData(buffer.GetString());
            }
        }
    }
}
