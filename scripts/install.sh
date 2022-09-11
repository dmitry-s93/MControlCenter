 #!/bin/bash -e

BIN_PATH='/usr/bin/'
LIB_EXEC_PATH='/usr/libexec/'
SCALABLE_ICONS_PATH='/usr/share/icons/hicolor/scalable/apps/'
SHORTCUTS_PATH='/usr/share/applications/'
DBUS_SYSTEM_PATH='/etc/dbus-1/system.d/'

APP_BIN='mcontrolcenter'
SVG_ICON='mcontrolcenter.svg'
SHORTCUT='mcontrolcenter.desktop'
HELPER_BIN='mcontrolcenter-helper'
DBUS_CONF='org.mcontrolcenter.helper.conf'

echo "Installation start"

cp -fv ./$APP_BIN $BIN_PATH
chmod -v 755 $BIN_PATH$APP_BIN

cp -fv ./$SHORTCUT $SHORTCUTS_PATH
chmod -v 644 $SHORTCUTS_PATH$SHORTCUT

cp -fv ./$SVG_ICON $SCALABLE_ICONS_PATH
chmod -v 644 $SCALABLE_ICONS_PATH$SVG_ICON

cp -fv ./$HELPER_BIN $LIB_EXEC_PATH
chmod -v 755 $LIB_EXEC_PATH$HELPER_BIN

cp -fv ./$DBUS_CONF $DBUS_SYSTEM_PATH
chmod -v 644 $DBUS_SYSTEM_PATH$DBUS_CONF

echo "Installation was successful"
