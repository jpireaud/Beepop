; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVarroaPopView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "varroapop.h"
LastPage=0

ClassCount=23
Class1=CBee
Class2=CColony
Class3=CColonyDataPage
Class4=CColonySelectionPage
Class5=CCreateWeatherHdr
Class6=CGraphDlg
Class7=CImmigrationDlg
Class8=CMainFrame
Class9=CMyPropSheet
Class10=CSelGraph
Class11=CSimDlg
Class12=CSimDlgBar
Class13=CSimulationPage
Class14=CVarroaPopApp
Class15=CAboutDlg
Class16=CVarroaPopDoc
Class17=CVarroaPopView
Class18=CWeatherPage

ResourceCount=19
Resource1=IDR_CHARTMENU
Resource2=IDD_COLONY_DATA_FORM
Resource3=IDD_SIMULATION_BAR
Resource4=IDB_WEATHERTOOLBAR
Resource5=IDD_WEATHEREDIT
Resource6=IDD_SPLASH
Resource7=IDD_ACTION_FORM
Resource8=IDD_REMOVECOMB
Resource9=IDD_WEATHER_FORM
Resource10=IDD_OLECTRAGRAPHDLG
Resource11=IDD_IMMIGRATION
Class19=COlectraGraphDlg
Resource12=IDD_SELECT_GRAPHS
Resource13=IDD_GRAPHDIALOG
Class20=CActionPage
Resource14=IDD_OPTIONS
Class21=CCombRemDlg
Resource15=IDD_PROGRESS
Class22=COptions
Resource16=IDD_CREATE_HEADER
Resource17=IDD_ABOUTBOX
Class23=CWeatherEditor
Resource18=IDR_MENUWEATHER
Resource19=IDR_MAINFRAME

[CLS:CBee]
Type=0
BaseClass=CCmdTarget
HeaderFile=Bee.h
ImplementationFile=Bee.cpp

[CLS:CColony]
Type=0
BaseClass=CCmdTarget
HeaderFile=Colony.h
ImplementationFile=Colony.cpp

[CLS:CColonyDataPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ColonyDataPage.h
ImplementationFile=ColonyDataPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDC_SLIDERFORAGER

[CLS:CColonySelectionPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ColonySelectionPage.h
ImplementationFile=ColonySelectionPage.cpp

[CLS:CCreateWeatherHdr]
Type=0
BaseClass=CDialog
HeaderFile=CreateWeatherHdr.h
ImplementationFile=CreateWeatherHdr.cpp

[CLS:CGraphDlg]
Type=0
BaseClass=CDialog
HeaderFile=Graphdlg.h
ImplementationFile=Graphdlg.cpp

[CLS:CImmigrationDlg]
Type=0
BaseClass=CDialog
HeaderFile=ImmigrationDlg.h
ImplementationFile=ImmigrationDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CImmigrationDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=Mainfrm.h
ImplementationFile=MainFrm.cpp
LastObject=ID_VIEW_DATA_FREQ
Filter=T
VirtualFilter=fWC

[CLS:CMyPropSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=MypropSheet.h
ImplementationFile=MypropSheet.cpp
LastObject=CMyPropSheet

[CLS:CSelGraph]
Type=0
BaseClass=CDialog
HeaderFile=Selgraph.h
ImplementationFile=Selgraph.cpp

[CLS:CSimDlg]
Type=0
BaseClass=CDialogBar
HeaderFile=Simdlg.h
ImplementationFile=Simdlg.cpp
LastObject=CSimDlg

[CLS:CSimDlgBar]
Type=0
BaseClass=CDialog
HeaderFile=SimdlgBar.h
ImplementationFile=SimdlgBar.cpp
LastObject=IDC_RADIO_IM_OFF

[CLS:CSimulationPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=SimulationPage.h
ImplementationFile=SimulationPage.cpp

[CLS:CVarroaPopApp]
Type=0
BaseClass=CWinApp
HeaderFile=VarroaPop.h
ImplementationFile=VarroaPop.cpp
LastObject=CVarroaPopApp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=VarroaPop.cpp
ImplementationFile=VarroaPop.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CVarroaPopDoc]
Type=0
BaseClass=CDocument
HeaderFile=VarroaPopDoc.h
ImplementationFile=VarroaPopDoc.cpp
LastObject=CVarroaPopDoc
Filter=N
VirtualFilter=DC

[CLS:CVarroaPopView]
Type=0
BaseClass=CListView
HeaderFile=VarroaPopView.h
ImplementationFile=VarroaPopView.cpp
LastObject=CVarroaPopView
Filter=C
VirtualFilter=VWC

[CLS:CWeatherPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=WeatherPage.h
ImplementationFile=WeatherPage.cpp

[DLG:IDD_COLONY_DATA_FORM]
Type=1
Class=CColonyDataPage
ControlCount=41
Control1=IDC_COLONY_LIST,combobox,1344340226
Control2=IDC_WORKER_EGGS,edit,1350639745
Control3=IDC_DRONE_EGGS,edit,1350639745
Control4=IDC_WORKER_LARVAE,edit,1350639745
Control5=IDC_DRONE_LARVAE,edit,1350639745
Control6=IDC_WORKER_BROOD,edit,1350639745
Control7=IDC_DRONE_BROOD,edit,1350639745
Control8=IDC_BROOD_WORKER_INFEST,edit,1350631553
Control9=IDC_BROOD_DRONE_INFEST,edit,1350631553
Control10=IDC_WORKER_ADULTS,edit,1350639745
Control11=IDC_DRONE_ADULTS,edit,1350639745
Control12=IDC_ADULT_WORKER_INFEST,edit,1350631553
Control13=IDC_ADULT_DRONE_INFEST,edit,1350631553
Control14=IDC_WORKER_MITE_OFFSPRING,edit,1350631553
Control15=IDC_DRONE_MITE_OFFSPRING,edit,1350631553
Control16=IDC_WORKER_MITE_SURVIVORSHIP,edit,1350631553
Control17=IDC_DRONE_MITE_SURVIVORSHIP,edit,1350631553
Control18=IDC_COLONY_GROUP,button,1342177287
Control19=IDC_EGGS_GROUP,button,1342177287
Control20=IDC_WORKER,static,1342308353
Control21=IDC_DRONE,static,1342308353
Control22=IDC_LARVAE,button,1342177287
Control23=IDC_ROW_HEADING1,static,1342308353
Control24=IDC_ROW_HEADING2,static,1342308353
Control25=IDC_LARVAE2,button,1342177287
Control26=IDC_ROW_HEADING3,static,1342308353
Control27=IDC_COLUMN_HEADING3,static,1342308353
Control28=IDC_WORKER2,static,1342308353
Control29=IDC_DRONE2,static,1342308353
Control30=IDC_ROW_HEADING4,static,1342308353
Control31=IDC_MITE_GROUP,button,1342177287
Control32=IDC_MITE_ROW_HEADING,static,1342308352
Control33=IDC_MITE_SURVIVORSHIP_GROUP,button,1342177287
Control34=IDC_STATIC,button,1342177287
Control35=IDC_SLIDERFORAGER,msctls_trackbar32,1342242825
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_FORAGERVAL,static,1342177280
Control39=IDC_SLIDERQUEEN,msctls_trackbar32,1342242825
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352

[DLG:IDD_COLONY_SELECTION_FORM]
Type=1
Class=CColonySelectionPage

[DLG:IDD_CREATE_HEADER]
Type=1
Class=CCreateWeatherHdr
ControlCount=38
Control1=IDC_AVTEMP,edit,1350631552
Control2=IDC_MAXTEMP,edit,1350631552
Control3=IDC_MINTEMP,edit,1350631552
Control4=IDC_RAINFALL,edit,1350631552
Control5=IDC_WINDSPEED,edit,1350631552
Control6=IDC_SOLAR_RAD,edit,1350631552
Control7=IDC_INTERVAL,edit,1350631552
Control8=IDC_W_BEG_TIME,edit,1484849280
Control9=IDC_W_END_TIME,edit,1484849280
Control10=IDC_W_BEG_DATE,edit,1484849280
Control11=IDC_W_END_DATE,edit,1484849280
Control12=IDC_RADIO_F,button,1342308361
Control13=IDC_RADIO_C,button,1342177289
Control14=IDC_SIM_TIME,edit,1484980352
Control15=IDC_SIM_DATE,edit,1484849280
Control16=IDC_RADIOMINMAX,button,1342308361
Control17=IDC_RADIOHOURLY,button,1342177289
Control18=IDOK,button,1342373889
Control19=IDCANCEL,button,1342242816
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,button,1342177287
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,button,1342177287
Control38=IDC_STATIC,static,1342308352

[DLG:IDD_GRAPHDIALOG]
Type=1
Class=CGraphDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_MSCHART1,{3A2B370C-BA0A-11D1-B137-0000F8753F5D},1342242816

[DLG:IDD_IMMIGRATION]
Type=1
Class=CImmigrationDlg
ControlCount=25
Control1=IDC_RADIOPOLY,button,1342312521
Control2=IDC_RADIOEXP,button,1342181449
Control3=IDC_RADIOLOG,button,1342181449
Control4=IDC_RADIOSIN,button,1342181449
Control5=IDC_RADIOCOS,button,1342181449
Control6=IDC_RADIOTAN,button,1342181449
Control7=IDC_IM_START,SysDateTimePick32,1342373920
Control8=IDC_IM_END,SysDateTimePick32,1342242848
Control9=IDC_MITE_NUM,edit,1350631553
Control10=IDC_MITE_PCT_RESISTANT,edit,1350631553
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_IM_SELECTED,static,1342308353
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,button,1342177287

[DLG:IDD_SELECT_GRAPHS]
Type=1
Class=CSelGraph
ControlCount=24
Control1=IDC_CHECK_F,button,1342242819
Control2=IDC_CHECK_AW,button,1342242819
Control3=IDC_CHECK_WB,button,1342242819
Control4=IDC_CHECK_WL,button,1342242819
Control5=IDC_CHECK_WE,button,1342242819
Control6=IDC_CHECK_CS,button,1342242819
Control7=IDC_CHECK_AD,button,1342242819
Control8=IDC_CHECK_DB,button,1342242819
Control9=IDC_CHECK_DL,button,1342242819
Control10=IDC_CHECK_DE,button,1342242819
Control11=IDC_CHECK_TM,button,1342242819
Control12=IDC_CHECK_RM,button,1342242819
Control13=IDC_CHECK_MWB,button,1342242819
Control14=IDC_CHECK_MDB,button,1342242819
Control15=IDC_CHECK_PWB,button,1342242819
Control16=IDC_CHECK_PDB,button,1342242819
Control17=IDC_CHECK_IM,button,1342242819
Control18=IDOK,button,1342242817
Control19=IDCANCEL,button,1342242816
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_CHECK_PRM,button,1342242819
Control23=IDC_CHECK_MD,button,1342242819
Control24=IDC_CHECK_PMD,button,1342242819

[DLG:IDD_SIMULATION_BAR1]
Type=1
Class=CSimDlg

[DLG:IDD_SIMULATION_BAR]
Type=1
Class=CSimDlgBar
ControlCount=12
Control1=IDC_RADIO_IM_ON,button,1342308361
Control2=IDC_RADIO_IM_OFF,button,1342177289
Control3=IDC_BUTTON_GO,button,1476460544
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_BUTTON_IM_SETUP,button,1476460544
Control9=IDC_IM_TYPE,static,1342308352
Control10=IDC_EDIT_START,SysDateTimePick32,1342242848
Control11=IDC_EDIT_STOP,SysDateTimePick32,1342242848
Control12=IDC_STATIC,static,1350565902

[DLG:IDD_SIMULATION_FORM]
Type=1
Class=CSimulationPage

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_VERSIONBOX,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342177283
Control8=IDOK,button,1342373889

[DLG:IDD_WEATHER_FORM]
Type=1
Class=CWeatherPage
ControlCount=5
Control1=IDC_WEATHER_FILE_LIST,combobox,1344340290
Control2=IDC_STATIC,static,1342308352
Control3=IDC_BUTTONSELECT,button,1342242816
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC_PATH,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
Command6=ID_SHOW_PROPSHEET
Command7=ID_SELECT_GRAPH
CommandCount=7

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE_SESSION
Command4=ID_FILE_SAVE_RESULTS
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_VIEW_PARAMETERS
Command14=ID_VIEW_PLOTDATA
Command15=ID_VIEW_DATA_FREQ
Command16=ID_VIEW_COMBREMOVALDATE
Command17=ID_VIEW_OPTIONS
Command18=ID_WEATHER_CREATENEWWEATHERFILE
Command19=ID_WEATHER_EDITWEATHERFILEFROMDISK
Command20=ID_WEATHER_EDITCURRENTWEATHERFILE
Command21=ID_HELP_FINDER
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_VIEW_ZOOMIN
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_VIEW_ZOOMOUT
Command6=ID_FILE_PRINT
Command7=ID_FILE_SAVE
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_HELP
Command12=ID_CONTEXT_HELP
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_CUT
Command18=ID_EDIT_UNDO
CommandCount=18

[DLG:IDD_PROGRESS]
Type=1
Class=?
ControlCount=1
Control1=IDC_PROGRESS,msctls_progress32,1350565888

[DLG:IDD_SPLASH]
Type=1
Class=?
ControlCount=1
Control1=IDC_SPLASH_CONT,static,1342177294

[DLG:IDD_OLECTRAGRAPHDLG]
Type=1
Class=COlectraGraphDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_OLECTRACHART,{92D71E93-25A8-11CF-A640-9986B64D9618},1342242816

[CLS:COlectraGraphDlg]
Type=0
HeaderFile=OlectraGraphDlg.h
ImplementationFile=OlectraGraphDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_OLECTRACHART
VirtualFilter=dWC

[MNU:IDR_CHARTMENU]
Type=1
Class=?
Command1=IDR_PRINTER
Command2=IDR_FILE
CommandCount=2

[DLG:IDD_ACTION_FORM]
Type=1
Class=CActionPage
ControlCount=26
Control1=IDC_STATIC,button,1342177287
Control2=IDC_ENABLE,button,1342242819
Control3=IDC_RADIO_SCHED,button,1342308361
Control4=IDC_RADIO_AUTO,button,1342177289
Control5=IDC_STATIC,static,1342308354
Control6=IDC_EDIT_DELAY,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_RQSLIDERQUEEN,msctls_trackbar32,1342242817
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATICDATE,static,1342177282
Control13=IDC_QUEEN_DATE,SysDateTimePick32,1342242848
Control14=IDC_RADIO_RQ_ONCE,button,1342308361
Control15=IDC_RADIO_RQ_ANNUAL,button,1342185481
Control16=IDC_STATIC,button,1342308359
Control17=IDC_VT_ENABLE,button,1342242819
Control18=IDC_TREATMENT_START,SysDateTimePick32,1342242848
Control19=IDC_STATIC,static,1342308354
Control20=IDC_TREATMENT_DURATION,edit,1350631552
Control21=IDC_STATIC,static,1342308354
Control22=IDC_STATIC,static,1342308352
Control23=IDC_MORTALITY,edit,1350631552
Control24=IDC_STATIC,static,1342308354
Control25=IDC_RESISTANT,edit,1350631552
Control26=IDC_STATIC,static,1342308354

[CLS:CActionPage]
Type=0
HeaderFile=ActionPage.h
ImplementationFile=ActionPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CActionPage

[DLG:IDD_REMOVECOMB]
Type=1
Class=CCombRemDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_REMCOMBEN,button,1342242819
Control4=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PERCENT,edit,1350631552
Control7=IDC_STATIC,static,1342308352

[CLS:CCombRemDlg]
Type=0
HeaderFile=CombRemDlg.h
ImplementationFile=CombRemDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCombRemDlg

[DLG:IDD_OPTIONS]
Type=1
Class=COptions
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIOWEEKLY,button,1342308361
Control5=IDC_RADIODAILY,button,1342177289
Control6=IDC_STATIC,button,1342308359
Control7=IDC_RADIOFIELDFIXED,button,1342308361
Control8=IDC_RADIODIELDCOMMA,button,1342177289
Control9=IDC_RADIOFIELDTAB,button,1342177289
Control10=IDC_CHECKWTHCOL,button,1342242819
Control11=IDC_STATIC,static,1342177294
Control12=IDC_STATIC,button,1342177287

[CLS:COptions]
Type=0
HeaderFile=Options.h
ImplementationFile=Options.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=COptions

[DLG:IDD_WEATHEREDIT]
Type=1
Class=CWeatherEditor
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_WEATHERGRAPH,{92D71E93-25A8-11CF-A640-9986B64D9618},1342242816

[MNU:IDR_MENUWEATHER]
Type=1
Class=?
Command1=ID_WEATHER_FILE_OPEN
Command2=ID_WEATHER_FILE_SAVE
Command3=ID_WEATHER_FILE_SAVEAS
Command4=ID_WEATHER_FILE_EXIT
Command5=ID_VIEW_ZOOMIN
Command6=ID_VIEW_ZOOMOUT
CommandCount=6

[CLS:CWeatherEditor]
Type=0
HeaderFile=WeatherEditor.h
ImplementationFile=WeatherEditor.cpp
BaseClass=CDialog
Filter=D
LastObject=CWeatherEditor
VirtualFilter=dWC

[TB:IDB_WEATHERTOOLBAR]
Type=1
Class=?
Command1=ID_BUTTON32800
Command2=ID_BUTTON32801
Command3=ID_BUTTON32802
Command4=ID_BUTTON32806
CommandCount=4
