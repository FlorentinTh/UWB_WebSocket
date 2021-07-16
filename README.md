# UWB_WebSocket

[![License](https://img.shields.io/github/license/FlorentinTh/LE2ML-API)](https://github.com/FlorentinTh/UWB_WebSocket/blob/master/LICENSE)

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
    $ sudo apt intall -y zip build-essential cmake \
                        libboost-all-dev qt5-default \
                        libqt5serialport5-dev
    ```

    * Download latest release:
    ```sh
    $ curl -OL https://github.com/FlorentinTh/UWB_WebSocket/releases/latest/download/UWB-WebSocket-linux.zip
    $ unzip UWB-WebSocket-linux.zip
    $ cd UWB-WebSocket-linux
    ```

    * Change files mode:

    ```sh
    $ sudo chmod a+x setup.sh UWB_WebSocket
    ```

    * Run the setup file:
    ```sh
    $ ./setup.sh
    ```

    * Start the app:
    ```sh
    $ ./UWB_WebSocket
    ```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
