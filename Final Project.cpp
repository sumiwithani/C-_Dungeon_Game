#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

bool game_on = true;
bool game_restart = false;
string answer;
string movement;
bool player_alive = true;
bool player_ran = false;

//creating the Player depending on what they choose
struct Player
{
    string name;
    int health;
    int strength;
    int dexterity;
};

//Creating Enemies Structs
struct Goblin {
    int goblin_health;
    int goblin_dexterity;
    int goblin_strength;
};

struct Knight {
    int knight_health;
    int knight_dexterity;
    int knight_strength;
};

struct Boss {
    int boss_health;
    int boss_dexterity;
    int boss_strength;
};

struct Dragon {
    int dragon_health;
    int dragon_dexterity;
    int dragon_strength;
};

//Creating Struct within a Struct for the enemies to make it easier
//this may be bad optimization however we shouldn't see a difference
struct All_Enemies
{
    Dragon dragon_information;
    Goblin goblin_information;
    Knight knight_information;
    Boss boss_information;


};

//All the functions are below to make the code look neater
//Creating Player
struct Player creatingplayer();

//Creating The Enemies
struct All_Enemies Creating_enemies();

//Fighting Functions
void player_attacking_goblin(struct Player& player_fighting, struct All_Enemies goblin);
void player_attacking_knight(struct Player& player_fighting, struct All_Enemies knight);
void player_attacking_boss(struct  Player& player_fighting, struct All_Enemies boss);
void player_attacking_final_boss(struct Player& player_fighting, struct All_Enemies dragon);

void dungeon();
void goblin_encounter(struct Player&, struct All_Enemies);
void knight_encounter(struct Player&, struct All_Enemies);
void boss_encounter(struct Player&, struct All_Enemies);
void dragon_encounter(struct Player&, struct All_Enemies);

//Reward Functions
void OpeningReward(struct Player&, struct All_Enemies);

void gameStagesStraight(struct Player&, struct All_Enemies);
void gameStagesTwisting(struct Player&, struct All_Enemies);
void game_over_victory();
void game_over_run();
void game_over_loss();

//Vector list of events in game
//All events we want to be random need to be included here.
vector<void (*) (Player&, All_Enemies)> Master_Events{ &goblin_encounter, &knight_encounter, &boss_encounter,&OpeningReward, &dragon_encounter };
//Copying vector list so elements can be removed so it can be repopulated if game restarts.
vector<void (*) (Player&, All_Enemies)> Random_Events = Master_Events;


//Creates random number based on size of "Random_Events" 
//Seems like it may not work correctly if inserted into "gameStages" funtion.
int random_num() {
    srand(static_cast<unsigned int>(time(nullptr))); // set seed value to current time
    int num = rand() % Random_Events.size();
    return num;
};

int main()
{
    while (game_on == true) {
        //game restart
        if (game_restart = true) {
            Random_Events = Master_Events;
        }

        cout << " Welcome to the game\n";
        // calling the function to create the character they choose.
        struct Player p1 = creatingplayer();
        struct All_Enemies enemies_characters = Creating_enemies();

        //Game sequences.
        dungeon();
        if (movement == "straight") {
            gameStagesStraight(p1, enemies_characters);
        }
        if (movement == "twisting") {
            gameStagesTwisting(p1, enemies_characters);
        }



        //End game based on character being alive or dead.
        if (player_alive == true != player_ran == true) {
            game_over_victory();
        }
        if (player_alive == false) {
            game_over_loss();
        }
        if (player_ran == true) {
            game_over_run();
        }

    }

    return 0;
}



//Functions are all displayed here
//
//



void game_over_victory() {
    cout << "\n" << "Victory!\n" << "restart?\n" << "yes/no\n";
    cin >> answer;
    if (answer == "no") {
        answer = "";
        game_on = false;
    }
}

void game_over_run() {
    cout << "\n" << "You ran away!\n" << "restart?\n" << "yes/no\n";
    cin >> answer;
    if (answer == "no") {
        answer = "";
        game_on = false;
    }
}

void game_over_loss() {
    cout << "\n" << "You have died!\n" << "restart?\n" << "yes/no\n";
    cin >> answer;
    if (answer == "no") {
        answer = "";
        game_on = false;
    }
}

//plays 3 events 
void gameStagesStraight(Player& player_event, All_Enemies enemy_events) {
    for (int i = 0; i < Master_Events.size(); i++)
    {
        Random_Events.at(i)(player_event, enemy_events);
        if (player_alive == false || player_ran == true) {
            break;
        }
    }
}

void gameStagesTwisting(Player& player_event, All_Enemies enemy_events) {
    for (int i = 0; i < 3; i++)
    {
        Random_Events.at(random_num())(player_event, enemy_events);
        Random_Events.erase(Random_Events.begin() + random_num());
        if (player_alive == false) {
            break;
        }
    }
}


//Returning Player Information
struct Player creatingplayer()

{
    while (true)
    {
        //getting players input depending on what character they choose

        cout << "1: Name: Warrior\n \tHealth: 50 \n \tStrength: 25 \n \tDexterity: 10 \n 2: Name: Archer\n \tHealth: 35\n \tStrength: 10\n \tDexterity: 15\n 3: Name: Tank\n \tHealth: 75 \n \tStrength: 50 \n \tDexterity: 3 \n";
        cout << "Please choose your character wisely (1-3)\n\n";
        int input;
        cin >> input;
        struct Player p1;
        //create the warrior character
        if (input == 1)
        {
            cout << "\nYou chose Warrior\n";
            p1.health = 50;
            p1.name = "Warrior";
            p1.strength = 25;
            p1.dexterity = 10;
            return p1;
            break;
        }
        //creating the archer character
        else if (input == 2)
        {
            cout << "\nYou chose Archer\n";
            p1.health = 35;
            p1.name = "Archer";
            p1.strength = 10;
            p1.dexterity = 15;

            return p1;
            break;
            //creating the tank character
        }
        else if (input == 3)
        {
            cout << "\nYou chose Tank \n";
            p1.health = 75;
            p1.name = "Tank";
            p1.strength = 50;
            p1.dexterity = 3;
            return p1;

            break;
        }
        else
        {
            //if they do not pick a correct number it output this
            cout << input << " is not a option\n";

        }
    }
}


void  OpeningReward(struct Player& player_rewards, struct All_Enemies)
{
    srand(static_cast<unsigned int>(time(nullptr))); // set seed value to current time
    int random = rand() % 100;
    // if random number is less than a specific number it runs that code
    if (random <= 10)
    {
        cout << "A globin has scratched you, you lost " << 5 << " health\n";
        player_rewards.health -= 5;
        cout << "Your new health is " << player_rewards.health << endl;
    }
    else if (random <= 50)
    {

        player_rewards.health += 5;
        cout << "Your health increased up to " << player_rewards.health << endl;
        
    }
    else if (random <= 75)
    {
        player_rewards.strength += 15;
        cout << "Your drank a potion and your strength went up 15\n";
        cout << player_rewards.strength;
    }

    else
    {

        player_rewards.dexterity += 7;
        cout << "Your dexterity increased up to " << player_rewards.dexterity << endl;
    }
    return;
};

struct All_Enemies Creating_enemies()
{
    //creating all the players in a function to make the code neater
    All_Enemies CreatingEnemies;
    //creating goblin
    CreatingEnemies.goblin_information.goblin_health = 8;
    CreatingEnemies.goblin_information.goblin_dexterity = 4;
    CreatingEnemies.goblin_information.goblin_strength = 2;
    //Creating Knight Information
    CreatingEnemies.knight_information.knight_health = 10;
    CreatingEnemies.knight_information.knight_dexterity = 6;
    CreatingEnemies.knight_information.knight_strength = 4;
    // Every boss information
    CreatingEnemies.boss_information.boss_health = 20;
    CreatingEnemies.boss_information.boss_dexterity = 15;
    CreatingEnemies.boss_information.boss_strength = 12;
    // Creating Dragon Information
    CreatingEnemies.dragon_information.dragon_health = 50;
    CreatingEnemies.dragon_information.dragon_dexterity = 45;
    CreatingEnemies.dragon_information.dragon_strength = 25;



    return CreatingEnemies;
};

//attacking functions
// We dereference the player_fighting because we want to know the players health  after this function ends
// we do not want to know the goblin health after the function ends because we will have multiple
void player_attacking_goblin(struct Player& player_fighting, struct All_Enemies goblin)
{
    //keeping track of how much dex they lost
    int lost_dex = 0;
    // set the seed for the random number generator
    srand(time(NULL));
    // giving the player to choose from 1-12
    int roll_dice = 12;
    int input = 0;
    // a random number between 1-12
    int random = rand() % roll_dice + 1;
    //cout << "Why is this not working " << random;
    cout << "Please choose a number wisely between 1-12: ";
    cin >> input;
    // we are making sure the player is inputting a number that is valid
    while (input < 0 || input > 12)
    {
        cout << "Invalid Number\n";
        cout << "Please choose a number wisely between 1-12: ";
        cin >> input;;

    }
    //a low chance but likely to give a player a higher chance to beat the boss and other enemies 
    if (input == random)
    {
        cout << "You found a goblin that wants you to kill their master. He gave you a potion that improved your strength. \n" << endl;
        player_fighting.strength += 15;
        cout << player_fighting.name << ", Your new strength is " << player_fighting.strength;

        //must add return if not it it does the other code
        return;


    }

    do
    {

        //doing this to give the player a higher chance to beat the goblin and not lose as much health
        // because a goblin should not be that hard to kill
        if (input - 2 <= random)
        {
            //making it harder to kill the goblin depending on strength.
            if (player_fighting.strength <= 16)
            {
                // Seed the random number generator with the current time
                srand(time(0));
                //Making the damage random so its not just 2 everytime 
                int num = rand() % 7 + 1;
                goblin.goblin_information.goblin_health -= num;
                cout << "You hit the goblin\n";
                cout << "Goblin health is: " << goblin.goblin_information.goblin_health << endl;
                player_fighting.dexterity -= -1;
                lost_dex++;
            }
            //this makes it easier to kill the goblin depending on strength
            else
            {
                // Seed the random number generator with the current time
                srand(time(0));
                //Making the damage random so its not just 2 everytime 
                int num = rand() % 10 + 3;
                goblin.goblin_information.goblin_health -= num;
                cout << "You hit the goblin\n";
                cout << "Goblin health is: " << goblin.goblin_information.goblin_health << endl;
                player_fighting.dexterity -= -1;
                lost_dex++;
            }
        }
        //else player loses health
        else if (input > random)
        {   // Seed the random number generator with the current time
            srand(time(0));
            int num = rand() % 2 + 1;
            player_fighting.health -= num;
            cout << "Player health is " << player_fighting.health << endl;
        }
        //breaks out of the while loop and prints out who wins
        if (goblin.goblin_information.goblin_health <= 0)
        {
            cout << "You defeated the goblin!" << endl;
            break;
        }
        else if (player_fighting.health <= 0)
        {
            cout << "You were defeated by the goblin." << endl;
            player_alive = false;
            break;
        }
        //gonna keep on battling until someones health equals 0
        random = rand() % roll_dice + 1;
        // cout << "Why is this not working" << random;

        cout << "Please choose a number wisely between 1-12: ";
        cin >> input;
        //safety check to make sure they don't go out of 1-12
        while (input < 1 || input > 12)
        {
            cout << "Invalid Number\n";
            cout << "Please choose a number wisely between 1-12: ";
            cin >> input;
        }


    } while (!(goblin.goblin_information.goblin_health <= 0 || player_fighting.health <= 0));


    //restoring the dex they lost
    player_fighting.dexterity += lost_dex;

};
//player attacking knight function
void player_attacking_knight(struct Player& player_fighting, struct All_Enemies knight)
{
    bool has_dex = true;
    //keeping track of how much dex they lost
    int lost_dex = 0;
    // set the seed for the random number generator
    srand(time(NULL));
    // giving the player to choose from 1-12
    int roll_dice = 12;
    int input = 0;
    // a random number between 1-12
    int random = rand() % roll_dice + 1;
    cout << "Please choose a number wisely between 1-12: ";
    cin >> input;



    // we are making sure the player is inputting a number that is valid
    while (input < 0 || input > 12)
    {
        cout << "Invalid Number\n";
        cout << "Please choose a number wisely between 1-12: ";
        cin >> input;;

    }
    //a low chance but likely to give a player a higher chance to beat the boss
    if (input == random)
    {
        cout << "You found a Knight that begged you not to kill him, so he gave you a potion that gave you extra dexterity." << endl;
        player_fighting.dexterity += 15;
        cout << player_fighting.name << ", Your new strength is " << player_fighting.strength << endl;

        //must add return if not it it does the other code
        return;


    }

    do
    {
        //doing this to make sure the player has dexterity to fight or block 


        // making it easier for them to kill the knight but not to much

        if (input - 1 <= random)
        {

            if (player_fighting.dexterity <= 0)
            {
                //Gaining dexterity back
                srand(time(0));
                //this one is for health
                int health_num = rand() % 3 + 1;
                //this one is for dex
                int dex_num = rand() % 4 + 1;
                cout << player_fighting.name << ", You have ran out of dexterity to fight back against the knight. Overtime you will regain dexterity back!";
                cout << " There is no way for you to escape this fight you must take damage until your dexterity regains! \n\n ";
                //Player losing some hp
                player_fighting.health -= health_num;
                cout << "The knight hit you! Your current hp is " << player_fighting.health << endl;
                //gaining some dex
                player_fighting.dexterity += dex_num;
                //tracking how much dex they lost
                lost_dex += dex_num;
                has_dex = false;
            }
            else
            {
                // turing the boolean true if player has dex
                has_dex = true;


            }
            // making sure the player has dex to attack
            if (has_dex == true)
            {
                if (player_fighting.strength >= 30)
                {
                    //(3-10) * 2
                    srand(time(0));
                    int num = rand() % 8 + 1;
                    //doing damage
                    knight.knight_information.knight_health -= num;
                    cout << "You hit the Knight\n ";
                    cout << "Knight health is: " << knight.knight_information.knight_health << endl;
                    player_fighting.dexterity -= 1;
                    lost_dex++;


                }
                else if (player_fighting.strength >= 20)
                {
                    //(2-8) * 2
                    srand(time(0));
                    int num = rand() % 7 + 1;
                    //doing double damage 
                    knight.knight_information.knight_health -= num;
                    cout << "You hit the Knight\n ";
                    cout << "Knight health is: " << knight.knight_information.knight_health << endl;
                    player_fighting.dexterity -= 1;
                    lost_dex++;
                }
                else
                {
                    //(1-6) * 2
                    srand(time(0));
                    int num = rand() % 5 + 1;
                    //doing double damage 
                    knight.knight_information.knight_health -= num;
                    cout << "You hit the Knight\n ";
                    cout << "Knight health is: " << knight.knight_information.knight_health << endl;
                    player_fighting.dexterity -= 1;
                    lost_dex++;
                }
            }

        }
        //else player loses health
        else if (input > random)
        {
            srand(time(0));
            int num = rand() % 3 + 1;
            player_fighting.health -= num;
            cout << "The knight hit you!\n";
            cout << "Your new health is: " << player_fighting.health << endl;
        }
        //breaks out of the while loop and prints out who wins
        if (knight.knight_information.knight_health <= 0)
        {
            cout << "You defeated the Knight!" << endl;
            break;
        }
        else if (player_fighting.health <= 0)
        {
            cout << "You were defeated by the Knight." << endl;
            player_alive = false;
            break;
        }
        //gonna keep on battling until someones health equals 0
        random = rand() % roll_dice + 1;

        cout << "Please choose a number wisely between 1-12: ";
        cin >> input;
        //safety check to make sure they don't go out of 1-12
        while (input < 1 || input > 12)
        {
            cout << "Invalid Number\n";
            cout << "Please choose a number wisely between 1-12: ";
            cin >> input;
        }


    } while (!(knight.knight_information.knight_health <= 0 || player_fighting.health <= 0));

    //restoring players dex
    player_fighting.dexterity += lost_dex;
};
//player attacking a boss
void player_attacking_boss(struct  Player& player_fighting, struct All_Enemies boss)

{

    bool has_dex = true;
    //keeping track of how much dex they lost
    int lost_dex = 0;
    // set the seed for the random number generator
    srand(time(NULL));
    // giving the player to choose from 1-12
    int roll_dice = 12;
    int input = 0;
    // a random number between 1-12
    int random = rand() % roll_dice + 1;
    cout << "Please choose a number wisely between 1-12: ";
    cin >> input;

    // we are making sure the player is inputting a number that is valid
    while (input < 0 || input > 12)
    {
        cout << "Invalid Number\n";
        cout << "Please choose a number wisely between 1-12: ";
        cin >> input;;

    }
    //a low chance but likely to give a player a higher chance to beat the boss
    if (input == random)
    {
        cout << "You Sneaked attack the boss!" << " The boss lost 9 hp!" << endl;
        boss.boss_information.boss_health -= 9;
        cout << player_fighting.name << ", The boss HP is now at" << boss.boss_information.boss_health;
    }

    do
    {


        //switching it up a little bit instead of a < we are doing a >
        if (input >= random)
        {
            //Player gets hit by a knight and needs time to gain dexterity
            if (player_fighting.dexterity <= 0)
            {
                srand(time(0));
                //this one is for health
                int health_num = rand() % 3 + 1;
                //this one is for dexterity
                int dex_num = rand() % 4 + 1;
                cout << player_fighting.name << ", You have ran out of dexterity to fight back against the Boss. Overtime you will regain dexterity back!";
                cout << " There is no way for you to escape this fight you must take damage until your dexterity regains! \n\n ";
                //Player losing some hp
                player_fighting.health -= health_num;
                cout << "The Boss hit you! Your current hp is " << player_fighting.health << endl;
                //gaining some dex
                player_fighting.dexterity += dex_num;
                //tracking how much dex they lost
                lost_dex += dex_num;
                //changing this to false because they did not have dex when they enter this if statement
                has_dex = false;
            }
            else
            {
                // turing the boolean true if player has dex
                has_dex = true;
            }
            // making sure the player has dex to attack
            if (has_dex == true)
            {
                if (player_fighting.strength >= 30)
                {
                    //(3-10) * 2
                    srand(time(0));
                    int num = rand() % 9 + 2;
                    //doing damage
                    boss.boss_information.boss_health -= num;
                    cout << "You hit the Boss\n ";
                    cout << "Boss health is: " << boss.boss_information.boss_health << endl;
                    player_fighting.dexterity -= 1;
                    lost_dex++;


                }
                else if (player_fighting.strength >= 20)
                {
                    //(2-8) * 2
                    srand(time(0));
                    int num = rand() % 6 + 2;
                    //doing double damage 
                    boss.boss_information.boss_health -= num;
                    cout << "You hit the Boss\n ";
                    cout << "Boss health is: " << boss.boss_information.boss_health << endl;
                    player_fighting.dexterity -= 1;
                    lost_dex++;
                }
                else
                {
                    //(1-6) * 2
                    srand(time(0));
                    int num = rand() % 5 + 1;
                    //doing double damage 
                    boss.boss_information.boss_health -= num;
                    cout << "You hit the Boss\n ";
                    cout << "Boss health is: " << boss.boss_information.boss_health << endl;
                    player_fighting.dexterity -= 1;
                    lost_dex++;
                }
            }
        }

        //else player loses health
        else if (input < random)
        {
            srand(time(0));
            int num = rand() % 5 + 1;
            player_fighting.health -= num;
            cout << "Your  health is " << player_fighting.health << endl;
        }
        //breaks out of the while loop and prints out who wins
        if (boss.boss_information.boss_health <= 0)
        {
            cout << "You defeated a boss!" << endl;
            player_fighting.dexterity += 10;
            player_fighting.strength += 5;
            cout << player_fighting.name << ", Congrats for beating one of the bosses you have gained " << 5 << " Strength and " << 10 << " dexterity" << endl;
            break;
        }
        else if (player_fighting.health <= 0)
        {
            cout << "You were defeated by a boss." << endl;
            player_alive = false;
            break;
        }
        //gonna keep on battling until someones health equals 0
        random = rand() % roll_dice + 1;

        cout << "Please choose a number wisely between 1-12: ";
        cin >> input;
        //safety check to make sure they don't go out of 1-12
        while (input < 1 || input > 12)
        {
            cout << "Invalid Number\n";
            cout << "Please choose a number wisely between 1-12: ";
            cin >> input;
        }
    } while (!(boss.boss_information.boss_health <= 0 || player_fighting.health <= 0));
    //resetting there dexterity
    player_fighting.dexterity += lost_dex++;
};
void player_attacking_final_boss(struct  Player& player_fighting, struct All_Enemies dragon)
{
    bool has_dex = true;
    //keeping track of how much dex they lost
    int lost_dex = 0;
    //give them crazy damage if they guess the number right
    bool double_damage = false;
    // set the seed for the random number generator
    srand(time(NULL));
    // giving the player to choose from 1-12
    int roll_dice = 12;
    int input = 0;
    // a random number between 1-12
    int random = rand() % roll_dice + 1;
    cout << "Please choose a number wisely between 1-12: ";
    cin >> input;
    // we are making sure the player is inputting a number that is valid
    while (input < 0 || input > 12)
    {
        cout << "Invalid Number\n";
        cout << "Please choose a number wisely between 1-12: ";
        cin >> input;;

    }
    //a low chance but likely to give a player a higher chance to beat the final boss
    if (input == random)
    {
        cout << "You drunk a potion and you do double the damage!" << endl;
        double_damage = true;
    }

    do
    {
        //switching it up a little bit instead of a < we are doing a >
        if (input >= random)
        {
            if (player_fighting.dexterity <= 0)
            {

                srand(time(0));
                //this one is for health
                int health_num = rand() % 3 + 1;
                //this one is for dexterity
                int dex_num = rand() % 4 + 1;
                cout << player_fighting.name << ", You have ran out of dexterity to fight back against the Final Boss! Overtime you will regain dexterity back!";
                cout << " There is no way for you to escape this fight you must take damage until your dexterity regains! \n\n ";
                //Player losing some hp
                player_fighting.health -= health_num;
                cout << "The Dragon hit you! Your current hp is " << player_fighting.health << endl;
                //gaining some dex
                player_fighting.dexterity += dex_num;
                //tracking how much dex they lost
                lost_dex += dex_num;
                //changing this to false because they did not have dex when they enter this if statement
                has_dex = false;
            }
            else
            {
                // turing the boolean true if player has dex
                has_dex = true;
            }
            // making sure the player has dex to attack
            if (has_dex == true)
            {
                //Making the damage random so its not boring and a little bit more entertaining 

                if (double_damage == true)
                {
                    //checks player strength
                    if (player_fighting.strength >= 30)
                    {
                        //(3-10) * 2
                        srand(time(0));
                        int num = rand() % 10 + 3;
                        //doing double damage 
                        dragon.dragon_information.dragon_health -= (2 * num);
                        cout << "You hit the Dragon with a powerful shot!\n ";
                        cout << "Dragon health is: " << dragon.dragon_information.dragon_health << endl;
                    }
                    else if (player_fighting.strength >= 20)
                    {
                        //(2-8) * 2
                        srand(time(0));
                        int num = rand() % 8 + 2;
                        //doing double damage 
                        dragon.dragon_information.dragon_health -= (2 * num);
                        cout << "You hit the Dragon with a powerful shot!\n ";
                        cout << "Dragon health is: " << dragon.dragon_information.dragon_health << endl;
                    }
                    else
                    {
                        //(1-6) * 2
                        srand(time(0));
                        int num = rand() % 6 + 1;
                        //doing double damage 
                        dragon.dragon_information.dragon_health -= (2 * num);
                        cout << "You hit the Dragon with a powerful shot!\n ";
                        cout << "Dragon health is: " << dragon.dragon_information.dragon_health << endl;
                    }
                }
                else
                {
                    //checks player strength
                    if (player_fighting.strength >= 30)
                    {
                        //(3-10)
                        srand(time(0));
                        int num = rand() % 10 + 3;
                        //doing double damage 
                        dragon.dragon_information.dragon_health -= num;
                        cout << "You hit the Dragon!\n ";
                        cout << "Dragon health is: " << dragon.dragon_information.dragon_health << endl;
                    }
                    else if (player_fighting.strength >= 20)
                    {
                        //(2-8)
                        srand(time(0));
                        int num = rand() % 8 + 2;
                        //doing double damage 
                        dragon.dragon_information.dragon_health -= num;
                        cout << "You hit the Dragon\n ";
                        cout << "Dragon health is: " << dragon.dragon_information.dragon_health << endl;
                    }
                    else
                    {
                        //(1-6)
                        srand(time(0));
                        int num = rand() % 6 + 1;
                        //doing double damage 
                        dragon.dragon_information.dragon_health -= (2 * num);
                        cout << "You hit the Dragon\n ";
                        cout << "Dragon health is: " << dragon.dragon_information.dragon_health << endl;
                    }
                }
            }
        }
        //else player loses health
        else
        {
            srand(time(0));
            int num = rand() % 9 + 1;
            player_fighting.health -= num;
            cout << player_fighting.name << ", you've gotten hit! You lost " << player_fighting.health << "HP" << endl;
        }


        //breaks out of the while loop and prints out who wins
        if (dragon.dragon_information.dragon_health <= 0)
        {
            cout << " You defeated the Dragon, YOU WIN!" << endl;

            break;
        }
        else if (player_fighting.health <= 0)
        {
            cout << " You were defeated by the Dragon, you lost." << endl;
            player_alive = false;
            break;
        }

        //gonna keep on battling until someones health equals 0
        random = rand() % roll_dice + 1;
        cout << " Please choose a number wisely between 1-12: ";
        cin >> input;
        //safety check to make sure they don't go out of 1-12
        while (input < 1 || input > 12)
        {
            cout << " Invalid Number\n";
            cout << " Please choose a number wisely between 1-12: ";
            cin >> input;
        }


    } while (!(dragon.dragon_information.dragon_health <= 0 || player_fighting.health <= 0));

}
//scences 
void dungeon() {
    int input;
    movement = "";
    cout << "You have arrived at the dungeon. You will encounter several dangers ahead. Two paths lead off one straight, the other twisting and winding. " << endl;
    cout << "Which path will you choose, straight or twisting?" << endl;
    while (movement != "straight" && movement != "twisting") {
        cin >> movement;
    }


}
void goblin_encounter(struct Player& player, struct All_Enemies goblin) {
    int input;
    srand(time(NULL));
    int chance = 10;
    int random = rand() % chance;
    cout << "You have encountered a goblin. Will you: \n1) attack, 2) negotiate, or 3) run? " << endl;
    cin >> input;
    if (input == 1) {
        cout << "You have chosen to attack the goblin." << endl;
        player_attacking_goblin(player, goblin);
    }
    if (input == 2) {
        cout << "You have chosen to negotiate with the goblin. ";
        cout << "The goblin isn't friendly, but he has a heart. ";
        cout << "If you were to be nice enough, he would let you go. ";
        cout << "Even better would be if he would benefit you in your journey, but that would be much too difficult. ";
        cout << "Don't lose your guard; however, because he could see you as weak and go for the attack." << endl;
        if (random < 5) {
            cout << "The goblin is not swayed and attacks ferociously" << endl;
            player_attacking_goblin(player, goblin);
        }
        if (random >= 5) {
            cout << "The goblin nods and lets you past" << "\n" << endl;
        }
    }
    if (input == 3) {
        cout << "You have chosen the safest option and flee altogether. ";
        cout << "The goblen is mostly weak, so he may be kind and let you off. ";
        cout << "However, he has the ability to refuse your request to flee and chase you down. ";
        cout << "The choice is ultimately his." << endl;
        player_ran = true;
    }

}
void knight_encounter(struct Player& player, struct All_Enemies knight) {
    int input;
    srand(time(NULL));
    int chance = 10;
    int random = rand() % chance;
    cout << "You have encountered a knight. Will you: \n1) attack, 2) negotiate, or 3) run?: " << endl;
    cin >> input;
    if (input == 1) {
        cout << "You have chosen to attack the knight." << endl;
        player_attacking_knight(player, knight);
    }
    if (input == 2) {
        cout << "You have chosen to negotiate with the knight. ";
        cout << "The knight's heart is very dark. Darker than even the goblin. ";
        cout << "However, his heart has some light inside. ";
        cout << "At most, he will feel bad and let you off. ";
        cout << "Don't lose your guard; however, because he could see you as weak and go for the attack." << endl;
        if (random < 7) {
            cout << "The knight is not swayed and attacks ferociously" << endl;
            player_attacking_knight(player, knight);
        }
        if (random >= 7) {
            cout << "The knight nods and lets you past" << "\n" << endl;
        }
    }
    if (input == 3) {
        cout << "You have chosen to flee the battle. ";
        cout << "The knight can see you as unimportant enough to shrug you off. ";
        cout << "However, he could see this as a chance to kill and chase you down. ";
        cout << "Pray for the former, because if he goes for the latter option, you're toast. ";
        cout << "The choice is ultimately his." << endl;
        player_ran = true;
    }


}
void boss_encounter(struct Player& player, struct All_Enemies knight) {
    int input;
    srand(time(NULL));
    int chance = 10;
    int random = rand() % chance;
    cout << "You encounter the black knight. Will you: \n1) attack, 2) negotiate, or 3) run?:" << endl;
    cin >> input;
    if (input == 1) {
        cout << "You have chosen to attack the black knight." << endl;
        player_attacking_boss(player, knight);
    }
    if (input == 2) {
        cout << "You have chosen to negotiate with the black knight. ";
        cout << "The black knight is confused because you wanted to duel with him, yet now you're negotiating. ";
        cout << "You barely have a chance to succeed in your negotiation. ";
        cout << "It'll cost you, but the results will be there. ";
        cout << "However, he will refuse your talks and just finish the fight instead. ";
        cout << "The choice is ultimately his." << endl;
        if (random < 9) {
            cout << "The black knight is not swayed and attacks ferociously" << endl;
            player_attacking_boss(player, knight);
        }
        if (random >= 9) {
            cout << "You somehow convince the black knight to lets you past!" << "\n" << endl;
        }

        if (input == 3) {
            cout << "What are you doing? You can't run from a duel! Who do you think you are?" << endl;
            player_attacking_boss(player, knight);
        }

    }
}

void dragon_encounter(struct Player& player, struct All_Enemies dragon) {
    int dragon_input;
    srand(time(NULL));
    int chance = 10;
    int random = rand() % chance;
    cout << "You encounter the mighty dragon." << endl;
    cout << "The mighty dragon has been unleashed upon you! Will you: \n1) attack, 2) negotiate, or 3) run?: " << endl;
    cin >> dragon_input;
    if (dragon_input == 1) {
        cout << "You have chosen to attack the mighty dragon.";
        cout << "This may be your end, but it is better to die a hero than live a villain." << endl;
        player_attacking_final_boss(player, dragon);
    }
    if (dragon_input == 2) {
        cout << "You have chosen to negotiate with the black knight. ";
        cout << "The black knight is confused because you wanted to duel with him, yet now you're negotiating. ";
        cout << "You barely have a chance to succeed in your negotiation. ";
        cout << "It'll cost you, but the results will be there. ";
        cout << "However, he will refuse your talks and just finish the fight instead. ";
        cout << "The choice is ultimately his." << endl;
        if (random < 10) {
            cout << "The dragon is not swayed and attacks ferociously" << endl;
            player_attacking_final_boss(player, dragon);
        }
        if (random >= 10) {
            cout << "You somehow convince the dragon to lets you past!" << "\n" << endl;
        }

        if (dragon_input == 3) {
            cout << "You have chosen the most dangerous part and flee. ";
            cout << "Not only are you a scaredycat, but also, you are an idiot. ";
            cout << "The mighty dragon is faster and stronger than you are, so running away from a fight is like prey running away from the predator. ";
            cout << "The dragon won't seem to mind though! He loves moving dinner. Loses weight and beings the reward in the end." << endl;
            player_alive = false;
        }

    }
}