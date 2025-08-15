# MControlCenter

MControlCenter is a Free and Open Source GNU/Linux application that allows you to change the settings of MSI laptops.

![Screen Shot of MCC](https://github.com/user-attachments/assets/1e1dcb9b-aa8e-4410-8c77-f9554c1840cb)




## Features

 - CPU and GPU temperature display
 - Fan speed display
 - Switch between modes (Since version 0.2):
   - High Performance
   - Balanced
   - Silent
   - Super Battery
 - Change the maximum battery level limit
 - Advanced Fan Speed Control (Since version 0.4)
 - Change other settings such as keyboard backlight mode, USB Power Share, etc.

## TODO

- Saving multiple fan speed profiles
- Automatically change performance mode on charger connect/disconnect

## Supported devices

With version 0.5.0 the app uses the msi-ec driver that comes with the linux kernel (you might need to reinstall the driver), so device support depends on whether the kernel driver supports your device or not.

[**List of tested devices by msi-ec**](https://github.com/BeardOverflow/msi-ec/discussions/277)

If your device is not on the list, follow the steps on the `msi-ec` github page and open an issue there to add support for your device.

## Installation

### Pre-Installation

- Check the output of ```cat /sys/devices/platform/msi-ec/shift_mode``` in your terminal, if it says ```No such file or directory``` it means that you need to install or reinstall (uninstall first then install) the [msi-ec driver](https://github.com/BeardOverflow/msi-ec?tab=readme-ov-file#installation). or the application will open **but will have limited functionality!**  

- If you're not installing from the packages, You'll need to install `libqt6widgets6` or its equivalent on your distribution (```qt6-base``` for example). **the application will fail to open without it!** 



-  to get temperature and fan curve support, you'll need to install `ec_sys`, which comes installed on most distributions, or `acpi_sys` (fedora) with `write_support=1`. the app can still work with only `msi-ec` installed.

### Installation from packages

1. Download the correct package for your distribution from the [releases page](https://github.com/dmitry-s93/MControlCenter/releases/)
2. Double click to open it in the software manager (ex. Discover or GNOME software)
3. Install

### If your distribution is not listed, use the generic installer:

1. Download MControlCenter-x.x.x.tar.gz from the [releases page](https://github.com/dmitry-s93/MControlCenter/releases/)
2. Unpack the archive with the program
3. Open a terminal in the unpacked directory
4. Run the script `sudo ./install`
5. (Optional) `sudo ./uninstall` to uninstall

**Note:** Below are the steps for compiling, usually needed if your distrobution ships old versions of Qt6

## Building from source
After installing the main package (```qt6-base``` or ```libqt6widgets6```), you'll need to install other packages to build the app.

For ubuntru/Linux mint:
```qt6-base-dev``` and/or ```qt6-tools-dev``` also ```build-essential```

For Arch ```qt6-tools``` And for fedora ```qt6-qttools```

After you install the packages:

Make sure the app is completely closed if it was installed before (check if there is a system tray icon and close it).

Download the source code and extract the zip file.

Open the ```scripts``` folder.

Open a terminal inside the folder, then run these scripts in order:

1. ```build```
2. ```create installer```

If things went well, you should see a compressed file,

4. Extract it.
5. Open a terminal inside the new folder
6. Run the **UNINSTALL** script as *sudo*, it might fail if you don't have MCC installed. thats fine.
7. Run the **INSTALL** script as *sudo*, the last line should be a confirmation that the install was successful.
8. Check your apps, McontrolCenter should be there.

If the installation was successful but the app fails to run, open a terminal and type ```mcontrolcenter```, copy the output and open an issue (**IF** there isn't one already).

## Launch MControlCenter on session startup

To restore settings after a reboot, add MControlCenter to startup.

Execute this command on a terminal:

`cp /usr/share/applications/mcontrolcenter.desktop ~/.config/autostart/mcontrolcenter.desktop`

## Localization

You can help translate the MControlCenter app into your native language

1. Copy `/src/i18n/MControlCenter_en.ts` to `src/i18n/MControlCenter_xx.ts` where xx is language code into which the translation is being made.
2. Open `MControlCenter_xx.ts` in text editor and change `language="en_US"` to your language code.
3. Translate strings into your language directly in a text editor or use the QT Linguist app or Lokalize.
4. Translate `GenericName` in app shortcut `resources/mcontrolcenter.desktop`. To do this, add the line `GenericName[xx]=translated generic name`.
5. Open a pull request on github.
