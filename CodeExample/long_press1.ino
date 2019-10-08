
int buttonPin = 5;

int longPressMs = 1000; //   milliseconds
int delayInt = 10;
int longPressDelays = longPressMs / delayInt;  // 100 loops
int pressCount = 0;
int prevVal = 0;



void setup()
{
  Serial.begin(9600);
}


int readButtonPress()
{
  // return 0 nothing
  // return 1 short press
  // return 2 long press
  
  int pinValue = digitalRead( buttonPin );  // 1 for pressed, 0 for not pressed...
            
  if( pinValue == 1 )
  {
    if( prevVal == 0 )
    {
      pressCount = 1;  
      prevVal = 1;
      return 0;  // nothing happens until button is released, or counter reaches longPressDelays
    }
    if( prevVal == 1 )
    {
      if( pressCount < longPressDelays )
      {
        pressCount = pressCount + 1;
        if ( pressCount == longPressDelays )
        {
          // button has been pressed for 1000 ms ( 100 10 ms delays )
        //  Serial.println( pressCount );
          return 2; 
        }
      }
      return 0; // it is not yet a long press
    }
  }
  if( pinValue == 0 )
  {
    if( prevVal == 0 )
    {
       return 0;
    }
    if( prevVal == 1 )
    {
      if( pressCount < longPressDelays )
      {
        pressCount = 0;
        prevVal = 0;
        return 1; // short press
      }
      else
      {
        pressCount = 0;
        prevVal = 0;
        return 0; // it was a long press before
      }
    }
  }

//return 0 ;
  }


void loop()
{
  int pressType = readButtonPress();
  // Serial.print( pressType );
  
  if( pressType == 1 )   // short press
  {
    Serial.println( pressType );
    // shortPress();
  }
  
  if( pressType == 2 )   // long press
  {
    Serial.println( pressType );
    // longPress();
  }
  
  pressType = 0;
  delay(delayInt );
}
