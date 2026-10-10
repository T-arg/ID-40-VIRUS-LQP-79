#ifndef PLAYER_H
#define PLAYER_H

// facing direction for a move of (x, y), index = (y + 1) * 3 + (x + 1), 255 = not moving
const byte PROGMEM facingByMove[9] = { 3, 4, 5, 2, 255, 6, 1, 0, 7 };

// initializePlayer
// sets the default values for player
void initializePlayer(Player& obj)
{
  scorePlayer = 0;
  rollingScore = 0;
  obj.direction = PLAYER_FACING_SOUTH;
  obj.health = PLAYER_START_HEALTH;
  obj.flashTime = 0;
  obj.shotDelay = 10;
  obj.coolDownVisible = true;
  obj.overHeated = false;
  obj.coolDownCounter = 0;
}

// updatePlayer
// updates the player according to game rules
void updatePlayer(Player& obj)
{
  if (obj.coolDownCounter > WEAPON_OVERHEAT) obj.overHeated = true;

  ///////////
  // input //
  ///////////

  bool rungun = arduboy.pressed(A_BUTTON);
  bool standgun = arduboy.pressed(B_BUTTON);

  // left wins from right, up wins from down
  char vx = 0;
  char vy = 0;
  if (arduboy.pressed(LEFT_BUTTON)) vx = -1;
  else if (arduboy.pressed(RIGHT_BUTTON)) vx = 1;
  if (arduboy.pressed(UP_BUTTON)) vy = -1;
  else if (arduboy.pressed(DOWN_BUTTON)) vy = 1;
  obj.walking = vx || vy;
  byte facing = pgm_read_byte(&facingByMove[(vy + 1) * 3 + (vx + 1)]);

  // Bullet timer
  if (obj.shotDelay > 0) obj.shotDelay--;

  // horizontal physics
  obj.x += vx;
  zombieCollide(obj.x, obj.y, true, vx);
  mapCollide(obj.x, obj.y, true, vx);

  // vertical physics
  obj.y += vy;
  zombieCollide(obj.x, obj.y, false, vy);
  mapCollide(obj.x, obj.y, false, vy);

  // collide with survivors, door and pickups
  survivorCollide(obj.x, obj.y);
  if (checkDoorCollision()) gameState = STATE_GAME_PREPARE_LEVEL;
  pickupCollision(obj.x, obj.y);

  ///////////////
  // direction //
  ///////////////

  // holding A strafes: the player keeps facing the same way while moving
  if (!rungun && facing != 255) obj.direction = facing;

  // the camera will only be updated if moving nondiagonally or look mode
  if ((standgun && !rungun) || (obj.direction % 2) == 0) obj.camDirection = obj.direction;

  ////////////
  // timers //
  ////////////

  if (arduboy.everyXFrames(4))
  {
    if (obj.coolDownCounter > 1) obj.coolDownCounter--;
    if ((rungun || standgun) && !obj.overHeated) obj.coolDownCounter += 2;
    if (obj.overHeated) obj.coolDownVisible = !obj.coolDownVisible;
  }

  if ((standgun || rungun) && !obj.overHeated && obj.shotDelay == 0)
  {
    addBullet(obj.x + 10, obj.y + 12, obj.direction);
    obj.shotDelay = 10;
  }

  if (obj.overHeated && obj.coolDownCounter < 2)
  {
    obj.overHeated = false;
    obj.coolDownVisible = true;
  }

  // Update animation
  if (arduboy.everyXFrames(6) && obj.walking) obj.frame++;
  if (obj.frame > 3) obj.frame = 0;

  // update score
  if (rollingScore > 0)
  {
    rollingScore -= 5;
    scorePlayer += 5;
  }

  // update flashing
  if (obj.flashTime > 0) obj.flashTime--;

  ////////////
  // camera //
  ////////////

  // the camera goal is the player in the middle of the screen, offset by the direction
  short mapGoalX = obj.x - WIDTH / 2 + SPRITE_SIZE / 2 + BulletXVelocities[obj.camDirection] * 4;
  short mapGoalY = obj.y - HEIGHT / 2 + SPRITE_SIZE / 2 - 4 + BulletXVelocities[(obj.camDirection + 6) % 8] * 4; // hud offset

  // move the camera toward the desired location
  mapPositionX = burp(mapPositionX, mapGoalX, 3);
  mapPositionY = burp(mapPositionY, mapGoalY, 3);

  // Clamp on screen boundaries
  mapPositionX = constrain(mapPositionX, 0, LEVEL_WIDTH - WIDTH);
  mapPositionY = constrain(mapPositionY, 0, LEVEL_HEIGHT - HEIGHT);
}

// playerHealthOffset
// changes the player health (damage when negative), the player blinks and is safe for a while after damage
void playerHealthOffset(Player& obj, char amount)
{
  if (obj.flashTime == 0)
  {
    obj.health += amount;

    if (amount < 0)
    {
      obj.flashTime = PLAYER_FLASH_TIME;
      sfx(sfxOuch);
    }

    if (obj.health > PLAYER_MAXHEALTH) obj.health = PLAYER_MAXHEALTH;
    else if (obj.health == 0) gameState = STATE_GAME_OVER;
  }
}

// drawPlayer
// draws the player to the screen
void drawPlayer(Player& obj)
{
  if ((obj.flashTime % 8) < 4)
  {
    int x = obj.x - mapPositionX;
    int y = obj.y - mapPositionY;
    if (obj.direction <= 4) drawMasked(x, y, playerAmyMask, obj.direction, playerAmy, obj.frame + 4 * obj.direction);
    else drawFlipped(x, y, playerAmy + 2 + (obj.frame + 4 * (8 - obj.direction)) * 32, playerAmyMask + 2 + (8 - obj.direction) * 32, 15);
  }
}

void drawLife(Player& obj)
{
  for (byte amountLife = 0; amountLife < obj.health; amountLife++)
  {
    sprites.drawPlusMask((amountLife / 2) * 10, 0, HUD_plus_mask, 0);
  }
  for (byte amountLife = 0; amountLife < obj.health / 2; amountLife++)
  {
    sprites.drawPlusMask(amountLife * 10, 0, HUD_plus_mask, 1);
  }
}

void drawCoolDown()
{
  if (coolGirl.coolDownVisible)
  {
    for (byte i = 0; i < coolGirl.coolDownCounter; i++)
    {
      sprites.drawPlusMask(i, 7, coolDownLine_plus_mask, 0);
    }
  }
}

#endif
