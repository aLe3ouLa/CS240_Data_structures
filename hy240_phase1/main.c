#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "events.h"

#define LINE_LENGTH 	1024	/* Maximum length of a line in input file */


ARTSTYLE *ArtStylesList;	/* List of art styles */
ARTIST *ArtistsList;		/* List of artists */
MUSEUM *MuseumsList;		/* List of museums */
PAINTING *PaintingsList = NULL;	 /*List of paintings */


int main(int argc, char** argv){

	FILE *fin = NULL;
	char line[LINE_LENGTH], event, *delim=" ";
	int i,j;
	ARTIST * Guard;


	/* Check command line arguments */
	if ( argc != 2 )	{
		printf("Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		printf("\n Could not open file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	/* Put your initialization code here */
	Guard = guardNode(&ArtistsList);

	/* Read input file line-by-line and handle the events */
	while( fgets(line, LINE_LENGTH, fin) != NULL ) {

		/* Un-comment the line below when in debug mode */

		/*printf("Event: %s \n", line);*/

		switch(line[0]) {

			/* Add a new art style:
			 * S <artStyleId> <styleName> */
			case 'S':
			{
				unsigned int artStyleId;
				char styleName[MAX_NAME_LENGTH];
				sscanf(line, "%c %d %s", &event, &artStyleId, styleName);
				S(artStyleId,styleName,&ArtStylesList);

				break;
			}

			/* Add a new artist:
			 * A <artistId> <artistName> <YearOfBirth> <YearOfDeath> <artStyleId> */
			case 'A':
			{
				unsigned int artistId, YearOfBirth, YearOfDeath, artStyleId;
				char artistName[MAX_NAME_LENGTH];
				sscanf(line, "%c %d %s %d %d %d", &event, &artistId, artistName, &YearOfBirth, &YearOfDeath, &artStyleId);

				A(artistId,artistName,YearOfBirth,YearOfDeath,artStyleId,&ArtistsList,&ArtStylesList, Guard);

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
				roomIds = (unsigned int **) malloc ((f+1)*sizeof(unsigned int *));
				roomNums = (unsigned int *) malloc ((f+1)*sizeof(unsigned int));

				for (i=0; i<=f; i++) {							/* CHANGE: i<f --> i<=f */
					fgets(line, LINE_LENGTH, fin);					/* CHANGE: ADDED */

					roomNums[i] = atoi(strtok(line, delim));			/* CHANGE: strtok(NULL, delim) -->  strtok(line, delim)*/
					roomIds[i] = (unsigned int *) malloc (roomNums[i]*sizeof( unsigned int));



					for (j=0; j<roomNums[i]; j++) {
						roomIds[i][j] = atoi(strtok(NULL, delim));

					}
				}

				M(&MuseumsList,museumId,museumName,museumAddress,f,roomIds,roomNums);

				break;
			}

			/* Add another floor to some museum:
			 * O <museumId> <r> <roomId1> ... <roomId<r>> */
			case 'O':
			{
				unsigned int museumId, r, *roomIds;
				sscanf(line, "%c %d %d", &event, &museumId, &r);
				roomIds = malloc (r*sizeof(int));

				strtok(line, delim);
				for (i=0; i < 2; i++)
					strtok(NULL, delim);

				for (i=0; i<r; i++) {
					roomIds[i] = atoi(strtok(NULL, delim));

				}

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

				R(museumId,floorNum,roomId,roomId_src,flag,&MuseumsList,&PaintingsList);

				break;
			}

			/* Add a painting:
			 * N <paintingId> <paintingName> <artistId> <museumId> <floorNum> <roomid> */
			case 'N':
			{
				unsigned int paintingId, artistId, museumId, floorNum, roomId;
				char paintingName[MAX_NAME_LENGTH];
				sscanf(line, "%c %d %s %d %d %d %d", &event, &paintingId, paintingName, &artistId, &museumId, &floorNum, &roomId);

				N(paintingId,paintingName,artistId,museumId,floorNum,roomId, &PaintingsList,&MuseumsList,&ArtistsList,&Guard);
				break;
			}

			/* Move a painting from one room to another room (of a possibly different floor and/or museum):
			 * V <paintingID> <museumId> <floorNum> <roomId> <museumId_dest> <floorNum_dest> <roomId_dest> */
			case 'V':
			{
				unsigned int paintingId, museumId, floorNum, roomId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d %d %d %d", &event, &paintingId, &museumId, &floorNum, &roomId, &museumId_dest, &floorNum_dest, &roomId_dest);

				V(paintingId,museumId,floorNum,roomId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList,&PaintingsList);

				break;
			}

			/* Move all paintings from one room to another room (of a possibly different floor and/or museum):
			 * L <museumId> <floorId> <roomId> <museumId_dest> <floorId_dest> <roomId_dest> */
			case 'L':
			{
				unsigned int museumId, floorNum, roomId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d %d %d", &event, &museumId, &floorNum, &roomId, &museumId_dest, &floorNum_dest, &roomId_dest);


				L(museumId,floorNum,roomId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList,&PaintingsList);

				break;
			}

			/* Merge rooms of the the same museum and the same floor:
			 * G <roomId> <roomId_dest> */
			case 'G':
			{
				unsigned int roomId, roomId_dest;
				sscanf(line, "%c %d %d", &event, &roomId, &roomId_dest);

				G(roomId,roomId_dest,&MuseumsList,&PaintingsList);


				break;
			}

			/* Temporal painting exhibition of some artist:
			 * I <artistId> <museumÉd_dest> <floorNum_dest> <roomid_dest> */
			case 'I':
			{
				unsigned int artistId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d", &event, &artistId, &museumId_dest, &floorNum_dest, &roomId_dest);


				I(artistId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList,&PaintingsList);

				break;
			}

			/* Temporal painting exhibition of some art style:
			 * Y <artStyleId> <museumÉd_dest> <floorNum_dest> <roomid_dest> */
			case 'Y':
			{
				unsigned int artStyleId, museumId_dest, floorNum_dest, roomId_dest;
				sscanf(line, "%c %d %d %d %d", &event, &artStyleId, &museumId_dest, &floorNum_dest, &roomId_dest);


				Y(artStyleId,museumId_dest,floorNum_dest,roomId_dest,&MuseumsList,&PaintingsList);
				break;
			}

			/* Print works of art of some room:
			 * T <museumId> <floorNum> <roomId> */
			case 'T':
			{
				unsigned int museumId, floorNum, roomId;
				sscanf(line, "%c %d %d %d", &event, &museumId, &floorNum, &roomId);


				T(museumId,floorNum,roomId,&MuseumsList,&PaintingsList);
				break;
			}

			/* Print system's data structures:
			 * P */
			case 'P':
			{
				sscanf(line, "%c", &event);


				P(&MuseumsList,&PaintingsList);

				break;
			}

			/* Ignore everything else */
			default:

				break;
		}
	}

	return (EXIT_SUCCESS);
}



