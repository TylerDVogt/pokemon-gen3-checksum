# pokemon-gen3-checksum
Calculates the specified section's checksum on a gen3 .sav file. Coded in C.

This program is the first step to save file editing and can be used to create larger programs.

Run "make" to build the program.

The program takes two arguments: The .sav file path and the section being calculated respectively.

When making any changes to a gen3 save file, the checksum for the respective section changes. When this checksum is incorrect, the save file will be corrupted. Using this program, you can make edits on the save file, calculate the new checksum, then replace the old checksum.

![image](https://github.com/TylerDVogt/pokemon-gen3-checksum/assets/89884480/7e2b073a-7411-4cbf-bced-143a5f52d907)

Every time the game is saved, the previous and newest save are swapped. The program takes that into account and finds the offset to the newest save file.

![image](https://github.com/TylerDVogt/pokemon-gen3-checksum/assets/89884480/49bcb410-da4b-4df0-96b1-b75dad52f565)

There are 14 sections, each being 4096 bytes,

![image](https://github.com/TylerDVogt/pokemon-gen3-checksum/assets/89884480/2cc2d029-9e95-4ee5-b2e8-4331275460d9)

Each section is 4096 bytes despite the table above being less. This is because there is other random data stored in each section such as pokedex data.
An easy way to find a section is to search for the signature magic number 0x08012025 in little-endian format. Two bytes before this is the section id. Make sure you are editing the correct save block.
