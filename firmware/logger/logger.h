
#ifndef LOGGER_H
#define LOGGER_H

// Functions used by libraries
// extern void void info(const char * name, const char * data);
// extern void error(int error_id);

void info(const char * name, const char * data);
void error(int error_id);

int std_out(const char * data);
int std_err(const char * data);

#endif // LOGGER_H
