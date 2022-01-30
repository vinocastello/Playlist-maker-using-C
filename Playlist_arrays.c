#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for song
typedef struct song
{
	char title[50];
	char artist[50];
	char album[50];
}SONG;

// structure for playlist
typedef struct playlist
{
	char name[50];
	int song_count;
	SONG songs[10];
}PLAYLIST;

// looks for index of song with matching song name in array of songs
// returns index
int find_song(char *song_name,SONG songs[10],int song_count)
{	
	for(int i = 0;i<song_count;i++)
	{	
		if(strcmp(songs[i].title,song_name) == 0)
		{	
			return i;
		}
	}
	return -1;
}

void show_songs_only(PLAYLIST *p)
{	
	printf("THE SONGS AVAILABLE ARE:\n");
	for(int i = 0;i<p->song_count;i++)
	{
		printf("\t[%d] %s by %s\n",i,p->songs[i].title,p->songs[i].artist);
	}
}

void show_playlists_only(PLAYLIST plist[10],int plists_index)
{	
	printf("THE PLAYLISTS AVAILABLE ARE:\n");
	for(int i = 0;i<plists_index;i++)
	{
		printf("\t[%d] %s\n",i,plist[i].name);
	}
}

// add a new song to a playlist
void add_song(PLAYLIST *p)
{
	if(p->song_count != 10)
	{	
		char new_song[20];
		printf("Enter song title: ");
		scanf(" %[^\n]",new_song);
		if(find_song(new_song,p->songs,p->song_count) != -1)
		{
			printf("Song already in this playlist!\n");
		}
		else
		{	
			strcpy(p->songs[p->song_count].title,new_song);
			printf("Enter song artist: ");
			scanf(" %[^\n]",p->songs[p->song_count].artist);
			printf("Enter song album: ");
			scanf(" %[^\n]",p->songs[p->song_count].album);
			p->song_count++;
			printf("successfully added %s to %s\n",p->songs[p->song_count-1].title,p->name);
		}
	}
	else
	{
		printf("Playlist %s is full!\n",p->name);
	}
}

// remove a song from a playlist
void remove_song(PLAYLIST *p)
{	
	int target_song;
	show_songs_only(p);
	printf("Enter song number to delete: ");
	scanf("%d",&target_song);
	if(target_song < p->song_count)
	{
		for(int i = target_song;i<p->song_count;i++)
		{
			p->songs[i] = p->songs[i+1];
			p->song_count--;
		}
		printf("successfully deleted song!\n");
	}
	else
	{
		printf("Invalid song number!\n");
	}	
}

// prints details of a song
void view_song(SONG s)
{
	printf("\tSONG TITLE: %s\n",s.title);
	printf("\tSONG ARTIST: %s\n",s.artist);
	printf("\tSONG ALBUM: %s\n",s.album);
}

// writes details of a song to file
void fprintf_songs(FILE *fp,PLAYLIST p)
{
	if(p.song_count > 0)
	{
		for(int i = 0;i<p.song_count;i++)
		{
			fprintf(fp,"Title of Song %d \t\t\t\t\t%s\n",(i+1),p.songs[i].title);
			fprintf(fp,"Artist of Song %d\t\t\t\t\t%s\n",(i+1),p.songs[i].artist);
			fprintf(fp,"Album of Song %d \t\t\t\t\t%s\n",(i+1),p.songs[i].album);
		}
	}
}

// loads details of songs from file to a playlist
void fgets_songs(FILE *fp, PLAYLIST *p)
{
	if(p->song_count == 0)
	{
		printf("Playlist is empty!\n");
	}
	else
	{
		for(int i = 0;i<p->song_count;i++)
		{	
			char buffer_str[100];
			fgets(buffer_str,sizeof(buffer_str),fp);
			sscanf(buffer_str,"Title of Song %*d \t\t\t\t\t%s\n",p->songs[i].title);
			fgets(buffer_str,sizeof(buffer_str),fp);
			sscanf(buffer_str,"Artist of Song %*d\t\t\t\t\t%s\n",p->songs[i].artist);
			fgets(buffer_str,sizeof(buffer_str),fp);
			sscanf(buffer_str,"Album of Song %*d \t\t\t\t\t%s\n",p->songs[i].album);
		}
	}
}

// looks for index of playlist with matching playlist name in array of playlists
// returns index
int find_playlist(char* str,PLAYLIST plists[10],int plists_index)
{
	for(int i = 0;i<plists_index;i++)
	{
		if(strcmp(plists[i].name,str) == 0)
		{
			return i;
		}
	}
	return -1;
}

// prints details of a playlist
void view_playlist(PLAYLIST plists[10],int target_index)
{
	printf("PLAYLIST: %s\n",plists[target_index].name);
	printf("SONG COUNT: %d\n",plists[target_index].song_count);
	for(int i = 0;i<plists[target_index].song_count;i++)
	{	
		view_song(plists[target_index].songs[i]);
		printf("\n");
	}
}

// writes details of all playlists to file
void fprintf_playlists(FILE *fp,PLAYLIST plists[10],int plists_index)
{
	for(int i = 0;i<plists_index;i++)
	{
		fprintf(fp,"Name of Playlist %d\t\t\t\t\t%s\n",(i+1),plists[i].name);
		fprintf(fp,"Number of Songs in Playlist %d\t\t\t\t%d\n",(i+1),plists[i].song_count);
		fprintf_songs(fp,plists[i]);
	}
}

// saving all playlists to file
void savePlaylists(PLAYLIST plists[10],int plists_index)
{	
	if(plists_index != 0)
	{
		FILE *fp = fopen("playlists.txt","w");
		fprintf(fp,"Total Count of the Playlists\t\t\t\t%d\n",plists_index);
		fprintf_playlists(fp,plists,plists_index);
		fclose(fp);
		printf("Successfully saved playlist/s!\n");
	}
	else
	{
		printf("There is nothing to save!\n");
	}
	
}

// add a new playlist to array of playlists
void add_playlist(PLAYLIST plists[10], int index)
{	
	int num_of_songs;
	plists[index].song_count = 0;
	printf("Enter playlist's name: ");
	char plist_name[50];
	scanf(" %[^\n]",plist_name);
	if(find_playlist(plist_name,plists,index) != -1)
	{
		printf("Playlist name already exists!\n");
	}
	else
	{
		strcpy(plists[index].name,plist_name);
		printf("Successfully added playlist!\n");
	}
}

// checks whether file pointed to by fp is empty or not
// returns 1 if yes, 0 otherwise
int isFileEmpty(FILE *fp)
{	
	if(fp == NULL)
	{
		return 0;
	}
	else
	{
		fseek (fp, 0, SEEK_END);
		int size = ftell(fp);
		if (size == 0) 
		{
			return 1;
		}
		else
		{
			return 0;
		}	
	}
}
 
// loads details of all playlists from file
void load_playlists(PLAYLIST plists[10],int *plists_index)
{
	FILE *fp = fopen("playlists.txt","r+");
	if(isFileEmpty(fp) == 1)
	{
		printf("The file is empty!\n");
	}
	else
	{	
		FILE *fp = fopen("playlists.txt","r+");
		char buffer_str[100];
		fgets(buffer_str,sizeof(buffer_str),fp);
		sscanf(buffer_str,"Total Count of the Playlists\t\t\t\t%d\n",plists_index);
		if(*plists_index == 0)
		{
			printf("There are no Playlists!\n");
			fclose(fp);
		}
		else
		{
			for(int i = 0;i<(*plists_index);i++)
			{	
				fgets(buffer_str,sizeof(buffer_str),fp);
				sscanf(buffer_str,"Name of Playlist %*d\t\t\t\t\t%s\n",plists[i].name);
				fgets(buffer_str,sizeof(buffer_str),fp);
				sscanf(buffer_str,"Number of Songs in Playlist %*d\t\t\t\t%d\n",&plists[i].song_count);
				fgets_songs(fp,&plists[i]);
			}
			printf("Successfully loaded data!\n");
		}
	}
}

int main()
{	
	PLAYLIST plists[10];
	int plists_index = 0;
	load_playlists(plists,&plists_index);
	while(1)
	{	
		// menu and the choices
		printf("======= MENU =======\n");
		printf("[1] Add Playlist\n[2]Add Song to Playlist\n");
		printf("[3] Remove Song from Playlist\n[4] View a Playlist\n");
		printf("[5] View All Data\n[6] Exit\n");
		int choice;
		printf("Enter choice: ");
		scanf("%d",&choice);
		// conditions for choice
		if(choice == 1)
		{
			if(plists_index != 9)
			{
				add_playlist(plists,plists_index);
				plists_index++;
			}
			else
			{
				printf("You already have 10 playlists!\n");
			}
		}
		else if(choice == 2)
		{	
			if(plists_index == 0)
			{
				printf("There are no playlists yet!\n");
			}
			else
			{	
				show_playlists_only(plists,plists_index);
				printf("Enter playlist number: ");
				int target_playlist;
				scanf("%d",&target_playlist);
				if(target_playlist >= plists_index)
				{
					printf("Invalid playlist!\n");
					
				}
				else
				{
					add_song(&plists[target_playlist]);
				}
			}
		}
		else if(choice == 3)
		{
			if(plists_index == 0)
			{
				printf("There are no playlists yet!\n");				
			}
			else
			{
				show_playlists_only(plists,plists_index);
				printf("Enter playlist number: ");
				int target_playlist;
				scanf("%d",&target_playlist);
				if(target_playlist >= plists_index)
				{
					printf("Invalid playlist!\n");
					
				}
				else
				{	
					if(plists[target_playlist].song_count == 0)
					{
						printf("Playlist is still empty!\n");
					}
					else
					{	
						remove_song(&plists[target_playlist]);
					}
				}
			}
		}
		else if(choice == 4)
		{
			if(plists_index == 0)
			{
				printf("There are no playlists yet!\n");
			}
			else
			{
				show_playlists_only(plists,plists_index);
				printf("Enter playlist number: ");
				int target_playlist;
				scanf("%d",&target_playlist);
				if(target_playlist >= plists_index)
				{
					printf("Invalid playlist!\n");
					
				}
				else
				{
					view_playlist(plists,target_playlist);
				}
			}
		}
		else if(choice == 5)
		{
			if(plists_index == 0)
			{
				printf("There are no playlists yet!\n");
			}
			else
			{
				for(int i = 0;i<plists_index;i++)
				{
					view_playlist(plists,i);
				}
			}
		}
		else if(choice == 6)
		{	
			savePlaylists(plists,plists_index);
			break;
		}

	}
	return 0;
}