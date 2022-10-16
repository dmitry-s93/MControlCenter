#!/bin/bash -e

BIN_PATH='/usr/bin/'
LIB_EXEC_PATH='/usr/libexec/'
SCALABLE_ICONS_PATH='/usr/share/icons/hicolor/scalable/apps/'
SHORTCUTS_PATH='/usr/share/applications/'
DBUS_SYSTEM_PATH='/etc/dbus-1/system.d/'
DBUS_SERVICES_PATH='/usr/share/dbus-1/system-services/'

APP_DIR='./app/'

APP_BIN='mcontrolcenter'
SVG_ICON='mcontrolcenter.svg'
SHORTCUT='mcontrolcenter.desktop'
HELPER_BIN='mcontrolcenter-helper'
DBUS_CONF='mcontrolcenter-helper.conf'
DBUS_SERVICE='mcontrolcenter.helper.service'

echo "Installation start"

cp -fv $APP_DIR$APP_BIN $BIN_PATH
chmod -v 755 $BIN_PATH$APP_BIN

rm -fv /home/$SUDO_USER/.local/share/applications/$SHORTCUT
cp -fv $APP_DIR$SHORTCUT $SHORTCUTS_PATH
chmod -v 644 $SHORTCUTS_PATH$SHORTCUT

cp -fv $APP_DIR$SVG_ICON $SCALABLE_ICONS_PATH
chmod -v 644 $SCALABLE_ICONS_PATH$SVG_ICON

cp -fv $APP_DIR$HELPER_BIN $LIB_EXEC_PATH
chmod -v 755 $LIB_EXEC_PATH$HELPER_BIN

cp -fv $APP_DIR$DBUS_CONF $DBUS_SYSTEM_PATH
chmod -v 644 $DBUS_SYSTEM_PATH$DBUS_CONF

cp -fv $APP_DIR$DBUS_SERVICE $DBUS_SERVICES_PATH
chmod -v 644 $DBUS_SERVICES_PATH$DBUS_SERVICE

echo "Installation was successful"
