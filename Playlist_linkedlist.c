#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song_tag SONG;
typedef struct playlist_tag PLAYLIST;

// structure for songs
typedef struct song_tag
{   
    int index;
    char *title;
    char *artist;
    char *album;
    SONG *nextSong;
}SONG;

// structure for playlists
typedef struct playlist_tag
{   
    int index;
    char *name;
    int songCount;
    SONG *songHead;
    PLAYLIST *next;
}PLAYLIST;

// function for checking whether file to be opened is empty
// returns 1 if it is empty, 0 otherwise
int isFileEmpty(FILE *fp)
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

// swaps contents of 2 songs
void song_Swap(SONG *s1,SONG *s2)
{      
    // swap index
    int temp_index = s1->index;
    s1->index = s2->index;
    s2->index = temp_index;
    //swap title
    char *temp_title = s1->title;
    s1->title = s2->title;
    s2->title = temp_title;
    // swap artist
    char *temp_artist = s1->artist;
    s1->artist = s2->artist;
    s2->artist = temp_artist;
    // swap album
    char *temp_album = s1->album;
    s1->album = s2->album;
    s2->album = temp_album;
}

// swaps contents of 2 playlists
void playlist_swap(PLAYLIST *p1,PLAYLIST *p2)
{   
    // swap playlist names
    char* temp_name = p1->name;
    p1->name = p2->name;
    p2->name = temp_name;
    // swap song count
    int temp_songcount = p1->songCount;
    p1->songCount = p2->songCount;
    p2->songCount = temp_songcount;
    // swap songHead
    SONG *temp_songhead = p1->songHead;
    p1->songHead = p2->songHead;
    p2->songHead = temp_songhead;
}

// sorts a linked list of playlists
// using selection sort
void playlist_selectionsort(PLAYLIST *head)
{
    PLAYLIST *start = head;
    PLAYLIST *traverse;
    PLAYLIST *min;
    while(start->next)
    {
        min = start;
        traverse = start->next;
        while(traverse)
        {
            if(strcmp(min->name,traverse->name) > 0)
            {
                min = traverse;
            }
            traverse = traverse->next;
        }
        playlist_swap(start,min);
        start = start->next;
    }
}

// sorts a linked list of songs
// using selection sort
void song_selectionsort(SONG *head)
{
    SONG *start = head;
    SONG *traverse;
    SONG *min;
    while(start->nextSong)
    {
        min = start;
        traverse = start->nextSong;
        while(traverse)
        {
            if(strcmp(min->title,traverse->title) > 0)
            {
                min = traverse;
            }
            traverse = traverse->nextSong;
        }
        song_Swap(start,min);
        start = start->nextSong;
    }
}

void show_songs_only(PLAYLIST *p)
{   
    printf("THE SONGS AVAILABLE ARE:\n");
    SONG *curr = p->songHead;
    while(curr != NULL)
    {
        printf("\t[%d] %s by %s\n",curr->index,curr->title,curr->artist);
        curr = curr->nextSong;
    }
}

void show_playlists_only(PLAYLIST *head)
{   
    printf("THE PLAYLISTS AVAILABLE ARE:\n");
    PLAYLIST *curr = head;
    while(curr != NULL)
    {
        printf("\t[%d] %s\n",curr->index,curr->name);
        curr = curr->next;
    }
}

// initializes a song
void song_init(SONG *s)
{   
    s->title = (char*)malloc(sizeof(char)*50);
    s->artist = (char*)malloc(sizeof(char)*50);
    s->album = (char*)malloc(sizeof(char)*50);
    s->nextSong = NULL;
}

// initializes a playlist
void playlist_init(PLAYLIST *p)
{
    p->name = (char *)malloc(sizeof(char)*50);
    p->songCount = 0;
    p->songHead = malloc(sizeof(SONG));
    song_init(p->songHead);
    p->next = NULL;
}

// inserts a playlist into linked list of playlists in increasing order
void sorted_playlists_insert(PLAYLIST *head,PLAYLIST *new_playlist)
{
    PLAYLIST *curr = head;
    while(curr->next != NULL && strcmp(curr->next->name,new_playlist->name) < 0)
    {
        curr = curr->next;
    }
    new_playlist->next = curr->next;
    curr->next = new_playlist;
}

// inserts a song into linked list of songs in increasing order
void sorted_song_insert(SONG *head,SONG *new_song)
{
    SONG *curr = head;
    while(curr->nextSong != NULL && strcmp(curr->nextSong->title,new_song->title) < 0)
    {
        curr = curr->nextSong;
    }
    new_song->nextSong = curr->nextSong;
    curr->nextSong = new_song;
}

// checks whether new song name is already in the playlist
// returns 1 if yes, 0 otherwise
int isSongRepeat(char *new_song_name, PLAYLIST *p)
{
    SONG *curr;
    curr = p->songHead;
    while(curr != NULL)
    {   
        if(strcmp(new_song_name,curr->title) == 0)
        {
            return 1;
        }
        curr = curr->nextSong;
    }
    return 0;
}

// add new song to a playlist
void add_songs(PLAYLIST *p)
{   
    printf("Enter song title: ");
    char new_song_name[50];
    scanf(" %[^\n]",new_song_name);
    if(isSongRepeat(new_song_name,p) == 1)
    {
        printf("Song already in this playlist!\n");
    }
    else
    {
        if(p->songCount == 0)
        {   
            printf("%d\n",p->songHead->index);
            strcpy(p->songHead->title,new_song_name);
            printf("Enter song's artist: ");
            scanf(" %[^\n]",p->songHead->artist);
            printf("Enter song's album name: ");
            scanf(" %[^\n]",p->songHead->album);
            p->songHead->index = p->songCount;
            p->songCount++;
        }
        else
        {
            SONG *new_song = malloc(sizeof(SONG));
            song_init(new_song);
            strcpy(new_song->title,new_song_name);
            printf("Enter song's artist: ");
            scanf(" %[^\n]",new_song->artist);
            printf("Enter song's album name: ");
            scanf(" %[^\n]",new_song->album);
            new_song->index = p->songCount;
            // insert in proper place
            sorted_song_insert(p->songHead,new_song);
            p->songCount++;
            // sort linked list
            song_selectionsort(p->songHead);
        }
        printf("Successfully added Playlist!\n");
    }
    // make sure that indices are correct
    SONG *curr = p->songHead;
    int start = 0;
    while (curr != NULL)
    {
        curr->index = start;
        curr = curr->nextSong;
        start++;
    }
}

// remove song from a playlist
void remove_song(PLAYLIST *p,SONG **songHead)
{
    if(p->songCount == 0)
    {
        printf("There are no songs in %s yet!\n",*p->name);
    }
    else
    {   
        char *target_song = (char*)malloc(sizeof(char)*50);
        char *target_artist = (char*)malloc(sizeof(char)*50);
        show_songs_only(p);
        printf("Enter song title to delete: ");
        scanf(" %[^\n]",target_song);
        printf("Enter song artist to delete: ");
        scanf(" %[^\n]",target_artist);
        SONG *temp = *songHead;
        SONG *prev;
        if(temp != NULL && (strcmp(temp->title,target_song) == 0) && strcmp(temp->artist,target_artist) == 0)
        {
            *songHead = (*songHead)->nextSong;
            // free(temp);
            p->songCount--;
            printf("successfully deleted song!\n");
        }
        else
        {
            while(temp != NULL && (strcmp(temp->title,target_song) != 0) || strcmp(temp->artist,target_artist) != 0)
            {
                prev = temp;
                temp = temp->nextSong;
            }
            if(temp == NULL)
            {
                printf("Song not found!\n");
            }
            else
            {
                prev->nextSong = temp->nextSong;
                free(temp);
                p->songCount--;
                printf("successfully deleted song!\n");
            }
        }
        free(target_song);
        free(target_artist);
        SONG *curr = *songHead;
        int start = 0;
        while(curr != NULL)
        {
            curr->index = start;
            start++;
            curr = curr->nextSong;
        }
    }
}

// checks whether playlist name already exists
// returns 1 if yes, 0 otherwise
int isPlaylistRepeat(char *new_plist_name, PLAYLIST *head)
{   
    PLAYLIST *curr;
    curr = head;
    while(curr != NULL)
    {   
        if(strcmp(new_plist_name,curr->name) == 0)
        {   
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

// adding a new playlist
void add_playlist(PLAYLIST *head,int playlist_count)
{   
    int num_of_songs;
    char *new_plist_name = (char*)malloc(sizeof(char)*50);
    printf("Enter playlist's name: ");
    scanf(" %[^\n]",new_plist_name);
    if(playlist_count == 0)
    {   
        strcpy(head->name,new_plist_name);
        head->index = playlist_count;
        printf("successfully added playlist %s\n",new_plist_name);
    }
    else
    {
        if(isPlaylistRepeat(new_plist_name,head) == 1)
        {
            printf("Playlist name already exists!\n");
        }
        else
        {   
            PLAYLIST *new_playlist = (PLAYLIST *)malloc(sizeof(PLAYLIST));
            playlist_init(new_playlist);
            strcpy(new_playlist->name,new_plist_name);
            new_playlist->index = playlist_count;
            // insert in proper place
            sorted_playlists_insert(head,new_playlist);
            printf("successfully added playlist %s\n",new_plist_name);
        }
    }
    free(new_plist_name);
    // make sure that indices are correct
    int start = 0;
    PLAYLIST *curr = head;
    while(curr != NULL)
    {
        curr->index = start;
        curr = curr->next;
        start++;
    }
}

// prints details of song
void view_song(SONG *s)
{
    printf("\tSONG TITLE: %s\n",s->title);
	printf("\tSONG ARTIST: %s\n",s->artist);
	printf("\tSONG ALBUM: %s\n",s->album);
}

// prints details of playlist
void view_playlist(PLAYLIST *p)
{   
    printf("PLAYLIST: %s\n",p->name);
    printf("SONG COUNT: %d\n",p->songCount);
    if(p->songCount == 0)
    {
        return;
    }
    SONG *curr = p->songHead;
    while(curr != NULL)
    {
        view_song(curr);
        printf("\n");
        curr = curr->nextSong;
    }
}

// writes details of 1 song to file
void fprintf_songs(FILE *fp, SONG *s, int count)
{
    fprintf(fp,"Title of Song %d \t\t\t\t\t%s\n",count,s->title);
    fprintf(fp,"Artist of Song %d\t\t\t\t\t%s\n",count,s->artist);
    fprintf(fp,"Album of Song %d \t\t\t\t\t%s\n",count,s->album);
}

// writes details of all songs in a playlist to file
void save_songs(FILE *fp,PLAYLIST *p)
{
    SONG *curr = p->songHead;
    int count = 1;
    while(curr != NULL)
    {
        fprintf_songs(fp,curr,count);
        curr = curr->nextSong;
        count++;
    }
}
 
// writes details of a playlist to file
void fprintf_playlist(FILE *fp,PLAYLIST *p,int count)
{
    fprintf(fp,"Name of Playlist %d\t\t\t\t\t%s\n",count,p->name);
    fprintf(fp,"Number of Songs in Playlist %d\t\t\t\t%d\n",count,p->songCount);
    if(p->songCount > 0)
    {
        save_songs(fp,p);
    }
}

// writes all details of all playlists to file
void save_playlist(PLAYLIST *head, int plist_count)
{   
    if(plist_count > 0)
    {   
        FILE *fp = fopen("Playlists.txt","w");
        PLAYLIST *curr = head;
        int count = 1;
        fprintf(fp,"Total Count of the Playlists\t\t\t\t%d\n",plist_count);
        while (curr != NULL)
        {
            fprintf_playlist(fp,curr,count);
            curr = curr->next;
            count++;
        }
        fclose(fp);
        printf("Successfully saved playlist/s!\n");
    }
    else
    {
        printf("There are no playlists yet!\n");
    }
}

// loads details of songs from file to playlist
void fgets_songs(FILE *fp,PLAYLIST *p)
{
    if(p->songCount == 0)
    {
        printf("Playlist %s is empty!\n",p->name);
    }
    else
    {   
        char buffer_str[100];
        int temp_index;
        for(int i = 0;i<p->songCount;i++)
        {
            if(i == 0)
            {
                fgets(buffer_str,sizeof(buffer_str),fp);
                sscanf(buffer_str,"Title of Song %d \t\t\t\t\t%[^\t\n]\n",&temp_index,p->songHead->title);
                p->songHead->index = temp_index - 1;
                fgets(buffer_str,sizeof(buffer_str),fp);
                sscanf(buffer_str,"Artist of Song %*d\t\t\t\t\t%[^\t\n]\n",p->songHead->artist);
                fgets(buffer_str,sizeof(buffer_str),fp);
                sscanf(buffer_str,"Album of Song %*d \t\t\t\t\t%[^\t\n]\n",p->songHead->album);
            }
            else
            {   
                SONG *s = (SONG *)malloc(sizeof(SONG));
                song_init(s);
                fgets(buffer_str,sizeof(buffer_str),fp);
                sscanf(buffer_str,"Title of Song %d \t\t\t\t\t%[^\t\n]\n",&temp_index,s->title);
                s->index = temp_index - 1;
                fgets(buffer_str,sizeof(buffer_str),fp);
                sscanf(buffer_str,"Artist of Song %*d\t\t\t\t\t%[^\t\n]\n",s->artist);
                fgets(buffer_str,sizeof(buffer_str),fp);
                sscanf(buffer_str,"Album of Song %*d \t\t\t\t\t%[^\t\n]\n",s->album);
                sorted_song_insert(p->songHead,s);
            }
        }
    }
}

// loads details of playlist from file
void load_playlist(PLAYLIST *head,int *playlist_count)
{
    FILE *fp = fopen("Playlists.txt","r");
    if(isFileEmpty(fp) == 1)
	{
		printf("The file is empty!\n");
        fclose(fp);
	}
    else
    {
        char buffer_str[100];
        FILE *fp = fopen("Playlists.txt","r");
		fgets(buffer_str,sizeof(buffer_str),fp);
		sscanf(buffer_str,"Total Count of the Playlists\t\t\t\t%d\n",playlist_count);
        if(*playlist_count == 0)
		{
			printf("There are no Playlists!\n");
			fclose(fp);
		}
        else
        {   
            for(int i = 0;i<*playlist_count;i++)
            {   
                if(i == 0)
                {   
                    int temp_songCount;
                    int temp_index;
                    fgets(buffer_str,sizeof(buffer_str),fp);
                    sscanf(buffer_str,"Name of Playlist %d\t\t\t\t\t%[^\t\n]\n",&temp_index,head->name);
                    head->index = temp_index - 1;
                    fgets(buffer_str,sizeof(buffer_str),fp);
                    sscanf(buffer_str,"Number of Songs in Playlist %*d\t\t\t\t%d\n",&temp_songCount);
                    head->songCount = temp_songCount;
                    fgets_songs(fp,head);
                }
                else
                {   
                    int temp_song_count;
                    int temp_index;
                    PLAYLIST *p = (PLAYLIST *)malloc(sizeof(PLAYLIST));
                    playlist_init(p);
                    fgets(buffer_str,sizeof(buffer_str),fp);
                    sscanf(buffer_str,"Name of Playlist %d\t\t\t\t\t%[^\t\n]\n",&temp_index,p->name);
                    p->index = temp_index - 1;
                    fgets(buffer_str,sizeof(buffer_str),fp);
                    sscanf(buffer_str,"Number of Songs in Playlist %*d\t\t\t\t%d\n",&temp_song_count);
                    p->songCount = temp_song_count;
                    fgets_songs(fp,p);
                    sorted_playlists_insert(head,p);
                }   
            }
        }
        printf("Successfully loaded data!\n");
    }
    
}

int main()
{   
    int playlist_count = 0;
    PLAYLIST *plist_head = (PLAYLIST *)malloc(sizeof(PLAYLIST));
    playlist_init(plist_head);
    load_playlist(plist_head,&playlist_count);
    while(1)
    {
        // menu and the choices
		printf("======= MENU =======\n");
		printf("[1] Add Playlist\n[2] Add Song to Playlist\n");
		printf("[3] Remove Song from Playlist\n[4] View a Playlist\n");
		printf("[5] View All Data\n[6] Exit\n");
		int choice;
		printf("Enter choice: ");
		scanf("%d",&choice);
		// conditions for choice
        if(choice == 1)
        {   
            add_playlist(plist_head,playlist_count);
            playlist_count++;
            playlist_selectionsort(plist_head);
        }
        else if(choice == 2)
        {
            if(playlist_count == 0)
            {
                printf("There are no playlists yet!\n");
            }
            else
            {       
                show_playlists_only(plist_head);
                printf("Enter playlist name: ");
				char target_playlist[50];
				scanf(" %[^\n]",target_playlist);
                PLAYLIST *curr = plist_head;
                int found = 0;
                while (curr != NULL)
                {
                    if(strcmp(curr->name,target_playlist) == 0)
                    {   
                        add_songs(curr);
                        found = 1;
                        break;
                    }
                    curr = curr->next;
                }
                if(found == 0)
                {
                    printf("Invalid Playlist!\n");
                }
            }
        }
        else if(choice == 3)
        {
            if(playlist_count == 0)
            {
                printf("There are no playlists yet!\n");
            }
            else
            {   
                show_playlists_only(plist_head);
                printf("Enter playlist name: ");
				char target_playlist[50];
				scanf(" %[^\n]",target_playlist);
                PLAYLIST *curr = plist_head;
                while (curr != NULL)
                {
                    if(strcmp(curr->name,target_playlist) == 0)
                    {
                        remove_song(curr,&(curr->songHead));
                        break;
                    }
                    curr = curr->next;
                }
                if(curr == NULL)
                {
                    printf("Target playlist not found!\n");
                }
            }
        }
        else if(choice == 4)
        {
            if(playlist_count == 0)
            {
                printf("There are no playlists yet!\n");
            }
            else
            {   
                show_playlists_only(plist_head);
                printf("Enter playlist name: ");
				char target_playlist[60];
				scanf(" %[^\n]",target_playlist);
                PLAYLIST *curr = plist_head;
                while (curr != NULL)
                {   
                    if(strcmp(curr->name,target_playlist) == 0)
                    {   
                        view_playlist(curr);
                        break;
                    }
                    curr = curr->next;
                }
                if(curr == NULL)
                {
                    printf("Target playlist not found!\n");
                }
            }
        }
        else if(choice == 5)
        {   
            if(playlist_count == 0)
            {
                printf("There are no playlists yet!\n");
            }
            else
            {
                PLAYLIST *curr = plist_head;
                while(curr != NULL)
                {   
                    view_playlist(curr);
                    curr = curr->next;
                }
            }
        }
        else if(choice == 6)
        {   
            save_playlist(plist_head,playlist_count);
            free(plist_head->songHead);
            free(plist_head);
            break;
        }
        else
        {
            printf("Invalid choice number!\n");
        }
        
    }   
}