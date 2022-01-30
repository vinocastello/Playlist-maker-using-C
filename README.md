# Playlist-maker-using-C
This C program allows the user to create and view a playlist as well as add and remove songs from it
## Preview of menu
```
======= MENU =======
[1] Add Playlist
[2] Add Song to Playlist
[3] Remove Song from Playlist
[4] View a Playlist
[5] View All Data
[6] Exit
Enter choice:
```
The user will be prompted to enter the corresponding number of the operation desired.
Note that initially, the program will load from a text file that contains the information about the playlists and their songs.
When the user chooses [6] Exit, the text file will be updated to contain the saved playlists and the songs they contain.
## The differences betweens Playlist_arrays.c and Playlist_linkedlist.c
- When adding/removing a song to/from an existing playlist, the user will be prompted to enter the target playlist's number in Playlist_arrays.c while in Playlist_linkedlist.c, the user will be prompted to enter the name of the target playlist.
- When viewing a playlist, the user will be prompted to enter the target playlist's number in Playlist_arrays.c while in Playlist_linkedlist.c, the user will be prompted to enter the name of the target playlist.
- When removing a song, the user will be prompted to enter the number of the song to be removed in Playlist_arrays.c while in Playlist_linkedlist.c, the user will be prompted to enter the title of the target song and its artist
- Playlist_arrays.c stores the playlists in an array of struct for the playlist and the songs are stored in an array of struct for the songs
- Playlist_linkedlist.c stores the playlists in a linked list of playlist structs while the songs are stored in each playlist's linked list of songs
- Playlist_arrays.c stores and saves the state of the playlists in playlist in playlists_arr.txt
- Playlist_linkedlist.c stores and saves the state of the playlists in playlists_linkedlist.txt
