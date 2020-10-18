#include "commandline.h"

CommandLineFeatures commandLineFeatures;




#include "cli_help.h"
#include "cli_php.h"
#include "cli_request.h"

void PopulateCommandLineFeatures() {
 commandLineFeatures.Append(new CLI_Help);
 commandLineFeatures.Append(new CLI_PHP);
 commandLineFeatures.Append(new CLI_Request);
}
