// ---------------------------------------------------------------------------
// Graveyard Shift
// E minor spooky march: chromatic riff (+5, +7 lifts), offbeat stabs, driving bass, drums with a roll. Tempo 32, loop 512 ticks.
// 250 bytes
// ---------------------------------------------------------------------------
#ifndef MUSIC_H
#define MUSIC_H

#ifndef Song
#define Song const uint8_t PROGMEM
#endif

Song graveyardShift[] = {          // total song in bytes = 250
  0x0D,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  drums (CH3 entry)
  0x09, 0x00,                   // Address of track 1   //9  chromatic riff (CH0)
  0x21, 0x00,                   // Address of track 2   //33  stabs (CH1)
  0x31, 0x00,                   // Address of track 3   //49  driving bass (CH2)
  0x4B, 0x00,                   // Address of track 4   //75  riff, 2 bars
  0x68, 0x00,                   // Address of track 5   //104  stab Em
  0x73, 0x00,                   // Address of track 6   //115  stab Am
  0x7E, 0x00,                   // Address of track 7   //126  stab B
  0x89, 0x00,                   // Address of track 8   //137  bass beat
  0x92, 0x00,                   // Address of track 9   //146  kick + hats
  0xA2, 0x00,                   // Address of track 10   //162  snare + open hat
  0xAD, 0x00,                   // Address of track 11   //173  kick/snare pair
  0xB2, 0x00,                   // Address of track 12   //178  snare roll

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (chords)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (drums)

  //"Track 0" drums (CH3 entry)  [9 bytes]
  ATM_REPEAT(14, 11),   // 15 x pair
  ATM_GOTO(9),   // kickhat
  ATM_GOTO(12),   // roll
  ATM_GOTO(0),   // drums

  //"Track 1" chromatic riff (CH0)  [24 bytes]
  ATM_SET_TEMPO(32),
  ATM_VOL(36),
  ATM_SL_VOL((uint8_t)-3),
  ATM_SET_TRA(0),
  ATM_GOTO(4),   // riff
  ATM_SET_TRA(5),
  ATM_GOTO(4),   // riff
  ATM_SET_TRA(0),
  ATM_GOTO(4),   // riff
  ATM_SET_TRA(7),
  ATM_GOTO(4),   // riff
  ATM_GOTO(1),   // lead

  //"Track 2" stabs (CH1)  [16 bytes]
  ATM_SL_VOL((uint8_t)-2),
  ATM_REPEAT(1, 5),   // 2 x stabEm
  ATM_REPEAT(1, 6),   // 2 x stabAm
  ATM_REPEAT(1, 5),   // 2 x stabEm
  ATM_REPEAT(1, 7),   // 2 x stabB
  ATM_GOTO(2),   // chords

  //"Track 3" driving bass (CH2)  [26 bytes]
  ATM_VOL(56),
  ATM_SL_VOL((uint8_t)-2),
  ATM_SET_TRA(0),
  ATM_REPEAT(3, 8),   // 4 x beat
  ATM_SET_TRA(5),
  ATM_REPEAT(3, 8),   // 4 x beat
  ATM_SET_TRA(0),
  ATM_REPEAT(3, 8),   // 4 x beat
  ATM_SET_TRA(7),
  ATM_REPEAT(3, 8),   // 4 x beat
  ATM_GOTO(3),   // bass

  //"Track 4" riff, 2 bars  [29 bytes]
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_F5_,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_D5_,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(16),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_A4_,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 5" stab Em  [11 bytes]
  ATM_ARP(0x34, 0x20),
  ATM_DELAY(16),
  ATM_VOL(26),
  ATM_NOTE_E4,
  ATM_DELAY(32),
  ATM_NOTE_E4,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 6" stab Am  [11 bytes]
  ATM_ARP(0x34, 0x20),
  ATM_DELAY(16),
  ATM_VOL(26),
  ATM_NOTE_A3,
  ATM_DELAY(32),
  ATM_NOTE_A3,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 7" stab B  [11 bytes]
  ATM_ARP(0x43, 0x20),
  ATM_DELAY(16),
  ATM_VOL(26),
  ATM_NOTE_B3,
  ATM_DELAY(32),
  ATM_NOTE_B3,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 8" bass beat  [9 bytes]
  ATM_NOTE_E2,
  ATM_DELAY(8),
  ATM_NOTE_E2,
  ATM_DELAY(8),
  ATM_NOTE_E3,
  ATM_DELAY(8),
  ATM_NOTE_E2,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 9" kick + hats  [16 bytes]
  ATM_VOL(48),
  ATM_SL_VOL((uint8_t)-12),
  ATM_DELAY(4),
  ATM_VOL(14),
  ATM_SL_VOL((uint8_t)-7),
  ATM_DELAY(4),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-3),
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 10" snare + open hat  [11 bytes]
  ATM_VOL(44),
  ATM_SL_VOL((uint8_t)-5),
  ATM_DELAY(8),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-3),
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 11" kick/snare pair  [5 bytes]
  ATM_GOTO(9),   // kickhat
  ATM_GOTO(10),   // snare
  ATM_RETURN,

  //"Track 12" snare roll  [41 bytes]
  ATM_VOL(22),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(26),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(30),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(34),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(38),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(42),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(46),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(50),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_RETURN,

};

// sound effects, all played on channel 1 ---------------------------------------
ATM_SFX_TRACK(sfxShot,  ATM_VOL(50), ATM_SL_VOL((uint8_t)-3), ATM_SL_FRQ((uint8_t)-80), ATM_NOTE_A5, ATM_DELAY(5));                                // pew
ATM_SFX_TRACK(sfxHit,   ATM_VOL(55), ATM_SL_VOL((uint8_t)-7), ATM_GLIS(0x80), ATM_NOTE_E4, ATM_DELAY(5));                                         // zombie hit
ATM_SFX_TRACK(sfxDie,   ATM_VOL(63), ATM_SL_VOL((uint8_t)-4), ATM_GLIS(0x80), ATM_NOTE_G3, ATM_DELAY(12));                                        // zombie dies
ATM_SFX_TRACK(sfxOuch,  ATM_VOL(50), ATM_SL_VOL((uint8_t)-1), ATM_NOTE_B4, ATM_DELAY(3), ATM_GLIS(0x80), ATM_NOTE_E3, ATM_DELAY(14));          // player hurt
ATM_SFX_TRACK(sfxCoin,  ATM_VOL(45), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_B5, ATM_DELAY(2), ATM_NOTE_E6, ATM_DELAY(8));                              // bonus
ATM_SFX_TRACK(sfxHeart, ATM_VOL(40), ATM_SL_VOL((uint8_t)-1), ATM_NOTE_C5, ATM_DELAY(2), ATM_NOTE_E5, ATM_DELAY(2), ATM_NOTE_G5, ATM_DELAY(2), ATM_NOTE_C6, ATM_DELAY(10)); // heart
ATM_SFX_TRACK(sfxRescue, ATM_VOL(40), ATM_SL_VOL((uint8_t)-1), ATM_NOTE_E5, ATM_DELAY(2), ATM_NOTE_G5, ATM_DELAY(2), ATM_NOTE_E6, ATM_DELAY(2), ATM_NOTE_C6, ATM_DELAY(2), ATM_NOTE_D6, ATM_DELAY(2), ATM_NOTE_G6, ATM_DELAY(10)); // survivor saved

// ATMlib does not look at the Arduboy sound setting, so we do it here
byte musicOn = 0;
byte sfxTimer = 0;

void sfx(const uint8_t *track)
{
  if (!arduboy.audio.enabled()) return;
  ATM.playSfx(track, 1);
  sfxTimer = 45;                                            // frames until the player is switched off again
}

// called once per frame: title music in the menus, silence in the game
void musicUpdate()
{
  if (gameState <= STATE_MENU_SOUNDFX && arduboy.audio.enabled())
  {
    if (!musicOn)
    {
      ATM.play(graveyardShift);
      musicOn = 1;
    }
  }
  else if (musicOn)
  {
    ATM.stop();
    musicOn = 0;
  }
  if (sfxTimer && !--sfxTimer && !musicOn) ATM.stop();      // sfx finished, free the CPU
}

#endif
