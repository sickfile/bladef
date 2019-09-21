# bladef
win32 front end for the blade encoder writen in C

To compile and link this with:

1. Microsoft Visual Studio 2003 Professional command line tools you can download the The Microsoft Visual C++ Toolkit 2003 from here: http://kael.civfanatics.net/files/VCToolkitSetup.exe

Run the toolkit and install it in say C:\LANG\MSVC

Then you'll need to install the platform SDK. Windows Server 2003 R2 Platform SDK will do the job, you can download it from here: https://download.cnet.com/Windows-Server-2003-R2-Platform-SDK-ISO-Download/3000-10248_4-10731094.html

Extract the files from the image with 7Z archiver and run Setup. Disable all the SDKs except the Micsrosoft Windows Core SDK. You can disable all parts of it, you will need only Build Environment > Build Environment (x86 32-bit).
In short: Micsrosoft Windows Core SDK > Build Environment > Build Environment (x86 32-bit).

Install the Platform SDK also in C:\LANG\MSVC

Right click on "My Computer" and go to Properties, find "Environment Variables" in the advanced setings.
Click it and under "User variables for ..." hit the "New" button.
For "Variable name" enter PATH, for "Variable value" enter C:\LANG\MSVC\BIN then click OK.
Hit the "New" button again. For "Variable name" enter INCLUDE, for "Variable value" enter C:\LANG\MSVC\INCLUDE then click OK.
Hit the "New" button again. For "Variable name" enter LIB, for "Variable value" enter C:\LANG\MSVC\LIB then click OK.

Open "Command Prompt" and enter SET. In the text that poped up on the screen there should be INCLUDE=C:\LANG\MSVC\INCLUDE and LIB=C:\LANG\MSVC\LIB, also C:\LANG\MSVC\BIN should be on the PATH.

CD to the directory where you have the source files from this project and enter

cl bladef.c wndshift.c

The Microsoft Visual Studio 2003 Professional compiler/linker should have created bladef.exe
