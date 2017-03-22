#include <iostream>
#include <cstring>
#include "mf.h"

namespace 
{

void main_help()
{
    printf(
    "usage: kdmf <command> [<args>]\n"
    "\n"
    "Commands include:\n"
    "    --build-index  build kd-tree index from a text file\n"
    "    --train		Train a model from a binary training file\n"
    "    --predict		Predict a binary test file from a model\n"
    "    --view			View model and data info\n"
    "\n"
    "See 'kdmf <command>' for more information on a specific command.\n"
    );
}

} //namespace

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        main_help();
        return EXIT_FAILURE;
    }

    if(!strcmp(argv[1], "--build-index"))
        return convert(argc-2, argv+2);
    else if(!strcmp(argv[1], "--train"))
        return train(argc-2, argv+2);
    else if(!strcmp(argv[1], "--predict"))
        return predict(argc-2, argv+2);
    else if(!strcmp(argv[1], "--view"))
        return view(argc-2, argv+2);

    fprintf(stderr, "Error: Invalid command %s\n", argv[1]);
    return EXIT_FAILURE;
}
