cinel phymotion testing automation
====================

INFORMATION
-----------
To start the environment, you should make first few steps:
* installation Conda & Sardana, 
* running tango Pool and MacroServer
* installation scangui

INSTALLATION
------------
Conda is an open source package management system and environment management system. Thanks to Conda we will install Sardana. 
From https://docs.conda.io/en/latest/miniconda.html download installer and then run it.
To install Sardana package paste:
    conda install -c conda-forge sardana
Now 
Launch the gui by using the launcher in the menu or by running

    scangui

If not configured the gui asks for input:
* Lists of motors to be scanned. If left empty the GUI will dynamically get all motors from sardana.
* Path to where the sardana .h5 files are accessible for the client
* Macroserver/Door

If the sardana jsonrecorder is not enabled the GUI will ask you if it should enable it for you.

The config files are stored in  ~/.config/MAXIV/scangui.ini

