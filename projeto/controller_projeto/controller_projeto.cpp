// File: controller_projeto.cpp
// Date: 2024-11-01
// Description:
// Authors: Álvaro Coelho Jesus, Nicolas Moraes Coppola, Renan Guastella Piva
// Modifications:

#include <cmath>
#include <iostream>
#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/utils/AnsiCodes.hpp>

using namespace webots;

#define TIME_STEP 64

int main(int argc, char **argv)
{
  Robot *robot = new Robot();

  int timeStep = (int)robot->getBasicTimeStep();

  double leftSpeed = 2.0;
  double rightSpeed = 2.0;
  double t = 0;

  // Define os motores
  Motor *leftMotor = robot->getMotor("left wheel motor");
  Motor *rightMotor = robot->getMotor("right wheel motor");
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);

  // Define os sensores de posicao dos motores
  MotorPosition *leftMotorPosition = positionSensor->getMotorPosition("left wheel sensor");
  MotorPosition *rightMotorPosition = positionSensor->getMotorPosition("right wheel sensor");
  leftMotorPosition->enable(TIME_STEP);
  rightMotorPosition->enable(TIME_STEP);

  // Define os sensores
  DistanceSensor *sensorD_direita = robot->getDistanceSensor("ps0");
  DistanceSensor *sensorD_esquerda = robot->getDistanceSensor("ps7");
  sensorD_front->enable(TIME_STEP);
  sensorD_back->enable(TIME_STEP);

  // While onde acontece tudo
  while (robot->step(timeStep) != -1)
  {
    // Leitura dos sensores:
    // sensores de distancia
    double val_sensor_distance_front = sensorD_direita->getValue();
    double val_sensor_distance_back = sensorD_esquerda->getValue();
    std::cout << "Sensor distance direita: " << val_sensor_distance_front << std::endl;
    std::cout << "Sensor distance esquerda: " << val_sensor_distance_back << std::endl;

    // sensores de posicao
    double val_sensor_posicao_esq = leftMotorPosition->getValue();
    double val_sensor_posicao_dir = rightMotorPosition->getValue();
    std::cout << "Sensor posicao direita: " << val_sensor_posicao_dir << std::endl;
    std::cout << "Sensor posicao esquerda: " << val_sensor_posicao_esq << std::endl;
    
    // Processamento dos dados
    /* if (val_sensor_distance_front <= 650)
    {
      std::cout << "Sensor distance frente (so3): " << AnsiCodes::RED_FOREGROUND << val_sensor_distance_front << AnsiCodes::RESET << std::endl;
      std::cout << "Sensor distance tras (so11): " << val_sensor_distance_back << std::endl;
    }
    else if (val_sensor_distance_back <= 650)
    {
      std::cout << "Sensor distance frente (so3): " << val_sensor_distance_front << std::endl;
      std::cout << "Sensor distance tras (so11): " << AnsiCodes::RED_FOREGROUND << val_sensor_distance_back << AnsiCodes::RESET << std::endl;
    }
    else
    {
      std::cout << "Sensor distance frente (so3): " << val_sensor_distance_front << std::endl;
      std::cout << "Sensor distance tras (so11): " << val_sensor_distance_back << std::endl;
    }

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    if (val_sensor_distance_front <= 650)
    {
      std::cout << "Sensor da frente (so3)" << std::endl;
      left_motor_front->setVelocity(leftSpeed);
      left_motor_back->setVelocity(leftSpeed);
      right_motor_front->setVelocity(rightSpeed);
      right_motor_back->setVelocity(rightSpeed);
      t += (double)TIME_STEP / 1000.0;
    }
    else if (val_sensor_distance_back <= 650)
    {
      std::cout << "Sensor de tras (so11)" << std::endl;
      left_motor_front->setVelocity((leftSpeed * -1));
      left_motor_back->setVelocity((leftSpeed * -1));
      right_motor_front->setVelocity((rightSpeed * -1));
      right_motor_back->setVelocity((rightSpeed * -1));
      t += (double)TIME_STEP / 1000.0;
    } */
  };

  // Enter here exit cleanup code.
  delete robot;
  return 0;
}
