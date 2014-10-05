#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, I2C_3)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, I2C_4)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, I2C_2)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_HBridge, openLoop, reversed, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port6,           rightLift,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port7,           leftLift,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorVex393_HBridge, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "LCD Display Functions 2014-2015.h"

//////////////////
//Control Config//
//////////////////

//TVexJoysticks strafeLeft = Btn7L;
//TVexJoysticks strafeRight = Btn7R;

TVexJoysticks up = Btn5U;
TVexJoysticks down = Btn5D;

TVexJoysticks left_up = Btn7U;
TVexJoysticks left_down = Btn7D;

TVexJoysticks right_up = Btn8U;
TVexJoysticks right_down = Btn8D;

TVexJoysticks clawOpen = Btn6U;
TVexJoysticks clawClose = Btn6D;

TVexJoysticks forward_backward = Ch3;
TVexJoysticks left_right = Ch4;

TVexJoysticks forward_backward_strafe = Ch2;
TVexJoysticks left_right_strafe = Ch1;

TVexJoysticks toggle_drive = Btn8D;

TVexJoysticks softTurnModifier = Ch1;


/////////////
//Variables//
/////////////

bool driveMode = true;
bool driveModeButtonPressed = false;

/////////////
//Constants//
/////////////

const int LIFT_SPEED = 127;
const int CLAW_SPEED = 100;
const int ADJUST_LIFT_SPEED = 127;
const int DRIVE_THRESHOLD = 5;

/////////
//Enums//
/////////

typedef enum {
    right = 0,
    left = 1
} Side;

/*
 * Spin the wheels towards each other
 * Spin the wheels awat from each other
 * Spin the wheels in the same direction
 */
typedef enum {
    towards = 0,
    away = 1,
    same = 2
} WheelDirection;


////////////////////////
//FUNCTION PROTOTYPES//
///////////////////////
void stopDrive();
void stopAllMotors();
void resetDriveEncoders();
void setLeftMotorSpeed(int speed, WheelDirection dir = same);
void setRightMotorSpeed(int speed, WheelDirection dir = same);
//void setLeftLiftSpeed(int speed);
//void setRightLiftSpeed(int speed);
void setLiftSpeed(int speed);
void strafe(int speed, Side dir);
void drive(int speed);
void moveLift(int speed);
void handleClawInput();
void basicStickDrive();

void handleLiftInput();
void handleDriveInput();
//void toggleDriveInput();
void readInput();

////////////////////////////////
//External Function Prototypes//
////////////////////////////////

//void displayFirmware();
//void displayBattery();

/////////////
//FUNCTIONS//
/////////////

void stopDrive() {
    setLeftMotorSpeed(0);
    setRightMotorSpeed(0);
}

void stopAllMotors() {
    motor[port1]  = 0;
    motor[port2]  = 0;
    motor[port3]  = 0;
    motor[port4]  = 0;
    motor[port5]  = 0;
    motor[port6]  = 0;
    motor[port7]  = 0;
    motor[port8]  = 0;
    motor[port9]  = 0;
    motor[port10] = 0;
}

void resetDriveEncoders() {
    nMotorEncoder[backLeft] = 0;
    nMotorEncoder[frontLeft] = 0;
    nMotorEncoder[backRight] = 0;
    nMotorEncoder[frontRight] = 0;
}

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setLeftMotorSpeed(int speed, WheelDirection dir) {
    if (dir == same) {
        motor[frontLeft] = speed;
        motor[backLeft]  = speed;
    } else if (dir == towards) {
        speed = abs(speed);
        motor[frontLeft] = speed;
        motor[backLeft]  = -speed;
    } else if (dir == away) {
        speed = abs(speed);
        motor[frontLeft] = -speed;
        motor[backLeft]  = speed;
    }
}

/*
 * A positive value for speed is forwards
 * A negetive value for speed is backwards (only works if the direction is same)
 */
void setRightMotorSpeed(int speed, WheelDirection dir) {
    if (dir == same) {
        motor[frontRight] = speed;
        motor[backRight]  = speed;
    } else if (dir == towards) {
        speed = abs(speed);
        motor[frontRight] = -speed;
        motor[backRight]  = speed;
    } else if (dir == away) {
        speed = abs(speed);
        motor[frontRight] = speed;
        motor[backRight]  = -speed;
    }
}

/*
 * Strafe left and right at a particular speed
 */
void strafe(int speed, Side dir) {
		speed = abs(speed);
    if (dir == left) {
        setLeftMotorSpeed(speed, towards);
        setRightMotorSpeed(speed, away);
    } else if (dir == right) {
        setLeftMotorSpeed(speed, away);
        setRightMotorSpeed(speed, towards);
    }
}

/*
 * Speed is the speed that will be applied to the motors
 * Use a positive value for forward and a negetive one for backwards
 */
void drive(int speed) {
    setLeftMotorSpeed(speed);
    setRightMotorSpeed(speed);
}

//void setLeftLiftSpeed(int speed){
//	motor[leftLift] = speed;
//	motor[leftLift2] = speed;
//}

//void setRightLiftSpeed(int speed){
//	motor[rightLift] = speed;
//	motor[rightLift2] = speed;
//}

void setLiftSpeed(int speed){
	motor[leftLift] = speed;
	motor[rightLift] = speed;
}

void handleClawInput(){
	if(vexRT[clawOpen] == 1){
		motor[claw] = CLAW_SPEED;
	} else if(vexRT[clawClose] == 1){
		motor[claw] = -CLAW_SPEED;
	} else {
		motor[claw] = 0;
	}
}

/*
 * Speed is the speed that will be applied to the motors
 * Use a positive value for up and a negetive one for down
 */
void moveLift(int speed) {
    //setLeftLiftSpeed(speed);
    //setRightLiftSpeed(speed);
		setLiftSpeed(speed);
}

void handleLiftInput() {
    if (vexRT[up] == 1) {
        moveLift(LIFT_SPEED);
    } else if (vexRT[down] == 1) {
        moveLift(-LIFT_SPEED);
    } else {
    	moveLift(0);
  	}
    //else {
   	//		if (vexRT[left_up] == 1) {
    //  	  setLeftLiftSpeed(ADJUST_LIFT_SPEED);
   	//		} else if (vexRT[left_down] == 1) {
   	//    	 setLeftLiftSpeed(-ADJUST_LIFT_SPEED);
  		//	} else {
    //   		setLeftLiftSpeed(0);
    //   	}

    //   	if (vexRT[right_up] == 1) {
    //    	setRightLiftSpeed(ADJUST_LIFT_SPEED);
    //		} else if (vexRT[right_down] == 1) {
    //  		  setRightLiftSpeed(-ADJUST_LIFT_SPEED);
    //		} else {
    // 		 	  setRightLiftSpeed(0);
    //		}
    //	}
    }

void basicStickDrive(){
		if(abs(vexRT[forward_backward]) > abs(vexRT[left_right])){
			drive(vexRT[forward_backward]);
		}else{
			setRightMotorSpeed(-vexRT[left_right]);
			setLeftMotorSpeed(vexRT[left_right]);
		//	if(vexRT[left_right] > 0){
		//		setLeftMotorSpeed(vexRT[left_right]);
		//		setRightMotorSpeed(vexRT[left_right], towards);
		//	} else {
		//		setLeftMotorSpeed(-vexRT[left_right], towards);
		//		setRightMotorSpeed(-vexRT[left_right]);
		//}
	}
}

void basicStrafing(){
		if(abs(vexRT[forward_backward_strafe]) > abs(vexRT[left_right_strafe])){
			drive(vexRT[forward_backward_strafe]);
		}else{
			if(vexRT[left_right_strafe] < 0){
				strafe(vexRT[left_right_strafe], left);
			} else {
				strafe(vexRT[left_right_strafe], right);
			}
		}
}

//void toggleDriveInput(){
//	if(vexRT[toggle_drive] == 1 && driveModeButtonPressed == false){
//		driveModeButtonPressed = true;
//		driveMode = !driveMode;
//	} else {
//		driveModeButtonPressed = false;
//	}
//}

void handleDriveInput() {
	//toggleDriveInput();
	//if(driveMode){
	//	basicStickDrive();
	//}else{
	//	basicStrafing();
	//}

	if(abs(vexRT[forward_backward]) <= DRIVE_THRESHOLD && abs(vexRT[left_right]) <= DRIVE_THRESHOLD){
		basicStrafing();
	} else {
		basicStickDrive();
	}
}

void readInput() {
    handleLiftInput();
    handleDriveInput();
    handleClawInput();
}

void moveMotor(float percentageOfPower){
	motor[port7] = percentageOfPower * vexRT[Ch2];
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	drive(-vexRT[forward_backward]);
	wait1Msec(500);
	drive(0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	resetDriveEncoders();
    while (true) {
        readInput();
    }
}
