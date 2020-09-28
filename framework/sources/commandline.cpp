#include "commandline.h"

CommandLineFeatures commandLineFeatures;




#include "cli_help.h"

void PopulateCommandLineFeatures() {
 commandLineFeatures.Append(new CLI_Help);
}
