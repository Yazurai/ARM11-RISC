#ifndef MESSAGES_H
#define MESSAGES_H

// Error and general console messages
#define MSG_ERR_FOPEN "Could not open file.\n"
#define MSG_ERR_FILE_EX_MEMORY "Binary file size exceeds memory (max %d, required %d).\n"
#define MSG_ERR_NOT_ENOUGH_ARG "Not enough arguments.\n"
#define MSG_ERR_NOT_ENOUGH_MEMORY "There isn't enough memory."
#define MSG_ERR_FILE_READ "There was a problem reading the file.\n"
#define MSG_ERR_FILE_WRITE "There was a problem writing to the file.\n"
#define MSG_ERR_INVALID_INSTRUCTION "There was an invalid instruction (I: %08x).\n"
#define MSG_ERR_INVALID_OPCODE "The opcode of the instruction is invalid (I: %08x).\n"
#define MSG_ERR_INVALID_CONDITION "The condition code of the instruction is invalid. (I: %08x).\n"
#define MSG_ERR_INVALID_ADDRESS "The address the instruction points to is invalid. (I: %08x).\n"
#define MSG_ERR_MEMORY_ALLOCATION "Failed to allocate memory at location: %x.\n"
#define MSG_ERR_MEMORY_ALLOCATION_NO_DETAIL "Failed to allocate memory.\n"
#define MSG_INVALID_ASSEMBLY_LINE "Unsupported or invlaid assembly instruction.\n"
#endif
