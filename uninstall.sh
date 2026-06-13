#!/bin/bash
set -e

# Check if running as root
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script with sudo:"
  echo "  sudo $0"
  exit 1
fi

echo "=== Uninstalling MControlCenter ==="
rm -fv /usr/bin/mcontrolcenter
rm -fv /usr/share/applications/mcontrolcenter.desktop
rm -fv /usr/share/icons/hicolor/scalable/apps/mcontrolcenter.svg
rm -fv /usr/libexec/mcontrolcenter-helper
rm -fv /etc/dbus-1/system.d/mcontrolcenter-helper.conf
rm -fv /usr/share/dbus-1/system.d/mcontrolcenter-helper.conf
rm -fv /usr/share/dbus-1/system-services/mcontrolcenter.helper.service

if [ -n "$SUDO_USER" ]; then
    rm -fv "/home/$SUDO_USER/.local/share/applications/mcontrolcenter.desktop"
fi

# Kill helper if running
killall mcontrolcenter-helper 2>/dev/null || true

echo "=== Uninstallation successful! ==="
