#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Functions Declarations
*/

void display_teams();
void add_team();

void update_team();

void generate_schedule();

void update_schedule();

struct IPL_Teams
{
    char teamCode[5];
    char teamName[32];
    char teamCity[32];
    char teamPlayers[4][64];
};

struct IPL_Schedules
{
    int matchID;
    char teamA[5];
    char teamB[5];
    char date[12];
    char venue[32];
};

int teamCount = 0;
int matchCount = 0;

int main()
{
    FILE *fp, *fp2;
    fp = fopen("iplTeams.dat", "wb");

    int n = 0;
    while (n < 2)
    {

        printf("Enter number of teams: ");
        scanf("%d", &n);
        if (n < 2)
        {
            printf("Minimum of two teams are required.\n");
        }
    }

    fflush(stdin);

    printf("Fill the details of all the teams:\n");
    int i;
    for (i = 0; i < n; i++)
    {
        struct IPL_Teams team;
        printf("Enter Team %d details: \n", i + 1);
        printf("Enter team code: ");
        gets(team.teamCode);
        printf("Enter team name: ");
        gets(team.teamName);
        printf("Enter team city: ");
        gets(team.teamCity);
        printf("Enter team player details: \n");
        int j;
        for (j = 0; j < 4; j++)
        {
            printf("Enter player %d name: ", j + 1);
            gets(team.teamPlayers[j]);
        }

        fwrite(&team, sizeof(team), 1, fp);
        teamCount++;
    }
    fclose(fp);

    printf("Fill the match schedules:\n");
    fp2 = fopen("iplSchedules.dat", "wb");
    while (1)
    {
        struct IPL_Schedules schedules;
        printf("Enter match %d details: \n", matchCount + 1);
        printf("Enter match ID: ");
        scanf("%d", &schedules.matchID);
        fflush(stdin);
        printf("Enter team A: ");
        gets(schedules.teamA);
        printf("Enter team B: ");
        gets(schedules.teamB);
        printf("Enter match date: ");
        gets(schedules.date);
        printf("Enter match venue: ");
        gets(schedules.venue);

        fwrite(&schedules, sizeof(schedules), 1, fp);
        matchCount++;
        printf("Do you want to add another match schedule? (y/n) : ");
        char response;
        response = getc(stdin);
        if (response == 'Y' || response == 'y')
            continue;
        else
            break;
    }
    fclose(fp2);

    printf("\n\n\n\t\t\t===================================================\t\t\t");
    printf("\n\n\n\t\t\t=======  IPL Cricket Tournament Schedular  ========\t\t\t");
    printf("\n\n\n\t\t\t===================================================\t\t\n\n\n");
    int choice = 0;
    while (1)
    {
        printf("1. Display the names of all the teams and their players\n");
        printf("2. Add a team to the tournament\n");
        printf("3. Update a team's details\n");
        printf("4. Generate the schedule\n");
        printf("5. Update the schedule\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_teams();
            break;
        case 2:
            add_team();
            break;
        case 3:
            update_team();
            break;
        case 4:
            generate_schedule();
            break;
        case 5:
            update_schedule();
            break;
        case 6:
            exit(0);
        default:
            printf("Error: invalid choice.\n");
            break;
        }
    }

    return 0;
}

void display_teams()
{
    FILE *fp;
    fp = fopen("iplTeams.dat", "rb");

    printf("========= Team List =========\n");
    for (int i = 0; i < teamCount; i++)
    {
        struct IPL_Teams team;
        fread(&team, sizeof(team), 1, fp);
        printf("-----------------------------------------\n");
        printf("| Team %d Details: \n", i + 1);
        printf("|\tTeam Code: %s\n", team.teamCode);
        printf("|\tTeam Name: %s\n", team.teamName);
        printf("|\tTeam City: %s\n", team.teamCity);
        printf("|\tTeam Players: ");
        int j;
        for (j = 0; j < 4; j++)
        {
            printf("%s%s", team.teamPlayers[j], (j == 3) ? ".\n" : ", ");
        }
        printf("-----------------------------------------\n\n");
    }

    fclose(fp);
}

void add_team()
{
    FILE *fp;
    fp = fopen("iplTeams.dat", "ab");
    while (1)
    {
        struct IPL_Teams team;
        printf("Enter Team details: \n");
        printf("Enter team code: ");
        fflush(stdin);
        gets(team.teamCode);
        printf("Enter team name: ");
        gets(team.teamName);
        printf("Enter team city: ");
        gets(team.teamCity);
        printf("Enter team player details: \n");
        int j;
        for (j = 0; j < 4; j++)
        {
            printf("Enter player %d name: ", j + 1);
            gets(team.teamPlayers[j]);
        }

        fwrite(&team, sizeof(team), 1, fp);
        teamCount++;
        printf("Do you want to add another team? (y/n) : ");
        char response;
        response = getc(stdin);
        if (response == 'Y' || response == 'y')
            continue;
        else
            break;
    }

    fclose(fp);
}

void update_team()
{
    FILE *fp, *fp2;
    fp = fopen("iplTeams.dat", "rb");
    fp2 = fopen("temp.dat", "wb");
    char teamCode[5];
    printf("Enter team code to edit: ");
    scanf("%s", teamCode);
    int i;
    for (i = 0; i < teamCount; i++)
    {
        struct IPL_Teams team;
        fread(&team, sizeof(team), 1, fp);
        if (strcmp(teamCode, team.teamCode) == 0)
        {

            printf("Enter Team details to edit: \n");
            printf("Enter team code: ");
            fflush(stdin);
            gets(team.teamCode);
            printf("Enter team name: ");
            gets(team.teamName);
            printf("Enter team city: ");
            gets(team.teamCity);
            printf("Enter team player details: \n");
            int j;
            for (j = 0; j < 4; j++)
            {
                printf("Enter %d player name: ", j + 1);
                gets(team.teamPlayers[j]);
            }
        }
        fwrite(&team, sizeof(team), 1, fp2);
    }
    fclose(fp);
    fclose(fp2);
    remove("iplTeams.dat");
    rename("temp.dat", "iplTeams.dat");
    remove("temp.dat");
}

void generate_schedule()
{
    FILE *fp;
    fp = fopen("iplSchedules.dat", "rb");
    int i;
    for (i = 0; i < matchCount; i++)
    {
        struct IPL_Schedules schedule;
        fread(&schedule, sizeof(schedule), 1, fp);
        printf("-----------------------------------------\n");
        printf("| Match %d Details: \n", i + 1);
        printf("|\tMatch ID: %d\n", schedule.matchID);
        printf("|\tTeam A: %s\n", schedule.teamA);
        printf("|\tTeam B: %s\n", schedule.teamB);
        printf("|\tVenue: %s\n", schedule.venue);
        printf("|\tDate: %s\n", schedule.date);
        printf("-----------------------------------------\n\n");
    }
    fclose(fp);
    printf("\n\nDo you want to add more schedule matches? (y/n): ");
    char response;
    fflush(stdin);
    response = getc(stdin);
    if (response == 'Y' || response == 'y')
    {
        fp = fopen("iplSchedules.dat", "ab");
        while (1)
        {
            struct IPL_Schedules schedule;
            printf("Enter match %d details: \n", matchCount + 1);
            printf("Enter match ID: ");
            scanf("%d", &schedule.matchID);
            fflush(stdin);
            printf("Enter team A: ");
            gets(schedule.teamA);
            printf("Enter team B: ");
            gets(schedule.teamB);
            printf("Enter match date: ");
            gets(schedule.date);
            printf("Enter match venue: ");
            gets(schedule.venue);

            fwrite(&schedule, sizeof(schedule), 1, fp);
            matchCount++;
            printf("Do you want to add another match schedule? (y/n) : ");
            char response;
            response = getc(stdin);
            if (response == 'Y' || response == 'y')
                continue;
            break;
        }
        fclose(fp);
    }
}

void update_schedule()
{
    FILE *fp, *fp2;
    fp = fopen("iplSchedules.dat", "rb");
    fp2 = fopen("temp2.dat", "wb");
    int matchID;
    printf("Enter match ID to edit: ");
    scanf("%d", &matchID);
    fflush(stdin);
    int i;
    for (i = 0; i < matchCount; i++)
    {
        struct IPL_Schedules schedule;
        fread(&schedule, sizeof(schedule), 1, fp);
        if (matchID == schedule.matchID)
        {
            printf("Enter match details to edit: \n");
            printf("Enter match ID: ");
            scanf("%d", &schedule.matchID);
            fflush(stdin);
            printf("Enter team A: ");
            gets(schedule.teamA);
            printf("Enter team B: ");
            gets(schedule.teamB);
            printf("Enter match date: ");
            gets(schedule.date);
            printf("Enter match venue: ");
            gets(schedule.venue);
        }
        fwrite(&schedule, sizeof(schedule), 1, fp2);
    }
    fclose(fp);
    fclose(fp2);
    remove("iplSchedules.dat");
    rename("temp2.dat", "iplSchedules.dat");
    remove("temp2.dat");
}
