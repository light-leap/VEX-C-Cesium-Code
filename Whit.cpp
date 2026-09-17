#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;


brain Brain;


controller Controller = controller(primary);
motor LeftDriveSmartA = motor(PORT1, ratio18_1, true);
motor LeftDriveSmartB = motor(PORT2, ratio6_1, true);
motor LeftDriveSmartC = motor(PORT3, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(LeftDriveSmartA, LeftDriveSmartB, LeftDriveSmartC);
motor RightDriveSmartA = motor(PORT4, ratio6_1, false);
motor RightDriveSmartB = motor(PORT6, ratio18_1, false);
motor RightDriveSmartC = motor(PORT5, ratio6_1, false);
motor_group RightDriveSmart = motor_group(RightDriveSmartA, RightDriveSmartB, RightDriveSmartC);
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
smartdrive Drivetrain = smartdrive(LeftDriveSmart,  RightDriveSmart,TurnGyroSmart, 319.19, 320, 130, mm, 1);
pneumatics Claw = pneumatics(Brain.ThreeWirePort.A);
pneumatics Fin = pneumatics(Brain.ThreeWirePort.B);
pneumatics ClawAngle = pneumatics(Brain.ThreeWirePort.C);
motor ArmMotorA = motor(PORT14, ratio6_1, true);
motor ArmMotorB = motor(PORT13, ratio6_1, true);
motor_group LiftyArm = motor_group(ArmMotorA, ArmMotorB);
motor Intake1 = motor(PORT7, ratio18_1, true);
motor Intake2 = motor(PORT9, ratio18_1, true);
motor_group Sucker = motor_group(Intake1, Intake2);



bool RemoteControlEnabled = true;
bool DrivetrainLNeedsToBeStopped_Controller = true;
bool DrivetrainRNeedsToBeStopped_Controller = true;
bool ButtonArm = true;
bool ButtonIntake = true;
bool ButtonClaw = true;

void vexcodeInit(void) {
  while (1) {
    if (RemoteControlEnabled) {
      int drivetrainLeftSideSpeed = Controller.Axis3.position() + Controller.Axis1.position();
      int drivetrainRightSideSpeed = Controller.Axis3.position()- Controller.Axis1.position();
      
              
      
      if(drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        if (DrivetrainLNeedsToBeStopped_Controller) {
          LeftDriveSmart.stop();
          DrivetrainLNeedsToBeStopped_Controller = false;
        }

      } else {
        DrivetrainLNeedsToBeStopped_Controller = true;
      }
      
      if(drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        if (DrivetrainRNeedsToBeStopped_Controller) {
          RightDriveSmart.stop();
          DrivetrainRNeedsToBeStopped_Controller = false;
        }

      } else {
        DrivetrainRNeedsToBeStopped_Controller = true;
      }

      if (DrivetrainLNeedsToBeStopped_Controller){
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      if (DrivetrainRNeedsToBeStopped_Controller){
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }


     if (Controller.ButtonX.pressing()) {
      ArmMotorA.spin(forward,100,percent);
      ArmMotorB.spin(reverse,100, percent);
      ButtonArm = false;

     } else if (Controller.ButtonB.pressing()){
      ArmMotorA.spin(reverse,100,percent);
      ArmMotorB.spin(forward,100,percent);
      ButtonArm = false;
     
    } else if (!ButtonArm) {
      ArmMotorA.stop();
      ArmMotorB.stop();
      ButtonArm = true;
    }


    if (Controller.ButtonR2.pressing()) {
      Intake1.spin(forward,100,percent);
      Intake2.spin(reverse,100, percent);
      ButtonIntake = false;

     } else if (Controller.ButtonL2.pressing()){
      Intake1.spin(reverse,100,percent);
      Intake2.spin(forward,100,percent);
      ButtonIntake = false;
     
    } else if (ButtonIntake) {
      Intake1.stop();
      Intake2.stop();
      ButtonIntake = true;

    
    }

    if (Controller.ButtonR1.pressing());{
    Claw.open();
    
    } if (Controller.ButtonL1.pressing());{
      Claw.close();
    }

    if (Controller.ButtonUp.pressing());{
    Fin.open();
    
    } if (Controller.ButtonDown.pressing());{
      Fin.close();
    }

if (Controller.ButtonRight.pressing());{
    ClawAngle.open();
    
    } if (Controller.ButtonLeft.pressing());{
      ClawAngle.close();
    }

  }
if (Controller.ButtonX.pressing());{
  //Controller1.rumble("..-");
  Controller.Screen.print("Up we go.");
}
 if (Controller.ButtonB.pressing());{
 // Controller1.rumble("..-");
  Controller.Screen.print("Down already? :(");
}     
if (Controller.ButtonR2.pressing());{
 // Controller1.rumble("..-");
  Controller.Screen.print("Yummy.");
}
if (Controller.ButtonL2.pressing());{
 // Controller1.rumble("..-");
  Controller.Screen.print("Not good.");
}

if (Controller.ButtonX.pressing());{
  //Controller1.rumble("..-");
  Brain.Screen.print("Up we go.");
}
 if (Controller.ButtonB.pressing());{
 // Controller1.rumble("..-");
  Brain.Screen.print("Down already? :(");
}     
if (Controller.ButtonR2.pressing());{
 // Controller1.rumble("..-");
  Brain.Screen.print("Yummy.");
}
if (Controller.ButtonL2.pressing());{
 // Controller1.rumble("..-");
  Brain.Screen.print("Not good.");
} 
Brain.Screen.drawRectangle(50, 50, 130, 60);
Brain.Screen.drawCircle(240, 120, 40);



}
    

    }
    