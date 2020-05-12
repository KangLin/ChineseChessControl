========================================================================
		ActiveX Control DLL : 中国象棋控件
========================================================================

ControlWizard has created this project for your ChineseChessControl ActiveX Control
DLL, which contains 1 control.

This skeleton project not only demonstrates the basics of writing an
ActiveX Control, but is also a starting point for writing the specific
features of your control.

This file contains a summary of what you will find in each of the files
that make up your ChineseChessControl ActiveX Control DLL.

ChineseChessControl.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

ChineseChessControl.h
	This is the main include file for the ActiveX Control DLL.  It
	includes other project-specific includes such as resource.h.

ChineseChessControl.cpp
	This is the main source file that contains code for DLL initialization,
	termination and other bookkeeping.

ChineseChessControl.rc
	This is a listing of the Microsoft Windows resources that the project
	uses.  This file can be directly edited with the Visual C++ resource
	editor.

ChineseChessControl.def
	This file contains information about the ActiveX Control DLL that
	must be provided to run with Microsoft Windows.

ChineseChessControl.odl
	This file contains the Object Description Language source code for the
	type library of your control.

/////////////////////////////////////////////////////////////////////////////
XQ control:

XQCtl.h
	This file contains the declaration of the CXQCtrl C++ class.

XQCtl.cpp
	This file contains the implementation of the CXQCtrl C++ class.

XQPpg.h
	This file contains the declaration of the CXQPropPage C++ class.

XQPpg.cpp
	This file contains the implementation of the CXQPropPage C++ class.

XQCtl.bmp
	This file contains a bitmap that a container will use to represent the
	CXQCtrl control when it appears on a tool palette.  This bitmap
	is included by the main resource file 中国象棋控件.rc.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

stdafx.h, stdafx.cpp
	These files are used to build a precompiled header (PCH) file
	named stdafx.pch and a precompiled types (PCT) file named stdafx.obj.

resource.h
	This is the standard header file, which defines new resource IDs.
	The Visual C++ resource editor reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
走棋规则文件

GoRule.h
        走棋头文件

GoRule.cpp
        走棋实现文件

ControlWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
