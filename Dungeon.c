#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <unistd.h>


void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void printFlashingTitle() {


    char *title = "--- R E A D Y   T O   R O C K ? ---";
    char *title1 = "--- E A Y R D   O T   K C R O ? ---";
    char *title2 = "--- D Y R A E   T O   C R K C ? ---";
    char *title3 = "--- Y R D E A   O T   O K O R ? ---";
    int flashes = 1;

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    for (int i = 0; i < flashes; i++) {

        printf("\r\t\t\t\t\t\t\t   \e[0;107m%s\033[0m", title1);
        Sleep(150);
        printf("\r\t\t\t\t\t\t\t   \e[0;92m%s\033[0m", title2);
        Sleep(200);
        printf("\r\t\t\t\t\t\t\t   \e[1;92m%s\033[0m", title3);
        Sleep(150);

    }

    printf("\r\t\t\t\t\t\t\t   %s\033[0m", title);
    printf("\n\n\n\n\n");

}

void loadingScreen() {
    system("cls");
    printFlashingTitle();

    int progress = 0;
    int barWidth = 75;

    printf("\n\t\t\t\t\t\t\t[");
    for (int i = 0; i < barWidth; i++) {
        printf(" ");
    }


    for (progress = 0; progress <= 100; progress += 1) {
        printf("\r\t\t\t\t\t[");
        for (int i = 0; i < barWidth; i++) {
            if (i < (progress * barWidth / 100)) {

                printf("\e[1;92m|");
            } else {

                printf(" ");
            }
        }
        setColor(7);
        printf("]");

        setColor(7);
        printf("%d%%", progress);
        Sleep(5);
    }

    printf("\n\n\n\t\t\t\t\t\t\t\t L O A D I N G   D O N E !\t\t\t\t\n");
    Sleep(10);

}


// --- STRUCTURES ---

typedef struct
{
    int maximum_hp;
    int current_hp;
    int level;
    int experience;
    float gold;
    int attack_multiplier;
    int stun_duration;
} PlayerStats_t;

typedef struct
{
    char name[30];
    int max_hp;
    int damage;
    int experience_value;
} Monster_t;

enum CraftedItemIndex {
    ITEM_LESSER_HEAL, ITEM_MODERATE_HEAL, ITEM_FULL_HEAL,
    ITEM_LESSER_STR, ITEM_MODERATE_STR, ITEM_FULL_STR,
    ITEM_LESSER_STUN, ITEM_MODERATE_STUN, ITEM_FULL_STUN,
    ITEM_RETURN, ITEM_AROMA, ITEM_INTELLIGENCE
};

typedef struct {
    float gold_min;
    float gold_max;

    // Drop chance percentages (0-100) for items in this loot table
    int holy_tears;
    int goblin_eyes;
    int goblin_cloth;
    int orc_blood;
    int orc_meat;
    int cobra_venom;
    int cobra_scales;
    int magic_dust;
    int wraith_skull;
    int wyvern_blood;
    int dragon_blood;
    int xp_gained;

    // --- CRAFTABLE/CONSUMABLE ITEMS (TRACKED BY QUANTITY) ---
    int lesser_healing_potion;
    int moderate_healing_potion;
    int full_healing_potion;

    int lesser_strength_potion;
    int moderate_strength_potion;
    int full_strength_potion;

    int lesser_stun_splash;
    int moderate_stun_splash;
    int full_stun_splash;

    int return_potion;
    int monster_aroma;
    int intelligence_potion;
} Inv_t;

typedef struct {
    char crafted_item_name[50];
    int crafted_item_index; // Index to map to the correct inventory field
    int crafted_item_count;

    // Material costs (0 if not required) - must match Inv_t drop materials
    int holy_tears;
    int goblin_eyes;
    int goblin_cloth;
    int orc_blood;
    int orc_meat;
    int cobra_venom;
    int cobra_scales;
    int magic_dust;
    int wraith_skull;
    int wyvern_blood;
    int dragon_blood;

    // Potions used as crafting ingredients
    int lesser_healing_potion;
    int moderate_healing_potion;
} Recipe_t;

typedef struct
{
    int floor_level;
    const Monster_t *monster_group[3];
    const Monster_t *boss_monster;
    const Inv_t *loot_table;
} DungeonLevel_t;

typedef struct {
    char player_name[50];
    PlayerStats_t stats;
    Inv_t inventory;
} Player_t;

typedef struct {
    char name[30];
    int heal_amount;
    float cost;
} Potion_t;

// --- GLOBAL VARIABLES ---

Player_t g_Player;
const char *SAVE_FILE = "savegame.dat";

// --- MONSTER DEFINITIONS ---
const Monster_t MONSTER_SLIME = {"Baby Slime", 20, 5, 5};
const Monster_t MONSTER_GOBLIN = {"Goblin Grunt", 50, 10, 10};
const Monster_t MONSTER_ORC = {"Orc Raider", 100, 25, 25};

const Monster_t MONSTER_GREATER = {"Greater Slime", 20, 5, 5};
const Monster_t MONSTER_COBRA = {"Cave Cobra", 120, 20, 30};
const Monster_t MONSTER_STONE = {"Stone Golem", 60, 30, 10};

const Monster_t MONSTER_KING = {"King Slime", 150, 30, 40};
const Monster_t MONSTER_WYVERN = {"Elemental Wyvern", 200, 40, 50};
const Monster_t MONSTER_GOLD = {"Gold Golem", 500, 60, 100};

const Monster_t MONSTER_EMPEROR = {"Emperor Slime", 150, 30, 40};
const Monster_t MONSTER_EARTH = {"Earth Dragon", 200, 40, 50};
const Monster_t MONSTER_TITANIUM = {"Titanium Withered Soldier", 500, 60, 100};

const Monster_t MONSTER_SAGE = {"Undead Sage", 150, 0, 40};
const Monster_t MONSTER_SHADOW = {"Shadow Wyvern", 200, 0, 50};
const Monster_t MONSTER_HYDRA = {"Ancient Dragon", 500, 0, 100};

// --- BOSS MONSTER DEFINITIONS ---
const Monster_t BOSS_GATE = {"Geometry Gate", 200, 20, 50};
const Monster_t BOSS_ARCHER = {"Physics Archer", 300, 40, 75};
const Monster_t BOSS_PYTHAGORAS = {"The Bridge of Pythagoras", 600, 70, 150};
const Monster_t BOSS_BOULDER = {"The Heavy Boulder", 500, 800, 500};
const Monster_t BOSS_ARCHITECT = {"M.A.D.Z", 1000, 0, 2500};

// --- LOOT TABLES ---
const Inv_t LOOT_FLOOR1 = {5.0f, 15.0f, 90, 70, 45, 0, 0, 0, 0, 0, 0, 0, 10};
const Inv_t LOOT_FLOOR2 = {15.0f, 30.0f, 0, 0, 0, 80, 60, 35, 0, 0, 0, 0, 25};
const Inv_t LOOT_FLOOR3 = {30.0f, 60.0f, 0, 0, 0, 0, 0, 0, 70, 50, 25, 0, 50};
const Inv_t LOOT_FLOOR4 = {45.0f, 90.0f, 0, 0, 0, 0, 0, 0, 0, 60, 40, 15, 50};
const Inv_t LOOT_FLOOR5 = {60.0f, 120.0f, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 50};

// --- POTION DEFINITIONS (Used in Store/Combat) ---
const Potion_t POTION_LESSER_HEAL = {"Lesser Healing Potion", 50, 25.0f};

// --- RECIPES DEFINITIONS (The 12 Recipes) ---
const Recipe_t RECIPE_L_HEAL = {"Lesser Healing Potion", ITEM_LESSER_HEAL, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_M_HEAL = {"Moderate Healing Potion", ITEM_MODERATE_HEAL, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0};
const Recipe_t RECIPE_F_HEAL = {"Full Healing Potion", ITEM_FULL_HEAL, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1};
const Recipe_t RECIPE_L_STR = {"Lesser Strength Potion (2x Dmg)", ITEM_LESSER_STR, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_M_STR = {"Moderate Strength Potion (3x Dmg)", ITEM_MODERATE_STR, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_F_STR = {"Full Strength Potion (4x Dmg)", ITEM_FULL_STR, 1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_L_STUN = {"Lesser Stun Splash (1 T)", ITEM_LESSER_STUN, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_M_STUN = {"Moderate Stun Splash (2 T)", ITEM_MODERATE_STUN, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_F_STUN = {"Full Stun Splash (3 T)", ITEM_FULL_STUN, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0};
const Recipe_t RECIPE_RETURN = {"Return Potion", ITEM_RETURN, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_AROMA = {"Monster Aroma", ITEM_AROMA, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0};
const Recipe_t RECIPE_INTEL = {"Intelligence Potion", ITEM_INTELLIGENCE, 1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0};


const Recipe_t *g_Recipes[] = {
    &RECIPE_L_HEAL, &RECIPE_M_HEAL, &RECIPE_F_HEAL,
    &RECIPE_L_STR, &RECIPE_M_STR, &RECIPE_F_STR,
    &RECIPE_L_STUN, &RECIPE_M_STUN, &RECIPE_F_STUN,
    &RECIPE_RETURN, &RECIPE_AROMA, &RECIPE_INTEL
};
const int G_NUM_RECIPES = 12;


// --- DUNGEON LEVEL DEFINITIONS ---
const DungeonLevel_t DUNGEON_FLOOR1 = {1, {&MONSTER_GOBLIN, &MONSTER_ORC, &MONSTER_SLIME}, &BOSS_GATE, &LOOT_FLOOR1};
const DungeonLevel_t DUNGEON_FLOOR2 = {2, {&MONSTER_GREATER, &MONSTER_COBRA, &MONSTER_STONE}, &BOSS_ARCHER, &LOOT_FLOOR2};
const DungeonLevel_t DUNGEON_FLOOR3 = {3, {&MONSTER_KING, &MONSTER_WYVERN, &MONSTER_GOLD}, &BOSS_PYTHAGORAS, &LOOT_FLOOR3};
const DungeonLevel_t DUNGEON_FLOOR4 = {4, {&MONSTER_EMPEROR, &MONSTER_EARTH, &MONSTER_TITANIUM}, &BOSS_BOULDER, &LOOT_FLOOR4};
const DungeonLevel_t DUNGEON_FLOOR5 = {5, {&MONSTER_SAGE, &MONSTER_SHADOW, &MONSTER_HYDRA}, &BOSS_ARCHITECT, &LOOT_FLOOR5};

// --- FUNCTION PROTOTYPES ---
void load(int delay_ms);
void initialize_new_game(Player_t *player);
void save_game();
int load_game();
void main_menu();
void TownMenu();
int DungeonMenu();
void FloorLoop(const DungeonLevel_t *dungeon, int aroma_active);
int DungeonFight(const Monster_t *monster, const Inv_t *loot_table);
int GeometryGateFight(int *monster_hp, int player_damage);
int PhysicsArcherFight(int *monster_hp, int player_damage);
void award_loot(const Monster_t *monster, const Inv_t *loot_table);
void check_level_up();
int InventoryMenu();
int PotionStore();
void Church();
void clear_input_buffer();
int timed_input_int(int timeout_sec);

// --- CRAFTING FUNCTION PROTOTYPES (NEW) ---
void display_crafter();
void craft_item(const Recipe_t *recipe);
int check_recipe_requirements(const Recipe_t *recipe);
int UseItemMenu(const Monster_t *monster, int *monster_hp, int player_damage);
int BridgeOfPythagorasFight(int *monster_hp, int player_damage);
int timed_input_string(int timeout_sec, const char *target_string, char *user_buffer);


// --- IMPLEMENTATIONS ---

void load(int delay_ms)
{
    clock_t start = clock();
    while (clock() < start + (delay_ms * CLOCKS_PER_SEC / 1000));
}

void update_timer_display(int remaining_time, const char* input_buffer)
{
    // Use carriage return (\r) to reset the cursor to the beginning of the line.
    // The fixed width padding (%-60s) ensures we fully clear the old line.
    // NOTE: 60 is an estimate; adjust if your window is wider or narrower.
    printf("\r%-60s\r", ""); // Clear the previous line completely

    printf("\t\t\t\tTime Remaining: %d seconds. Answer: %s",
           remaining_time, input_buffer);
    fflush(stdout); // Force the output to display immediately
}

// Returns the integer entered, or -99999 if the time runs out or input is invalid.
int timed_input_int(int timeout_sec)
{
    clock_t start_time = clock();
    char buffer[20] = {0};
    int i = 0;
    int previous_remaining_time = timeout_sec + 1;

    // --- INITIAL PROMPT (Printed ONLY once) ---
    // We print a placeholder line which will be overwritten by the timer display
    update_timer_display(timeout_sec, buffer);

    // Loop continues as long as the elapsed time is less than the timeout
    while (((clock() - start_time) / CLOCKS_PER_SEC) < timeout_sec)
    {
        int time_elapsed = (int)((clock() - start_time) / CLOCKS_PER_SEC);
        int remaining_time = timeout_sec - time_elapsed;

        // --- EFFICIENT VISUAL TIMER LOGIC ---
        // Only update the display when a whole second has passed
        if (remaining_time != previous_remaining_time)
        {
            update_timer_display(remaining_time, buffer);
            previous_remaining_time = remaining_time;
        }

        if (kbhit())
        {
            char c = getch();

            if (c == '\r' || c == '\n') // Enter key pressed (Submission)
            {
                buffer[i] = '\0';
                // Final cleanup before returning
                printf("\r%60s\r\n", "");

                int user_input = -99999;
                if (sscanf(buffer, "%d", &user_input) == 1)
                {
                    return user_input;
                }
                else
                {
                    return -99999;
                }
            }
            else if (c >= '0' && c <= '9' && i < 19)
            {
                // Accept digits and append to buffer
                buffer[i++] = c;
                // Since input changed, update the display immediately (no lag due to fast loop)
                update_timer_display(remaining_time, buffer);
            }
            else if (c == 8 && i > 0) // Backspace
            {
                // Handle backspace: remove character from buffer
                buffer[--i] = '\0';
                // Since input changed, update the display immediately
                update_timer_display(remaining_time, buffer);
            }
        }
    }

    // Time ran out: Final cleanup
    printf("\r%60s\r\n", "");

    return -99999;
}

// Utility function to print the current timer and input buffer
void update_string_timer_display(int remaining_time, const char* input_buffer)
{
    // \r moves cursor back. Use a wide string to clear the previous line.
    // NOTE: Adjust the '80' width if your console window is much wider/narrower.
    printf("\r%-80s\r", "");
    printf("\t\t\t\tTime Remaining: %d seconds. Signature: %s",
           remaining_time, input_buffer);
    fflush(stdout); // Force the output to display immediately
}

// Returns 1 on successful match, 0 on timeout, -1 on incorrect entry.
int timed_input_string(int timeout_sec, const char *target_string, char *user_buffer)
{
    clock_t start_time = clock();

    // Clear the user buffer and set index i
    user_buffer[0] = '\0';
    int i = 0;

    int previous_remaining_time = timeout_sec + 1;

    // --- INITIAL DISPLAY ---
    // Show the initial status (Time remaining and empty buffer)
    update_string_timer_display(timeout_sec, user_buffer);

    // Loop continues as long as the elapsed time is less than the timeout
    while (((clock() - start_time) / CLOCKS_PER_SEC) < timeout_sec)
    {
        int time_elapsed = (int)((clock() - start_time) / CLOCKS_PER_SEC);
        int remaining_time = timeout_sec - time_elapsed;

        // EFFICIENT VISUAL TIMER LOGIC: Only update on a new second
        if (remaining_time != previous_remaining_time)
        {
            update_string_timer_display(remaining_time, user_buffer);
            previous_remaining_time = remaining_time;
        }

        if (kbhit())
        {
            char c = getch();
            size_t target_len = strlen(target_string);

            if (c == '\r' || c == '\n') // Enter key pressed (Submission)
            {
                user_buffer[i] = '\0'; // Null-terminate the string

                // Final cleanup before returning
                printf("\r%80s\r\n", "");

                // Compare entered string with target string
                if (strcmp(user_buffer, target_string) == 0)
                {
                    return 1; // SUCCESS
                }
                else
                {
                    return -1; // INCORRECT ENTRY
                }
            }
            // Check for valid alphanumeric input AND buffer space
            else if (i < (int)target_len &&
                     ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) )
            {
                user_buffer[i++] = c;
                // Update display immediately for responsive typing feedback
                update_string_timer_display(remaining_time, user_buffer);
            }
            else if (c == 8 && i > 0) // Backspace (ASCII 8)
            {
                user_buffer[--i] = '\0';
                // Update display immediately
                update_string_timer_display(remaining_time, user_buffer);
            }
        }
    }

    // Time ran out: Final cleanup
    printf("\r%80s\r\n", "");

    return 0; // TIMEOUT
}

void save_game()
{
    FILE *file = fopen(SAVE_FILE, "wb");
    if (file) {
        fwrite(&g_Player, sizeof(Player_t), 1, file);
        fclose(file);
        setColor(9);
        printf("\n\t\t\t\t\t\t\t       Game saved successfully!\n");
        setColor(7);
    } else {
        printf("\n\t\t\t\t\t\t       Error saving game.\n");
    }
    load(1500);
}

int load_game()
{
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file) {
        fread(&g_Player, sizeof(Player_t), 1, file);
        fclose(file);
        printf("\n\t\t\t\t\t\t\t Game loaded successfully! Welcome back, \e[0;33m%s\033[0m.\n", g_Player.player_name);
        load(1500);
        return 1;
    } else {
        printf("\n\t\t\t\t\t\t\t   No save file found.\n");
        load(1500);
        return 0;
    }
}

/* STARTING BACKSTORY */
void type_text(const char *text, unsigned int delay_microseconds)
{
    for (int i = 0; i < (int)strlen(text); i++)
    {
        putchar(text[i]);
        fflush(stdout);
        usleep(delay_microseconds);
    }
}

/* STARTING BACKSTORY */
void display_story(const char **sentences, int num_sentences, unsigned int char_speed, unsigned int sentence_delay_seconds)
{
    for (int i = 0; i < num_sentences; i++)
    {
        type_text(sentences[i], char_speed);
        sleep(sentence_delay_seconds);
        system("cls");
    }
}

void display_starting_backstory()
{
    const char *sentences[] =
    {
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mIt\'s \e[0;107m\e[1;90myear 147\033[0m which means one hundred forty-seven years have  \n\n\t\t\t\t\t\t  passed since the birth \e[0;107m\e[1;90mof Amos.\033[0m\n",
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mIt also means 147 years have passed since the \e[0;107m\e[1;90mrise of wars\033[0m  \n\n\t\t\t\t\t\t  from the different powerful empires that ruled Amos.\033[0m\n",
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mThese wars were said to transpire all because of a mysterious core  \n\n\t\t\t\t\t\t  that is responsible for holding the planet together and preventing it from \n\n\t\t\t\t\t\t \e[0;107m\e[1;90m extinction.\033[0m\n",
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mThis core is what they called the Aether core which is one of\n\n\t\t\t\t\t\t  the \e[0;107m\e[1;90mrarest cores\033[0m to exist in all planets in the universe.\033[0m\n",
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mThere is no denying on why these powerful empires desire to own it  \n\n\t\t\t\t\t\t  and are willing to \e[0;107m\e[1;90msacrifice hundreds of men\033[0m to search for it.\033[0m\n",
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mTo this day, the core is \e[0;107m\e[0;91mstill not found\033[0m as it is in the deepest  \n\n\t\t\t\t\t\t  \e[0;107m\e[1;90mdungeons of Amos\033[0m to which all of the greatest monsters are located.\033[0m\n",
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mThe aftermath of the war affected the citizens and made them  \n\n\t\t\t\t\t\t  survive through\e[0;107m\e[1;90m witchcraft, potion-making, and offering of sacrifices.\033[0m\n",
        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  \t\e[1;97mAs a \e[0;91mvictim of the war\033[0m, you plan to defeat these monsters and \n\n\t\t\t\t\t\t  take the \e[0;107m\e[1;90mAether core.\033[0m\n"
    };

    int num_sentences = sizeof(sentences) / sizeof(sentences[0]);
    unsigned int char_speed = 40000;
    unsigned int sentence_delay_seconds = 3;

    display_story(sentences, num_sentences, char_speed, sentence_delay_seconds);

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tPress any key to continue . . .\n");
    getch();
}

void initialize_new_game(Player_t *player)
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t  Enter your Adventurer's name: ");
    scanf("%49s", player->player_name);

    player->stats.level = 1;
    player->stats.experience = 0;
    player->stats.maximum_hp = 100;
    player->stats.current_hp = 100;
    player->stats.gold = 50.0f;
    // SET NEW STATS
    player->stats.attack_multiplier = 1;
    player->stats.stun_duration = 0;

    memset(&(player->inventory), 0, sizeof(Inv_t));
    // Player starts with one Lesser Healing Potion
    player->inventory.lesser_healing_potion = 1;
    player->inventory.return_potion = 10;

    printf("\n\t\t\t\t\t\t\t  Welcome, %s! Your journey begins.\n", player->player_name);
    load(1500);

    system("cls");

    display_starting_backstory();
}

void main_menu()
{
    int choices = 0;
    int press;
    int has_save = 0;
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file) {
        has_save = 1;
        fclose(file);
    }
    const int max_choices = has_save ? 2 : 1;
    int confirm_quit = 0;
    int confirm_choice = 0; // 0 for Yes, 1 for No

    while(1)
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t    \e[0;95m===================================");
        printf("\n\t\t\t\t\t\t\t    ============ \e[1;93mMain Menu \033[0m\e[1;95m============\033[0m");
        printf("\n\t\t\t\t\t\t\t    \e[0;95m===================================\033[0m\n");
        printf("\t\t\t\t\t\t\t    \e[0;93m-----------------------------------\033[0m\t\t\t\t\t\n\n");

        if (!confirm_quit) {
            if (choices == 0) {
                printf("\t\t\t\t\t\t\t\t  \e[0;92m>> New Game\n\033[0m");
            } else {
                printf("\t\t\t\t\t\t\t\t      New Game\n");
            }
            if (has_save) {
                if (choices == 1) {
                    setColor(1);
                    printf("\t\t\t\t\t\t\t\t  >> Load Game\n");
                    setColor(7);
                } else {
                    printf("\t\t\t\t\t\t\t\t      Load Game\n");
                }
            }
            if (choices == max_choices) {
                setColor(12);
                printf("\t\t\t\t\t\t\t\t  >> Quit\n");
                setColor(7);
            } else {
                printf("\t\t\t\t\t\t\t\t      Quit\n");
            }
            printf("\n\n\t\t\t\t\t\t\t    \e[1;33m-----------------------------------\033[0m\n");
        } else {
            printf("\t\t\t\t\t\t\t     \e[0;31mAre you sure you want to quit?\033[0m\n\n");
            if (confirm_choice == 0) {
                printf("\t\t\t\t\t\t\t     \e[0;31m>> Yes\033[0m\n");
                printf("\t\t\t\t\t\t\t         No\n");
            } else {
                printf("\t\t\t\t\t\t\t         Yes\n");
                printf("\t\t\t\t\t\t\t     >> No\n");
            }
                printf("\t\t\t\t\t\t\t    \e[1;33m-----------------------------------\033[0m");
        }

        press = getch();

        if (!confirm_quit) {
            if (press == 0 || press == 224) {
                press = getch();
                if (press == 72) choices = (choices == 0) ? max_choices : choices - 1;
                else if (press == 80) choices = (choices == max_choices) ? 0 : choices + 1;
            } else if (press == '\r') {
                if (choices == 0) {
                    initialize_new_game(&g_Player);
                    TownMenu();
                } else if (choices == 1 && has_save) {
                    if (load_game()) {
                        TownMenu();
                    }
                } else if (choices == max_choices) {
                    confirm_quit = 1;
                    confirm_choice = 0;
                }
            }
        } else {
            if (press == 0 || press == 224) {
                press = getch();
                if (press == 72) confirm_choice = (confirm_choice == 0) ? 1 : 0;
                else if (press == 80) confirm_choice = (confirm_choice == 1) ? 0 : 1;
            } else if (press == '\r') {
                if (confirm_choice == 0) {
                    exit(0);
                } else {
                    confirm_quit = 0;
                }
            }
        }
    }
}


void TownMenu()
{
    int choices = 0;
    int press;

    while(1)
    {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t  \e[0;95m==================================");
        printf("\n\t\t\t\t\t\t\t  \e[0;95m============\033[0m \e[0;93mTown Menu\033[0m \e[0;95m===========");
        printf("\n\t\t\t\t\t\t\t  \e[0;95m==================================\033[0m\n");
        printf("\t\t\t\t\t\t\t  \e[0;93m----------------------------------\033[0m\n");
        // RETAINED NEW UI FOR STATS
        printf("\t\t\t\t\t\t\t\t%s - Level %d\n", g_Player.player_name, g_Player.stats.level);
        printf("\t\t\t\t\t\t\t\t\e[0;32mHP: %d/%d\033[0m | \e[0;93mGold: %.2f\033[0m\n", g_Player.stats.current_hp, g_Player.stats.maximum_hp, g_Player.stats.gold);
        printf("\t\t\t\t\t\t\t  \e[0;93m----------------------------------\033[0m\n");

        if (choices == 0){
            printf("\t\t\t\t\t\t\t  \e[0;34m>> Enter Dungeon\033[0m\n");

        } else {
            printf("\t\t\t\t\t\t\t      Enter Dungeon\n");
        }

        if (choices == 1) {

            printf("\t\t\t\t\t\t\t  \e[0;36m>> Visit Potion Store\033[0m\n");


        } else {
            printf("\t\t\t\t\t\t\t      Visit Potion Store\n");
        }

        if (choices == 2){
            printf("\t\t\t\t\t\t\t  \e[0;35m>> Crafting Bench\033[0m\n");

         } else {
             printf("\t\t\t\t\t\t\t      Crafting Bench\n");
         }

        if (choices == 3){
            printf("\t\t\t\t\t\t\t  \e[0;92m>> Visit Church (Heal HP)\033[0m\n");

         } else {
             printf("\t\t\t\t\t\t\t      Visit Church (Heal HP)\n");
         }

        if (choices == 4){

            printf("\t\t\t\t\t\t\t  >> Inventory\n");

        } else {
            printf("\t\t\t\t\t\t\t      Inventory\n");
        }
        // Restored Save & Exit/Home Menu flow
        if (choices == 5){

            printf("\t\t\t\t\t\t\t  \e[0;94m>> Save Game\033[0m\n");


        } else {
            printf("\t\t\t\t\t\t\t      Save Game\n");
        }

        if (choices == 6){

            printf("\t\t\t\t\t\t\t  \e[0;91m>> Exit to Main Menu\033[0m\n");

        } else {
            printf("\t\t\t\t\t\t\t      Exit to Main Menu\n");
        }

        printf("\t\t\t\t\t\t\t  \e[0;93m---------------------------------\033[0m");

        press = getch();

        if (press == 0 || press == 224) {
            press = getch();
            if (press == 72) choices = (choices == 0) ? 6 : choices - 1; // Up arrow (0 to 6)
            else if (press == 80) choices = (choices == 6) ? 0 : choices + 1; // Down arrow (6 to 0)
        } else if (press == '\r') { // Enter key
            if (choices == 0) DungeonMenu();
            else if (choices == 1) PotionStore();
            else if (choices == 2) display_crafter();
            else if (choices == 3) Church();
            else if (choices == 4) InventoryMenu();
            else if (choices == 5) save_game();
            else if (choices == 6) main_menu(); // Return to Main Menu
        }
    }
}

void Church()
{
    float heal_cost = (g_Player.stats.maximum_hp - g_Player.stats.current_hp) * 0.5f;
    int press;

    while(1)
    {
        system("cls");
        printf("\n\n\n\t\t\t\t\t\t=== The Church ===\n\n");
        printf("\t\t\t\t\t\tCurrent HP: %d/%d\n", g_Player.stats.current_hp, g_Player.stats.maximum_hp);
        printf("\t\t\t\t\t\tCurrent Gold: %.2f\n", g_Player.stats.gold);
        printf("\t\t\t\t\t      ------------------------\n\n");

        if (g_Player.stats.current_hp == g_Player.stats.maximum_hp)
        {
            printf("\t\t\t\t\t   \e[0;32mYou are perfectly healthy, child.\n\e[0m");
            printf("\n\t\t\t\t\t   [4] Go Back\n");
        }
        else
        {
            printf("\t\t\t\t\t[1] Fully Heal (Cost: %.2f Gold)\n", heal_cost);
            printf("\t\t\t\t\t[4] Go Back\n");
        }

        press = getch();

        if (press == '1' && g_Player.stats.current_hp < g_Player.stats.maximum_hp)
        {
            if (g_Player.stats.gold >= heal_cost)
            {
                g_Player.stats.gold -= heal_cost;
                g_Player.stats.current_hp = g_Player.stats.maximum_hp;
                setColor(10);
                printf("\n\t\t\t\t\tYou have been healed by divine light!\n");
                setColor(7);
                getch();
                return; // Return to Town Menu
            }
            else
            {
                printf("\n\t\t\t\t\tYou do not have enough gold to pay for a full healing.\n");
                getch();
            }
        }
        else if (press == '4')
        {
            return; // Go Back to Town Menu
        }
    }
}

int PotionStore()
{
    int press;
    int buy_amount = 1;
    // Uses the new Lesser Healing Potion definition
    const Potion_t *potion = &POTION_LESSER_HEAL;
    float total_cost;

    while(1)
    {
        total_cost = potion->cost * buy_amount;
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t\t\t\t  \e[0;95m==================================\033[0m");
        printf("\n\t\t\t\t\t\t\t\t      \e[0;96mPotion Store\033[0m ");
        printf("\n\t\t\t\t\t\t\t  \e[0;95m==================================\033[0m");
        printf("\n\t\t\t\t\t\t\t\t  \e[1;93mCurrent Gold: %.2f\033[0m\n", g_Player.stats.gold);
        printf("\n\t\t\t\t\t\t\t\t  \e[1;92mPotions Held: %d\033[0m\n", g_Player.inventory.lesser_healing_potion);
        printf("\n\t\t\t\t\t\t\t  \e[0;95m==================================\033[0m\n\n");

        printf("\t\t\t\t\t\t\t [1] Buy %d %s (Heals %d HP)\n", buy_amount, potion->name, potion->heal_amount);
        printf("\t\t\t\t\t\t\t Cost: %.2f Gold\n", total_cost);
        printf("\t\t\t\t\t\t\t [2] Buy x5\n");
        printf("\t\t\t\t\t\t\t [3] Buy x10\n");
        printf("\t\t\t\t\t\t\t [4] Go Back\n");

        press = getch();

        if (press == '1') // Buy Potion
        {
            if (g_Player.stats.gold >= total_cost)
            {
                g_Player.stats.gold -= total_cost;
                // Uses the new inventory field
                g_Player.inventory.lesser_healing_potion += buy_amount;
                printf("\n\t\t\t\t\t\t\t \e[0;33mPurchased %d %s!\n", buy_amount, potion->name);
                buy_amount = 1; // Reset quantity
                getch();
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t \e[1;31mNot enough gold!\n");
                getch();
            }
        }
        else if (press == '2') // Set quantity to 5
        {
            buy_amount = 5;
        }
        else if (press == '3') // Set quantity to 10
        {
            buy_amount = 10;
        }
        else if (press == '4') // Go Back
        {
            return 0;
        }
    }
}

int InventoryMenu()
{
    int press;
    Inv_t *inv = &g_Player.inventory;

    while (1)
    {
        system("cls");
        setColor(13);
        printf("\n\n\n\t\t\t\t\t\t\t=== Inventory ===\n");
        setColor(7);
        printf("\t\t\t\t\t\t\t\e[1;31m%s - Level %d\n\e[0m", g_Player.player_name, g_Player.stats.level);
        printf("\t\t\t\t\t\t\t\e[0;31m\e[43mGold: %.2f\n\e[0m", g_Player.stats.gold);
        printf("\t\t\t\t\t\t   --------------------------\n");

        setColor(13);
        printf("\t\t\t\t\t\t\t--- Potions ---\n");
        setColor(7);
        if (inv->lesser_healing_potion > 0) printf("\t\t\t\t\t\t\tLesser HP: x%d\n", inv->lesser_healing_potion);
        if (inv->moderate_healing_potion > 0) printf("\t\t\t\t\t\t\tModerate HP: x%d\n", inv->moderate_healing_potion);
        if (inv->full_healing_potion > 0) printf("\t\t\t\t\t\t\tFull HP: x%d\n", inv->full_healing_potion);
        if (inv->lesser_strength_potion > 0) printf("\t\t\t\t\t\t\tLesser Strength: x%d\n", inv->lesser_strength_potion);
        if (inv->moderate_strength_potion > 0) printf("\t\t\t\t\t\t\tModerate Strength: x%d\n", inv->moderate_strength_potion);
        if (inv->full_strength_potion > 0) printf("\t\t\t\t\t\t\tFull Strength: x%d\n", inv->full_strength_potion);
        if (inv->lesser_stun_splash > 0) printf("\t\t\t\t\t\t\tLesser Stun: x%d\n", inv->lesser_stun_splash);
        if (inv->moderate_stun_splash > 0) printf("\t\t\t\t\t\t\tModerate Stun: x%d\n", inv->moderate_stun_splash);
        if (inv->full_stun_splash > 0) printf("\t\t\t\t\t\t\tFull Stun: x%d\n", inv->full_stun_splash);
        if (inv->return_potion > 0) printf("\t\t\t\t\t\t\tReturn Potion: x%d\n", inv->return_potion);
        if (inv->monster_aroma > 0) printf("\t\t\t\t\t\t\tMonster Aroma: x%d\n", inv->monster_aroma);
        if (inv->intelligence_potion > 0) printf("\t\t\t\t\t\t\tIntelligence Potion: x%d\n", inv->intelligence_potion);

        setColor(13);
        printf("\t\t\t\t\t\t\t--- Materials ---\n");
        setColor(7);
        if (inv->holy_tears > 0) printf("\t\t\t\t\t\t\tHoly Tears: x%d\n", inv->holy_tears);
        if (inv->goblin_eyes > 0) printf("\t\t\t\t\t\t\tGoblin Eyes: x%d\n", inv->goblin_eyes);
        if (inv->goblin_cloth > 0) printf("\t\t\t\t\t\t\tGoblin Cloth: x%d\n", inv->goblin_cloth);
        if (inv->orc_blood > 0) printf("\t\t\t\t\t\t\tOrc Blood: x%d\n", inv->orc_blood);
        if (inv->orc_meat > 0) printf("\t\t\t\t\t\t\tOrc Meat: x%d\n", inv->orc_meat);
        if (inv->cobra_venom > 0) printf("\t\t\t\t\t\t\tCobra Venom: x%d\n", inv->cobra_venom);
        if (inv->cobra_scales > 0) printf("\t\t\t\t\t\t\tCobra Scales: x%d\n", inv->cobra_scales);
        if (inv->magic_dust > 0) printf("\t\t\t\t\t\t\tMagic Dust: x%d\n", inv->magic_dust);
        if (inv->wraith_skull > 0) printf("\t\t\t\t\t\t\tWraith Skull: x%d\n", inv->wraith_skull);
        if (inv->wyvern_blood > 0) printf("\t\t\t\t\t\t\tWyvern Blood: x%d\n", inv->wyvern_blood);
        if (inv->dragon_blood > 0) printf("\t\t\t\t\t\t\tDragon Blood: x%d\n", inv->dragon_blood);

        printf("\t\t\t\t\t\t   --------------------------\n");
        printf("\t\t\t\t\t\t\t[4] Go Back\n");

        press = getch();
        if (press == '4')
        {
            return 0;
        }
    }
}

int DungeonMenu()
{
    const DungeonLevel_t *dungeon_floors[] = {&DUNGEON_FLOOR1, &DUNGEON_FLOOR2, &DUNGEON_FLOOR3, &DUNGEON_FLOOR4, &DUNGEON_FLOOR5};
    const int num_dungeon_floors = 5;
    int choices = 0;
    int press;
    int aroma_active = 0;
    const int max_choices = num_dungeon_floors; // Floor choices (0, 1, 2) + Go Back (3)

    while(1)
    {
        system("cls");
      printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t  ==================================");
        setColor(4);
        printf("\n\t\t\t\t\t\t\t  ======== Dungeon Entrance ========");
        setColor(7);
        printf("\n\t\t\t\t\t\t\t  ==================================\n");
        printf("\t\t\t\t\t\t\t  ----------------------------------\n");
        // RETAINED NEW UI FOR STATS

        for (int i = 0; i < num_dungeon_floors; i++)
        {
            if (choices == i)
                printf("\t\t\t\t\t\t\t\e[0;31m  >> Floor %d: %s\e[0m\n", dungeon_floors[i]->floor_level, dungeon_floors[i]->boss_monster->name);
            else
                printf("\t\t\t\t\t\t\t      Floor %d: %s\n", dungeon_floors[i]->floor_level, dungeon_floors[i]->boss_monster->name);
        }

        // Option to use Monster Aroma
        if (g_Player.inventory.monster_aroma > 0)
        {
            if (aroma_active)
                printf("\t\t\t\t\t\t[A] Monster Aroma is **ACTIVE** (x%d remaining)\n", g_Player.inventory.monster_aroma);
            else
                printf("\t\t\t\t\t\t[A] Use Monster Aroma (x%d) for a tougher challenge?\n", g_Player.inventory.monster_aroma);
        }

        // Go Back option
        if (choices == max_choices)
            printf("\t\t\t\t\t\t\t  >> Home (Go Back to Town)\n"); // Restored 'Home' feel
        else
            printf("\t\t\t\t\t\t\t      Home (Go Back to Town)\n");

        printf("\t\t\t\t\t\t\t  ---------------------------------\n");

        press = getch();

        if (press == 0 || press == 224) {
            press = getch();
            if (press == 72) choices = (choices == 0) ? max_choices : choices - 1;
            else if (press == 80) choices = (choices == max_choices) ? 0 : choices + 1;
        }
        else if (press == 'a' || press == 'A') // Monster Aroma Activation
        {
            if (g_Player.inventory.monster_aroma > 0 && !aroma_active)
            {
                g_Player.inventory.monster_aroma--;
                aroma_active = 1;
                printf("\n\t\t\t\tA powerful scent fills the air... Prepare for a tougher challenge!\n");
                load(1000);
            }
            else if (aroma_active)
            {
                printf("\n\t\t\t\tMonster Aroma is already active for this run!\n");
                getch();
            }
            else
            {
                printf("\n\t\t\t\tYou have no Monster Aroma potions!\n");
                getch();
            }
        }
        else if (press == '\r') // Enter Key
        {
            if (choices == max_choices)
                return 0; // Go Back to TownMenu
            else
            {
                FloorLoop(dungeon_floors[choices], aroma_active);
                aroma_active = 0; // Reset aroma after the loop finishes
            }
        }
    }
}

void FloorLoop(const DungeonLevel_t *dungeon, int aroma_active)
{
    char press;
    int win_status;

    // Set floor 1 seed constraint
    if (dungeon->floor_level == 1)
    {
        // Limiting the time seed by modulo 99 to influence the initial random numbers
        srand(time(NULL) % 99);
    }
    else
    {
        srand(time(NULL));
    }

    // --- PART 1: MOB ENCOUNTERS ---
    for (int i = 0; i < 3; i++)
    {
        int mob_index = rand() % 3;
        const Monster_t *mob = dungeon->monster_group[mob_index];
        system("cls");

        Monster_t modified_mob = *mob;
        if (aroma_active)
        {
            modified_mob.max_hp = (int)(modified_mob.max_hp * 1.5);
            modified_mob.damage = (int)(modified_mob.damage * 1.5);
            modified_mob.experience_value = (int)(modified_mob.experience_value * 1.5);
        }

        win_status = DungeonFight(&modified_mob, dungeon->loot_table);

        if (win_status == 0)
        {
            return;
        }

        printf("\n\t\t\t\t\t\t\t \e[0;35mPress any key to continue exploring...\033[0m\n\n");
        getch();
    }

    // --- PART 2: BOSS ENCOUNTER ---
    printf("\n\t\t\t\t\t\t\t You have reached the Boss of Floor %d: %s!\n", dungeon->floor_level, dungeon->boss_monster->name);

    // --- Return Potion Check (Utility) ---
    if (g_Player.inventory.return_potion > 0)
    {
        printf("\n\t\t\t\t\t\t\t You sense the Boss's overwhelming power! You have a Return Potion (x%d).\n", g_Player.inventory.return_potion);
        printf("\n\t\t\t\t\t\t\t Use it to retreat? (U - Use / Any key - Face Boss)\n");
        press = getch();

        if (press == 'u' || press == 'U')
        {
            g_Player.inventory.return_potion--;
            printf("\n\t\t\t\t\t\t\t   You shattered the potion, teleporting back to town!\n");
            getch();
            return; // Exit FloorLoop
        }
    }

    // Boss fight setup (adjust boss stats if aroma is active)
    Monster_t modified_boss = *dungeon->boss_monster;
    if (aroma_active)
    {
        modified_boss.max_hp = (int)(modified_boss.max_hp * 1.5);
        modified_boss.damage = (int)(modified_boss.damage * 1.5);
        modified_boss.experience_value = (int)(modified_boss.experience_value * 1.5);
    }

    win_status = DungeonFight(&modified_boss, dungeon->loot_table);

    if (win_status == 1)
    {
        printf("\n\t\t\t\t\t\t\t   You have cleared Floor %d!\n", dungeon->floor_level);
        srand(time(NULL));
    }
    else
    {
        // Lost or Ran away (Game Over handled in DungeonFight)
    }
    printf("\n\t\t\t\t\t\t\t   Press any key to return to town...");
    getch();
}

int GeometryGateFight(int *monster_hp, int player_damage)
{
    // Constants for the fight
    const int TIMEOUT = 10;
    const int GATE_PENALTY_DAMAGE = 15;

    int num1, num2, correct_answer;
    int user_answer; // Use user_answer to hold the result from timed_input_int

    num1 = (rand() % 8) + 2;
    num2 = (rand() % 8) + 2;
    correct_answer = num1 * num2;

    printf("\n\t\t\t\t\t\t\t   >>> GEOMETRY GATE CHALLENGE <<<\n");
    printf("\t\t\t\t\t\t\t What is the **Area** of a rectangle with sides %d and %d?\n", num1, num2);

    // Intelligence Potion Hint Logic
    if (g_Player.inventory.intelligence_potion > 0)
    {
        printf("\t\t\t\t\t\t\t [HINT] The answer is %d. (Potion will be used on next successful attack)\n", correct_answer);
    }

    // --- TIMER IMPLEMENTATION START ---

    printf("\t\t\t\tAnswer: ");
    user_answer = timed_input_int(TIMEOUT); // Call the timed input function

    // --- TIMER IMPLEMENTATION END ---

    if (user_answer == correct_answer)
    {
        system("cls");
        *monster_hp -= player_damage;
        printf("\n\t\t\t\t**CORRECT!** You struck the gate for %d damage!\n", player_damage);
        load(1000);

        // Consume Intelligence Potion if used successfully
        if (g_Player.inventory.intelligence_potion > 0)
        {
            g_Player.inventory.intelligence_potion--;
            printf("\t\t\t\tIntelligence Potion consumed.\n");
        }
        return 1;
    }
    else // Handles Incorrect Answer, Timeout, or Invalid Input
    {
        int damage_taken = GATE_PENALTY_DAMAGE;
        g_Player.stats.current_hp -= damage_taken;

        if (user_answer == -99999) // Check for timeout/invalid input flag
            printf("\n\t\t\t\t**TIME OUT/INVALID INPUT!** The Gate punishes your delay and strikes you for %d damage!\n", damage_taken);
        else
            printf("\n\t\t\t\t**INCORRECT!** The Gate retaliates and strikes you for %d damage!\n", damage_taken);

        return 1;
    }
}

int PhysicsArcherFight(int *monster_hp, int player_damage)
{
    // Variables for the physics problem (a simple calculation)
    float distance, speed;
    int time_to_hit_archery_target;
    int user_answer;
    const int TIMEOUT = 10;
    const int ARCHER_PENALTY_DAMAGE = 20; // Slightly higher penalty than the Gate

    // Problem Setup: Simple Distance = Speed * Time
    distance = (float)((rand() % 41) + 10); // Distance between 10 and 50 meters
    speed = (float)((rand() % 5) + 5);      // Speed between 5 and 9 m/s

    // Calculate the correct time (answer)
    // Time = Distance / Speed. We'll round the answer down to an integer for simplicity.
    time_to_hit_archery_target = (int)floor(distance / speed);

    printf("\n\t\t\t\t>>> PHYSICS ARCHER CHALLENGE <<<\n");
    printf("\t\t\t\tThe Archer fires an arrow at you from %.2f meters away.\n", distance);
    printf("\t\t\t\tIf the arrow travels at %.2f m/s, how many **whole seconds** do you have to dodge?\n", speed);

    // Hint for Intelligence Potion
    if (g_Player.inventory.intelligence_potion > 0)
    {
        printf("\t\t\t\t[HINT] The answer (rounded down) is %d. (Potion will be used on next successful hit)\n", time_to_hit_archery_target);
    }

    printf("\t\t\t\tAnswer (in whole seconds): ");
    user_answer = timed_input_int(TIMEOUT);

    if (user_answer == time_to_hit_archery_target)
    {
        *monster_hp -= player_damage;
        printf("\n\t\t\t\t**SUCCESS!** You calculated the flight time and dodged perfectly!\n");
        printf("\t\t\t\tYou countered the Archer for %d damage!\n", player_damage);

        if (g_Player.inventory.intelligence_potion > 0)
        {
            g_Player.inventory.intelligence_potion--;
            printf("\t\t\t\tIntelligence Potion consumed.\n");
        }
        return 1; // Turn consumed, successful action
    }
    else
    {
        int damage_taken = ARCHER_PENALTY_DAMAGE;
        g_Player.stats.current_hp -= damage_taken;

        if (user_answer == -99999)
            printf("\n\t\t\t\t**TIME OUT/INVALID INPUT!** You hesitated and the arrow struck you for %d damage!\n", damage_taken);
        else
            printf("\n\t\t\t\t**INCORRECT!** You miscalculated the arc and were hit for %d damage!\n", damage_taken);

        return 1; // Turn consumed, failed action (took damage)
    }
}

int BridgeOfPythagorasFight(int *monster_hp, int player_damage)
{
    // Constants using const int, as you preferred
    const int TIMEOUT = 10;
    const int BRIDGE_PENALTY_DAMAGE = 25;

    int a = (rand() % 10) + 25; // Leg a between 3 and 7
    int b = (rand() % 10) + 25; // Leg b between 3 and 7
    double c_squared = (double)(a * a) + (double)(b * b);
    int correct_answer = (int)round(sqrt(c_squared));
    int user_answer;

    printf("\n\t\t\t\t>>> BRIDGE OF PYTHAGORAS CHALLENGE <<<\n");
    printf("\t\t\t\tThe missing plank has legs a = %d and b = %d.\n", a, b);
    printf("\t\t\t\tWhat is the hypotenuse (c) **rounded to the nearest whole number**?\n");

    if (g_Player.inventory.intelligence_potion > 0)
    {
        printf("\t\t\t\t[HINT] The answer (rounded) is %d. (Potion will be used on next successful hit)\n", correct_answer);
    }

    printf("\t\t\t\tAnswer (rounded): ");
    user_answer = timed_input_int(TIMEOUT);

    if (user_answer == correct_answer)
    {
        *monster_hp -= player_damage;
        printf("\n\t\t\t\t**PERFECT FIT!** The plank snaps into place, striking the Bridge for %d damage!\n", player_damage);

        if (g_Player.inventory.intelligence_potion > 0)
        {
            g_Player.inventory.intelligence_potion--;
            printf("\t\t\t\tIntelligence Potion consumed.\n");
        }
        return 1;
    }
    else
    {
        int damage_taken = BRIDGE_PENALTY_DAMAGE;
        g_Player.stats.current_hp -= damage_taken;

        if (user_answer == -99999)
            printf("\n\t\t\t\t**TIME OUT/INVALID INPUT!** The bridge crumbles, dealing %d damage!\n", damage_taken);
        else
            printf("\n\t\t\t\t**INCORRECT!** You measured wrong and were hit for %d damage!\n", damage_taken);

        return 1;
    }
}

int HeavyBoulderFight(int *monster_hp, int player_damage)
{
    // Constants for the fight
    const int TIMEOUT = 10;
    const int BOULDER_PENALTY_DAMAGE = 35; // High penalty for the final challenge

    // Problem Setup: F = ma => a = F/m
    float force;
    float mass;
    int correct_answer;
    int user_answer;

    // Generate Force (F) between 50 and 150 Newtons
    force = (float)((rand() % 101) + 50);
    // Generate Mass (m) between 5 and 15 kg
    mass = (float)((rand() % 11) + 5);

    // Calculate the correct acceleration (a = F/m)
    double acceleration = (double)force / (double)mass;

    // The correct answer is the acceleration rounded to the nearest integer
    correct_answer = (int)round(acceleration);

    printf("\n\t\t\t\t>>> HEAVY BOULDER CHALLENGE <<<\n");
    printf("\t\t\t\tA massive boulder with a mass of %.2f kg blocks your path.\n", mass);
    printf("\t\t\t\tIf you apply a force of %.2f Newtons, what is the resulting acceleration (a = F/m)?\n", force);
    printf("\t\t\t\tProvide the answer **rounded to the nearest whole number** (in m/s^2).\n");


    // Hint for Intelligence Potion
    if (g_Player.inventory.intelligence_potion > 0)
    {
        printf("\t\t\t\t[HINT] The answer (rounded) is %d. (Potion will be used on next successful hit)\n", correct_answer);
    }

    printf("\t\t\t\tAnswer (rounded): ");
    user_answer = timed_input_int(TIMEOUT);

    if (user_answer == correct_answer)
    {
        *monster_hp -= player_damage;
        printf("\n\t\t\t\t**SUCCESS!** You calculated the acceleration and pushed the Boulder off its track for %d damage!\n", player_damage);

        if (g_Player.inventory.intelligence_potion > 0)
        {
            g_Player.inventory.intelligence_potion--;
            printf("\t\t\t\tIntelligence Potion consumed.\n");
        }
        return 1; // Turn consumed, successful action
    }
    else
    {
        int damage_taken = BOULDER_PENALTY_DAMAGE;
        g_Player.stats.current_hp -= damage_taken;

        if (user_answer == -99999)
            printf("\n\t\t\t\t**TIME OUT/INVALID INPUT!** The Boulder rolls over you, dealing %d damage!\n", damage_taken);
        else
            printf("\n\t\t\t\t**INCORRECT!** You calculated wrong and the Boulder crushed you for %d damage!\n", damage_taken);

        return 1; // Turn consumed, failed action (took damage)
    }
}

// Utility function to generate a random alphanumeric string
void generate_random_signature(char *buffer, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < length; i++) {
        int index = rand() % (sizeof(charset) - 1);
        buffer[i] = charset[index];
    }
    buffer[length] = '\0';
}


int FinalBossFight(int *monster_hp, int player_damage)
{
    const int TIMEOUT = 8; // Very high pressure, 7 seconds
    const int SENTINEL_PENALTY_DAMAGE = 40;
    const int SIG_LENGTH = 10; // Length of the required string

    char required_signature[SIG_LENGTH + 1];
    char user_input_buffer[SIG_LENGTH + 1];
    int result;

    // 1. Generate the random string the player must type
    generate_random_signature(required_signature, SIG_LENGTH);

    printf("\n\t\t\t\t>>> Malicious Analytic Data Zero (M.A.D.Z) (KERNEL DDoS BLOCK) <<<\n");
    printf("\t\t\t\tM.A.D.Z is initiating a Kernel DDoS! Block the attack NOW!\n");
    printf("\t\t\t\tYou must exactly type the following signature before the timer runs out:\n");

    // Display the target string clearly
    printf("\t\t\t\t[SIGNATURE]: **%s**\n\n", required_signature);


    // Hint for Intelligence Potion
    if (g_Player.inventory.intelligence_potion > 0)
    {
        printf("\t\t\t\t[HINT] The answer is the signature itself. (Potion will be used on next successful hit)\n");
    }

    // 2. Call the new timed input string function
    result = timed_input_string(TIMEOUT, required_signature, user_input_buffer);

    if (result == 1) // SUCCESS: String typed correctly
    {
        *monster_hp -= player_damage;
        printf("\n\t\t\t\t**BLOCK SUCCESSFUL!** You diverted the DDoS, hitting the Sentinel for %d damage!\n", player_damage);
        load(1000);

        if (g_Player.inventory.intelligence_potion > 0)
        {
            g_Player.inventory.intelligence_potion--;
            printf("\t\t\t\tIntelligence Potion consumed.\n");
        }
        return 1; // Turn consumed, successful action
    }
    else // FAILURE: Timeout or Incorrect Entry
    {
        int damage_taken = SENTINEL_PENALTY_DAMAGE;
        g_Player.stats.current_hp -= damage_taken;

        if (result == 0)
        {// Timeout
            printf("\n\t\t\t\t**DDOS FAILURE!** The attack penetrates, striking you for %d damage!\n", damage_taken);
            load(1000);
        }
        else
        {// Incorrect Entry
            printf("\n\t\t\t\t**INCORRECT SIGNATURE!** The Sentinel retaliates for %d damage!\n", damage_taken);
            load(1000);
        }
        return 1; // Turn consumed, failed action (took damage)
    }
}

void award_loot(const Monster_t *monster, const Inv_t *loot_table)
{
    Inv_t *inv = &g_Player.inventory;
    float gold_earned = (float)(rand() % (int)(loot_table->gold_max * 100 - loot_table->gold_min * 100 + 1) + loot_table->gold_min * 100) / 100.0f;
    g_Player.stats.gold += gold_earned;
    printf("\n\t\t\t\t\t\t\t   Gained %.2f Gold.\n", gold_earned);

    int xp_gained = monster->experience_value;
    if (loot_table->xp_gained > 0 && rand() % 100 < loot_table->xp_gained)
    {
        xp_gained = (int)(xp_gained * 1.5);
    }
    g_Player.stats.experience += xp_gained;
    printf("\t\t\t\t\t\t\t   Gained %d XP.\n", xp_gained);
    check_level_up();

    // Materials
    if (loot_table->holy_tears > 0 && rand() % 100 < loot_table->holy_tears) inv->holy_tears += 1;
    if (loot_table->goblin_eyes > 0 && rand() % 100 < loot_table->goblin_eyes) inv->goblin_eyes += 1;
    if (loot_table->goblin_cloth > 0 && rand() % 100 < loot_table->goblin_cloth) inv->goblin_cloth += 1;
    if (loot_table->orc_blood > 0 && rand() % 100 < loot_table->orc_blood) inv->orc_blood += 1;
    if (loot_table->orc_meat > 0 && rand() % 100 < loot_table->orc_meat) inv->orc_meat += 1;
    if (loot_table->cobra_venom > 0 && rand() % 100 < loot_table->cobra_venom) inv->cobra_venom += 1;
    if (loot_table->cobra_scales > 0 && rand() % 100 < loot_table->cobra_scales) inv->cobra_scales += 1;
    if (loot_table->magic_dust > 0 && rand() % 100 < loot_table->magic_dust) inv->magic_dust += 1;
    if (loot_table->wraith_skull > 0 && rand() % 100 < loot_table->wraith_skull) inv->wraith_skull += 1;
    if (loot_table->wyvern_blood > 0 && rand() % 100 < loot_table->wyvern_blood) inv->wyvern_blood += 1;
    if (loot_table->dragon_blood > 0 && rand() % 100 < loot_table->dragon_blood) inv->dragon_blood += 1;

    printf("\t\t\t\t\t\t\t   Loot collected.\n");
}

void check_level_up()
{
    int required_xp = g_Player.stats.level * 100;
    while (g_Player.stats.experience >= required_xp)
    {
        g_Player.stats.level++;
        g_Player.stats.experience -= required_xp;
        g_Player.stats.maximum_hp += 20;
        g_Player.stats.current_hp = g_Player.stats.maximum_hp;

        printf("\n\t\t\t\t*** LEVEL UP! ***\n");
        printf("\t\t\t\tYou are now Level %d! HP fully restored and increased.\n", g_Player.stats.level);
        required_xp = g_Player.stats.level * 100;
    }
}

// --- CRAFTING LOGIC IMPLEMENTATION (UNCHANGED) ---

int check_recipe_requirements(const Recipe_t *recipe)
{
    const Inv_t *inv = &g_Player.inventory;

    if (inv->holy_tears < recipe->holy_tears) return 0;
    if (inv->goblin_eyes < recipe->goblin_eyes) return 0;
    if (inv->goblin_cloth < recipe->goblin_cloth) return 0;
    if (inv->orc_blood < recipe->orc_blood) return 0;
    if (inv->orc_meat < recipe->orc_meat) return 0;
    if (inv->cobra_venom < recipe->cobra_venom) return 0;
    if (inv->cobra_scales < recipe->cobra_scales) return 0;
    if (inv->magic_dust < recipe->magic_dust) return 0;
    if (inv->wraith_skull < recipe->wraith_skull) return 0;
    if (inv->wyvern_blood < recipe->wyvern_blood) return 0;
    if (inv->dragon_blood < recipe->dragon_blood) return 0;
    if (inv->lesser_healing_potion < recipe->lesser_healing_potion) return 0;
    if (inv->moderate_healing_potion < recipe->moderate_healing_potion) return 0;

    return 1;
}

void craft_item(const Recipe_t *recipe)
{
    Inv_t *inv = &g_Player.inventory;
    int *target_item_ptr = NULL;

    // --- 1. SUBTRACT MATERIALS ---
    inv->holy_tears -= recipe->holy_tears;
    inv->goblin_eyes -= recipe->goblin_eyes;
    inv->goblin_cloth -= recipe->goblin_cloth;
    inv->orc_blood -= recipe->orc_blood;
    inv->orc_meat -= recipe->orc_meat;
    inv->cobra_venom -= recipe->cobra_venom;
    inv->cobra_scales -= recipe->cobra_scales;
    inv->magic_dust -= recipe->magic_dust;
    inv->wraith_skull -= recipe->wraith_skull;
    inv->wyvern_blood -= recipe->wyvern_blood;
    inv->dragon_blood -= recipe->dragon_blood;
    inv->lesser_healing_potion -= recipe->lesser_healing_potion;
    inv->moderate_healing_potion -= recipe->moderate_healing_potion;

    // --- 2. FIND TARGET INVENTORY FIELD ---
    switch(recipe->crafted_item_index)
    {
        case ITEM_LESSER_HEAL: target_item_ptr = &inv->lesser_healing_potion; break;
        case ITEM_MODERATE_HEAL: target_item_ptr = &inv->moderate_healing_potion; break;
        case ITEM_FULL_HEAL: target_item_ptr = &inv->full_healing_potion; break;
        case ITEM_LESSER_STR: target_item_ptr = &inv->lesser_strength_potion; break;
        case ITEM_MODERATE_STR: target_item_ptr = &inv->moderate_strength_potion; break;
        case ITEM_FULL_STR: target_item_ptr = &inv->full_strength_potion; break;
        case ITEM_LESSER_STUN: target_item_ptr = &inv->lesser_stun_splash; break;
        case ITEM_MODERATE_STUN: target_item_ptr = &inv->moderate_stun_splash; break;
        case ITEM_FULL_STUN: target_item_ptr = &inv->full_stun_splash; break;
        case ITEM_RETURN: target_item_ptr = &inv->return_potion; break;
        case ITEM_AROMA: target_item_ptr = &inv->monster_aroma; break;
        case ITEM_INTELLIGENCE: target_item_ptr = &inv->intelligence_potion; break;
        default: target_item_ptr = NULL; break;
    }

    // --- 3. ADD ITEM TO INVENTORY ---
    if (target_item_ptr != NULL)
    {
        *target_item_ptr += recipe->crafted_item_count;
        printf("\n\t\t\t\t\t**SUCCESS!** You crafted %d x %s!\n",
               recipe->crafted_item_count, recipe->crafted_item_name);
    }
    else
    {
        printf("\n\t\t\t\t\tCrafting Error: Invalid item index.\n");
    }

    printf("\t\t\t\t\t(Materials deducted)\n");
}

void display_crafter()
{
    int choices = 0, press;
    int is_craftable;

    while(1)
    {
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t\t\t\t  \e[0;95m=====================================\033[0m");
        printf("\n\t\t\t\t\t\t\t\t      \e[1;97mCrafter's Bench\033[0m ");
        printf("\n\t\t\t\t\t\t\t  \e[0;95m=====================================\033[0m\n");
        printf("\n\t\t\t\t\t\t\t\t  \e[1;93mCurrent Gold: %.2f\n\033[0m\n",  g_Player.stats.gold);
        printf("\n\t\t\t\t\t\t\t  \e[0;95m=====================================\033[0m\n\n");


        // Display Recipes
        for (int i = 0; i < G_NUM_RECIPES; i++)
        {
            is_craftable = check_recipe_requirements(g_Recipes[i]);

            if (i == choices)
                printf("\t\t\t\t\t\t\t\e[1;92m>> %s (Ready: %s)\033[0m\n",
                       g_Recipes[i]->crafted_item_name, is_craftable ? "YES" : "NO");
            else
                printf("\t\t\t\t\t\t\t    %s (Ready: %s)\n",
                       g_Recipes[i]->crafted_item_name, is_craftable ? "YES" : "NO");
        }

        // Go Back option
        if (choices == G_NUM_RECIPES)
            printf("\t\t\t\t\t\t\t>> Go Back\n");
        else
            printf("\t\t\t\t\t\t\t    Go Back\n");

        printf("\t\t\t\t\t\t\t  ====================================\n");

        press = getch();
        if (press == 0 || press == 224) {
            press = getch();
            if (press == 72 && choices > 0) choices--;
            else if (press == 80 && choices < G_NUM_RECIPES) choices++;
        }
        else if (press == '\r')
        {
            if (choices == G_NUM_RECIPES)
                return;
            else
            {
                const Recipe_t *selected_recipe = g_Recipes[choices];

                system("cls");
                printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t");
                printf("\n\n\n\t\t\t\t\t\t\t-- Crafting: %s --\n", selected_recipe->crafted_item_name);
                printf("\n\n\n\t\t\t\t\t\t\tCost: ");

                // Print required materials (only non-zero costs)
                if (selected_recipe->holy_tears > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Holy Tears: %d / %d (Held: %d)\n", g_Player.inventory.holy_tears, selected_recipe->holy_tears, g_Player.inventory.holy_tears);
                if (selected_recipe->goblin_eyes > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Goblin Eyes: %d / %d (Held: %d)\n", g_Player.inventory.goblin_eyes, selected_recipe->goblin_eyes, g_Player.inventory.goblin_eyes);
                if (selected_recipe->goblin_cloth > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Goblin Cloth: %d / %d (Held: %d)\n", g_Player.inventory.goblin_cloth, selected_recipe->goblin_cloth, g_Player.inventory.goblin_cloth);
                if (selected_recipe->orc_blood > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Orc Blood: %d / %d (Held: %d)\n", g_Player.inventory.orc_blood, selected_recipe->orc_blood, g_Player.inventory.orc_blood);
                if (selected_recipe->orc_meat > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Orc Meat: %d / %d (Held: %d)\n", g_Player.inventory.orc_meat, selected_recipe->orc_meat, g_Player.inventory.orc_meat);
                if (selected_recipe->cobra_venom > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Cobra Venom: %d / %d (Held: %d)\n", g_Player.inventory.cobra_venom, selected_recipe->cobra_venom, g_Player.inventory.cobra_venom);
                if (selected_recipe->cobra_scales > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Cobra Scales: %d / %d (Held: %d)\n", g_Player.inventory.cobra_scales, selected_recipe->cobra_scales, g_Player.inventory.cobra_scales);
                if (selected_recipe->magic_dust > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Magic Dust: %d / %d (Held: %d)\n", g_Player.inventory.magic_dust, selected_recipe->magic_dust, g_Player.inventory.magic_dust);
                if (selected_recipe->wraith_skull > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Wraith Skull: %d / %d (Held: %d)\n", g_Player.inventory.wraith_skull, selected_recipe->wraith_skull, g_Player.inventory.wraith_skull);
                if (selected_recipe->wyvern_blood > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Wyvern Blood: %d / %d (Held: %d)\n", g_Player.inventory.wyvern_blood, selected_recipe->wyvern_blood, g_Player.inventory.wyvern_blood);
                if (selected_recipe->dragon_blood > 0)
                    printf("\n\n\t\t\t\t\t\t\t\t- Dragon Blood: %d / %d (Held: %d)\n", g_Player.inventory.dragon_blood, selected_recipe->dragon_blood, g_Player.inventory.dragon_blood);

                // Print potion costs
                if (selected_recipe->lesser_healing_potion > 0)
                    printf("\n\t\t\t\t\t\t\t- Lesser Healing Potion: %d / %d (Held: %d)\n", g_Player.inventory.lesser_healing_potion, selected_recipe->lesser_healing_potion, g_Player.inventory.lesser_healing_potion);
                if (selected_recipe->moderate_healing_potion > 0)
                    printf("\n\t\t\t\t\t\t\t- Moderate Healing Potion: %d / %d (Held: %d)\n", g_Player.inventory.moderate_healing_potion, selected_recipe->moderate_healing_potion, g_Player.inventory.moderate_healing_potion);

                printf("\n\n\n\t\t\t\t\t\t\tDo you want to craft %s? (Y/N)\n", selected_recipe->crafted_item_name);
                press = getch();

                if (press == 'y' || press == 'Y')
                {
                    if (check_recipe_requirements(selected_recipe))
                    {
                        craft_item(selected_recipe);
                    }
                    else
                    {
                        printf("\n\t\t\t\t\t\t\t  \e[1;91mCannot craft! You are missing materials.\033[0m\n");
                    }
                    getch();
                }
            }
        }
    }
}


// --- COMBAT ITEM USAGE MENU (UNCHANGED) ---
int UseItemMenu(const Monster_t *monster, int *monster_hp, int player_damage)
{
    struct CombatItem {
        const char *name;
        int *count_ptr;
        char choice_key;
    } combat_items[] = {
        {"Lesser Healing Potion (50 HP)", &g_Player.inventory.lesser_healing_potion, '1'},
        {"Moderate Healing Potion (150 HP)", &g_Player.inventory.moderate_healing_potion, '2'},
        {"Full Healing Potion (300 HP)", &g_Player.inventory.full_healing_potion, '3'},
        {"Lesser Strength Potion (2x Dmg)", &g_Player.inventory.lesser_strength_potion, '4'},
        {"Moderate Strength Potion (3x Dmg)", &g_Player.inventory.moderate_strength_potion, '5'},
        {"Full Strength Potion (4x Dmg)", &g_Player.inventory.full_strength_potion, '6'},
        {"Lesser Stun Splash (1T)", &g_Player.inventory.lesser_stun_splash, '7'},
        {"Moderate Stun Splash (2T)", &g_Player.inventory.moderate_stun_splash, '8'},
        {"Full Stun Splash (3T)", &g_Player.inventory.full_stun_splash, '9'},
        {"Intelligence Potion (Hint)", &g_Player.inventory.intelligence_potion, '0'}
    };
    int num_items = 10;
    int press, healed_amount, stun_turns;

    while(1)
    {
        system("cls");
        printf("\n\n\n\t\t\t\t*** Use Potion Menu ***\n");
        printf("\t\t\t\t-----------------------\n");
        printf("\t\t\t\t%s HP: %d/%d (Lvl %d)\n", g_Player.player_name, g_Player.stats.current_hp, g_Player.stats.maximum_hp, g_Player.stats.level);
        printf("\t\t\t\t%s HP: %d/%d\n", monster->name, *monster_hp, monster->max_hp);
        printf("\t\t\t\t-----------------------\n");

        for (int i = 0; i < num_items; i++)
        {
            if (*combat_items[i].count_ptr > 0)
            {
                printf("\t\t\t\t[%c] %s x%d\n",
                       combat_items[i].choice_key, combat_items[i].name, *combat_items[i].count_ptr);
            }
        }
        printf("\t\t\t\t[X] Go Back\n");

        press = getch();

        if (press == 'x' || press == 'X') return 0;

        for (int i = 0; i < num_items; i++)
        {
            if (press == combat_items[i].choice_key)
            {
                if (*combat_items[i].count_ptr > 0)
                {
                    (*combat_items[i].count_ptr)--;

                    // HEALING POTIONS
                    if (i >= 0 && i <= 2)
                    {
                        healed_amount = (i == 0) ? 50 : (i == 1) ? 150 : 300;
                        g_Player.stats.current_hp = fmin(g_Player.stats.current_hp + healed_amount, g_Player.stats.maximum_hp);
                        printf("\n\t\t\t\tYou used %s! Healed %d HP.\n", combat_items[i].name, healed_amount);
                        getch();
                        return 1;
                    }
                    // STRENGTH POTIONS
                    else if (i >= 3 && i <= 5)
                    {
                        g_Player.stats.attack_multiplier = (i == 3) ? 2 : (i == 4) ? 3 : 4;
                        printf("\n\t\t\t\tYou used %s! Your attack power is now x%d.\n", combat_items[i].name, g_Player.stats.attack_multiplier);
                        getch();
                        return 1;
                    }
                    // STUN SPLASHES
                    else if (i >= 6 && i <= 8)
                    {
                        stun_turns = (i == 6) ? 1 : (i == 7) ? 2 : 3;
                        g_Player.stats.stun_duration = stun_turns;
                        printf("\n\t\t\t\tYou threw the %s! %s is stunned for %d turn(s)!\n",
                               combat_items[i].name, monster->name, stun_turns);
                        getch();
                        return 1;
                    }
                    // INTELLIGENCE POTION
                    else if (i == 9)
                    {
                        printf("\n\t\t\t\tYou used the Intelligence Potion! The next boss puzzle will reveal the answer.\n");
                        getch();
                        return 1;
                    }
                }
                else
                {
                    printf("\n\t\t\t\tYou don't have that item!\n");
                    getch();
                    return 0;
                }
            }
        }
        return 0;
    }
}


int DungeonFight(const Monster_t *monster, const Inv_t *loot_table)
{
    int monster_hp = monster->max_hp;
    // Base damage calculation (adjust based on your overall player stats)
    int player_damage = 20 + (g_Player.stats.level * 10);
    int choice;
    int turn_consumed = 0;

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\t\t\t\t\t\t\t     *** Encounter: %s ***\n", monster->name);
    load(1000);

    // Status effects reset
    if(g_Player.stats.stun_duration < 0) g_Player.stats.stun_duration = 0;
    if(g_Player.stats.attack_multiplier < 1) g_Player.stats.attack_multiplier = 1;

    while (g_Player.stats.current_hp > 0 && monster_hp > 0)
    {
        // Status display (Uses new detailed UI for combat)
        printf("\t\t\t\t\t\t    -----------------------------------------------\n");
        printf("\t\t\t\t\t\t    %s HP: %d/%d (Lvl %d) | Damage Multiplier: x%d\n",
               g_Player.player_name, g_Player.stats.current_hp, g_Player.stats.maximum_hp,
               g_Player.stats.level, g_Player.stats.attack_multiplier);
        printf("\t\t\t\t\t\t    %s HP: %d/%d | Stun Turns Left: %d\n",
               monster->name, monster_hp, monster->max_hp, g_Player.stats.stun_duration);
        printf("\t\t\t\t\t\t    -----------------------------------------------\n");
        printf("\n\t\t\t\t\t\t\t   (1) Attack (2) Run (3) Use Item\n");

        // Boss-specific notes
        if (strcmp(monster->name, "Geometry Gate") == 0 ||
            strcmp(monster->name, "Physics Archer") == 0 ||
            strcmp(monster->name, "Bridge of Pythagoras") == 0 ||
            strcmp(monster->name, "The Heavy Boulder") == 0 ||
            strcmp(monster->name, "M.A.D.Z") == 0)

        {
             printf("\n\t\t\t\t\t\t\tNOTE: Attacking this boss requires solving a puzzle!\n");
             if (g_Player.inventory.intelligence_potion > 0)
                 printf("\t\t\t\t\t\t\t\t(Hint available via Intelligence Potion [3])\n");
        }

        choice = getch();
        clear_input_buffer(); // Clear any extra inputs
        turn_consumed = 0;
        int final_player_damage = player_damage * g_Player.stats.attack_multiplier;

        if (choice == '1') // Attack
        {
            g_Player.stats.attack_multiplier = 1;

            if (strcmp(monster->name, "Geometry Gate") == 0)
            {
                turn_consumed = GeometryGateFight(&monster_hp, final_player_damage);
            }
            else if (strcmp(monster->name, "Physics Archer") == 0)
            {
                turn_consumed = PhysicsArcherFight(&monster_hp, final_player_damage);
            }
            else if (strcmp(monster->name, "Bridge of Pythagoras") == 0)
            {
                turn_consumed = BridgeOfPythagorasFight(&monster_hp, final_player_damage);
            }
            else if (strcmp(monster->name, "The Heavy Boulder") == 0)
            {
                turn_consumed = HeavyBoulderFight(&monster_hp, final_player_damage);
            }
            else if (strcmp(monster->name, "M.A.D.Z") == 0)
            {
                turn_consumed = FinalBossFight(&monster_hp, final_player_damage);
            }
            else
            {
                // Regular Monster Attack
                monster_hp -= final_player_damage;
                printf("\n\t\t\t\t\t\t\t You hit the %s for %d damage!\n", monster->name, final_player_damage);
                turn_consumed = 1;
                load(550);
            }
        }
        else if (choice == '2') // Run attempt
        {
            int run_chance = rand() % 100;
            if (run_chance < 50)
            {
                printf("\n\t\t\t\t\t\t\t\ttSuccessfully escaped!\n");
                return 0;
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t\tFailed to escape!\n");
                turn_consumed = 1;
            }
            load(500);
        }
        else if (choice == '3') // Use Item
        {
            // Assuming UseItemMenu handles turn_consumed logic (returns 1 if item used, 0 otherwise)
            turn_consumed = UseItemMenu(monster, &monster_hp, player_damage);
        }
        else // Invalid Input
        {
            printf("\n\t\t\t\t\t\t\t\t choice. You lose your turn!\n");
            turn_consumed = 1;
            load(500);
        }

        if (monster_hp <= 0)
        {
            printf("\n\t\t\t\t\t\t\t You defeated the %s!\n", monster->name);
            load(550);
            award_loot(monster, loot_table);
            return 1;
        }

        // --- MONSTER TURN (ATTACK PHASE) ---
        if (turn_consumed)
        {
            if (g_Player.stats.stun_duration > 0)
            {
                // Stun logic: Boss/Monster is stunned
                printf("\t\t\t\t\t\t\t\tThe %s is STUNNED and cannot attack! (%d turn(s) remaining)\n", monster->name, g_Player.stats.stun_duration);
                g_Player.stats.stun_duration--;
                load(500);
            }
            else
            {
                // Check if the monster is a REGULAR mob OR if the player chose a non-attack action (Run/Item)
                if ( (strcmp(monster->name, "Geometry Gate") != 0 &&
                      strcmp(monster->name, "Physics Archer") != 0 &&
                      strcmp(monster->name, "Bridge of Pythagoras") != 0 &&
                      strcmp(monster->name, "The Heavy Boulder") != 0 &&
                      strcmp(monster->name, "M.A.D.Z") != 0) ||
                      (choice != '1') )
                {
                    // Execute standard monster attack logic
                    if (choice != '2' || (choice == '2' && rand() % 100 >= 50))
                    {
                        int damage_taken = monster->damage;
                        // Assuming you want to subtract player defense here (if defense stat exists)
                        // int damage_taken = monster->attack - g_Player.stats.defense;
                        // if (damage_taken < 0) damage_taken = 0;

                        g_Player.stats.current_hp -= damage_taken;
                        printf("\t\t\t\t\t\t\t\tThe %s strikes you for %d damage!\n", monster->name, damage_taken);
                        load(500);
                    }
                }
                // If it IS a boss AND the player chose '1', this block is skipped,
                // effectively blocking the boss's standard attack because the
                // consequence (penalty damage or successful hit) was already
                // calculated inside the specialized boss function.
            }
        }

        system("cls");

        if (g_Player.stats.current_hp <= 0)
        {
            g_Player.stats.current_hp = 1;
            printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t You have been defeated by the %s!\n", monster->name);
            printf("\t\t\t\t\t\t\t\t--- GAME OVER ---\n");
            load(2000);
            return 0;
        }
    }
    return 0;
}


int main()
{
    srand(time(NULL));
    loadingScreen();
    main_menu();
    return 0;
}

void clear_input_buffer()
{

    while (kbhit())
    {
        getch();
    }
}
