#include <Arduboy2.h>
#include <ArduboyTones.h>

// Include one of the headers for sound effects

// Space Quest 1 sounds
#include "SQ1.h"
// Space Quest 2 sounds
//#include "SQ2.h"
// Wolfenstein 3D sounds
//#include "Wolf3D.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
int playIndex;

void setup() 
{
  arduboy.boot(); 
  arduboy.flashlight();
  arduboy.audio.begin();

  playIndex = 0;
}

void loop() 
{
  if(arduboy.nextFrame())
  {
    arduboy.clear();
    arduboy.print("Current audio:");
    arduboy.print(playIndex);
    arduboy.print("\n");
    arduboy.print("\nLeft/Right: Select\nA:Play");
    if(arduboy.pressed(RIGHT_BUTTON))
    {
      playIndex++;
      if(playIndex >= NUM_AUDIO_PATTERNS)
      {
        playIndex = 0;
      }
    }
    if(arduboy.pressed(LEFT_BUTTON))
    {
      playIndex--;
      if(playIndex < 0)
      {
        playIndex = NUM_AUDIO_PATTERNS - 1;
      }
    }
    if(arduboy.pressed(A_BUTTON) || arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON))
    {
      sound.tones((uint16_t*)pgm_read_ptr(&Data_AudioPatterns[playIndex]));
      do 
      {
        delay(50);
      } while (arduboy.buttonsState());
    }
    arduboy.display(true);
  }
}

