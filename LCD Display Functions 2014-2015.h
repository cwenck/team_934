/////////////////////////
//LCD Display Functions//
/////////////////////////

//task updateLCD();
//void initLCD();
//void updatePressedButtons();
//void clearScreen();
//void displayPressedButtons();
//void displayFirmware();
//void displayBattery();


//typedef enum {
//		home = 0
//} Screen;

//typedef struct {
//	bool rightBtn;
//	bool centerBtn;
//	bool leftBtn;
//} ButtonsPressed;

/////////////
//Variables//
/////////////

//Screen currentScreen = home;
//ButtonsPressed lcdButtons;

/////////////
//Functions//
/////////////

//task updateLCD(){
//	initLCD();
//	while(true){
//		//displayBattery();
//		updatePressedButtons();
//		displayPressedButtons();
//		wait1Msec(5);
//	}
//}

//void initLCD(){
//	lcdButtons.rightBtn = false;
//	lcdButtons.centerBtn = false;
//	lcdButtons.leftBtn = false;
//}

//void displayPressedButtons(){
//	string buttonString = "";
//	sprintf(buttonString, "L: %i C:%i R: %i", lcdButtons.leftBtn, lcdButtons.centerBtn, lcdButtons.rightBtn);
//	displayLCDCenteredString(0, buttonString);
//}

// 1 = left
// 2 = center
// 3 = left + center
// 4 = right
// 5 = left + right
// 6 = center + right
// 7 = left + center + right

//void updatePressedButtons() {
//    switch ((int)nLCDButtons) {
//        case 0:
//            lcdButtons.leftBtn = false;
//            lcdButtons.centerBtn = false;
//            lcdButtons.rightBtn = false;
//            break;
//        case 1:
//            lcdButtons.leftBtn = true;
//            lcdButtons.centerBtn = false;
//            lcdButtons.rightBtn = false;
//            break;
//        case 2:
//            lcdButtons.leftBtn = false;
//            lcdButtons.centerBtn = true;
//            lcdButtons.rightBtn = false;
//            break;
//        case 3:
//            lcdButtons.leftBtn = true;
//            lcdButtons.centerBtn = true;
//            lcdButtons.rightBtn = false;
//            break;
//        case 4:
//            lcdButtons.leftBtn = false;
//            lcdButtons.centerBtn = false;
//            lcdButtons.rightBtn = true;
//            break;
//        case 5:
//            lcdButtons.leftBtn = true;
//            lcdButtons.centerBtn = false;
//            lcdButtons.rightBtn = true;
//            break;
//        case 6:
//            lcdButtons.leftBtn = false;
//            lcdButtons.centerBtn = true;
//            lcdButtons.rightBtn = true;
//            break;
//        case 7:
//            lcdButtons.leftBtn = true;
//            lcdButtons.centerBtn = true;
//            lcdButtons.rightBtn = true;
//            break;
//    }
//}

//void clearScreen() {
//    clearLCDLine(0);
//    clearLCDLine(1);
//}

//void displayFirmware() {
//    string master = "";
//    string robot_c = "";
//    sprintf(master, "Master: %i", (int)nVexMasterVersion);
//    sprintf(robot_c, "RobotC: %i", (int)version);
//    displayLCDCenteredString(0, master);
//    displayLCDCenteredString(1, robot_c);
//}


//const float powerExpDevisorOne = 46.5;
//const float powerExpDevisorTwo = 70.0;

//void displayBattery() {
//    int mainVoltage = nImmediateBatteryLevel;
//    int powerExpVoltage = SensorValue[powerExpInfo] / powerExpDevisorOne;
//    int backupVoltage = BackupBatteryLevel;

//    string mVoltage;
//    string pExpVoltage;
//    string bVoltage;

//    sprintf(mVoltage, "Main: %.2fV", (mainVoltage / 1000.0));
//    sprintf(bVoltage, "Backup: %.2fV", (backupVoltage / 1000.0));
//    sprintf(pExpVoltage, "PowExp: %.2fV", powerExpVoltage);

//    displayLCDCenteredString(0, mVoltage);
//    //displayLCDCenteredString(1, bVoltage);
//    displayLCDCenteredString(1, pExpVoltage);
//}
