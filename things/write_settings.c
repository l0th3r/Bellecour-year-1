#include <stdio.h>
#include <stdlib.h>

#include <libconfig.h>

int main(void)
{
	static const char *output_file = "newconfig.cfg";
  	config_t cfg;
	config_setting_t *root, *setting, *group, *array;
	int i;

	config_init(&cfg);
	root = config_root_setting(&cfg);

	/* Add some settings to the configuration. */
	group = config_setting_add(root, "address", CONFIG_TYPE_GROUP);

	setting = config_setting_add(group, "street", CONFIG_TYPE_STRING);
	config_setting_set_string(setting, "1 Woz Way");

	setting = config_setting_add(group, "city", CONFIG_TYPE_STRING);
	config_setting_set_string(setting, "San Jose");

	setting = config_setting_add(group, "state", CONFIG_TYPE_STRING);
	config_setting_set_string(setting, "CA");

	setting = config_setting_add(group, "zip", CONFIG_TYPE_INT);
	config_setting_set_int(setting, 95110);

	array = config_setting_add(root, "numbers", CONFIG_TYPE_ARRAY);

	for(i = 0; i < 10; ++i)
	{
		setting = config_setting_add(array, NULL, CONFIG_TYPE_INT);
		config_setting_set_int(setting, 10 * i);
	}

	/* Write out the new configuration. */
	if(! config_write_file(&cfg, output_file))
	{
		fprintf(stderr, "Error while writing file.\n");
		config_destroy(&cfg);
		return(EXIT_FAILURE);
	}	

	fprintf(stderr, "New configuration successfully written to: %s\n",
			output_file);

	config_destroy(&cfg);
	return(EXIT_SUCCESS);
}