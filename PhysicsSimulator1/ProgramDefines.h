#ifndef PROGRAMDEFINES_H
#define PROGRAMDEFINES_H

/**
*    @author John Allard
* This file is used to define aliases for all of the UI elements used in our file.
* In Windows Forms Applications, all UI elements must be represented by a unique interger, to
* allow our code to still be readable, we will define the names of the UI elements here and assign them
* to a unique interger. I don't really like it either, but it's the reccomended way of writing Windows Forms Applications,
* and allows for consistant definitions across all windows in the program
*/


// Program Wide Includes
#include "resource.h"
#include "Colors.h"

#include <Windows.h>
#include <commctrl.h>
#include <vector>

//=========================
//=== COLORS ============
//========================

//static HBRUSH BACKGROUNDCOLOR = CreateSolidBrush(RGB(51, 51, 51));// deep blue
static HBRUSH BACKGROUNDCOLOR = CreateSolidBrush(RGB(51, 51, 51));// deep blue
static HBRUSH BOXCOLOR = CreateSolidBrush(RGB(0, 35, 51)); //white    



//===========================
//=== MAIN MENU DEFINES =====
//===========================
// 5200 - 5300

//----button defines----

// start simulation buttons
#define bDPSIM            5200
#define b2DWAVE            5201
#define b3DWAVE            5202
#define bSPRING            5203
#define bTRAJEC            5204

// help and about buttons
#define bMAINHELP        5205
#define bMAINABOUT        5206





//===========================
//=== DOUBLE PENDULUM DEFINES
//===========================
//5500 - 6000

//buttons
#define bDPSTARTSIM     5500
#define bDPHELP            5501
#define bDPBACK            5502
#define bDPLOAD            5503
#define bDPSAVE            5504
#define bDPRANDOMIZE    5561
#define bDPRESET        5562
#define dDPSIMSETTINGS  5563
#define bDPCLEAR        5564
#define bDPCONFIGURE1   5520
#define bDPCONFIGURE2    5521
#define bDPABOUT        5499

// drop down boxes
#define cbDPSELECTSYSTEM 5565
#define cbDPSYSTEMPLOT1  5566
#define cbDPSYSTEMPLOT2     5567

// radio buttons
#define rbDPPLOT1SYS1        5522
#define rbDPPLOT1SYS2        5523
#define rbDPPLOT2SYS1        5524
#define rbDPPLOT2SYS2        5525


//edit text
#define etDPULENGTH     5505
#define etDPUMASS        5506
#define etDPUANGLE        5507
#define etDPUVEL        5508

#define etDPLLENGTH     5509
#define etDPLMASS        5510
#define etDPLANGLE        5511
#define etDPLVEL        5512

#define etDPTIME        5550
#define etDPGRAVITY        5551
#define etDPSIMSPEED    5552
#define etDPSIMLENGTH   5526

// spin controls
#define scDPULENGTH        5513
#define scDPUMASS        5514
#define scDPUANGLE        5515
#define scDPUVEL        5516

#define scDPLLENGTH        5513
#define scDPLMASS        5514
#define scDPLANGLE        5515
#define scDPLVEL        5516
#define scDPTIME        5517

#define scDPGRAVITY        5518
#define scDPSIMSPEED    5519
#define scDPSIMLENGTH    5527

#define DPSETTINGSDIALOG    5571

// GENERAL PLOT CALLBACK UI ELEMENTS 
#define bDPDIALOGCLOSE            5575
#define bDPDIALOGSAVE            5576
#define cbDPINCLUDETITLE        5577
#define cbDPINCLUDEGRID            5578


// POSITION PLOT CALLBACK UI ELEMENTS
#define cbDPINCLUDELINE            6000
#define ddDPUMASSCOLOR            6001
#define ddDPLMASSCOLOR            6002
#define ddDPLINECOLOR            6003

#define scDPLINETHICKNESS        6004
#define etDPLINETHICKNESS        6005

// ENERGY PLOT CALLBACK UI ELEMENTS
#define ddDPKINCOLOR            6006
#define ddDPPOTCOLOR            6007
#define ddDPTOTCOLOR            6008

#define cbDPINCLUDEKIN            6009
#define cbDPINCLUDEPOT            6010
#define cbDPINCLUDETOT            6011

// ANGLE PLOT CALLBACK UI ELEMENTS

#define ddDPANGLETYPE            6020
#define ddDPANGLEUNITS            6021
#define ddDPANGLECOLOR            6022

#define scDPLINEWIDTH            6023
#define etDPLINEWIDTH            6024
#define cbDPNORMALIZE            6025


// ANGVEL PLOT CALLBACK UI ELEMENTS

#define ddDPANGVELTYPE            6026
#define ddDPANGVELUNITS            6027
#define ddDPANGVELCOLOR            6028





//===========================
//=== 2D WAVE SIM DEFINES ===
//===========================






//===========================
//=== 3D WAVE SIM DEFINES ===
//===========================







//===========================
//=== SPRING/MASS DEFINES ===
//===========================






//===========================
//=== TRAJECTORY DEFINES =====
//===========================





#endif
