NTP Digital Clock
=================

NTP Digital Clock based on ESP32 chip.

## Preparing

### Obtain the source

```
git clone --recursive https://github.com/redchenjs/ntp_digital_clock_esp32.git
```

### Update an existing repository

```
git pull
git submodule update --init --recursive
```

### Setup the tools

```
./esp-idf/install.sh
```

## Building

### Setup the environment variables

```
export IDF_PATH=$PWD/esp-idf
source ./esp-idf/export.sh
```

### Configure

```
idf.py menuconfig
```

* All project configurations are under the `NTP Digital Clock` menu.

### Flash & Monitor

```
idf.py flash monitor
```
