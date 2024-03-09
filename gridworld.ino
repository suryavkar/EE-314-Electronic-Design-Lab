#include <SoftwareSerial.h>
SoftwareSerial bt(51,52); // rxPin, txPin

// flags
int state_flag=0; // check if in state or not
int init_flag=0; // initialisation flag
int end_flag=0; // episode end flag
int stop_flag=0; // flag to stop printing
int back_flag=0; // back flag

/* motor controll pins */
const int motorRPin1 = 25; // signal pin 1 for the right motor, connect to IN1               
const int motorRPin2 = 24;  // signal pin 2 for the right motor, connect to IN2
const int motorREnable = 12; // enable pin for the right motor (PWM enabled)

const int motorLPin1 = 23; // signal pin 1 for the left motor, connect to IN3           
const int motorLPin2 = 22; // signal pin 2 for the left motor, connect to IN4
const int motorLEnable = 13; // enable pin for the left motor (PWM enabled)

/* sensor pins */
const int irPins[8] = {48,50,44,46,42,40,36,38};

const int trigPin = 30;
const int echoPin = 31;

const int led_pin = 2;

/* parameters */
long duration;
int distance;

int irSensors = B00000000; 

int motorLSpeed = 200;
int motorRSpeed = 200 ;
int error = 105;   // 145 best 200  //  normal 255  // mad 0 

/* initial parameters */
int presx=0;
int presy=0;
char orient='r';

int prevx;
int prevy;

/* RL parameters */
float reward = 0.0;

char pres_act;
char prev_act;

const float alpha = 0.1;
const float gamma = 1;
const long eps = 100;

const int grid_size = 3;
// initial Q table
float Q_table[grid_size*grid_size][4] = {0};
// 2 7
// float Q_table[grid_size*grid_size][4] = {-1.06,-1.08,-1.1,-0.75,1.31,-0.85,-0.63,-1.0.00,0.00,0.00,0.00,0.00,-0.6,-2.75,-0.71,-0.08,-2.71,-0.4,-0.43,4.76,8.5,-0.08,-1.0.00,0.46,-0.48,-0.5,-0.56,-1.9,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00};
// 1 7
// float Q_table[grid_size*grid_size][4] = {-1.28,-1.44,-1.45,-6.13,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00,-0.68,-0.68,-0.78,0.31,-1.9,-0.13,-1.9,3.39,7.71,-0.1,0.00,0.00,-0.5,-0.5,-0.44,-3.44,0.00,0.00,0.00,0.00,0.00,0.00,0.00,0.00};

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  bt.begin(9600);

  pinMode(motorLPin1,OUTPUT);        
  pinMode(motorLPin2,OUTPUT);
  pinMode(motorLEnable,OUTPUT);
  
  pinMode(motorRPin1,OUTPUT);        
  pinMode(motorRPin2,OUTPUT);
  pinMode(motorREnable,OUTPUT);

  pinMode(led_pin, OUTPUT);

  pres_act = get_act();
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  
  randomSeed(analogRead(0));

  if(distance<=5)
    end_flag=1;

  // stop for sensor detection
  if (end_flag==1)
  {
    stopme();
    if (stop_flag==0)
    {
      update_pos();
      get_reward();
      update_Q();
      stop_flag++;
      serial_Q();
      digitalWrite(led_pin, HIGH);
    }
  }
  else // default action
  {
    // initial action
    if(init_flag==0)
    {
      pres_act=get_act();
      if (forbid_act()==0)
        take(pres_act);
      else
        stopme();
      serial_Q();
      init_flag++;
    }
    scanD();
    check();
    // new state detected
    if(state_flag==1)
    {
      prev_act=pres_act;
      update_pos();
      get_reward();
      update_Q();
      if (end_flag==0)
      {
        pres_act=get_act();
        if (forbid_act()==0)
          take(pres_act);
        else
          stopme();
      }
      else
      {
        stopme();
        stop_flag++;
      }
      state_flag=0;
      serial_Q();
    }
  }
}

void scanD()
{
  for ( byte count = 0; count < 8;count++ )
  {
    bitWrite(irSensors, count, !digitalRead( irPins[count] ));
  }
}

void update_pos()
{
  prevx = presx;
  prevy = presy;
  if (forbid_act()==0)
  {
    switch (prev_act)
    {
      case 'l':
      presx=presx-1;
      break;

      case 'd':
      presy=presy-1;
      break;

      case 'u':
      presy=presy+1;
      break;

      case 'r':
      presx=presx+1;
      break;

      default:
      break;
    }
    if (presx+presy==2*grid_size-2)
      end_flag=1;
  }
}

void serial_Q()
{
  bt.print("    U   L   D   R\n");
  for (int s=0;s<grid_size*grid_size;s++)
  {
    bt.print(s);
    bt.print(" ");
    for (int a=0;a<4;a++)
    { bt.print(Q_table[s][a]);
      bt.print("   ");
    }
    bt.print("\n\n");
  }

  bt.print("Present State: ");
  bt.print(grid_size*presy+presx);
  bt.print("\n");
  if (end_flag==0)
  {
    bt.print("Present Action: ");
    bt.print(pres_act);
    bt.print("\n\n");
  }

  if (end_flag==1)
  {
    bt.print("\n{");
    for (int s=0;s<grid_size*grid_size;s++)
    {
      for (int a=0;a<4;a++)
      {
        bt.print(Q_table[s][a]);
        if ((s+a) < grid_size*grid_size+2)
          bt.print(",");
      }
    }
    bt.print("}\n\n");
    bt.print(distance);
  }
}