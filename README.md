# UWB_WebSocket



[![Platforms](https://img.shields.io/badge/platforms-linux--64%20%7C%20win--32%20%7C%20win--64-lightgrey)](#) [![Release Version](https://img.shields.io/github/release/FlorentinTh/UWB_WebSocket)](https://github.com/FlorentinTh/UWB_WebSocket/releases) [![License](https://img.shields.io/github/license/FlorentinTh/UWB_WebSocket)](https://github.com/FlorentinTh/UWB_WebSocket/blob/main/LICENSE)

A simple program that streams data produced by XeThru X4 UWB radars at 50Hz through WebSocket.

## Authors

- [**Florentin Thullier**](https://github.com/FlorentinTh) - 2021

## Installation

- **Windows x86/x64** :

  	* download the latest version of the installer according to your system architecture [here](https://github.com/FlorentinTh/UWB_WebSocket/releases/latest).

  * Install and start the UWB WebSocket app.

> **Note:** if you encounter some issues, try running the app as administrator.

- **Linux (Debian / Ubuntu)** :

    * Install required dependencies:

    ```sh
    $ sudo apt update
    $ sudo apt intall -y qt5-default libqt5serialport5-dev
    ```

    * Download latest release:
    ```sh
    $ curl -sSL https://github.com/FlorentinTh/UWB_WebSocket/releases/latest/download/uwb-websocket_latest_amd64.deb
    ```

    * Install the package:

    ```sh
    $ sudo dpkg -i uwb-websocket_latest_amd64.deb
    ```

    * Link libraries:
    ```sh
    $ echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/uwb-websocket" >> ~/.bashrc
    $ source ~/.bashrc
    ```

## How to use it

Inside the LIARA laboratory, the application is deployed on the linux server ```liara-srv0```. It's IP address is **192.168.1.10**. Hence, once you are connected inside the private network of the lab (either through a wired, or a wireless connection), you can access to the UWB WebSocket server through the following address :

```
ws://192.168.1.10:9002
```

> _**Note:** if the WebSocket server is not responding, ask for the recovery procedure in order to let you know how to restart the application remotely._

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
