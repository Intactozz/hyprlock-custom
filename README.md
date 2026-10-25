# Hyprlock Custom

**A customized fork of Hyprlock featuring animated wallpaper blur, authentication feedback, and a synchronized login shake effect.**

Built on top of [Hyprlock](https://github.com/hyprwm/hyprlock), the screen locker for Hyprland.

## Overview

Hyprlock Custom extends the original Hyprlock experience with subtle visual animations and improved authentication feedback, while preserving its core screen-locking functionality.

The project focuses on creating a polished and responsive lock screen for Hyprland.

## Features

### Animated Wallpaper Blur

The wallpaper initially appears sharp and progressively blurs when the user starts entering a password.

The transition is designed to keep the lock screen visually clean while emphasizing the authentication interface.

### Synchronized Login Shake

When authentication fails, the password input and user avatar shake horizontally together.

The wallpaper remains stationary, keeping the effect focused on the authentication elements.

### Animated Authentication Feedback

While the system verifies the entered password, the lock screen displays an animated verification message.

The text smoothly pulses in opacity until authentication completes.

### Custom Avatar

Supports a circular user avatar positioned above the password input field.

The avatar participates in the synchronized shake animation after a failed login attempt.

### Hyprland Integration

The custom executable can be launched directly, through a keyboard shortcut, or from a Waybar power menu.

The original system-installed Hyprlock can remain untouched.

## Requirements

- Linux with Hyprland
- A working Hyprlock build environment
- CMake and a compatible C++ compiler
- The build dependencies required by the upstream Hyprlock project
- A valid PAM configuration for authentication

Optional components:

- Waybar for panel integration
- Wofi for a graphical power menu
- A custom wallpaper and avatar image

## Installation

### 1. Clone the repository

```bash
git clone --branch feature/animated-lockscreen https://github.com/Intactozz/hyprlock-custom.git
cd hyprlock-custom
```

### 2. Install dependencies

Install the build dependencies documented by the [upstream Hyprlock project](https://github.com/hyprwm/hyprlock).

Dependency package names may vary between Linux distributions.

### 3. Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"
```

The compiled executable will be available at:

```text
build/hyprlock
```

**Note:** Installing the custom executable system-wide is not required. Running it directly from the build directory allows the original Hyprlock installation to remain unchanged.

## Configuration

Create a separate configuration file for the customized version:

```bash
mkdir -p ~/.config/hypr
nano ~/.config/hypr/hyprlock-custom.conf
```

A personalized setup can include:

- A wallpaper image
- A circular avatar
- A password input field
- Authentication status text
- Animation settings

For example, the animation section can include:

```ini
animations {
    enabled = true

    bezier = suave, 0.22, 1, 0.36, 1

    animation = inputFieldColors, 1, 4, suave
}
```

The verification message can be configured through the password input field's `check_text` option:

```ini
check_text = Verificando...
```

The complete configuration must follow Hyprlock's configuration syntax.

Wallpaper and avatar assets are user-provided and should be referenced using valid local paths.

## Usage

Launch the customized lock screen with:

```bash
./build/hyprlock --config ~/.config/hypr/hyprlock-custom.conf
```

When running from another directory, use the absolute path to the executable.

## Waybar and Wofi Integration

A Waybar power menu can launch the custom executable instead of the system-installed Hyprlock.

Example `powermenu.sh`:

```bash
#!/usr/bin/env bash

option=$(printf 'Shutdown\nReboot\nLock\nSuspend' |
    wofi --dmenu --prompt "Power")

case "$option" in
    "Shutdown")
        systemctl poweroff
        ;;
    "Reboot")
        systemctl reboot
        ;;
    "Lock")
        (
            sleep 0.3
            exec "$HOME/Projetos/hyprlock-custom/build/hyprlock" \
                --config "$HOME/.config/hypr/hyprlock-custom.conf"
        ) >/tmp/hyprlock-power.log 2>&1 &
        ;;
    "Suspend")
        systemctl suspend
        ;;
esac
```

Adjust the executable path to match your local installation.

The short delay allows Wofi to close before the screen locker starts. This helped avoid a brief transition freeze in the development environment.

## Project Structure

Relevant implementation files include:

```text
src/
├── auth/
│   ├── Auth.cpp
│   └── Pam.cpp
├── config/
│   └── ConfigManager.cpp
├── core/
│   └── hyprlock.cpp
└── renderer/
    ├── Renderer.cpp
    ├── Renderer.hpp
    └── widgets/
        ├── Background.cpp
        ├── Image.cpp
        ├── PasswordInputField.cpp
        └── ShakeAnimation.hpp
```

The modifications focus on rendering, animation management, and authentication feedback.

## Development Status

The following features have been implemented and tested in the development environment:

- [x] Progressive wallpaper blur
- [x] Circular avatar integration
- [x] Synchronized failed-login shake
- [x] Animated verification text
- [x] Custom Waybar power-menu integration
- [x] Separate executable and configuration
- [x] Successful authentication and session unlocking

The project is a personal customization and has not been validated across all Hyprland environments or Linux distributions.

## Troubleshooting

**The system-installed Hyprlock opens instead of the custom version.**

Ensure that your launcher calls the compiled executable using its absolute path rather than the generic `hyprlock` command.

**The wallpaper or avatar does not appear.**

Verify that the image files exist and that their paths in the configuration are correct.

**The lock screen briefly freezes when launched from Wofi.**

Try launching the custom executable after a short delay, as shown in the Waybar integration example.

**Authentication is slow.**

Authentication is handled through PAM. The response time can depend on the system's authentication configuration and modules.

Avoid modifying PAM settings without understanding their security implications.

## Upstream Project and Credits

This repository is based on the original [Hyprlock](https://github.com/hyprwm/hyprlock) project developed by the Hyprland contributors.

All credit for the upstream screen locker, architecture, and original functionality belongs to their respective authors.

The custom modifications in this fork focus on animated visual feedback and the lock-screen experience.

## License

This project is derived from Hyprlock and remains subject to the applicable upstream license terms.

Refer to the repository's license file for the authoritative license text.

---

**Hyprlock Custom** — Animated, personalized screen locking for Hyprland.