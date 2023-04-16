#include "Stop.hpp"
#include "Server.hpp"
#include "World.hpp"

void command_parser::Stop::autocomplete(std::vector<std::string> &args, Player *invoker) const
{
    if (invoker)
        return;
    else
        LINFO("autocomplete stop");
}

void command_parser::Stop::execute(std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        if (invoker->isOperator()) {
            invoker->getDimension()->getWorld()->getChat()->sendSystemMessage("Stopping server...", invoker);
            Server::getInstance()->stop();
        }
    } else
        Server::getInstance()->stop();
}

void command_parser::Stop::help(std::vector<std::string> &args, Player *invoker) const
{
    if (invoker) {
        if (invoker->isOperator())
            invoker->getDimension()->getWorld()->getChat()->sendSystemMessage("/stop", invoker);
    } else
        LINFO("/stop");
}
