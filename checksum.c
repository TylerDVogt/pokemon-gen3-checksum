#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <byteswap.h>
#include "checksum.h"


#define SECTION_SIZE 4096
#define SECTIONS 14

int main(int argc, char *argv[]){   
    if(argc != 3){
        printf("Error: Please specify the .sav file and section ID\n");
        return -1;
    }
    uint16_t checksum = calculateChecksum(argv[1],atoi(argv[2]));
    printf("Calculated checksum for section %i is: 0x%x\n",atoi(argv[2]), checksum);
    return 0;
}

uint16_t calculateChecksum(char *fileName, int sectionId){
    uint32_t checksum = 0;
    uint16_t upperBits = 0;
    uint16_t lowerBits = 0;
    unsigned int buffer = 0;
    unsigned int offset = getOffsetToSection(fileName, sectionId);
    if(offset == -1){
        printf("Error, couldn't find the offset to the specified section.\n");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(fileName, "rb");
    fseek(file, offset, SEEK_SET);

    for(int i = 0; i < getValidationBytes(sectionId) && !feof(file); i+=4){
        fread(&buffer, 4, 1, file);
        checksum += buffer;
    }
    fclose(file);
    upperBits = checksum >> 16;
    lowerBits = checksum & 0xFFFF;
    return upperBits+lowerBits;
}



unsigned int getOffsetToSection(char *fileName, int sectionId){
    unsigned int buffer = 0;
    unsigned int offset = 0;
    int i = 0;
    FILE *file = fopen(fileName, "rb");
    if(getRecentSaveBlock(fileName) == 1){
        offset += SECTION_SIZE*SECTIONS;
    }
    while (!feof(file) && i < SECTIONS)
    {
        if(i == 0){
            offset += SECTION_SIZE - 12;
        }else{
            offset += SECTION_SIZE;
        }
        fseek(file, offset, SEEK_SET);
        fread(&buffer, 2, 1, file);
        if(buffer == sectionId){
            fclose(file);
            return offset - (SECTION_SIZE - 12);
        }
        i++;
    }
    fclose(file);
    return -1;

}

int getRecentSaveBlock(char *fileName){//0 = Recent save in first block, 1 = Recent save in second block
    unsigned int buffer = 0;
    int firstBlock = 0;
    FILE *file = fopen(fileName, "rb");
    fseek(file, (SECTION_SIZE*SECTIONS)-4, SEEK_SET);
    fread(&buffer, 4, 1, file);
    firstBlock = buffer;
    fseek(file, ((SECTION_SIZE*SECTIONS)*2)-4, SEEK_SET);
    fread(&buffer, 4, 1, file);
    fclose(file);
    if(firstBlock > buffer){
        return 0;
    }else{
        return 1;
    }
}





int getValidationBytes(int section){
    switch(section){
        case 0:
            return 3884;
        case 1:
            return 3968;
        case 2:
            return 3968;
        case 3:
            return 3968;
        case 4:
            return 3848;
        case 5:
            return 3968;
        case 6:
            return 3968;
        case 7:
            return 3968;
        case 8:
            return 3968;
        case 9:
            return 3968;
        case 10:
            return 3968;
        case 11:
            return 3968;
        case 12:
            return 3968;
        case 13:
            return 2000;
    }
}