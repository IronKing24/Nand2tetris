#include "CodeModule.h"

namespace HackAssembler
{
    const std::string& CodeModule::dest(const std::string& dest)
    {
        if (dests.find(dest) == dests.end())
        {
            throw std::runtime_error("unrecognized destination: " + dest + "\n");
        }

        return dests.at(dest);
    }
    const std::string& CodeModule::comp(const std::string& comp)
    {
        if (comps.find(comp) == comps.end())
        {
            throw std::runtime_error("unrecognized computation: " + comp + "\n");
        }

        return comps.at(comp);
    }
    const std::string& CodeModule::jump(const std::string& jump)
    {
        if (jumps.find(jump) == jumps.end())
        {
            throw std::runtime_error("unrecognized jump: " + jump + "\n");
        }

        return jumps.at(jump);
    }

} // namespace HackAssembler
