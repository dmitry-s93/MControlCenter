#!/bin/bash
set -e

# Check if running as root
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script with sudo:"
  echo "  sudo $0"
  exit 1
fi

# Get the directory of this script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

echo "=== Building MControlCenter ==="
if [ -n "$SUDO_USER" ]; then
    # Run build as the original user to keep file ownership correct
    sudo -u "$SUDO_USER" mkdir -p build
    sudo -u "$SUDO_USER" sh -c "cd build && cmake .. && make -j$(nproc)"
else
    mkdir -p build
    cd build
    cmake ..
    make -j$(nproc)
    cd ..
fi

echo "=== Installing MControlCenter ==="
BIN_PATH='/usr/bin/'
LIB_EXEC_PATH='/usr/libexec/'
SCALABLE_ICONS_PATH='/usr/share/icons/hicolor/scalable/apps/'
SHORTCUTS_PATH='/usr/share/applications/'
DBUS_SYSTEM_PATH='/usr/share/dbus-1/system.d/'
DBUS_SERVICES_PATH='/usr/share/dbus-1/system-services/'

# Copy binaries
install -vDm755 build/mcontrolcenter "$BIN_PATH"mcontrolcenter
install -vDm755 build/helper/mcontrolcenter-helper "$LIB_EXEC_PATH"mcontrolcenter-helper

# Icons & Shortcuts
install -vDm644 resources/mcontrolcenter.desktop "$SHORTCUTS_PATH"mcontrolcenter.desktop
install -vDm644 resources/mcontrolcenter.svg "$SCALABLE_ICONS_PATH"mcontrolcenter.svg

# D-Bus configuration
install -vDm644 src/helper/mcontrolcenter-helper.conf "$DBUS_SYSTEM_PATH"mcontrolcenter-helper.conf
install -vDm644 src/helper/mcontrolcenter.helper.service "$DBUS_SERVICES_PATH"mcontrolcenter.helper.service

# Clean up local user shortcuts if any
if [ -n "$SUDO_USER" ]; then
    rm -fv "/home/$SUDO_USER/.local/share/applications/mcontrolcenter.desktop"
fi

# Restart helper service
echo "=== Restarting helper service ==="
killall mcontrolcenter-helper 2>/dev/null || true

echo "=== Installation successful! ==="
