# IsLandscape.exe

IsLandscape.exe is a small command line utility and gets an image file as parameter and returns 1 (errorcode) if the image is in landscape format and 0 if the image is in portrait format. To do this the [exit()](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/exit-exit-exit) function is used for this.

![img](https://github.com/uhwgmxorg/IsLandscape/blob/master/Doc/65_l_example.jpg)

An example of a lock screen photo from Microsoft (c)

![img](https://github.com/uhwgmxorg/IsLandscape/blob/master/Doc/65_p_example.jpg)

and the portrait version from Microsoft (c)

![img](https://github.com/uhwgmxorg/IsLandscape/blob/master/Doc/65_3.jpg)

The idea is to be able to distinguish, for example, in a batch between a picture whether it is in landscape or portrait format.
An example of a batch file:

    @ECHO OFF
    SETLOCAL EnableDelayedExpansion
    FOR /r %%i IN (.\*.jpg) DO (
      %OneDrive%\Bat\IsLandscape.exe %%i
	    IF !ERRORLEVEL! EQU 1 ECHO %%i is LANDSCAPE
	    IF !ERRORLEVEL! EQU 0 DEL %%i
    )

The prerequisites for compiling the project are VS 2017 Windows 10 SDK from 10.0.18362.0 to 10.0.17134.0 or
you can download a signed Exe version on uhwgmxorg.com [here](http://uhwgmxorg.com/IsLandscape.exe?dl=0)
