#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// PURPOSE:
// A very simple text adventure game. When the game is started, a “$” prompt is printed on
// the screen to let the player know that he/she can type in a new command. To start playing, the player
// will need to load a dungeon file which describes the rooms in your dungeon and how they are
// connected. The player begins in an initial room which is specified in the dungeon file. When the
// dungeon file is loaded, the description of the initial room is printed on the screen, followed by a prompt
// on the next line. Then the player can issue commands to move in a direction, either north, south, east,
// or west. When a player moves, a description of the new room that he moves into is printed on the
// screen and the player is prompted to enter a new move. The adventure ends when the player enters the
// “quit” command.


// Dungeon File Format:
// The dungeon file will be a text file containing information about each room in a specific format. Each line
// of the file will contain information about a single room in the dungeon. 
// All 6 fields of information about each room are contained in order on a single line in the dungeon file.
// Each field of information is separated by one or more spaces. The room described on the first line of the
// file is the initial room where the player will start after the dungeon file is loaded.
// Each room is associated with the following 6 fields of information:
// 1. Room number: This is a positive integer which uniquely identifies the room.
// 2. Description: This is a string which is printed when the player enters the room.
// 3. North room: This is the room number of the room immediately to the north of this room. If
// there is no room to the north of this room then this value is -1.
// 4. South room: This is the room number of the room immediately to the south of this room. If
// there is no room to the south of this room then this value is -1.
// 5. East room: This is the room number of the room immediately to the east of this room. If there is
// no room to the east of this room then this value is -1.
// 6. West room: This is the room number of the room immediately to the west of this room. If there
// is no room to the west of this room then this value is -1.


// EXAMPLE FILE:
// copy this into a seperate text file called 'dfile.txt'
// 1 $This is an open field west of a white house, with a boarded front door.$ 2 -1 -1 -1
// 2 $North of House: You are facing the north side of a white house.$ -1 1 3 -1
// 3 $Behind House: You are behind the white house.$ -1 4 -1 2
// 4 $South of House: You are facing the south side of a white house.$ 3 -1 -1 -1


// COMMANDS:
// 1. loaddungeon - loads the information contained in a dungeon file. The command
// 					takes one argument, the name of the dungeon file. 
//					This command should be the first command
// 					issued by the player after starting the game.
// The directional commands moves the player into the room to the desired direction 
// of the current room. If there is a room to the desired direction then the 
// description of the new room is printed. If there is no room to the desired direction 
// then the message, “You can’t go there.” is printed to the screen.
// 2. north
// 3. south
// 4. east
// 5. west


// EXAMPLE INPUT/OUTPUT:
// The following is a running example showing how your program should respond to commands for an
// example dungeon file. User input is on the line following a '$' character.
// $ loaddungeon dfile.txt 
// This is an open field west of a white house, with a boarded front
// door.
// $ north
// North of House: You are facing the north side of a white house.
// $ east
// Behind House: You are behind the white house.
// $ south
// South of House: You are facing the south side of a white house.
// $ quit


struct room {
	char *description;
	int northRoomNum;
	int southRoomNum;
	int eastRoomNum;
	int westRoomNum;
};


void startGame(){

	char firstCommand[80];
	char *loadCommand;
	char *fileName;

 	// gets first input line
	printf("$ ");
	fgets(firstCommand, 80, stdin);
	loadCommand = strtok(firstCommand, " ");
	while(strncmp(loadCommand,"loaddungeon", 11) != 0){
		printf("%s\n", "Wrong command, try again" );
		printf("$ ");
		fgets(firstCommand, 80, stdin);
		loadCommand = strtok(firstCommand, " ");
	} 
	fileName = strtok(NULL, " ");
	fileName[strlen(fileName) - 1] = 0; //This nulls the last character (the \n).

	// reads file and assigns 6 fields 
	FILE *fp;

	char *roomNumber;
	char *roomDescription;
	char *northRoom;
	char *southRoom;
	char *eastRoom;
	char *westRoom;
	char instructions[256];

	// loaddungeon dfile.txt
	// loaddungeon dfile2.txt

    fp = fopen(fileName, "r");
    // if file name/path is not correct, then repeat whole process
	while (fp == NULL) {
		perror ("Error opening file, try again");
		printf("$ ");
		fgets(firstCommand, 80, stdin);
		loadCommand = strtok(firstCommand, " ");
		while(strncmp(loadCommand,"loaddungeon", 11) != 0){
			printf("%s\n", "Wrong command, try again" );
			printf("$ ");
			fgets(firstCommand, 80, stdin);
			loadCommand = strtok(firstCommand, " ");
		} 
		fileName = strtok(NULL, " ");
		fileName[strlen(fileName) - 1] = 0;
		fp = fopen(fileName, "r");
	}

	// if fopen works, then proceed with beginning game
	// get the number of lines in the file to allocate memory for array
	int lines = 0;
	int ch = 0;
	while(!feof(fp)){
 		ch = fgetc(fp);
  		if(ch == '\n'){
    	lines++;
  		}
	}
	fclose(fp);

	struct room dungeon[lines+2]; 

	fp = fopen(fileName, "r");
	fgets(instructions, 256, fp); // gets first line in txt file

	// checks for invalid file format
	int rNum;
	char temp[100];
	char tempDes[100];
	int n;
	int s;
	int e;
	int w;
	strcpy(temp, instructions);
	while (sscanf(temp, "%d $%[^$]$ %d %d %d %d", &rNum, tempDes, &n,&s,&e,&w) != 6){
		printf("%s\n", "Invalid file format, try again" );
		printf("$ ");
		fgets(firstCommand, 80, stdin);
		loadCommand = strtok(firstCommand, " ");
		while(strncmp(loadCommand,"loaddungeon", 11) != 0){
			printf("%s\n", "Wrong command, try again" );
			printf("$ ");
			fgets(firstCommand, 80, stdin);
			loadCommand = strtok(firstCommand, " ");
		} 
		fileName = strtok(NULL, " ");
		fileName[strlen(fileName) - 1] = 0;

		fp = fopen(fileName, "r");
	    // if file name/path is not correct, then repeat whole process
		while (fp == NULL) {
			perror ("Error opening file, try again");
			printf("$ ");
			fgets(firstCommand, 80, stdin);
			loadCommand = strtok(firstCommand, " ");
			while(strncmp(loadCommand,"loaddungeon", 11) != 0){
				printf("%s\n", "Wrong command, try again" );
				printf("$ ");
				fgets(firstCommand, 80, stdin);
				loadCommand = strtok(firstCommand, " ");
			} 
			fileName = strtok(NULL, " ");
			fileName[strlen(fileName) - 1] = 0;
			fp = fopen(fileName, "r");
		}

		// if fopen works, then proceed with beginning game
		// get the number of lines in the file to allocate memory for array
		lines = 0;
		ch = 0;
		while(!feof(fp)){
	 		ch = fgetc(fp);
	  		if(ch == '\n'){
	    	lines++;
	  		}
		}
		fclose(fp);

		fp = fopen(fileName, "r");
		fgets(instructions, 256, fp); 
		strcpy(temp, instructions);
	}
    // loaddungeon dfile.txt

    roomNumber = strtok(instructions, " ");
    //int roomNumberInt = *roomNumber - '0';
    int roomNumberInt = atoi(roomNumber);

    roomDescription = strtok(NULL, "$"); // after this line, doesn't work if file invalid format
    dungeon[roomNumberInt].description = (char*)malloc(sizeof(char)*strlen(roomDescription));
    strcpy(dungeon[roomNumberInt].description, roomDescription);
    char * word = dungeon[roomNumberInt].description;

    northRoom = strtok(NULL, " ");
    //int northRoomInt = *northRoom - '0'; // alternate technique
    int northRoomInt = atoi(northRoom);
    southRoom = strtok(NULL, " ");
    // int southRoomInt = *southRoom - '0';
    int southRoomInt = atoi(southRoom);
    eastRoom = strtok(NULL, " ");
    // int eastRoomInt = *eastRoom - '0';
    int eastRoomInt = atoi(eastRoom);
    westRoom = strtok(NULL, " ");
    // int westRoomInt = *westRoom - '0';
    int westRoomInt = atoi(westRoom);

    dungeon[roomNumberInt].northRoomNum = northRoomInt;
    dungeon[roomNumberInt].southRoomNum = southRoomInt;
    dungeon[roomNumberInt].eastRoomNum = eastRoomInt;
    dungeon[roomNumberInt].westRoomNum = westRoomInt;

    printf("%s \n", dungeon[roomNumberInt].description);

    // reads whole file and puts it into array of struct
    while( !(feof(fp)) ){
    	fgets(instructions, 256, fp);

    	strcpy(temp, instructions);
		while (sscanf(temp, "%d $%[^$]$ %d %d %d %d", &rNum, tempDes, &n,&s,&e,&w) != 6){
			printf("%s\n", "Invalid file format, try again" );
			printf("$ ");
			fgets(firstCommand, 80, stdin);
			loadCommand = strtok(firstCommand, " ");
			while(strncmp(loadCommand,"loaddungeon", 11) != 0){
				printf("%s\n", "Wrong command, try again" );
				printf("$ ");
				fgets(firstCommand, 80, stdin);
				loadCommand = strtok(firstCommand, " ");
			} 
			fileName = strtok(NULL, " ");
			fileName[strlen(fileName) - 1] = 0;

			fp = fopen(fileName, "r");
		    // if file name/path is not correct, then repeat whole process
			while (fp == NULL) {
				perror ("Error opening file, try again");
				printf("$ ");
				fgets(firstCommand, 80, stdin);
				loadCommand = strtok(firstCommand, " ");
				while(strncmp(loadCommand,"loaddungeon", 11) != 0){
					printf("%s\n", "Wrong command, try again" );
					printf("$ ");
					fgets(firstCommand, 80, stdin);
					loadCommand = strtok(firstCommand, " ");
				} 
				fileName = strtok(NULL, " ");
				fileName[strlen(fileName) - 1] = 0;
				fp = fopen(fileName, "r");
			}

			// if fopen works, then proceed with beginning game
			// get the number of lines in the file to allocate memory for array
			lines = 0;
			ch = 0;
			while(!feof(fp)){
		 		ch = fgetc(fp);
		  		if(ch == '\n'){
		    	lines++;
		  		}
			}
			fclose(fp);

			fp = fopen(fileName, "r");
			fgets(instructions, 256, fp); 
			strcpy(temp, instructions);
		}
        
        roomNumber = strtok(instructions, " ");
    	roomNumberInt = *roomNumber - '0';

   	 	roomDescription = strtok(NULL, "$");
   	 	
   	 	// replaces dungeon[roomNumberInt].description = roomDescription
   	 	dungeon[roomNumberInt].description = (char*)malloc(sizeof(char)*strlen(roomDescription));
    	strcpy(dungeon[roomNumberInt].description, roomDescription);

    	northRoom = strtok(NULL, " ");
    	//northRoomInt = *northRoom - '0';
    	northRoomInt = atoi(northRoom);

    	southRoom = strtok(NULL, " ");
    	//southRoomInt = *southRoom - '0';
    	southRoomInt = atoi(southRoom);

    	eastRoom = strtok(NULL, " ");
    	//eastRoomInt = *eastRoom - '0';
    	eastRoomInt = atoi(eastRoom);

    	westRoom = strtok(NULL, " ");
    	//westRoomInt = *westRoom - '0';
    	westRoomInt = atoi(westRoom);

    	dungeon[roomNumberInt].northRoomNum = northRoomInt;
   		dungeon[roomNumberInt].southRoomNum = southRoomInt;
    	dungeon[roomNumberInt].eastRoomNum = eastRoomInt;
    	dungeon[roomNumberInt].westRoomNum = westRoomInt;
    	
    	//if( feof(fp) ) break;

    }

    fclose(fp);

    // begins game by asking for next input command
    struct room currentRoom = dungeon[1];
    char gameCommand[80];

    while ( strncmp(gameCommand,"quit",4) != 0){
    	printf("%s ", "$" );
		fgets(gameCommand, 80, stdin);

		// if player decides to load another dungeon in the middle of the game
		if ( strncmp(gameCommand,"loaddungeon",11) == 0 ){
			// resets the dungeon
			for (int i = 1; i < lines+2; i++){
				dungeon[i].description[0] = 0;
				dungeon[i].northRoomNum = -1;
   				dungeon[i].southRoomNum = -1;
    			dungeon[i].eastRoomNum = -1;
    			dungeon[i].westRoomNum = -1;
			}
			loadCommand = strtok(gameCommand, " ");
			fileName = strtok(NULL, " ");
			fileName[strlen(fileName) - 1] = 0;
			fp = fopen(fileName, "r");
    		// if file name/path is not correct, then repeat whole process
			while (fp == NULL) {
				perror ("Error opening file, try again");
				printf("$ ");
				fgets(firstCommand, 80, stdin);
				loadCommand = strtok(firstCommand, " ");
				while(strncmp(loadCommand,"loaddungeon", 11) != 0){
					printf("%s\n", "Wrong command, try again" );
					printf("$ ");
					fgets(firstCommand, 80, stdin);
					loadCommand = strtok(firstCommand, " ");
				} 
				fileName = strtok(NULL, " ");
				fileName[strlen(fileName) - 1] = 0;
				fp = fopen(fileName, "r");
			}

			// if fopen works, then proceed with beginning game
			// get the number of lines in the file to allocate memory for array
			 lines = 0;
			 ch = 0;
			while(!feof(fp)){
		 		ch = fgetc(fp);
		  		if(ch == '\n'){
		    	lines++;
		  		}
			}
			fclose(fp);

			struct room newdungeon[lines+2]; 
			*dungeon = *newdungeon; 

			fp = fopen(fileName, "r");
			fgets(instructions, 256, fp); // gets first line in txt file
		    
		    roomNumber = strtok(instructions, " ");
		    //int roomNumberInt = *roomNumber - '0';
		     roomNumberInt = atoi(roomNumber);

		    roomDescription = strtok(NULL, "$"); // after this line, doesn't work if file invalid format
		    dungeon[roomNumberInt].description = (char*)malloc(sizeof(char)*strlen(roomDescription));
		    strcpy(dungeon[roomNumberInt].description, roomDescription);


		    northRoom = strtok(NULL, " ");
		    //int northRoomInt = *northRoom - '0'; // alternate technique
		     northRoomInt = atoi(northRoom);
		    southRoom = strtok(NULL, " ");
		    // int southRoomInt = *southRoom - '0';
		     southRoomInt = atoi(southRoom);
		    eastRoom = strtok(NULL, " ");
		    // int eastRoomInt = *eastRoom - '0';
		     eastRoomInt = atoi(eastRoom);
		    westRoom = strtok(NULL, " ");
		    // int westRoomInt = *westRoom - '0';
		     westRoomInt = atoi(westRoom);

		    dungeon[roomNumberInt].northRoomNum = northRoomInt;
		    dungeon[roomNumberInt].southRoomNum = southRoomInt;
		    dungeon[roomNumberInt].eastRoomNum = eastRoomInt;
		    dungeon[roomNumberInt].westRoomNum = westRoomInt;

		    printf("%s \n", dungeon[roomNumberInt].description);

		    // reads whole file and puts it into array of struct
		    while( !(feof(fp)) ){
		    	fgets(instructions, 256, fp);
		        
		        roomNumber = strtok(instructions, " ");
		    	roomNumberInt = *roomNumber - '0';

		   	 	roomDescription = strtok(NULL, "$");
		   	 	
		   	 	// replaces dungeon[roomNumberInt].description = roomDescription
		   	 	dungeon[roomNumberInt].description = (char*)malloc(sizeof(char)*strlen(roomDescription));
		    	strcpy(dungeon[roomNumberInt].description, roomDescription);

		    	northRoom = strtok(NULL, " ");
		    	//northRoomInt = *northRoom - '0';
		    	northRoomInt = atoi(northRoom);

		    	southRoom = strtok(NULL, " ");
		    	//southRoomInt = *southRoom - '0';
		    	southRoomInt = atoi(southRoom);

		    	eastRoom = strtok(NULL, " ");
		    	//eastRoomInt = *eastRoom - '0';
		    	eastRoomInt = atoi(eastRoom);

		    	westRoom = strtok(NULL, " ");
		    	//westRoomInt = *westRoom - '0';
		    	westRoomInt = atoi(westRoom);

		    	
		    	dungeon[roomNumberInt].northRoomNum = (int)malloc(sizeof(int)*northRoomInt);
		    	dungeon[roomNumberInt].northRoomNum = northRoomInt;
		   		
		   		dungeon[roomNumberInt].southRoomNum = (int)malloc(sizeof(int)*(northRoomInt));
		   		dungeon[roomNumberInt].southRoomNum = southRoomInt;
		    	
		    	dungeon[roomNumberInt].eastRoomNum = (int)malloc(sizeof(int)*(northRoomInt));
		    	dungeon[roomNumberInt].eastRoomNum = eastRoomInt;
		    	
		    	dungeon[roomNumberInt].westRoomNum = (int)malloc(sizeof(int)*(northRoomInt));
		    	dungeon[roomNumberInt].westRoomNum = westRoomInt;
		    	
		    	//if( feof(fp) ) break;

		    }
		    	fclose(fp);
		}
		// loaddungeon dfile.txt
		else if ( strncmp(gameCommand,"north",5) == 0 ){
			if (strlen(gameCommand) != 6) printf("%s \n", "Invalid command, try agan" );
			else if (currentRoom.northRoomNum == -1) printf("%s\n", "You can’t go there." );
			else {
				currentRoom = dungeon[currentRoom.northRoomNum];
				printf("%s \n", currentRoom.description );
			}
		}
		else if ( strncmp(gameCommand,"south",5) == 0){
			if (strlen(gameCommand) != 6) printf("%s \n", "Invalid command, try agan" );
			else if (currentRoom.southRoomNum == -1) printf("%s\n", "You can’t go there." );
			else {
				currentRoom = dungeon[currentRoom.southRoomNum];
				printf("%s \n", currentRoom.description);
			}
		}
		else if ( strncmp(gameCommand,"east",4) == 0){
			if (strlen(gameCommand) != 5) printf("%s \n", "Invalid command, try agan" );
			else if (currentRoom.eastRoomNum == -1) printf("%s\n", "You can’t go there." );
			else {
				currentRoom = dungeon[currentRoom.eastRoomNum];
				printf("%s \n", currentRoom.description );
			}
		}
		else if ( strncmp(gameCommand,"west",4) == 0){
			if (strlen(gameCommand) != 5) printf("%s \n", "Invalid command, try agan" );
			else if (currentRoom.westRoomNum == -1) printf("%s\n", "You can’t go there." );
			else {
				currentRoom = dungeon[currentRoom.westRoomNum];
				printf("%s \n", currentRoom.description );
			}
		}
		else if ( strncmp(gameCommand, "quit", 4) == 0) {
			break;
		}
		else printf("%s \n", "Invalid command, try again" );

    }
}


int main(){
	startGame();

	return 0;
}




