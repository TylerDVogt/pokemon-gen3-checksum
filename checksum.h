#ifndef CHECKSUM_H
#define CHECKSUM_H



int getValidationBytes(int section);
uint16_t calculateChecksum(char *fileName, int sectionId);
unsigned int getOffsetToSection(char *fileName, int sectionId);
int getRecentSaveBlock(char *fileName);

#endif