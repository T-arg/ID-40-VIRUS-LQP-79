#ifndef MUSIC_H
#define MUSIC_H

// All music for Virus LQP-79 (ATMlib).
//   graveyardShift                title screen / menus, full volume
//   tuneBat ... tuneBrew      in-game, one per level in this order, then it starts over, at 60 % volume

#ifndef Song
#define Song const uint8_t PROGMEM
#endif

#define MUSIC_VOL_PCT 60
#define MV(v) ((v) * MUSIC_VOL_PCT / 100)
#define MS(n) ((uint8_t)-((((n) * MUSIC_VOL_PCT + 50) / 100) < 1 ? 1 : (((n) * MUSIC_VOL_PCT + 50) / 100)))

// ---------------------------------------------------------------------------
// Graveyard Shift
// E minor spooky march: chromatic riff (+5, +7 lifts), offbeat stabs, driving bass, drums with a roll. Tempo 32, loop 512 ticks.
// 250 bytes
// ---------------------------------------------------------------------------
Song graveyardShift[] = {          // total song in bytes = 229
  0x0D,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  drums (CH3 entry)
  0x09, 0x00,                   // Address of track 1   //9  chromatic riff (CH0)
  0x21, 0x00,                   // Address of track 2   //33  stabs (CH1)
  0x31, 0x00,                   // Address of track 3   //49  driving bass (CH2)
  0x4B, 0x00,                   // Address of track 4   //75  riff, 2 bars
  0x68, 0x00,                   // Address of track 5   //104  stab Em
  0x73, 0x00,                   // Address of track 6   //115  stab Am
  0x79, 0x00,                   // Address of track 7   //121  stab B
  0x82, 0x00,                   // Address of track 8   //130  bass beat
  0x8B, 0x00,                   // Address of track 9   //139  kick + hats
  0x9B, 0x00,                   // Address of track 10   //155  snare + open hat
  0xA6, 0x00,                   // Address of track 11   //166  kick/snare pair
  0xAB, 0x00,                   // Address of track 12   //171  snare roll

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

  //"Track 6" stab Am  [6 bytes]
  ATM_DELAY(16),
  ATM_NOTE_A3,
  ATM_DELAY(32),
  ATM_NOTE_A3,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 7" stab B  [9 bytes]
  ATM_ARP(0x43, 0x20),
  ATM_DELAY(16),
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

  //"Track 12" snare roll  [27 bytes]
  ATM_VOL(22),
  ATM_SL_VOL((uint8_t)-9),
  ATM_DELAY(2),
  ATM_VOL(26),
  ATM_DELAY(2),
  ATM_VOL(30),
  ATM_DELAY(2),
  ATM_VOL(34),
  ATM_DELAY(2),
  ATM_VOL(38),
  ATM_DELAY(2),
  ATM_VOL(42),
  ATM_DELAY(2),
  ATM_VOL(46),
  ATM_DELAY(2),
  ATM_VOL(50),
  ATM_DELAY(2),
  ATM_RETURN,

};

// ---------------------------------------------------------------------------
// Bat Chase
// D minor chase: jumpy riff, echo a beat later, octave-pumping bass, drums. Tempo 40, loop 512 ticks.
// 222 bytes
// ---------------------------------------------------------------------------
Song tuneBat[] = {          // total song in bytes = 220
  0x0C,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  drums (CH3 entry)
  0x05, 0x00,                   // Address of track 1   //5  jumpy riff (CH0)
  0x27, 0x00,                   // Address of track 2   //39  echo one beat later (CH1)
  0x45, 0x00,                   // Address of track 3   //69  driving octave bass (CH2)
  0x65, 0x00,                   // Address of track 4   //101  riff notes, 48 ticks
  0x78, 0x00,                   // Address of track 5   //120  riff variation, 48 ticks
  0x8B, 0x00,                   // Address of track 6   //139  riff bar
  0x8F, 0x00,                   // Address of track 7   //143  echo bar
  0x95, 0x00,                   // Address of track 8   //149  variation bar
  0x99, 0x00,                   // Address of track 9   //153  variation echo bar
  0x9D, 0x00,                   // Address of track 10   //157  octave ostinato bar
  0xAE, 0x00,                   // Address of track 11   //174  kick/snare pair

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (echo)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (drums)

  //"Track 0" drums (CH3 entry)  [5 bytes]
  ATM_REPEAT(15, 11),   // 16 x pair
  ATM_GOTO(0),   // drums

  //"Track 1" jumpy riff (CH0)  [34 bytes]
  ATM_SET_TEMPO(40),
  ATM_VOL(MV(36)),
  ATM_SL_VOL(MS(1)),
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 6),   // 2 x barL
  ATM_SET_TRA((uint8_t)-4),
  ATM_GOTO(6),   // barL
  ATM_SET_TRA((uint8_t)-5),
  ATM_GOTO(6),   // barL
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 8),   // 2 x barL2
  ATM_SET_TRA(5),
  ATM_GOTO(8),   // barL2
  ATM_SET_TRA((uint8_t)-5),
  ATM_GOTO(8),   // barL2
  ATM_GOTO(1),   // lead

  //"Track 2" echo one beat later (CH1)  [30 bytes]
  ATM_SL_VOL(MS(1)),
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 7),   // 2 x barE
  ATM_SET_TRA((uint8_t)-4),
  ATM_GOTO(7),   // barE
  ATM_SET_TRA((uint8_t)-5),
  ATM_GOTO(7),   // barE
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 9),   // 2 x barE2
  ATM_SET_TRA(5),
  ATM_GOTO(9),   // barE2
  ATM_SET_TRA((uint8_t)-5),
  ATM_GOTO(9),   // barE2
  ATM_GOTO(2),   // echo

  //"Track 3" driving octave bass (CH2)  [32 bytes]
  ATM_VOL(MV(54)),
  ATM_SL_VOL(MS(1)),
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 10),   // 2 x ost
  ATM_SET_TRA((uint8_t)-4),
  ATM_GOTO(10),   // ost
  ATM_SET_TRA((uint8_t)-5),
  ATM_GOTO(10),   // ost
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 10),   // 2 x ost
  ATM_SET_TRA(5),
  ATM_GOTO(10),   // ost
  ATM_SET_TRA((uint8_t)-5),
  ATM_GOTO(10),   // ost
  ATM_GOTO(3),   // bass

  //"Track 4" riff notes, 48 ticks  [19 bytes]
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_F5,
  ATM_DELAY(4),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(4),
  ATM_NOTE_F5,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_F5,
  ATM_DELAY(4),
  ATM_NOTE_A5_,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 5" riff variation, 48 ticks  [19 bytes]
  ATM_NOTE_A5,
  ATM_DELAY(4),
  ATM_NOTE_G5,
  ATM_DELAY(4),
  ATM_NOTE_F5,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(4),
  ATM_NOTE_C6_,
  ATM_DELAY(4),
  ATM_NOTE_D6,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 6" riff bar  [4 bytes]
  ATM_GOTO(4),   // notes
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 7" echo bar  [6 bytes]
  ATM_DELAY(16),
  ATM_VOL(MV(20)),
  ATM_GOTO(4),   // notes
  ATM_RETURN,

  //"Track 8" variation bar  [4 bytes]
  ATM_GOTO(5),   // notesB
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 9" variation echo bar  [4 bytes]
  ATM_DELAY(16),
  ATM_GOTO(5),   // notesB
  ATM_RETURN,

  //"Track 10" octave ostinato bar  [17 bytes]
  ATM_NOTE_D3,
  ATM_DELAY(8),
  ATM_NOTE_D4,
  ATM_DELAY(8),
  ATM_NOTE_D3,
  ATM_DELAY(8),
  ATM_NOTE_D4,
  ATM_DELAY(8),
  ATM_NOTE_D3,
  ATM_DELAY(8),
  ATM_NOTE_D4,
  ATM_DELAY(8),
  ATM_NOTE_A3,
  ATM_DELAY(8),
  ATM_NOTE_D4,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 11" kick/snare pair  [17 bytes]
  ATM_VOL(MV(44)),
  ATM_SL_VOL(MS(12)),
  ATM_DELAY(8),
  ATM_VOL(MV(12)),
  ATM_DELAY(8),
  ATM_VOL(MV(40)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(8),
  ATM_VOL(MV(12)),
  ATM_DELAY(8),
  ATM_RETURN,

};

// ---------------------------------------------------------------------------
// Haunted Hallway
// Slow creeping E phrygian: heartbeat, vibrato ghost lead, tritone bass (A#). Tempo 24, loop 512 ticks.
// 160 bytes
// ---------------------------------------------------------------------------
Song tuneHallway[] = {          // total song in bytes = 160
  0x06,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  heartbeat (CH3 entry)
  0x09, 0x00,                   // Address of track 1   //9  ghost lead (CH0)
  0x3C, 0x00,                   // Address of track 2   //60  dim/min pad (CH1)
  0x62, 0x00,                   // Address of track 3   //98  creeping bass (CH2)
  0x78, 0x00,                   // Address of track 4   //120  lub-dub
  0x7F, 0x00,                   // Address of track 5   //127  lub-dub + knock

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (pad)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (heart)

  //"Track 0" heartbeat (CH3 entry)  [9 bytes]
  ATM_SL_VOL(MS(6)),
  ATM_REPEAT(14, 4),   // 15 x hb
  ATM_GOTO(5),   // hbend
  ATM_GOTO(0),   // heart

  //"Track 1" ghost lead (CH0)  [51 bytes]
  ATM_SET_TEMPO(24),
  ATM_VOL(MV(34)),
  ATM_SL_VOL(MS(1)),
  ATM_VIB(3, 7),
  ATM_NOTE_B4,
  ATM_DELAY(32),
  ATM_NOTE_C5,
  ATM_DELAY(16),
  ATM_NOTE_B4,
  ATM_DELAY(16),
  ATM_NOTE_G4,
  ATM_DELAY(32),
  ATM_NOTE_F4_,
  ATM_DELAY(32),
  ATM_NOTE_A4,
  ATM_DELAY(32),
  ATM_NOTE_C5,
  ATM_DELAY(16),
  ATM_NOTE_A4,
  ATM_DELAY(16),
  ATM_NOTE_F5,
  ATM_DELAY(32),
  ATM_NOTE_E5,
  ATM_DELAY(32),
  ATM_NOTE_B4,
  ATM_DELAY(32),
  ATM_NOTE_E5,
  ATM_DELAY(32),
  ATM_NOTE_B4,
  ATM_DELAY(16),
  ATM_NOTE_C5,
  ATM_DELAY(16),
  ATM_NOTE_B4,
  ATM_DELAY(32),
  ATM_NOTE_F5,
  ATM_DELAY(32),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_NOTE_D5_,
  ATM_DELAY(16),
  ATM_NOTE_D5_,
  ATM_DELAY(48),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_GOTO(1),   // lead

  //"Track 2" dim/min pad (CH1)  [38 bytes]
  ATM_VOL(MV(22)),
  ATM_TREM(1, 7),
  ATM_ARP(0x34, 0x23),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_ARP(0x43, 0x23),
  ATM_NOTE_F4,
  ATM_DELAY(64),
  ATM_NOTE_F4,
  ATM_DELAY(64),
  ATM_ARP(0x34, 0x23),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_ARP(0x33, 0x23),
  ATM_NOTE_A3_,
  ATM_DELAY(64),
  ATM_ARP(0x43, 0x23),
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_GOTO(2),   // pad

  //"Track 3" creeping bass (CH2)  [22 bytes]
  ATM_VOL(MV(50)),
  ATM_SL_VOL(MS(1)),
  ATM_NOTE_E2,
  ATM_DELAY(64),
  ATM_NOTE_E2,
  ATM_DELAY(64),
  ATM_NOTE_F2,
  ATM_DELAY(64),
  ATM_NOTE_F2,
  ATM_DELAY(64),
  ATM_NOTE_E2,
  ATM_DELAY(64),
  ATM_NOTE_E2,
  ATM_DELAY(64),
  ATM_NOTE_A2_,
  ATM_DELAY(64),
  ATM_NOTE_B2,
  ATM_DELAY(64),
  ATM_GOTO(3),   // bass

  //"Track 4" lub-dub  [7 bytes]
  ATM_VOL(MV(44)),
  ATM_DELAY(6),
  ATM_VOL(MV(36)),
  ATM_DELAY(26),
  ATM_RETURN,

  //"Track 5" lub-dub + knock  [16 bytes]
  ATM_VOL(MV(44)),
  ATM_DELAY(6),
  ATM_VOL(MV(36)),
  ATM_DELAY(10),
  ATM_VOL(MV(46)),
  ATM_DELAY(4),
  ATM_VOL(MV(46)),
  ATM_DELAY(4),
  ATM_VOL(MV(30)),
  ATM_DELAY(8),
  ATM_RETURN,

};

// ---------------------------------------------------------------------------
// Pumpkin Patch
// C minor jaunty creepy-fun: vibrato hook, walking bass, fast-arp organ chops on the off-beat. Tempo 34, loop 512 ticks.
// 260 bytes
// ---------------------------------------------------------------------------
Song tunePumpkin[] = {          // total song in bytes = 251
  0x0C,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  drums (CH3 entry)
  0x05, 0x00,                   // Address of track 1   //5  cheeky hook (CH0)
  0x61, 0x00,                   // Address of track 2   //97  organ chops (CH1)
  0x86, 0x00,                   // Address of track 3   //134  walking bass (CH2)
  0xA3, 0x00,                   // Address of track 4   //163  minor walking bar
  0xAC, 0x00,                   // Address of track 5   //172  dominant walking bar
  0xB5, 0x00,                   // Address of track 6   //181  chop Cm
  0xBB, 0x00,                   // Address of track 7   //187  chop Fm
  0xBF, 0x00,                   // Address of track 8   //191  chop Ab
  0xC3, 0x00,                   // Address of track 9   //195  chop G
  0xC7, 0x00,                   // Address of track 10   //199  kick/snare pair
  0xD8, 0x00,                   // Address of track 11   //216  shared 0

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (organ)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (drums)

  //"Track 0" drums (CH3 entry)  [5 bytes]
  ATM_REPEAT(15, 10),   // 16 x pair
  ATM_GOTO(0),   // drums

  //"Track 1" cheeky hook (CH0)  [92 bytes]
  ATM_SET_TEMPO(34),
  ATM_VOL(MV(34)),
  ATM_SL_VOL(MS(1)),
  ATM_VIB(2, 3),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_D5_,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(16),
  ATM_NOTE_F5,
  ATM_GOTO(11),   // shared 0
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_D5_,
  ATM_DELAY(8),
  ATM_NOTE_F5,
  ATM_DELAY(16),
  ATM_NOTE_D5_,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(16),
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_G5_,
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(16),
  ATM_NOTE_A5_,
  ATM_DELAY(8),
  ATM_NOTE_G5_,
  ATM_DELAY(8),
  ATM_NOTE_F5,
  ATM_DELAY(16),
  ATM_NOTE_G5,
  ATM_GOTO(11),   // shared 0
  ATM_NOTE_D5_,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(16),
  ATM_NOTE_C5,
  ATM_DELAY(8),
  ATM_NOTE_D5_,
  ATM_DELAY(8),
  ATM_NOTE_G5_,
  ATM_DELAY(16),
  ATM_NOTE_G5,
  ATM_GOTO(11),   // shared 0
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_F5,
  ATM_DELAY(16),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_G4,
  ATM_DELAY(16),
  ATM_NOTE_D5_,
  ATM_DELAY(16),
  ATM_NOTE_G5,
  ATM_DELAY(16),
  ATM_NOTE_C6,
  ATM_DELAY(16),
  ATM_NOTE_G5,
  ATM_DELAY(16),
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_NOTE_B4,
  ATM_DELAY(8),
  ATM_NOTE_G4,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(32),
  ATM_GOTO(1),   // lead

  //"Track 2" organ chops (CH1)  [37 bytes]
  ATM_SL_VOL(MS(2)),
  ATM_ARP(0x34, 0x20),
  ATM_REPEAT(7, 6),   // 8 x chopCm
  ATM_REPEAT(3, 7),   // 4 x chopFm
  ATM_REPEAT(3, 6),   // 4 x chopCm
  ATM_ARP(0x43, 0x20),
  ATM_REPEAT(3, 8),   // 4 x chopAb
  ATM_REPEAT(3, 9),   // 4 x chopG
  ATM_ARP(0x34, 0x20),
  ATM_REPEAT(3, 6),   // 4 x chopCm
  ATM_ARP(0x43, 0x20),
  ATM_REPEAT(3, 9),   // 4 x chopG
  ATM_GOTO(2),   // organ

  //"Track 3" walking bass (CH2)  [29 bytes]
  ATM_VOL(MV(60)),
  ATM_SL_VOL(MS(2)),
  ATM_REPEAT(1, 4),   // 2 x bar
  ATM_SET_TRA(5),
  ATM_GOTO(4),   // bar
  ATM_SET_TRA(0),
  ATM_GOTO(4),   // bar
  ATM_SET_TRA(8),
  ATM_GOTO(4),   // bar
  ATM_SET_TRA(0),
  ATM_GOTO(5),   // dom
  ATM_GOTO(4),   // bar
  ATM_GOTO(5),   // dom
  ATM_GOTO(3),   // bass

  //"Track 4" minor walking bar  [9 bytes]
  ATM_NOTE_C3,
  ATM_DELAY(16),
  ATM_NOTE_D3_,
  ATM_DELAY(16),
  ATM_NOTE_G3,
  ATM_DELAY(16),
  ATM_NOTE_D3_,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 5" dominant walking bar  [9 bytes]
  ATM_NOTE_G2,
  ATM_DELAY(16),
  ATM_NOTE_B2,
  ATM_DELAY(16),
  ATM_NOTE_D3,
  ATM_DELAY(16),
  ATM_NOTE_B2,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 6" chop Cm  [6 bytes]
  ATM_DELAY(8),
  ATM_VOL(MV(24)),
  ATM_NOTE_C4,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 7" chop Fm  [4 bytes]
  ATM_DELAY(8),
  ATM_NOTE_F4,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 8" chop Ab  [4 bytes]
  ATM_DELAY(8),
  ATM_NOTE_G3_,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 9" chop G  [4 bytes]
  ATM_DELAY(8),
  ATM_NOTE_G3,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 10" kick/snare pair  [17 bytes]
  ATM_VOL(MV(44)),
  ATM_SL_VOL(MS(12)),
  ATM_DELAY(8),
  ATM_VOL(MV(12)),
  ATM_DELAY(8),
  ATM_VOL(MV(40)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(8),
  ATM_VOL(MV(12)),
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 11" shared 0  [6 bytes]
  ATM_DELAY(8),
  ATM_NOTE_D5_,
  ATM_DELAY(8),
  ATM_NOTE_C5,
  ATM_DELAY(16),
  ATM_RETURN,

};

// ---------------------------------------------------------------------------
// Crypt Waltz
// Haunted waltz in A harmonic minor, 3/4, 16 bars. Bells + oom-pah-pah + clock ticks. Tempo 24, loop 576 ticks.
// 244 bytes
// ---------------------------------------------------------------------------
Song tuneCrypt[] = {          // total song in bytes = 237
  0x0B,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  clock ticks (CH3 entry)
  0x07, 0x00,                   // Address of track 1   //7  bell melody (CH0)
  0x73, 0x00,                   // Address of track 2   //115  chord stabs (CH1)
  0x7A, 0x00,                   // Address of track 3   //122  oom bass (CH2)
  0x83, 0x00,                   // Address of track 4   //131  pah-pah Am
  0x8E, 0x00,                   // Address of track 5   //142  pah-pah Dm
  0x94, 0x00,                   // Address of track 6   //148  pah-pah E/G#
  0x9D, 0x00,                   // Address of track 7   //157  chords, 8 bars
  0xAC, 0x00,                   // Address of track 8   //172  bass bar
  0xAF, 0x00,                   // Address of track 9   //175  bass, 8 bars
  0xCA, 0x00,                   // Address of track 10   //202  soft tick-tock bar

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (chords)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (noise)

  //"Track 0" clock ticks (CH3 entry)  [7 bytes]
  ATM_SL_VOL(MS(4)),
  ATM_REPEAT(15, 10),   // 16 x tick
  ATM_GOTO(0),   // noise

  //"Track 1" bell melody (CH0)  [108 bytes]
  ATM_SET_TEMPO(24),
  ATM_VOL(MV(34)),
  ATM_SL_VOL(MS(1)),
  ATM_VIB_OFF,
  ATM_NOTE_E5,
  ATM_DELAY(18),
  ATM_NOTE_F5,
  ATM_DELAY(6),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_B4,
  ATM_DELAY(12),
  ATM_NOTE_F5,
  ATM_DELAY(18),
  ATM_NOTE_E5,
  ATM_DELAY(6),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_B4,
  ATM_DELAY(12),
  ATM_NOTE_A4,
  ATM_DELAY(12),
  ATM_NOTE_G4_,
  ATM_DELAY(12),
  ATM_NOTE_B4,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(18),
  ATM_NOTE_C5,
  ATM_DELAY(6),
  ATM_NOTE_B4,
  ATM_DELAY(12),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_G5_,
  ATM_DELAY(18),
  ATM_NOTE_F5,
  ATM_DELAY(6),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_VIB(2, 3),
  ATM_NOTE_A5,
  ATM_DELAY(18),
  ATM_NOTE_G5_,
  ATM_DELAY(6),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_C6,
  ATM_DELAY(12),
  ATM_NOTE_B5,
  ATM_DELAY(12),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_D6,
  ATM_DELAY(18),
  ATM_NOTE_C6,
  ATM_DELAY(6),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_A5,
  ATM_DELAY(12),
  ATM_NOTE_F5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_G5_,
  ATM_DELAY(12),
  ATM_NOTE_B5,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_F5,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_NOTE_B4,
  ATM_DELAY(12),
  ATM_NOTE_C5,
  ATM_DELAY(12),
  ATM_NOTE_A4,
  ATM_DELAY(12),
  ATM_NOTE_E5,
  ATM_DELAY(12),
  ATM_NOTE_G4_,
  ATM_DELAY(12),
  ATM_NOTE_B4,
  ATM_DELAY(12),
  ATM_NOTE_D5,
  ATM_DELAY(12),
  ATM_GOTO(1),   // lead

  //"Track 2" chord stabs (CH1)  [7 bytes]
  ATM_SL_VOL(MS(2)),
  ATM_REPEAT(1, 7),   // 2 x chords8
  ATM_GOTO(2),   // chords

  //"Track 3" oom bass (CH2)  [9 bytes]
  ATM_VOL(MV(60)),
  ATM_SL_VOL(MS(5)),
  ATM_REPEAT(1, 9),   // 2 x bass8
  ATM_GOTO(3),   // bass

  //"Track 4" pah-pah Am  [11 bytes]
  ATM_ARP(0x34, 0x20),
  ATM_DELAY(12),
  ATM_VOL(MV(26)),
  ATM_NOTE_A3,
  ATM_DELAY(12),
  ATM_NOTE_A3,
  ATM_DELAY(12),
  ATM_RETURN,

  //"Track 5" pah-pah Dm  [6 bytes]
  ATM_DELAY(12),
  ATM_NOTE_D4,
  ATM_DELAY(12),
  ATM_NOTE_D4,
  ATM_DELAY(12),
  ATM_RETURN,

  //"Track 6" pah-pah E/G#  [9 bytes]
  ATM_ARP(0x35, 0x20),
  ATM_DELAY(12),
  ATM_NOTE_G3_,
  ATM_DELAY(12),
  ATM_NOTE_G3_,
  ATM_DELAY(12),
  ATM_RETURN,

  //"Track 7" chords, 8 bars  [15 bytes]
  ATM_REPEAT(1, 4),   // 2 x pahAm
  ATM_GOTO(5),   // pahDm
  ATM_GOTO(4),   // pahAm
  ATM_REPEAT(1, 6),   // 2 x pahE
  ATM_GOTO(4),   // pahAm
  ATM_GOTO(6),   // pahE
  ATM_RETURN,

  //"Track 8" bass bar  [3 bytes]
  ATM_NOTE_A2,
  ATM_DELAY(36),
  ATM_RETURN,

  //"Track 9" bass, 8 bars  [27 bytes]
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 8),   // 2 x bassbar
  ATM_SET_TRA(5),
  ATM_GOTO(8),   // bassbar
  ATM_SET_TRA(0),
  ATM_GOTO(8),   // bassbar
  ATM_SET_TRA(7),
  ATM_REPEAT(1, 8),   // 2 x bassbar
  ATM_SET_TRA(0),
  ATM_GOTO(8),   // bassbar
  ATM_SET_TRA(7),
  ATM_GOTO(8),   // bassbar
  ATM_RETURN,

  //"Track 10" soft tick-tock bar  [8 bytes]
  ATM_DELAY(12),
  ATM_VOL(MV(14)),
  ATM_DELAY(12),
  ATM_VOL(MV(14)),
  ATM_DELAY(12),
  ATM_RETURN,

};

// ---------------------------------------------------------------------------
// Seance
// A minor music box with a creeping A# twist, tolling bass, dim pad, wind swells. Tempo 22, loop 512 ticks.
// 240 bytes
// ---------------------------------------------------------------------------
Song tuneSeance[] = {          // total song in bytes = 222
  0x10,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  wind (CH3 entry)
  0x05, 0x00,                   // Address of track 1   //5  music box (CH0)
  0x1D, 0x00,                   // Address of track 2   //29  dim/min pad (CH1)
  0x25, 0x00,                   // Address of track 3   //37  tolling bass (CH2)
  0x37, 0x00,                   // Address of track 4   //55  wind swell
  0x40, 0x00,                   // Address of track 5   //64  box bar 1
  0x49, 0x00,                   // Address of track 6   //73  box bar 2
  0x56, 0x00,                   // Address of track 7   //86  box bar 3
  0x63, 0x00,                   // Address of track 8   //99  box bar 4
  0x6C, 0x00,                   // Address of track 9   //108  box bar 5
  0x77, 0x00,                   // Address of track 10   //119  box bar 6
  0x84, 0x00,                   // Address of track 11   //132  box bar 7 (A# twist)
  0x91, 0x00,                   // Address of track 12   //145  box bar 8 (falling run)
  0x9C, 0x00,                   // Address of track 13   //156  toll
  0xA1, 0x00,                   // Address of track 14   //161  shared 0
  0xB2, 0x00,                   // Address of track 15   //178  shared 1

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (pad)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (wind)

  //"Track 0" wind (CH3 entry)  [5 bytes]
  ATM_REPEAT(3, 4),   // 4 x wh
  ATM_GOTO(0),   // wind

  //"Track 1" music box (CH0)  [24 bytes]
  ATM_SET_TEMPO(22),
  ATM_VOL(MV(34)),
  ATM_SL_VOL(MS(2)),
  ATM_GOTO(5),   // b1
  ATM_GOTO(6),   // b2
  ATM_GOTO(7),   // b3
  ATM_GOTO(8),   // b4
  ATM_GOTO(9),   // b5
  ATM_GOTO(10),   // b6
  ATM_GOTO(11),   // b7
  ATM_GOTO(12),   // b8
  ATM_GOTO(1),   // lead

  //"Track 2" dim/min pad (CH1)  [8 bytes]
  ATM_VOL(MV(18)),
  ATM_GOTO(14),   // shared 0
  ATM_GOTO(14),   // shared 0
  ATM_GOTO(2),   // pad

  //"Track 3" tolling bass (CH2)  [18 bytes]
  ATM_SL_VOL(MS(1)),
  ATM_REPEAT(1, 13),   // 2 x toll
  ATM_GOTO(13),   // toll
  ATM_GOTO(13),   // toll
  ATM_REPEAT(1, 13),   // 2 x toll
  ATM_GOTO(13),   // toll
  ATM_GOTO(13),   // toll
  ATM_GOTO(3),   // bass

  //"Track 4" wind swell  [9 bytes]
  ATM_SL_VOL(1),
  ATM_DELAY(20),
  ATM_SL_VOL(MS(1)),
  ATM_DELAY(20),
  ATM_DELAY(64),
  ATM_DELAY(24),
  ATM_RETURN,

  //"Track 5" box bar 1  [9 bytes]
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_GOTO(15),   // shared 1
  ATM_DELAY(16),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 6" box bar 2  [13 bytes]
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_D6,
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(8),
  ATM_NOTE_B5,
  ATM_DELAY(16),
  ATM_NOTE_G5_,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 7" box bar 3  [13 bytes]
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(8),
  ATM_NOTE_E6,
  ATM_DELAY(8),
  ATM_NOTE_D6,
  ATM_DELAY(16),
  ATM_NOTE_C6,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 8" box bar 4  [9 bytes]
  ATM_NOTE_D6,
  ATM_GOTO(15),   // shared 1
  ATM_DELAY(8),
  ATM_NOTE_G5_,
  ATM_DELAY(16),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 9" box bar 5  [11 bytes]
  ATM_NOTE_E5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_GOTO(15),   // shared 1
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(8),
  ATM_NOTE_E6,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 10" box bar 6  [13 bytes]
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_DELAY(8),
  ATM_NOTE_D6,
  ATM_DELAY(8),
  ATM_NOTE_F6,
  ATM_DELAY(8),
  ATM_NOTE_E6,
  ATM_DELAY(16),
  ATM_NOTE_C6,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 11" box bar 7 (A# twist)  [13 bytes]
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_A5_,
  ATM_DELAY(8),
  ATM_NOTE_D6,
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(8),
  ATM_NOTE_A5_,
  ATM_DELAY(16),
  ATM_NOTE_G5_,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 12" box bar 8 (falling run)  [11 bytes]
  ATM_NOTE_D6,
  ATM_GOTO(15),   // shared 1
  ATM_DELAY(8),
  ATM_NOTE_G5_,
  ATM_DELAY(8),
  ATM_NOTE_F5,
  ATM_DELAY(8),
  ATM_NOTE_E5,
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 13" toll  [5 bytes]
  ATM_VOL(MV(56)),
  ATM_NOTE_A2,
  ATM_DELAY(64),
  ATM_RETURN,

  //"Track 14" shared 0  [17 bytes]
  ATM_ARP(0x34, 0x23),
  ATM_NOTE_A3,
  ATM_DELAY(64),
  ATM_DELAY(64),
  ATM_ARP(0x33, 0x23),
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_ARP(0x43, 0x23),
  ATM_NOTE_E3,
  ATM_DELAY(64),
  ATM_RETURN,

  //"Track 15" shared 1  [7 bytes]
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(8),
  ATM_NOTE_B5,
  ATM_DELAY(8),
  ATM_NOTE_A5,
  ATM_RETURN,

};

// ---------------------------------------------------------------------------
// Dark Cathedral
// B minor gothic organ: falling and rising toccata runs, arp organ chords, pedal bass, timpani. Tempo 26, loop 512 ticks.
// 211 bytes
// ---------------------------------------------------------------------------
Song tuneCathedral[] = {          // total song in bytes = 187
  0x0A,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  timpani (CH3 entry)
  0x07, 0x00,                   // Address of track 1   //7  toccata runs (CH0)
  0x2B, 0x00,                   // Address of track 2   //43  arp organ chords (CH1)
  0x3A, 0x00,                   // Address of track 3   //58  octave pedal bass (CH2)
  0x4C, 0x00,                   // Address of track 4   //76  falling run
  0x5D, 0x00,                   // Address of track 5   //93  rising run
  0x6E, 0x00,                   // Address of track 6   //110  timpani bar
  0x79, 0x00,                   // Address of track 7   //121  timpani roll
  0x88, 0x00,                   // Address of track 8   //136  shared 0
  0x95, 0x00,                   // Address of track 9   //149  shared 1

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (organ)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (drums)

  //"Track 0" timpani (CH3 entry)  [7 bytes]
  ATM_REPEAT(6, 6),   // 7 x tim
  ATM_GOTO(7),   // fill
  ATM_GOTO(0),   // drums

  //"Track 1" toccata runs (CH0)  [36 bytes]
  ATM_SET_TEMPO(26),
  ATM_VOL(MV(36)),
  ATM_SL_VOL(MS(1)),
  ATM_GOTO(4),   // down
  ATM_GOTO(5),   // up
  ATM_SET_TRA(5),
  ATM_GOTO(4),   // down
  ATM_SET_TRA(6),
  ATM_GOTO(4),   // down
  ATM_SET_TRA(0),
  ATM_GOTO(5),   // up
  ATM_SET_TRA(5),
  ATM_GOTO(5),   // up
  ATM_SET_TRA(6),
  ATM_GOTO(4),   // down
  ATM_SET_TRA(0),
  ATM_GOTO(4),   // down
  ATM_GOTO(1),   // lead

  //"Track 2" arp organ chords (CH1)  [15 bytes]
  ATM_VOL(MV(22)),
  ATM_ARP(0x34, 0x20),
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_GOTO(8),   // shared 0
  ATM_GOTO(8),   // shared 0
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_GOTO(2),   // organ

  //"Track 3" octave pedal bass (CH2)  [18 bytes]
  ATM_VOL(MV(60)),
  ATM_SL_VOL(MS(1)),
  ATM_NOTE_B2,
  ATM_DELAY(32),
  ATM_NOTE_B3,
  ATM_GOTO(9),   // shared 1
  ATM_GOTO(9),   // shared 1
  ATM_DELAY(32),
  ATM_NOTE_B2,
  ATM_DELAY(32),
  ATM_NOTE_B3,
  ATM_DELAY(32),
  ATM_GOTO(3),   // bass

  //"Track 4" falling run  [17 bytes]
  ATM_NOTE_B5,
  ATM_DELAY(4),
  ATM_NOTE_A5,
  ATM_DELAY(4),
  ATM_NOTE_G5,
  ATM_DELAY(4),
  ATM_NOTE_F5_,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_C5_,
  ATM_DELAY(4),
  ATM_NOTE_B4,
  ATM_DELAY(36),
  ATM_RETURN,

  //"Track 5" rising run  [17 bytes]
  ATM_NOTE_B4,
  ATM_DELAY(4),
  ATM_NOTE_C5_,
  ATM_DELAY(4),
  ATM_NOTE_D5,
  ATM_DELAY(4),
  ATM_NOTE_E5,
  ATM_DELAY(4),
  ATM_NOTE_F5_,
  ATM_DELAY(4),
  ATM_NOTE_G5,
  ATM_DELAY(4),
  ATM_NOTE_A5,
  ATM_DELAY(4),
  ATM_NOTE_B5,
  ATM_DELAY(36),
  ATM_RETURN,

  //"Track 6" timpani bar  [11 bytes]
  ATM_VOL(MV(50)),
  ATM_SL_VOL(MS(6)),
  ATM_DELAY(32),
  ATM_VOL(MV(26)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(32),
  ATM_RETURN,

  //"Track 7" timpani roll  [15 bytes]
  ATM_VOL(MV(34)),
  ATM_SL_VOL(MS(9)),
  ATM_DELAY(16),
  ATM_VOL(MV(40)),
  ATM_DELAY(16),
  ATM_VOL(MV(46)),
  ATM_DELAY(16),
  ATM_VOL(MV(52)),
  ATM_DELAY(16),
  ATM_RETURN,

  //"Track 8" shared 0  [13 bytes]
  ATM_NOTE_B3,
  ATM_DELAY(64),
  ATM_NOTE_E4,
  ATM_DELAY(64),
  ATM_ARP(0x43, 0x20),
  ATM_NOTE_F4_,
  ATM_DELAY(64),
  ATM_ARP(0x34, 0x20),
  ATM_RETURN,

  //"Track 9" shared 1  [13 bytes]
  ATM_DELAY(32),
  ATM_NOTE_B2,
  ATM_DELAY(32),
  ATM_NOTE_B3,
  ATM_DELAY(32),
  ATM_NOTE_E2,
  ATM_DELAY(32),
  ATM_NOTE_E3,
  ATM_DELAY(32),
  ATM_NOTE_F2_,
  ATM_DELAY(32),
  ATM_NOTE_F3_,
  ATM_RETURN,

};

// ---------------------------------------------------------------------------
// Witch's Brew
// G minor 6/8 lilt: bubbling lead, arp pad, octave bass, kick + snare. Tempo 30, loop 384 ticks.
// 139 bytes
// ---------------------------------------------------------------------------
Song tuneBrew[] = {          // total song in bytes = 132
  0x08,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0  drums (CH3 entry)
  0x05, 0x00,                   // Address of track 1   //5  bubbling lead (CH0)
  0x21, 0x00,                   // Address of track 2   //33  arp pad (CH1)
  0x37, 0x00,                   // Address of track 3   //55  bass (CH2)
  0x4D, 0x00,                   // Address of track 4   //77  figure a
  0x54, 0x00,                   // Address of track 5   //84  figure b
  0x5B, 0x00,                   // Address of track 6   //91  kick + snare, one 6/8 bar
  0x66, 0x00,                   // Address of track 7   //102  shared 0

  0x01,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (pad)
  0x03,                         // Channel 2 entry track (bass)
  0x00,                         // Channel 3 entry track (drums)

  //"Track 0" drums (CH3 entry)  [5 bytes]
  ATM_REPEAT(7, 6),   // 8 x pair
  ATM_GOTO(0),   // drums

  //"Track 1" bubbling lead (CH0)  [28 bytes]
  ATM_SET_TEMPO(30),
  ATM_VOL(MV(36)),
  ATM_SL_VOL(MS(1)),
  ATM_SET_TRA(0),
  ATM_REPEAT(1, 4),   // 2 x m
  ATM_SET_TRA(5),
  ATM_REPEAT(1, 4),   // 2 x m
  ATM_SET_TRA((uint8_t)-4),
  ATM_REPEAT(1, 5),   // 2 x n
  ATM_SET_TRA(7),
  ATM_REPEAT(1, 5),   // 2 x n
  ATM_GOTO(1),   // lead

  //"Track 2" arp pad (CH1)  [22 bytes]
  ATM_VOL(MV(20)),
  ATM_ARP(0x34, 0x20),
  ATM_NOTE_G3,
  ATM_DELAY(64),
  ATM_DELAY(32),
  ATM_NOTE_C4,
  ATM_DELAY(64),
  ATM_DELAY(32),
  ATM_ARP(0x43, 0x20),
  ATM_NOTE_D4_,
  ATM_DELAY(64),
  ATM_DELAY(32),
  ATM_NOTE_D4,
  ATM_DELAY(64),
  ATM_DELAY(32),
  ATM_GOTO(2),   // pad

  //"Track 3" bass (CH2)  [22 bytes]
  ATM_VOL(MV(58)),
  ATM_SL_VOL(MS(1)),
  ATM_NOTE_G2,
  ATM_DELAY(48),
  ATM_NOTE_G3,
  ATM_DELAY(48),
  ATM_NOTE_C3,
  ATM_DELAY(48),
  ATM_NOTE_C4,
  ATM_DELAY(48),
  ATM_NOTE_D3_,
  ATM_DELAY(48),
  ATM_NOTE_D4_,
  ATM_DELAY(48),
  ATM_NOTE_D3,
  ATM_DELAY(48),
  ATM_NOTE_D4,
  ATM_DELAY(48),
  ATM_GOTO(3),   // bass

  //"Track 4" figure a  [7 bytes]
  ATM_NOTE_G5,
  ATM_DELAY(8),
  ATM_NOTE_A5_,
  ATM_DELAY(8),
  ATM_GOTO(7),   // shared 0
  ATM_RETURN,

  //"Track 5" figure b  [7 bytes]
  ATM_GOTO(7),   // shared 0
  ATM_NOTE_A5_,
  ATM_DELAY(8),
  ATM_NOTE_D5,
  ATM_DELAY(8),
  ATM_RETURN,

  //"Track 6" kick + snare, one 6/8 bar  [11 bytes]
  ATM_VOL(MV(44)),
  ATM_SL_VOL(MS(12)),
  ATM_DELAY(24),
  ATM_VOL(MV(40)),
  ATM_SL_VOL(MS(5)),
  ATM_DELAY(24),
  ATM_RETURN,

  //"Track 7" shared 0  [9 bytes]
  ATM_NOTE_D6,
  ATM_DELAY(8),
  ATM_NOTE_C6,
  ATM_DELAY(8),
  ATM_NOTE_A5_,
  ATM_DELAY(8),
  ATM_NOTE_G5,
  ATM_DELAY(8),
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

// the in-game tunes, one per level (displayLevel 1 = first one)
#define NUM_TUNES 7
const uint8_t *const tunes[] PROGMEM = { tuneBat, tuneHallway, tunePumpkin, tuneCrypt, tuneSeance, tuneCathedral, tuneBrew };

#define MUSIC_OFF 255                                       // nothing playing
#define MUSIC_TITLE 0                                       // 1..NUM_TUNES = in-game tune

byte musicId = MUSIC_OFF;
byte sfxTimer = 0;

// ATMlib does not look at the Arduboy sound setting, so we do it here
void sfx(const uint8_t *track)
{
  if (!arduboy.audio.enabled()) return;
  ATM.playSfx(track, 1);
  sfxTimer = 45;                                            // frames until the player is switched off again
}

// play a tune (MUSIC_OFF = stop)
void musicPlay(byte id)
{
  musicId = id;
  if (id == MUSIC_OFF) ATM.stop();
  else ATM.play(id == MUSIC_TITLE ? graveyardShift : (const uint8_t *)pgm_read_word(&tunes[id - 1]));
}

// the jukebox (menu.h): tunes 0 = title, 1..NUM_TUNES = the level tunes, and the 7 sound effects
#define JBOX_MUSIC (NUM_TUNES + 1)
#define JBOX_SFX 7
const uint8_t *const sfxList[] PROGMEM = { sfxShot, sfxHit, sfxDie, sfxOuch, sfxCoin, sfxHeart, sfxRescue };

// called once per frame: title music in the menus, a tune per level while playing, silence in between
void musicUpdate()
{
  byte want = MUSIC_OFF;
  if (gameState == STATE_MENU_JBOX) want = musicId;           // the jukebox decides what plays
  else if (arduboy.audio.enabled())
  {
    if (gameState <= STATE_MENU_SOUNDFX && (gameState || globalCounter > 89)) want = MUSIC_TITLE;   // from the T-arg logo on
    else if (gameState == STATE_GAME_PLAYING || gameState == STATE_GAME_PAUSE) want = 1 + (displayLevel - 1) % NUM_TUNES;
  }
  if (want != musicId) musicPlay(want);
  if (sfxTimer && !--sfxTimer && musicId == MUSIC_OFF) ATM.stop();   // sfx finished, free the CPU
}

#endif
