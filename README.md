# Love Letter Simulator

A program using C++ that simulates a game of Love Letter. The user controls the actions of all the players in the game.

## How to use

Download the folder "C++ LL Sim" and all of its files. In the "main.cpp" file, a game between three players, Steven, Kevin, and Jonathan, is already premade. In order to add players, create a Player object with a name and add it to the "game" object, in the corresponding sections. To remove a player, just delete the lines corresponding to adding that player to the game. Bear in mind that a default game of Love Letter generally only supports 4 players. Afterwards, just compile and run the program using your preferred IDE.

### Example of adding a player
In the main function of the "main.cpp" file, under the "game" object:
```c++
// Create the player object
Player name("name");

// Add the player object to the game
game.addPlayer(name);
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
