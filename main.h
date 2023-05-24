#ifndef MAIN_H
#define MAIN_H
int main(void);
void command_path(char *command, char **arguments);
char command_line(char *command, char *path);
char *file_path(char *file);
void handle_cd(char **arguments)

void handle_Set_env(char **arguments);
void handleExit(char *status);
void handle_Unsetenv(char **arguments);
char* customGetLine();
int countArguments(char *command);
#endif
