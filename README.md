# ESP32 Mini Drone

A tiny DIY quadcopter built around an ESP32, brushed coreless motors, and a hand-written flight controller.

The project is split in two firmware images, both built with ESP-IDF:

- `firmware/drone`: runs on the drone (IMU, PID stabilisation, motor PWM)
- `firmware/controller`: runs on the handheld remote (joystick via ADC)

## Repository layout

```
Drone/
├── firmware/
│   ├── components/        # Shared code between drone and controller
│   ├── controller/        # Remote control firmware
│   │   └── main/          # adc, joystick, main
│   ├── drone/             # Drone firmware
│   │   └── main/          # i2c, ledc, motors, mpu, pid, main
│   └── settings.h         # Settings shared by both firmwares
├── schematics/            # Wiring and PCB files
├── LICENSE
└── README.md
```

## Requirements

- An ESP32 dev board for the drone and one for the controller
- A USB cable that carries data (not charge-only)
- Linux or macOS (Windows works too, but the commands below are for a Unix shell)
- ESP-IDF v5.x

## 1. ESP-IDF framework and env setup

Install ESP-IDF by following the official guide, and select the ESP32 target when it asks for one: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#installation

> **Important:** you must load the ESP-IDF environment in every new terminal before using `idf.py`. If you skip this, `idf.py` will not be found.

## 2. Clone the project

```bash
git clone https://github.com/NasriAnis/Drone Drone
cd Drone
```

## 3. Build and flash the drone and controller firmware

Go into the drone project:
```bash
cd firmware/drone
```

Set the chip target. This only needs to be done once per project (it resets `build/` and regenerates the config):
```bash
idf.py set-target <your-dev-board>
```

Build flash and monitor for errors:
```bash
idf.py build flash monitor -p <esp-port>
```

To leave the monitor, press `Ctrl+]` then disconnect the device.

Do the same steps for the `firmware/controller` folder.

## Settings

Shared values (pins, PID gains, limits, communication parameters) live in `firmware/settings.h`. After editing it, rebuild both firmwares and flash them again so they stay in sync.

## Editor / LSP (clangd)

To get proper completion and diagnostics, point clangd at the generated `compile_commands.json`. After a build, link it to the repo root:

```bash
ln -sf firmware/drone/build/compile_commands.json compile_commands.json
```

## License

See [LICENSE](LICENSE).