# IsLandscape.exe  (Under Construction!!)

gets an image file as parameter and returns a 1 (errorcode) if the image is in landscape format and a 0 if the image is in portrait format. To do this the exit() function is used for this.

![img](https://github.com/uhwgmxorg/IsLandscape/blob/master/Doc/65_l_example.jpg)

An example of a lock screen photo from Microsoft

![img](https://github.com/uhwgmxorg/IsLandscape/blob/master/Doc/65_p_example.jpg)

and the portrait version from Microsoft

![img](https://github.com/uhwgmxorg/IsLandscape/blob/master/Doc/65_3.jpg)

The idea is to be able to distinguish, for example, in a batch between a picture whether it is in landscape or portrait format.
An example of a batch file:

    @ECHO OFF
    SETLOCAL EnableDelayedExpansion
    FOR /r %%i IN (.\*.jpg) DO (
      %OneDrive%\Bat\MyCppJpgIsLandscape.exe %%i
	    IF !ERRORLEVEL! EQU 1 ECHO %%i is LANDSCAPE
	    IF !ERRORLEVEL! EQU 0 DEL %%i
    )