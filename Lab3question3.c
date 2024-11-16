//------------------------------------------------------include all libraries-------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//-------------------------------------------------Define constants----------------------------------------------------
#define NUM_TEAMS 10
#define SQUAD_SIZE 15
//-------------------------------------------------------Initialize structs-------------------------------------------
struct age {// day,month and year
    int day;
    int month;
    int year;
};

struct player {//name,kitnumber,club,age from struct,posiyion
    char name[26];
    int kit_number;
    char club[30];
    struct age age;
    char position[15];
};

struct team {//teamname,Playerstruct-no. of players
    char name[21];
    struct player players[SQUAD_SIZE];
    int activeSize;
};
//---------------------------------------------------prototype all functions--------------------------------------------
void display_menu();//function to display menu
int enroll_club(struct team teams[], int num_teams);//Function to enroll clubs
void add_player(struct team teams[], int num_teams);//Function to add players
void search_update(struct team teams[], int num_teams);//Function to search or update exisitng players
void display_club_statistics(struct team teams[], int num_teams);//Function to display stats
void handle_error(const char* error_message);//function to handle error at every step
//---------------------------------------------------Main------------------------------------------------------------------
int main() {
    struct team teams[NUM_TEAMS];
    int num_teams = 0;
    int choice;

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar(); 
        //switch to call the required function based on the users input
        switch (choice) {
            case 1:
                num_teams = enroll_club(teams, num_teams);
                break;
            case 2:
                add_player(teams, num_teams);
                break;
            case 3:
                search_update(teams, num_teams);
                break;
            case 4:
                display_club_statistics(teams, num_teams);
                break;
            case 5:
                printf("Exiting the program.\n");
                exit(0);
                break;
            default:
                handle_error("Invalid choice. Please try again.");//handle error funtion
        }
    }

    return 0;
}
//---------------------------------------------Main meny-----------------------------------------------------------
void display_menu() {
    printf("Menu:\n");
    printf("1. Enroll Club\n");
    printf("2. Add Player\n");
    printf("3. Search/Update Player\n");
    printf("4. Display Club Statistics\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}
//------------------------------------------------enroll club function---------------------------------------------
int enroll_club(struct team teams[], int num_teams) {
    if (num_teams >= NUM_TEAMS) {//if maximum number if teams enrolled skip
        handle_error("Maximum number of clubs reached.");
        return num_teams;
    }
    printf("Enter club name: ");
    fgets(teams[num_teams].name, 21, stdin);
    teams[num_teams].name[strcspn(teams[num_teams].name, "\n")] = '\0';
    teams[num_teams].activeSize = 0;
    num_teams++;//enroll team and increment numofteams for future reference
    printf("Club enrolled successfully.\n");
    return num_teams;
}
//--------------------------------------------function add player-----------------------------------------------
void add_player(struct team teams[], int num_teams) {
    int club_index;
    printf("Select club index (0-%d): ", num_teams - 1);
    scanf("%d", &club_index);
    getchar();

    if (club_index < 0 || club_index >= num_teams) {
        handle_error("Invalid club index.");
        return;
    }

    if (teams[club_index].activeSize >= SQUAD_SIZE) {
        handle_error("Squad size limit reached.");
        return;
    }

    struct player player;
    printf("Enter player name: ");
    fgets(player.name, 26, stdin);
    player.name[strcspn(player.name, "\n")] = '\0';

    printf("Enter kit number: ");
    scanf("%d", &player.kit_number);
    getchar();

    strcpy(player.club, teams[club_index].name);

    printf("Enter birth date (dd mm yyyy): ");
    scanf("%d %d %d", &player.age.day, &player.age.month, &player.age.year);
    getchar();

    printf("Enter position: ");
    fgets(player.position, 15, stdin);
    player.position[strcspn(player.position, "\n")] = '\0';

    teams[club_index].players[teams[club_index].activeSize] = player;
    teams[club_index].activeSize++;
    printf("Player added successfully.\n");
}
//--------------------------------------------function search/update-------------------------------------
void search_update(struct team teams[], int num_teams) {
    char player_name[26];
    printf("Enter player name to search: ");
    fgets(player_name, 26, stdin);
    player_name[strcspn(player_name, "\n")] = '\0';

    for (int i = 0; i < num_teams; i++) {
        for (int j = 0; j < teams[i].activeSize; j++) {
            if (strcmp(teams[i].players[j].name, player_name) == 0) {
                printf("Player found in team %s\n", teams[i].name);
                printf("Player name: %s\n", teams[i].players[j].name);
                printf("Kit number: %d\n", teams[i].players[j].kit_number);
                printf("Club: %s\n", teams[i].players[j].club);
                printf("Age: %02d-%02d-%04d\n", teams[i].players[j].age.day, teams[i].players[j].age.month, teams[i].players[j].age.year);
                printf("Position: %s\n", teams[i].players[j].position);

                printf("Do you want to update player details? (y/n): ");
                char choice;
                scanf("%c", &choice);
                getchar();

                if (choice == 'y' || choice == 'Y') {
                    printf("Enter new player name: ");
                    fgets(teams[i].players[j].name, 26, stdin);
                    teams[i].players[j].name[strcspn(teams[i].players[j].name, "\n")] = '\0';

                    printf("Enter new kit number: ");
                    scanf("%d", &teams[i].players[j].kit_number);
                    getchar();

                    printf("Enter new birth date (dd mm yyyy): ");
                    scanf("%d %d %d", &teams[i].players[j].age.day, &teams[i].players[j].age.month, &teams[i].players[j].age.year);
                    getchar();

                    printf("Enter new position: ");
                    fgets(teams[i].players[j].position, 15, stdin);
                    teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = '\0';

                    printf("Player details updated successfully.\n");
                }
                return;
            }
        }
    }
    handle_error("Player not found.");
}
//------------------------------------------display club stat function---------------------------------------
void display_club_statistics(struct team teams[], int num_teams) {
    for (int i = 0; i < num_teams; i++) {
        printf("Club: %s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].activeSize);
        for (int j = 0; j < teams[i].activeSize; j++) {
            printf("  Player name: %s\n", teams[i].players[j].name);
            printf("  Kit number: %d\n", teams[i].players[j].kit_number);
            printf("  Age: %02d-%02d-%04d\n", teams[i].players[j].age.day, teams[i].players[j].age.month, teams[i].players[j].age.year);
            printf("  Position: %s\n", teams[i].players[j].position);
        }
        printf("\n");
    }
}

void handle_error(const char* error_message) {
    printf("Error: %s\n", error_message);
}
