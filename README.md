# MControlCenter

MControlCenter is a Free and Open Source GNU/Linux application that allows you to change the settings of MSI laptops.
![Screenshots of MControlCenter](https://github.com/user-attachments/assets/31a6db8c-e2ea-4782-b8db-5d87fbfd63df)


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

## Supported devices

The app uses the msi-ec driver that comes with the linux kernel, so device support depends on whether the kernel driver supports your device or not.

[List of tested devices by msi-ec](https://github.com/BeardOverflow/msi-ec/blob/main/docs/supported_devices.md)

In case of missing performance mode selection, follow the steps on the msi-ec github page to add support for your device.

## Installation

The application requires the `ec_sys` module with option `write_support=1` to run.

If the `ec_sys` kernel module is not included in your distribution's kernel, you can use the `acpi_ec` kernel module.

This is QT application. You may need to install `libqt5widgets5` to run.

### Installation from the archive

1. Download `MControlCenter-x.x.x.tar.gz` from the releases page
2. Unpack the archive with the program
3. Open terminal in unpacked directory
4. Run the script `sudo ./install`

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
