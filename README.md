# MControlCenter

MControlCenter is a Free and Open Source GNU/Linux application that allows you to change the settings of MSI laptops.
![Screenshots of MControlCenter](https://user-images.githubusercontent.com/12676622/195147148-398b6cb5-6907-4a54-a8d8-e2386b7650fe.png)

## Features

 - CPU and GPU temperature display
 - Fan speed display
 - Switch between modes (Since version 0.2):
   - High Performance
   - Balanced
   - Silent
   - Super Battery
 - Change the maximum battery level limit
 - Change other settings such as keyboard backlight mode, USB Power Share, etc.

## TODO

 - Add the ability to adjust the fan speed

## Tested on

The main device on which the application is being tested: **MSI Summit E16 Flip Evo A12MT**

[List of tested devices](/docs/tested_devices.md)


## Installation

The application requires the `ec_sys` module with option `write_support=1` to run.

This is QT application. You may need to install `libqt5widgets5` to run.

### Installation from the archive

1. Unpack the archive with the program
2. Open terminal in unpacked directory
3. Run the script `sudo ./install`

### Installation from the repository

#### openSUSE Tumbleweed:

```sh
zypper addrepo https://download.opensuse.org/repositories/home:dmitry-s/openSUSE_Tumbleweed/home:dmitry-s.repo
zypper refresh
zypper install mcontrolcenter
```

#### openSUSE Leap 15.5

```sh
zypper addrepo https://download.opensuse.org/repositories/home:dmitry-s/openSUSE_Leap_15.5/home:dmitry-s.repo
zypper refresh
zypper install mcontrolcenter
```

#### openSUSE Leap 15.4:

```sh
zypper addrepo https://download.opensuse.org/repositories/home:dmitry-s/15.4/home:dmitry-s.repo
zypper refresh
zypper install mcontrolcenter
```

### Launch MControlCenter on session startup

To restore settings after a reboot, add MControlCenter to startup.

Execute this command on a terminal:

`cp /usr/share/applications/mcontrolcenter.desktop ~/.config/autostart/mcontrolcenter.desktop`

## Localization

You can help translate the MControlCenter app into your native language

1. Copy `/src/i18n/MControlCenter_en.ts` to `src/i18n/MControlCenter_xx.ts` where xx is language code into which the translation is being made.
2. Open `MControlCenter_xx.ts` in text editor and change `language="en_US"` to your language code.
3. Translate strings into your language directly in a text editor or use the QT Linguist app.
4. Translate `GenericName` in app shortcut `resources/mcontrolcenter.desktop`. To do this, add the line `GenericName[xx]=translated generic name`.
5. Send pull request on github.
