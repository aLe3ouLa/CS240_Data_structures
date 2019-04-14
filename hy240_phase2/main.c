#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "events.h"

#define LINE_LENGTH 	1024	/* Maximum length of a line in input file */
#define MAX_FLOORS_NUM	5		/* Maximum number of floors per museum*/
#define MAX_NAME_LENGTH 100

ARTSTYLE *ArtStylesHead;	/* Tree of art styles */
ARTIST *ArtistsHead;		/* Tree of artists */
MUSEUM *MuseumsList;		/* List of museums */

PAINTING ** PAINT;


int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char line[LINE_LENGTH], event, *delim=" ";
	int i,j;
	int m;
	ARTSTYLE * guard = NULL;


	/* Check command line arguments */
	if ( argc != 3 )	{
		printf("Usage: %s <M> <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	m = atoi(argv[1]);
	PAINT = (PAINTING**)malloc(m*sizeof(PAINTING*));
	for(i = 0; i < m; i++) { 
		PAINT[i] = NULL;
	}

	/* Open input file */
	if (( fin = fopen(argv[2], "r") ) == NULL ) {
		printf("\n Could not open file: %s\n", argv[2]);
		return EXIT_FAILURE;
	}

	/* Put your initialization code here */
	

	/* Read input file line-by-line and handle the events */
	while( fgets(line, LINE_LENGTH, fin) != NULL ) {

		/* Un-comment the line below when in debug mode */
		//printf("Event: %s \n", line);

		switch(line[0]) {

			/* Add a new art style:
			 * S <artStyleId> <styleName> */
			case 'S':
			{
				unsigned int artStyleId;
				char styleName[MAX_NAME_LENGTH];
				sscanf(line, "%c %d %s", &event, &artStyleId, styleName);

				S(artStyleId,styleName, &ArtStylesHead,guard);

				break;
			}

			/* Add a new artist:
			 * A <artistId> <artistName> <YearOfBirth> <YearOfDeath> <artStyleId> */
			case 'A':
			{
				unsigned int artistId, YearOfBirth, YearOfDeath, artStyleId;
				char artistName[MAX_NAME_LENGTH];
				sscanf(line, "%c %d %s %d %d %d", &event, &artistId, artistName, &YearOfBirth, &YearOfDeath, &artStyleId);
				
				A(artistId,artistName,YearOfBirth,YearOfDeath,artStyleId,&ArtistsHead,&ArtStylesHead,guard);
				
				break;
			}

			/* Add a new museum:
			 * M <museumId> <museumName> <museumAddress> <f>
			 * <rooms0> <roomId0-1> ... <roomId0-<r0>>
			 * <rooms1> <roomId1-1> ... <roomId1-<r1>>
			 * .
			 * <rooms<f>> <roomId<f>-1> ... <roomId<f>-<r<f>>> */
			case 'M':
			{
				unsigned int museumId, f, **roomIds, *roomNums;
				char museumName[MAX_NAME_LENGTH], museumAddress[MAX_NAME_LENGTH];
				sscanf(line, "%c %d %s %s %d", &event, &museumId, museumName, museumAddress, &f);
				roomIds = (unsigned int **) malloc ((f+1)*sizeof(unsigned int *));  // CHANGE: f --> f+1
				roomNums = (unsigned int *) malloc ((f+1)*sizeof(unsigned int));    // CHANGE: f --> f+1
				
				/* Un-comment the line below when in debug mode */
				printf("%c %d %s %s %d", event, museumId, museumName, museumAddress, f);

				//strtok(line, delim);							/* CHANGE: REMOVED */
				//for (i=0; i < 4; i++)							/* CHANGE: REMOVED */
				//    strtok(NULL, delim);						/* CHANGE: REMOVED */

				for (i=0; i<=f; i++) {							/* CHANGE: i<f --> i<=f */
					fgets(line, LINE_LENGTH, fin);					/* CHANGE: ADDED */
						
					roomNums[i] = atoi(strtok(line, delim));			/* CHANGE: strtok(NULL, delim) -->  strtok(line, delim)*/
					roomIds[i] = (unsigned int *) malloc (roomNums[i]*sizeof( unsigned int));
					
					/* Un-comment the line below when in debug mode */
					//printf("\n   %d ", roomNums[i]);

					for (j=0; j<roomNums[i]; j++) {
						roomIds[i][j] = atoi(strtok(NULL, delim));

						/* Un-comment the line below when in debug mode */
						//printf("%d ", roomIds[i][j]);
					}
				}
				/* Un-comment the line below when in debug mode */
				//printf("\n");

				/* put your code here */
				M(&MuseumsList,museumId,museumName, museumAddress, f,roomIds,roomNums);
				break;
			}

			/* Add another floor to some museum:
			 * O <museumId> <r> <roomId1> ... <roomId<r>> */
			case 'O':
			{
				unsigned int museumId, r, *roomIds;
				sscanf(line, "%c %d %d", &event, &museumId, &r);
				roomIds = (int *) malloc (r*sizeof(int));
				
				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d ", event, museumId, r);

				strtok(line, delim);
				for (i=0; i < 2; i++)
					strtok(NULL, delim);

				for (i=0; i<r; i++) {
					roomIds[i] = atoi(strtok(NULL, delim));

					/* Un-comment the line below when in debug mode */
					//printf("%d ", roomIds[i]);
				}
				/* Un-comment the line below when in debug mode */
				//printf("\n");
				
				/* put your code here */
				O(&MuseumsList,museumId,r,roomIds);
				break;
			}

			/* Add another room to a floor of some museum:
			 * R <museumId> <floorNum> <roomId> <roomId_src> <flag> */
			case 'R':
			{
				unsigned int museumId, floorNum, roomId, roomId_src;
				int flag;
				sscanf(line, "%c %d %d %d %d %d", &event, &museumId, &floorNum, &roomId, &roomId_src, &flag);

				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d %d %d %d\n", event, museumId, floorNum, roomId, roomId_src, flag);

				/* put your code here */
				R(museumId,floorNum,roomId,roomId_src,flag,&MuseumsList,PAINT,m);
				break;
			}

			/* Add a painting:
			 * N <paintingId> <paintingName> <artistId> <museumId> <floorNum> <roomid> */
			case 'N':
			{
				unsigned int paintingId, artistId, museumId, floorNum, roomId;
				char paintingName[MAX_NAME_LENGTH];
				sscanf(line, "%c %d %s %d %d %d %d", &event, &paintingId, paintingName, &artistId, &museumId, &floorNum, &roomId);

			
				N(paintingId,paintingName,artistId,museumId,floorNum,roomId,&MuseumsList,&ArtistsHead, PAINT, m);
				
				break;
			}

			/* Move a painting from one room to another room (of a possibly different floor and/or museum):
			 * V <paintingID> <museumId> <floorNum> <roomId> <museumId_dest> <floorNum_dest> <roomId_dest> */
			case 'V':
			{
				unsigned int paintingId, museumId, floorNum, roomId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d %d %d %d", &event, &paintingId, &museumId, &floorNum, &roomId, &museumId_dest, &floorNum_dest, &roomId_dest);

				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d %d %d %d %d %d\n", event, paintingId, museumId, floorNum, roomId, museumId_dest, floorNum_dest, roomId_dest);

				/* put your code here */
				V(paintingId,museumId,floorNum,roomId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList, PAINT, m);
				break;
			}

			/* Move all paintings from one room to another room (of a possibly different floor and/or museum):
			 * L <museumId> <floorId> <roomId> <museumId_dest> <floorId_dest> <roomId_dest> */
			case 'L':
			{
				unsigned int museumId, floorNum, roomId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d %d %d", &event, &museumId, &floorNum, &roomId, &museumId_dest, &floorNum_dest, &roomId_dest);

				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d %d %d %d %d\n", event, museumId, floorNum, roomId, museumId_dest, floorNum_dest, roomId_dest);

				/* put your code here */
				L(museumId,floorNum,roomId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList,PAINT,m);

				break;
			}

			/* Merge rooms of the the same museum and the same floor:
			 * G <roomId> <roomId_dest> */
			case 'G':
			{
				unsigned int roomId, roomId_dest;
				sscanf(line, "%c %d %d", &event, &roomId, &roomId_dest);

				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d\n", event, roomId, roomId_dest);

				/* put your code here */
				G(roomId,roomId_dest,&MuseumsList,PAINT,m);
				break;
			}

			/* Temporal painting exhibition of some artist:
			 * I <artistId> <museumÉd_dest> <floorNum_dest> <roomid_dest> */
			case 'I':
			{
				unsigned int artistId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d", &event, &artistId, &museumId_dest, &floorNum_dest, &roomId_dest);

				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d %d %d\n", event, artistId, museumId_dest, floorNum_dest, roomId_dest);

				I(artistId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList,PAINT,m);

				break;
			}

			/* Temporal painting exhibition of some art style:
			 * Y <artStyleId> <museumÉd_dest> <floorNum_dest> <roomid_dest> */
			case 'Y':
			{
				unsigned int artStyleId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d", &event, &artStyleId, &museumId_dest, &floorNum_dest, &roomId_dest);

				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d %d %d\n", event, artStyleId, museumId_dest, floorNum_dest, roomId_dest);

				Y(artStyleId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList,PAINT,m);
				break;
			}

			/* Print works of art of some room:
			 * T <museumId> <floorNum> <roomId> */
			case 'T':
			{
				unsigned int museumId, floorNum, roomId;
				sscanf(line, "%c %d %d %d", &event, &museumId, &floorNum, &roomId);

				/* Un-comment the line below when in debug mode */
				//printf("%c %d %d %d\n", event, museumId, floorNum, roomId);

				/* put your code here */
				T(museumId,floorNum,roomId,&MuseumsList,PAINT, m);
				break;
			}

			/* Print system's data structures:
			 * P */
			case 'P':
			{
				sscanf(line, "%c", &event);

				/* Un-comment the line below when in debug mode */
				//printf("%c\n", event);

				/* put your code here */
				P(&MuseumsList,PAINT, m);
				break;
			}

			/* Ignore everything else */
			default:
				/* Uncomment the line below when in debug mode */
				//printf("---Ignoring line: %s \n", line);

				break;
		}
	}
	
	return (EXIT_SUCCESS);
}



