typedef struct {
	void(*command)(int, char**);
	char * cmdstr;
	int keyval;
} command_t;

void init_commands(void);
void deinit_commands(void);
void execute(int);

