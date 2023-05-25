#include "shell.h"
/**
•	get_unique_history_file - gets a unique history file name
•	@info: parameter struct
•	Return: allocated string containing a unique history file name */
char *get_unique_history_file(info_t *info) { char *buf, *dir;
}
/**
•	save_history - creates a file and saves the command history
•	@info: the parameter struct
•	Return: 1 on success, else -1 */ int save_history(info_t *info) { ssize_t fd; char *filename = get_unique_history_file(info); list_t *node = NULL;
if (!filename) return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644); free(filename); if (fd == -1) return (-1); for (node = info->history; node; node = node->next) { _putsfd(node->str, fd); _putfd('\n', fd); } _putfd(BUF_FLUSH, fd); close(fd); return (1); }
/**
•	load_history - loads command history from a file
•	@info: the parameter struct
•	Return: histcount on success, 0 otherwise */ int load_history(info_t *info) { int i, last = 0, linecount = 0; ssize_t fd, rdlen, fsize = 0; struct stat st; char *buf = NULL, *filename = get_unique_history_file(info);
if (!filename) return (0);
fd = open(filename, O_RDONLY); free(filename); if (fd == -1) return (0); if (!fstat(fd, &st)) fsize = st.st_size; if (fsize < 2) return (0); buf = malloc(sizeof(char) * (fsize + 1)); if (!buf) return (0); rdlen = read(fd, buf, fsize); buf[fsize] = 0; if (rdlen <= 0) return (free(buf), 0); close(fd); for (i = 0; i < fsize; i++) if (buf[i] == '\n') { buf[i] = 0; add_history_entry(info, buf + last, linecount++); last = i + 1; } if (last != i) add_history_entry(info, buf + last, linecount++); free(buf); info->histcount = linecount; while (info->histcount-- >= HIST_MAX) delete_node_at_index(&(info->history), 0); renumber_history(info); return (info->histcount); }
/**
•	add_history_entry - adds an entry to the history linked list
•	@info: parameter struct
•	@buf: buffer
•	@linecount: the history line count
•	Return: Always 0 */ int add_history_entry(info_t *info, char *buf, int linecount) { list_t *node = NULL;
if (info->history) node = info->history; add_node_end(&node, buf, linecount);
if (!info->history) info->history = node; return (0); }
/**
•	renumber_history - renumbers the history linked list after changes
•	@info: parameter struct
•	Return: the new histcount */ int renumber_history(info_t *info) { list_t *node = info->history; int i = 0;
while (node) { node->num = i++; node = node->next; } return (info->histcount = i); }
