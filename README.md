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

To install scangui use installator setup.py

Preparation of Sardana
-----------------------
To run Pool and MacroServer tango servers follow these commands:

    Pool <system-name>
    MacroServer <system-name>
