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
#include <webots/Accelerometer.hpp>
#include <webots/LED.hpp>
#include <webots/LightSensor.hpp>
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
  double val_sensor_posicao_esq_ant = 0;
  double val_sensor_posicao_dir_ant = 0;

  // Define os motores
  Motor *leftMotor = robot->getMotor("left wheel motor");
  Motor *rightMotor = robot->getMotor("right wheel motor");
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);

  // Define os sensores de posicao dos motores
  PositionSensor *leftMotorPosition = robot->getPositionSensor("left wheel sensor");
  PositionSensor *rightMotorPosition = robot->getPositionSensor("right wheel sensor");
  leftMotorPosition->enable(TIME_STEP);
  rightMotorPosition->enable(TIME_STEP);

  // Define os sensores
  DistanceSensor *sensorD_direita = robot->getDistanceSensor("ps0");
  DistanceSensor *sensorD_esquerda = robot->getDistanceSensor("ps7");
  sensorD_direita->enable(TIME_STEP);
  sensorD_esquerda->enable(TIME_STEP);
  
  // Define sensor de chão
  bool brancoF = false;
  bool pretoF = false;
  bool brancoB = false;
  bool pretoB = false;
  // DistanceSensor *sensorIR_F = robot->getDistanceSensor("ir0");
  // DistanceSensor *sensorIR_B = robot->getDistanceSensor("ir1");
  LightSensor *sensorIR_F = robot->getLightSensor("ls0"); // maximo de 2630
  LightSensor *sensorIR_B = robot->getLightSensor("ls3"); // maximo de 2930
  sensorIR_F->enable(TIME_STEP);
  sensorIR_B->enable(TIME_STEP);
  
  // maximo frente de 2630
  // maximo tras de 2930
  // maximo caixa de 4078 talvez
  
  //Accelerometer *acc = robot->getAccelerometerSensor("accelerometer");
  //acc->enable(TIME_STEP);

  // Define os leds
  /*LED *led0 = robot->getLED("led0");
  LED *led1 = robot->getLED("led1");
  LED *led2 = robot->getLED("led2");
  LED *led3 = robot->getLED("led3");
  LED *led4 = robot->getLED("led4");
  LED *led5 = robot->getLED("led5");
  LED *led6 = robot->getLED("led6");
  LED led7 = robot->getLED("led7");*/
  // LED *leds[8] = {led1, led2, led3, led4, led5, led6, led7, led8};
  int empurrando = 0;
  int procurando = 1;
  int cont = 0;
  int cooldown = 0;
  double time = 0;

  // While onde acontece tudo
  while (robot->step(timeStep) != -1)
  {
    //std::cout << "tempo: " << t << std::endl;
    
    // Leitura dos sensores,:
    // sensor de chão
    double val_ir_F = sensorIR_F->getValue();
    std::cout << "Sensor IR Frente: " << val_ir_F << std::endl;
    
    if (val_ir_F < 9 && val_ir_F > 7)
    {
      std::cout << "chão preto FRONT: " << val_ir_F << std::endl;
      pretoF = true;
    } else
    {
      pretoF = false;
    }
    
    if (val_ir_F < 7 && val_ir_F > 1.5)
    {
      std::cout << "chão branco Front: " << val_ir_F << std::endl;
      brancoF = true;
    } 
    else 
    {
      brancoF = false;
    }
    
    double val_ir_B = sensorIR_B->getValue();
    std::cout << "Sensor IR Tras: " << val_ir_B << std::endl;
    
    if ((val_ir_B < 9) && (val_ir_B > 7))
    {
      std::cout << "chão preto BAC: " << val_ir_B << std::endl;
      pretoB = true;
    } 
    else 
    {
      pretoB = false;
    }

    if ((val_ir_B < 7) && (val_ir_B > 1.5))
    {
      std::cout << "chão branco BAC: " << val_ir_B << std::endl;
      brancoB = true;
    }
    else
    {
      brancoB = false;
    }
    
    
    // sensores de distancia
    double val_sensor_distance_Dir = sensorD_direita->getValue();
    double val_sensor_distance_Esq = sensorD_esquerda->getValue();
    //std::cout << "Sensor distance direita: " << val_sensor_distance_Dir << std::endl;
    //std::cout << "Sensor distance esquerda: " << val_sensor_distance_Esq << std::endl;

    // sensores de posicao
    double val_sensor_posicao_esq = leftMotorPosition->getValue();
    double val_sensor_posicao_dir = rightMotorPosition->getValue();
    //double delta_val_sensor_posicao_dir = val_sensor_posicao_dir - val_sensor_posicao_dir_ant;
    //double delta_val_sensor_posicao_esq = val_sensor_posicao_esq - val_sensor_posicao_esq_ant;
    //std::cout << "Sensor posicao direita (delta): " << delta_val_sensor_posicao_dir << std::endl;
    //std::cout << "Sensor posicao esquerda (delta): " << delta_val_sensor_posicao_esq << std::endl;
    
    // IF APENAS PARA TESTE DELETAR APÓS VERSÃO FINAL
    /* int x = 90;
    if(x < 10){
      std::cout << "Sensor posicao direita (delta): " << delta_val_sensor_posicao_dir << std::endl;
      std::cout << "Sensor posicao esquerda (delta): " << delta_val_sensor_posicao_esq << std::endl;
      
      std::cout << "Sensor distance direita: " << val_sensor_distance_Dir << std::endl;
      std::cout << "Sensor distance esquerda: " << val_sensor_distance_Esq << std::endl;
    }
    
    val_sensor_posicao_dir_ant = val_sensor_posicao_dir;
    val_sensor_posicao_esq_ant = val_sensor_posicao_esq;
    
    // CASO NADA AO ALCANCE PROSSEGUIR ENFRENTE || COMENTADO DEVIDO ESTA FUNÇÃO EXISTIR NO FINAL DO WHILE
    if(((val_sensor_distance_Dir < 90) || (val_sensor_distance_Esq < 90))){
      leftMotor->setVelocity(leftSpeed);
      rightMotor->setVelocity(rightSpeed);
      val_sensor_posicao_esq_ant = val_sensor_posicao_esq;
      val_sensor_posicao_dir_ant = val_sensor_posicao_dir;
      t += (double)TIME_STEP / 1000.0;
    }*/
    
    /*
      IFzao com detecção de parede e as cores do frente e trás,
        se após 3 segundos não mudar entra num if(cont > 5seg) que faz ele rodar,
        saindo do if principal ao sensor frontal não detectar mais o objeto.
    */
    // Processamento dos dados
    // Se os sensores de distancia estiverem abaixo de 650, verifica a posicao dos motores
    if ((val_sensor_distance_Dir > 150) || (val_sensor_distance_Esq > 150))
    {
      //leftMotor->setVelocity(2.0);
      //rightMotor->setVelocity(2.0);
      std::cout << "Sensor frontal encontrou algo " << std::endl;
      empurrando = 1;
      // Inicia tentativa de empurrão
      //(val_ir_F > 4) && (val_ir_F < 7)
      
      if ((val_ir_B < 7) && (val_ir_B > 1.5) && (val_ir_F < 7) && (val_ir_F > 1.5))
      {
        // Origem piso brancoF
        // ((empurrando = 1) && ((val_ir_F > 10)))
        //empurrando = 1;
        leftMotor->setVelocity(6.0);
        rightMotor->setVelocity(6.0);
        time += (double)TIME_STEP / 1000.0;
        std::cout << "TIME =  " << time << std::endl;
        if(time < 5.0)
        {
          std::cout << "Entrou empurrando em brancoF (x2) " << std::endl;
          leftMotor->setVelocity(6.0);
          rightMotor->setVelocity(6.0);
        }
      }
      else if ((empurrando == 1) && pretoF && (cooldown == 0))
      {
        // Origem piso pretoF
        if(cont < 99)
        {
          std::cout << "Entrou empurrando em pretoF " << std::endl;
          leftMotor->setVelocity(leftSpeed);
          rightMotor->setVelocity(rightSpeed);
          std::cout << "empurrando: " << std::endl;
          cont += 1;
        }
        else if(cont > 99)
        {
          cont = 0;
          cooldown = 1;
          empurrando = 0;
        }
      } 
      else 
      {
        // Se os sensores de posicao nao estiverem mudando de posicao, faz o robo virar para a direita
        leftMotor->setVelocity(-leftSpeed);
        rightMotor->setVelocity(rightSpeed);
        t += (double)TIME_STEP / 1000.0;
      }
    } 
    else if ((cooldown == 1)) 
    {
      leftMotor->setVelocity(leftSpeed);
      rightMotor->setVelocity(-rightSpeed);
      //t += (double)TIME_STEP / 1000.0;
      if((val_sensor_distance_Dir < 100) || (val_sensor_distance_Esq < 100))
      {
        cooldown = 0;
      // }
      } 
      else 
      {
        leftMotor->setVelocity(6.0);
        rightMotor->setVelocity(6.0);
        cooldown = 0;
        //val_sensor_posicao_esq_ant = val_sensor_posicao_esq;
        //val_sensor_posicao_dir_ant = val_sensor_posicao_dir;
        t += (double)TIME_STEP / 1000.0;
        time = 0;
      }
    };
  }

  // Enter here exit cleanup code.
  delete robot;
  return 0;
} 