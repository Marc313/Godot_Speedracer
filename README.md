# Lost At Sea
Guide your ship through a dangerous sea infested with sharks!

To gain more experience in C++, I recreated a game like speedracer in the Godot Engine. So not only am I learning C++, I am also learning to use Godot for the first time.

The structure of the code used in this game is loosely coupled, since every script has access to functions from Godot, like the _ready and _process functions. Most of the interactions between nodes are managed using Godot's signals, which is similar to an event system.

To ensure that all components are properly managed at the start of the game, a gameManager script was created to signal all relevant nodes. An enemyManager class was also created to manage the appearance and disappearance of enemies throughout the game, based on certain conditions. When the player collides with an enemy, a signal is emitted to the gameManager, which then signals all other nodes.
