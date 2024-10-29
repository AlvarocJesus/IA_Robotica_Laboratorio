// File:          controller_projeto.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <cmath>
#include <iostream>
#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/utils/AnsiCodes.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;

#define TIME_STEP 64

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  double leftSpeed = 2.0;
  double rightSpeed = 2.0;
  double t = 0;

  // Define os motores
  Motor *leftMotor = robot->getMotor("left wheel motor");
 Motor *rightMotor = robot->getMotor("right wheel motor");
 // set the target position of the motors
 leftMotor->setPosition(INFINITY);
 rightMotor->setPosition(INFINITY);

  // Define os sensores
  DistanceSensor *sensorD_front = robot->getDistanceSensor("so3");
  DistanceSensor *sensorD_back = robot->getDistanceSensor("so11");
  sensorD_front->enable(TIME_STEP);
  sensorD_back->enable(TIME_STEP);

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    double val_sensor_distance_front = sensorD_front->getValue();
    double val_sensor_distance_back = sensorD_back->getValue();
    // std::cout << "Sensor distance frente: " << val_sensor_distance_front <<
    // std::endl; std::cout << "Sensor distance tras: " <<
    // val_sensor_distance_back << std::endl;
    if (val_sensor_distance_front <= 650) {
      std::cout << "Sensor distance frente (so3): " << AnsiCodes::RED_FOREGROUND << val_sensor_distance_front << AnsiCodes::RESET << std::endl;
      std::cout << "Sensor distance tras (so11): " << val_sensor_distance_back << std::endl;
    } else if (val_sensor_distance_back <= 650) {
      std::cout << "Sensor distance frente (so3): " << val_sensor_distance_front << std::endl;
      std::cout << "Sensor distance tras (so11): " << AnsiCodes::RED_FOREGROUND << val_sensor_distance_back << AnsiCodes::RESET << std::endl;
    } else {
      std::cout << "Sensor distance frente (so3): " << val_sensor_distance_front << std::endl;
      std::cout << "Sensor distance tras (so11): " << val_sensor_distance_back << std::endl;
    }

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    if (val_sensor_distance_front <= 650) {
      std::cout << "Sensor da frente (so3)" << std::endl;
      left_motor_front->setVelocity(leftSpeed);
      left_motor_back->setVelocity(leftSpeed);
      right_motor_front->setVelocity(rightSpeed);
      right_motor_back->setVelocity(rightSpeed);
      t += (double)TIME_STEP/1000.0;
    } else if (val_sensor_distance_back <= 650) {
      std::cout << "Sensor de tras (so11)" << std::endl;
      left_motor_front->setVelocity((leftSpeed * -1));
      left_motor_back->setVelocity((leftSpeed * -1));
      right_motor_front->setVelocity((rightSpeed * -1));
      right_motor_back->setVelocity((rightSpeed * -1));
      t += (double)TIME_STEP/1000.0;
    }
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
