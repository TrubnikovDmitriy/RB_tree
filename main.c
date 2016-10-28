#include "RB_tree.h"


int main() {
	
	node* root = create_node();
		if (mc_ch(root)) return ERR;
	
	char* name = (char *)malloc(MAX_LENGTH*sizeof(char));
		if (mc_ch(name)) {
			free(root);
			return ERR;
		}
	
	float* key = (float *)malloc(sizeof(float));
		if (mc_ch(key)) {
			free(root);
			free(name);
			return ERR;
		}

        char ch_key[ID];
        char buff[MAX_LENGTH];
	if (!fgets(buff, MAX_LENGTH, stdin)) {
		printf("Empty file!\n");
        	return ex_free(ERR, name, key, root);
	}

	while (!feof(stdin)) {

			fgets(buff, MAX_LENGTH, stdin);
			if (buff[17] != '.')
				continue;

			for (int i = 9; i < 14; ++i)
				name[i - 9] = buff[i];
			name[5]='\n';

			for (int i = 15; i < 19; ++i)
				ch_key[i - 15] = buff [i];
			ch_key[4] = '\n';

			*key = atof(ch_key);
			
			if (add_node(root, key, name)) 
				return ex_free(ERR, name, key, root);
        }
	print_tree(root);
	write_nodes(root);
	return ex_free(SUC, name, key, root);
}


int ex_free(int flag, char* name, float* key, node* root) {

	free(name);
	free(key);
	if (free_tree(root)) {
		printf("Empty root!\n");
		return ERR;
	}
	return flag;
}
