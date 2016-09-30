# Microsoft Developer Studio Project File - Name="pFDevice" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=pFDevice - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pFDevice.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pFDevice.mak" CFG="pFDevice - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pFDevice - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pFDevice - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pFDevice - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "pFDevice - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GR /GX /ZI /Od /I "..\..\wxWindows-2" /I "5.1\include\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "__WXMSW__" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "__WXMSW__" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x405 /d "__WXMSW__" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wxmsw25d_html.lib wxmsw25d_core.lib wxbase25d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib winmm.lib comctl32.lib rpcrt4.lib wsock32.lib oleacc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /libpath:"..\..\wxWindows-2.5.1\lib\vc_lib"
# SUBTRACT LINK32 /pdb:none /incremental:no

!ENDIF 

# Begin Target

# Name "pFDevice - Win32 Release"
# Name "pFDevice - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\pfdevice.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cacquirehelp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cacquireshow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cchannelgrid.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ccomsettings.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ccomsettings.h
# End Source File
# Begin Source File

SOURCE=..\src\cconfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cconfig.h
# End Source File
# Begin Source File

SOURCE=..\src\cconfigfile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cconfigfile.h
# End Source File
# Begin Source File

SOURCE=..\src\cconnectionthread.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cconnectionthread.h
# End Source File
# Begin Source File

SOURCE=..\src\ccontrolcentre.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cdevicemanager.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cdevicescreen.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cdevicescreen.h
# End Source File
# Begin Source File

SOURCE=..\src\cdevicewindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cdevicewindow.h
# End Source File
# Begin Source File

SOURCE=..\src\cdisplayframe.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cdisplaythread.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cdisplaythread.h
# End Source File
# Begin Source File

SOURCE=..\src\cgraphwindow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\chardwaredlg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cmapdevice.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cmultiplexdisp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\portmapdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvirtcomdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\cvirtualcom.cpp
# End Source File
# Begin Source File

SOURCE=..\src\wxdefs.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\pfdevice.h
# End Source File
# Begin Source File

SOURCE=..\src\cacquirehelp.h
# End Source File
# Begin Source File

SOURCE=..\src\cacquireshow.h
# End Source File
# Begin Source File

SOURCE=..\src\cchannelgrid.h
# End Source File
# Begin Source File

SOURCE=..\src\ccontrolcentre.h
# End Source File
# Begin Source File

SOURCE=..\src\cdevicemanager.h
# End Source File
# Begin Source File

SOURCE=..\src\cdisplayframe.h
# End Source File
# Begin Source File

SOURCE=..\src\cgraphwindow.h
# End Source File
# Begin Source File

SOURCE=..\src\chardwaredlg.h
# End Source File
# Begin Source File

SOURCE=..\src\cmapdevice.h
# End Source File
# Begin Source File

SOURCE=..\src\cmultiplexdisp.h
# End Source File
# Begin Source File

SOURCE=..\src\portmapdlg.h
# End Source File
# Begin Source File

SOURCE=..\src\cvirtcomdlg.h
# End Source File
# Begin Source File

SOURCE=..\src\cvirtualcom.h
# End Source File
# Begin Source File

SOURCE=..\src\defines.h
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\icon8.ico
# End Source File
# Begin Source File

SOURCE=..\src\images.h
# End Source File
# Begin Source File

SOURCE=.\report.ico
# End Source File
# Begin Source File

SOURCE=..\src\version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
