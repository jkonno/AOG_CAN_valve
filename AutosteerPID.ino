void calcSteeringPID(void) 
 {  
  //Proportional only
  pValue = steerSettings.Kp * steerAngleError;
  pwmDrive = (int16_t)pValue;
  
  errorAbs = abs(steerAngleError);
  int16_t newMax = 0; 
   
  if (errorAbs < LOW_HIGH_DEGREES)
  {
    newMax = (errorAbs * highLowPerDeg) + steerSettings.lowPWM;
  }
  else newMax = steerSettings.highPWM;
    
  //add min throttle factor so no delay from motor resistance.
  if (pwmDrive < 0 ) pwmDrive -= steerSettings.minPWM;
  else if (pwmDrive > 0 ) pwmDrive += steerSettings.minPWM;
  
  //Serial.print(newMax); //The actual steering angle in degrees
  //Serial.print(",");

  //limit the pwm drive
  if (pwmDrive > newMax) pwmDrive = newMax;
  if (pwmDrive < -newMax) pwmDrive = -newMax;

  //if (errorAbs < 0.3) pwmDrive = 0;

  if (steerConfig.MotorDriveDirection) pwmDrive *= -1;
  
 }

//#########################################################################################

void motorDrive(void) 
  {
    //EDIT FOR CAN VALVE START
    // Used with Isobus message CAN valve
    if (pwmDrive > 0)
    {
      flowCommand.buf[2]=0x01;  //set the correct direction
    }
    else if (pwmDrive < 0) 
    {
      flowCommand.buf[2]=0x02;
      pwmDrive = -pwmDrive;
    } else
    {
      flowCommand.buf[2]=0x00;
      pwmDrive = 0;
    }
    //write out the 0 to 255 value
    flowCommand.buf[0]=(uint8_t)pwmDrive;
    writeToBus(flowCommand);
    pwmDisplay = pwmDrive;
    //EDIT FOR CAN VALVE END
  }
