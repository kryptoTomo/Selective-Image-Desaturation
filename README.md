cinel phymotion testing automation
====================

INFORMATION
-----------
To start the scangui, make first few steps:
* installation Conda & Sardana, 
* running tango Pool and MacroServer
* installation scangui

INSTALLATION
------------
Conda is an open source package management system and environment management system. Thanks to Conda we will install Sardana. 

From https://docs.conda.io/en/latest/miniconda.html download installer and then run it.

To install Sardana package paste:

    conda install -c conda-forge sardana

To install scangui use installator setup.py

Preparation of Sardana
-----------------------
1. Run Pool and MacroServer tango servers using these commands:

    Pool <system-name>
    MacroServer <system-name>
    
2. Connect the custom EncoderMotorController:
  * download and put controller EncoderMotorController.py in separate folder, 
  * in Jive go to Pool device in Sardana server and add PoolPath property to it, with the folder path
  * reset sardana server
3.
