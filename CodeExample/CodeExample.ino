

// another new test, again, 2
// morew demo

#include "pitches.h"
 
int buttonPin = 5;
int speakerPin = 8;

int longPressMs = 1000; //   milliseconds
int delayInt = 10;
int longPressDelays = longPressMs / delayInt;  // 100 loops
int pressCount = 0;
int prevVal = 0;

boolean playing = false;

int currentMelody = 0;
int selectMelody = 0;

int currentNote = 0;
int noteProgress = 0;


int melodyA[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
int noteDurationsA[] = {
  4, 8, 8, 4,4,4,4,4 };

int melodyB[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
int noteDurationsB[] = {
  4, 8, 8, 4,4,4,4,4 };

int melodyC[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
int noteDurationsC[] = {
  4, 8, 8, 4,4,4,4,4 };



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
          return 2; 
        }
        return 0; // it is not yet a long press
      }
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
  Serial.println( pressType );
  
  if( pressType == 1 )   // short press
  {
    shortPress();
  }
  
  if( pressType == 2 )   // long press
  {
    longPress();
  }
  
  if( playing == true )
  {
    // if current song == 0
    // playSong( melodyA, noteDurationsA);
    // else
    // if current song == 1
    // playSong( melodyB, noteDurationsB);
    // else
    // if current song == 2
    // playSong( melodyC, noteDurationsC);
  }
  
  delay(delayInt );
}

void shortPress()
{
  selectMelody = selectMelody + 1;
  selectMelody = selectMelody % 3;
  
  // update LCD
}


void longPress()
{
  // if selectMelody == currentMelody
    // if playing == true
      // pause //
      // playing = false
    // if playing == false
      // start //
      // playing = true

  // if selectMelody != currentMelody
    // start //
    // currentMelody = selectMelody
    // currentNote = 0
    // noteProgress = 0
    // playing = true
    
  // update LCD
}


void playSong( int melody[], int noteDurations[] )
{
  noteProgress = noteProgress + 1;
  
    // to calculate the note duration, take one second 
    // divided by the note type.
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    
  int noteLengthInDelays = ( 1000 / delayInt ) / noteDurations[ currentNote ];
  
  if( noteProgress > noteLengthInDelays )
  {
    // int pauseBetweenNotes = noteDuration * 1.30;
    currentNote = currentNote + 1;
    noteProgress = 0;
  }
  
  if( currentNote > sizeof(melody ) )
  {
    currentNote = 0;
  }
  
  tone( speakerPin , melody[currentNote], delayInt + 1);
}


