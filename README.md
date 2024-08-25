# MControlCenter

This is a fork of [MControlCenter](https://github.com/dmitry-s93/MControlCenter) created to work with QT6 on Ubuntu 24.04 and clang compiler.

MControlCenter is a Free and Open Source GNU/Linux application that allows you to change the settings of MSI laptops.
![Screenshots of MControlCenter](https://user-images.githubusercontent.com/12676622/219121128-0476b54b-3330-40c7-b7ac-8d4a884f8abd.png)

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

## Tested on

This fork tested on MSI Creator 17 B11UG and Ubuntu 24.04.

[List of original tested devices](/docs/tested_devices.md)


## Installation

The application requires the `ec_sys` module with option `write_support=1` to run.

If the `ec_sys` kernel module is not included in your distribution's kernel, you can use the `acpi_ec` kernel module.

### Installation from the archive

1. Download `MControlCenter-x.x.x.tar.gz` from the releases page
2. Unpack the archive with the program
3. Open terminal in unpacked directory
4. Run the script `sudo ./install`

### Installation from the repository

Create package with:

```bash
cd scripts/
bash build.sh
bash create_installer.sh
```

### Launch MControlCenter on session startup

To restore settings after a reboot, add MControlCenter to startup.

Execute this command on a terminal:

`cp /usr/share/applications/mcontrolcenter.desktop ~/.config/autostart/mcontrolcenter.desktop`

## Localization

You can help translate the MControlCenter app into your native language

1. Copy `/src/i18n/en.ts` to `src/i18n/xx.ts` where xx is language code into which the translation is being made.
2. Open `xx.ts` in text editor and change `language="en_US"` to your language code.
3. Translate strings into your language directly in a text editor or use the QT Linguist app.
4. Translate `GenericName` in app shortcut `resources/mcontrolcenter.desktop`. To do this, add the line `GenericName[xx]=translated generic name`.
5. Send pull request on github.
