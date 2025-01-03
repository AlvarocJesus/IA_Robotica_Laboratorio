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
	//double val_sensor_posicao_esq_ant = 0;
	//double val_sensor_posicao_dir_ant = 0;

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

           Accelerometer *acc = robot->getAccelerometer("accelerometer");
           acc->enable(TIME_STEP);
           
           
	// Define os leds
	/*LED *led0 = robot->getLED("led0");
	LED *led1 = robot->getLED("led1");
	LED *led2 = robot->getLED("led2");
	LED *led3 = robot->getLED("led3");
	LED *led4 = robot->getLED("led4");
	LED *led5 = robot->getLED("led5");
	LED *led6 = robot->getLED("led6");
	LED *led7 = robot->getLED("led7");*/
	// LED *leds[8] = {led1, led2, led3, led4, led5, led6, led7, led8};

	// While onde acontece tudo
	while (robot->step(timeStep) != -1)
	{
		// Leitura dos sensores:
		const double *teste = acc->getValues();
		std::cout <<"Teste do Accelerometro: " << teste[0] << std::endl;
				
		// sensores de distancia
		double val_sensor_distance_Dir = sensorD_direita->getValue();
		double val_sensor_distance_Esq = sensorD_esquerda->getValue();
		//std::cout << "Sensor distance direita: " << val_sensor_distance_Dir << std::endl;
		//std::cout << "Sensor distance esquerda: " << val_sensor_distance_Esq << std::endl;

		// sensores de posicao
		double val_sensor_posicao_esq = leftMotorPosition->getValue();
		double val_sensor_posicao_dir = rightMotorPosition->getValue();
		//std::cout << "Sensor posicao direita: " << val_sensor_posicao_dir << std::endl;
		//std::cout << "Sensor posicao esquerda: " << val_sensor_posicao_esq << std::endl;
		int x = 10;
		if(x < -99999999){
      		   std::cout << "Sensor distance direita: " << val_sensor_distance_Dir << std::endl;
		   std::cout << "Sensor distance esquerda: " << val_sensor_distance_Esq << std::endl;

		   std::cout << "Sensor posicao direita: " << val_sensor_posicao_dir << std::endl;
		   std::cout << "Sensor posicao esquerda: " << val_sensor_posicao_esq << std::endl;
		}
		/* CASO NADA AO ALCANCE PROSSEGUIR ENFRENTE || COMENTADO DEVIDO ESTA FUNÇÃO EXISTIR NO FINAL DO WHILE
		if(((val_sensor_distance_Dir < 90) || (val_sensor_distance_Esq < 90))){
            		leftMotor->setVelocity(leftSpeed);
            		rightMotor->setVelocity(rightSpeed);
            		val_sensor_posicao_esq_ant = val_sensor_posicao_esq;
            		val_sensor_posicao_dir_ant = val_sensor_posicao_dir;
            		t += (double)TIME_STEP / 1000.0;
		}*/
		
		// Processamento dos dados
		// Se os sensores de distancia estiverem abaixo de 650, verifica a posicao dos motores
		if (((val_sensor_distance_Dir > 150) || (val_sensor_distance_Esq > 150)))
		{
		
			//leftMotor->setVelocity(2.0);
			//rightMotor->setVelocity(2.0);
			std::cout << "Entrou no primeiro IF " << std::endl;
			// Se os sensores de posicao estiverem mudando de posicao, zera a velocidade dos motores e acende todos os leds
			if ((val_sensor_distance_Dir > 300) || (val_sensor_distance_Esq > 300))
			{
				std::cout << "Entrou no segundo IF " << std::endl;
				/*led0->set(1);
				led1->set(1);
				led2->set(1);
				led3->set(1);
				led4->set(1);
				led5->set(1);
				led6->set(1);
				led7->set(1);
				*/
				
				leftMotor->setVelocity(-3.0);
				rightMotor->setVelocity(-3.0);

				/*int x = 0;
				while (x <= 8)
				{
					for (int i = 0; i < 8; i++)
					{
						leds[i]->set(1);
					}
					x++;
				}*/
			}
			else
			{
				// Se os sensores de posicao nao estiverem mudando de posicao, faz o robo virar para a direita
				leftMotor->setVelocity(leftSpeed);
				rightMotor->setVelocity(-rightSpeed);
				t += (double)TIME_STEP / 1000.0;
			}
		} else {
		
		leftMotor->setVelocity(6.0);
		rightMotor->setVelocity(6.0);
		//val_sensor_posicao_esq_ant = val_sensor_posicao_esq;
		//val_sensor_posicao_dir_ant = val_sensor_posicao_dir;
		t += (double)TIME_STEP / 1000.0;
		}
		/* {
			std::cout << "Sensor da frente (so3)" << std::endl;
			t += (double)TIME_STEP / 1000.0;
		}
		else if (val_sensor_distance_Esq <= 650)
		{
			std::cout << "Sensor de tras (so11)" << std::endl;
			t += (double)TIME_STEP / 1000.0;
		} */
	};

	// Enter here exit cleanup code.
	delete robot;
	return 0;
}