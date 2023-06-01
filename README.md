# Warriors
A ZX Spectrum-style video game developed in C++ with help from [SFML](https://www.sfml-dev.org/index.php).
![artwork](http://jeremyelkayam.com/images/warriors.png)

## How to Play

- Press the arrow keys to control Alfelus (the blue Warrior), and press the left control key to swing your sword.
- Red warriors will come at you constantly. Your mission: survive the onslaught for as long as you can.
- Your sword is extended in the direction you are moving. Your sword can only be held for a few seconds at a time, and you will need to periodically put it away to recharge your energy.
- Once your health reaches 0, you die and can no longer fight. 
  - In singleplayer, the game ends when Alfelus dies. In multiplayer, the game ends when all players die. 

### Items 

- Green healing potions restore your health. 
  - Even if you haven't lost any health yet, you should still try collecting potions, as they will give you more health either way.
  - Healing potions disappear after a few seconds, so if one appears, pick it up as soon as possible.
- The bomb clears the screen of all warriors. 
- The gold ring grants you one unit of health for each Warrior you kill after collecting it. Its effect only lasts for a few seconds, so use it wisely. 
- The ring and bomb each appear only once per game, and will not disappear. Save them until the time is right. 
- If you use the ring, then the bomb, you will receive one health for every 2 warriors killed (half of what you would get otherwise). 

### Options
- You can remap the keys for all players using the third option on the main menu (redefine keys).
- You can tweak elements of the game (such as number of players) using the second option on the main menu (game with options).
