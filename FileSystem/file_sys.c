#include <malloc.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct file_node
{
	char* node_name;
	char* path;
	char* content;
	int node_type;

	struct file_node *adjecent_node;
	struct file_node *first_child;
	struct file_node *parent;
}file;
 
file *root, *pwd, *pwd_last;

int to_num(char *cmd)
{
	int choice, i;
	char commands[9][50] = {"pwd", "ls", "cd", "mkdir", "touch", "rmdir", "rm", "find", "exit"};

	for(i = 0;i < 9;i++)
	{
		if(!strcmp(cmd, commands[i]))
				return i;
	}
	return -1;
}
 
void NewNode(char*, int);
void mkdir();
void rmdir();
void Init();
void cd();
void ls();
void touch();
file* find(char*, file*);
file* find_rec(char*, file*);

void main()
{
	int choice;
	char cmd[20], tmp[50];

	Init();

	while(1)
	{
		scanf("%s", cmd);

		choice = to_num(cmd);

		switch(choice)
		{
			case 0: strcpy(tmp, pwd->path);
					strcat(tmp, pwd->node_name);	
					printf("%s\n", tmp);
					break;
			case 1: ls();
					break;
			case 2: cd();
					break;
			case 3: mkdir();
					break;
			case 4: touch();
					 break;
			case 5: rmdir(); 
					break;
			case 6: rmdir();
					break;
			case 7: scanf("%s", tmp);
					if(find_rec(tmp, pwd))
						printf("Found\n");
					else
						printf("Not Found\n");
					break;
			case 8: exit(0);
					break;
			default: printf("bash: No such command\n");
		}
	}
}
 
void NewNode(char *name, int type)
{
	int temp = strlen(pwd->node_name) + strlen(pwd->path);

	file* new_node = (file*)malloc(sizeof(file));

	new_node->node_name = (char*)malloc(strlen(name)*sizeof(char));
	new_node->path = (char*)malloc((temp+1)*sizeof(char));
	
	strcpy(new_node->node_name, name); 
	strcpy(new_node->path, pwd->path);
	strcat(new_node->path, pwd->node_name);
	new_node->path[temp] = '/';
	new_node->path[temp+1] = '\0';
	
	new_node->content = 0;
	new_node->node_type = type;
	new_node->adjecent_node = 0; 
	new_node->first_child = 0;
	new_node->parent = pwd;

	if(!(pwd->first_child))
	{
		pwd->first_child = new_node;
	}
	else
	{
		pwd_last->adjecent_node = new_node;
	}
	pwd_last = new_node;
}

void Init()
{
	root = (file*)malloc(sizeof(file));

	root->node_name = (char*)malloc(sizeof(char));
	root->path = (char*)malloc(sizeof(char));

	root->path[0] = '\0';
	root->node_name[0] = '~';
	root->content = 0;
	root->node_type = 1;
	root->first_child = 0;
	root->adjecent_node = 0;
	root->parent = 0;

	pwd = root;
	pwd_last = 0;	
}
void mkdir()
{
	char name[50];

	scanf("%s", name);
 
	NewNode(name, 1);
}
void touch()
{
	char name[50];

	scanf("%s", name);

	NewNode(name, 0);
}
void rmdir()
{ 
	char name[50];

	file *del_file, *temp;

	scanf("%s", name);

	del_file = find(name, pwd);

	if(del_file)
	{  
		if(del_file == pwd->first_child)
		{
			pwd->first_child = del_file->adjecent_node;

			if(pwd_last == del_file)
				pwd_last = 0;
		}
		else
		{
			temp = pwd->first_child;

			while(temp->adjecent_node != del_file)
				temp = temp->adjecent_node;

			temp->adjecent_node = del_file->adjecent_node;

			if(pwd_last == del_file)
				pwd_last = temp;
		}	
		
		free(del_file);
	}
	else
		printf("bash: No such file or directory");
}
file* find(char *name, file *search_dir)
{
	file* temp;

	temp = search_dir->first_child;

	while(temp)
	{
		if(!strcmp(temp->node_name ,name))
			return temp;
		temp = temp->adjecent_node;
	}
	return 0;
}
file* find_rec(char *name, file *search_dir)
{ 
	file *temp, *temp2;
 
	temp = search_dir->first_child;

	while(temp)
	{ 
		if(!strcmp(temp->node_name, name))
			return temp;
		else if(temp->node_type == 1)
			if(temp2 = find_rec(name, temp))
				return temp2;
		temp = temp->adjecent_node;
	}
	return 0;
}
void cd()
{
	char name[50];
	char par[] = "..";

	file* request;

	scanf("%s", name);

	if(!strcmp(name, par))
	{
		pwd = pwd->parent;
		return;
	}
 
	request = find(name, pwd);

	if(request)
	{
		if(request->node_type == 1)
			pwd = request;
		else
			printf("bash: not a directory\n");
	}
	else
		printf("bash: no such file or directory\n");
}
void ls()
{
	file *temp;

	temp = pwd->first_child;

	while(temp)
	{
		printf("%s\n", temp->node_name);
		temp = temp->adjecent_node;
	}
}
