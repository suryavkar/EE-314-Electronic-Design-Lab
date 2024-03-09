void take(char act)
{
  if(orient=='u')
  {
    switch (act)
    {
      case 'l':
      left90(600);
      orient='l';
      break;

      case 'd':
      back();
      orient=act;
      break;

      case 'u':
      go();
      delay(400);
      break;

      case 'r':
      right90(600);
      orient='r';
      break;

      default:
      stopme();
    }
  }
  else if(orient=='r')
  {
    switch (act)
    {
      case 'l':
      back();
      orient=act;
      break;

      case 'd':
      right90(600);
      orient='d';
      break;

      case 'u':
      left90(600);
      orient='u';
      break;

      case 'r':
      go();
      delay(400);
      break;

      default:
      stopme();
    }
  }

  else if(orient=='d')
  {
    switch (act)
    {
      case 'l':
      right90(600);
      orient='l';
      break;

      case 'd':
      go();
      delay(400);
      break;

      case 'u':
      back();
      orient=act;
      break;

      case 'r':
      left90(600);
      orient='r';
      break;

      default:
      stopme();
    }
  }
  else  //left orientation
  {  
    switch (act)
    {
      case 'l':
      go();
      delay(400);
      break;

      case 'd':
      left90(600);
      orient='d';
      break;

      case 'u':
      right90(600);
      orient='u';
      break;

      case 'r':
      back();
      orient=act;
      break;

      default:
      stopme();
    }
  }
}

void rightS()
{
  analogWrite(motorREnable, motorRSpeed);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);
  
  analogWrite(motorLEnable, motorLSpeed-error);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, HIGH);
}


void leftS()
{
  analogWrite(motorREnable, motorRSpeed-error);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);
  
  analogWrite(motorLEnable, motorLSpeed);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);
}

void go()
{
  analogWrite(motorREnable, motorRSpeed);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);
  
  analogWrite(motorLEnable, motorLSpeed);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);
}

void stopme()
{
  analogWrite(motorREnable, motorRSpeed);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, LOW);
  
  analogWrite(motorLEnable, motorLSpeed);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2, LOW);
  delay(500);
}

void right90(int dlay) 
{
  analogWrite(motorREnable, motorRSpeed+20);
  digitalWrite(motorRPin1, HIGH);
  digitalWrite(motorRPin2, LOW);

  analogWrite(motorLEnable, motorLSpeed-error);
  digitalWrite(motorLPin1, LOW);
  digitalWrite(motorLPin2,HIGH);
  delay(dlay);
} 

void left90(int dlay)
{
  analogWrite(motorREnable, motorRSpeed-error);
  digitalWrite(motorRPin1, LOW);
  digitalWrite(motorRPin2, HIGH);
  
  analogWrite(motorLEnable, motorLSpeed+20);
  digitalWrite(motorLPin1, HIGH);
  digitalWrite(motorLPin2, LOW);
  delay(dlay);
}

void back()
{
  if (back_flag%2==0)
  {
    analogWrite(motorREnable, motorRSpeed);
    digitalWrite(motorRPin1, LOW);
    digitalWrite(motorRPin2, HIGH);
    
    analogWrite(motorLEnable, motorLSpeed);
    digitalWrite(motorLPin1, HIGH);
    digitalWrite(motorLPin2, LOW);
  }
  else
  {
    analogWrite(motorREnable, motorRSpeed);
    digitalWrite(motorRPin1, HIGH);
    digitalWrite(motorRPin2, LOW);
    
    analogWrite(motorLEnable, motorLSpeed);
    digitalWrite(motorLPin1, LOW);
    digitalWrite(motorLPin2, HIGH);
  }
  back_flag++;
  delay(1200);
}