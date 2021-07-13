#ifndef UWBRADAR_H
#define UWBRADAR_H

#include "xethru/ModuleConnector.hpp"
#include "xethru/X4M200.hpp"
#include "xethru/xtid.h"
#include "xethru/XEP.hpp"
#include "websocketserver.h"
#include <QThread>

class UWBRadar : public QThread
{
public:
    uint32_t dac_min;
    uint32_t dac_max;
    uint32_t iteration;
    uint32_t pps;
    float fps;
    float offset;
    float frame_area_min;
    float frame_area_max;
    uint32_t bins;
    uint8_t dc;

    UWBRadar(std::string port, WebSocketServer *webSocketServer);
    ~UWBRadar();

protected:
    virtual void run() override;

private:
    std::string _port;
    std::string _serialNumber;

    XeThru::ModuleConnector _moduleConnector;
    XeThru::XEP *_xep;
    XeThru::X4M200 *_x4m200;

    WebSocketServer *_webSockerServer;

    bool _init();
    bool _configure();

};

#endif // UWBRADAR_H
