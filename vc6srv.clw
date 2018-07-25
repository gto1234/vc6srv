; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVc6srvDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "vc6srv.h"

ClassCount=2
Class1=CVc6srvApp
Class2=CVc6srvDlg

ResourceCount=4
Resource2=IDD_VC6SRV_DIALOG
Resource1=IDR_MAINFRAME
Resource3=IDD_VC6SRV_DIALOG (English (U.S.))
Resource4=IDR_MENU1

[CLS:CVc6srvApp]
Type=0
HeaderFile=vc6srv.h
ImplementationFile=vc6srv.cpp
Filter=N

[CLS:CVc6srvDlg]
Type=0
HeaderFile=vc6srvDlg.h
ImplementationFile=vc6srvDlg.cpp
Filter=D
LastObject=ID_FILE_STOP
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_VC6SRV_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CVc6srvDlg

[DLG:IDD_VC6SRV_DIALOG (English (U.S.))]
Type=1
Class=CVc6srvDlg
ControlCount=1
Control1=IDC_EDIT1,edit,1353779332

[MNU:IDR_MENU1]
Type=1
Class=CVc6srvDlg
Command1=ID_FILE_START
Command2=ID_FILE_STOP
Command3=ID_FILE_CLEAR
Command4=ID_FILE_RESPONSE
Command5=ID_FILE_EXIT
CommandCount=5

