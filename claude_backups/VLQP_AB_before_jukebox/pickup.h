#ifndef PICKUP_H
#define PICKUP_H

// what a killed zombie leaves behind, 2 out of 10 nothing, 1 out of 10 a heart, 7 out of 10 a coin
const byte PROGMEM pickupsAvailable[10] =
{
  PICKUP_TYPE_COIN, PICKUP_TYPE_COIN, PICKUP_TYPE_COIN, PICKUP_TYPE_INACTIVE, PICKUP_TYPE_COIN,
  PICKUP_TYPE_HEART, PICKUP_TYPE_INACTIVE, PICKUP_TYPE_COIN, PICKUP_TYPE_INACTIVE, PICKUP_TYPE_COIN
};

// addPickup
// puts a pickup in the first free slot of the world
void addPickup(int x, int y)
{
  for (byte id = 0; id < PICKUP_MAX; id++)
  {
    Pickup& pick = pickups[id];
    if (!pick.type)
    {
      pick.isVisible = true;
      pick.counter = 0;
      pick.x = x;
      pick.y = y;
      pick.type = pgm_read_byte(&pickupsAvailable[pickupsCounter]);
      pickupsCounter++;
      if (pickupsCounter > 9) pickupsCounter = 0;
      return;
    }
  }
}

// drawPickups
// draws the entire list of pickups, they blink and disappear after a while
void drawPickups()
{
  bool tick6 = arduboy.everyXFrames(6);
  bool tick2 = arduboy.everyXFrames(2);
  for (byte id = 0; id < PICKUP_MAX; id++)
  {
    Pickup& pick = pickups[id];
    if (tick6)
    {
      pick.counter++;
      pick.frame++;
    }
    if (tick2 && (pick.counter > 25)) pick.isVisible = !pick.isVisible;
    if (pick.counter > 30) pick.type = PICKUP_TYPE_INACTIVE;
    if (pick.frame > 5) pick.frame = 0;
    if (pick.type && pick.isVisible)
    {
      sprites.drawPlusMask(pick.x - mapPositionX, pick.y - mapPositionY, collectables_plus_mask, pick.frame + (6 * (pick.type - 1)));
    }
  }
}

// pickupCollision
// checks for collision against the player, and handles it
void pickupCollision(int x, int y)
{
  for (byte id = 0; id < PICKUP_MAX; id++)
  {
    Pickup& pick = pickups[id];
    if (pick.type && boxHit(pick.x, pick.y, x, y, SPRITE_SIZE, SPRITE_SIZE))
    {
      if (pick.type == PICKUP_TYPE_HEART)
      {
        sfx(sfxHeart);
        playerHealthOffset(coolGirl, 2);
      }
      else
      {
        sfx(sfxCoin);
        rollingScore += 100;
      }
      pick.type = PICKUP_TYPE_INACTIVE;
    }
  }
}

// clearPickups
// clears the entire list of pickups
void clearPickups()
{
  for (byte id = 0; id < PICKUP_MAX; id++) pickups[id].type = PICKUP_TYPE_INACTIVE;
}

#endif
