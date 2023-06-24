// By xchhe 2018.
#ifndef MODULE_H
#define MODULE_H

#include <fstream>
#include "str_proc.h"
#include "config_proc.h"

struct module
{
    std::string name;
    std::string def;
    std::string init;
    std::string exe;
    std::string exit;
};

bool mod_read(std::ifstream &fin, std::string &inp, module &mod);

#endif
