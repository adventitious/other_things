
int buttonPin = 5;

int longPressMs = 600; //   milliseconds
int delayInt = 10;
int longPressDelays = longPressMs / delayInt;  // 100 loops
int pressCount = 0;
int prevVal = 0;

int menuInt = 0;      // menu, used for both menus

String melodyNames[] = {"melodyA", "melodyB", "melodyC" };
int currentMelody = 0;  // playing
bool playing = true;
int menuLength = 4; // 3 melody + 1 menu

bool inMenu = false;
String varNames[] = {"varA", "varB", "varC" };
int varValues[] = {0,0,0 };
int subMenuLength = 4;  // 3 vars + 1 exit

void setup()
{
  Serial.begin(9600);
  Serial.println( "system begin" );
  Serial.println( "melody A" );
  Serial.println( "hold to play" );
  Serial.println( "" );
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
          // Serial.println( pressCount );
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
  // return 0 ;
}


void loop()
{
  int pressType = readButtonPress();
  // Serial.print( pressType );
  
  if( pressType == 1 )   // short press
  {
    Serial.println( " short press" );
    shortPress();
  }
  
  if( pressType == 2 )   // long press
  {
    Serial.println( " long press" );
    longPress();
  }
  
  pressType = 0;
  delay(delayInt );
}


void melodyPressed()
{
  if( menuInt == menuLength-1 )
  {
    inMenu = true;
    
    Serial.println( "menu" );
    Serial.println( "menu entered" );
  }
  else
  {
  
    if( playing == true  && menuInt == currentMelody )
    {
      playing = false;
      Serial.println( melodyNames[menuInt] );
      Serial.println( "hold to play" );
    }
    else
    {
      currentMelody = menuInt;
      playing = true;
      Serial.println( melodyNames[menuInt] );
      Serial.println( "hold to pause" );
    }
  }
}

void varPressed()
{

    if( menuInt == subMenuLength-1 )
    {
      inMenu = false;
      Serial.println( "menu" );
      Serial.println( "menu exited" );
    }
  
}

void longPress()
{
  if( inMenu == true )
  {
    varPressed();
  }
  else
  {
    melodyPressed();
  }

  Serial.println( "" );
}


void melodyChoose()
{

  menuInt = menuInt + 1;
  menuInt = menuInt % menuLength;

  if( menuInt == menuLength - 1 )
  {
      Serial.println( "menu" );
      Serial.println( "hold to enter" );
      Serial.println( "" );
    
  }
  else
  {
    if( playing == true  && menuInt == currentMelody )
    {
      Serial.println( melodyNames[menuInt] );
      Serial.println( "hold to pause" );
      Serial.println( "" );
    }
    else
    {
      Serial.println( melodyNames[menuInt] );
      Serial.println( "hold to play" );
      Serial.println( "" );
    }
  }
}

void varChoose()
{
  menuInt = menuInt + 1;
  menuInt = menuInt % menuLength;

  if( menuInt == subMenuLength - 1 )
  {
      Serial.println( "exit" );
      Serial.println( "hold to exit" );
      Serial.println( "" );
  }
  else
  {
      Serial.println( varNames[menuInt] );
      Serial.println( "hold to edit" );
      Serial.println( "" );
  }

  
}

void shortPress()
{
  if( inMenu == false )
  {
    melodyChoose();
  }
  else
  {
    varChoose();
  }
    
  // update LCD
}

