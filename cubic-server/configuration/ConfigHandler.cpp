#include "ConfigHandler.hpp"
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include "errors.hpp"

configuration::ConfigHandler::ConfigHandler(const std::string &name, const std::string &version):
    _arguments(name, version)
{
}

void configuration::ConfigHandler::load(const std::filesystem::path &path)
{ this->_config.load(path); }

void configuration::ConfigHandler::save(const std::filesystem::path &path)
{
    for (auto &[_, value]: this->_values) {
        if (value._defaultValueConfig.empty() || value._defaultValue.empty())
            continue;

        auto *node = &this->_config;
        for (auto &key: value._defaultValueConfig) {
            if (node->has(key))
                node = &node->at(key);
            else
                node = &node->add(key);
        }
        if (value._defaultValue.size() > 1)
            node->set(value._defaultValue);
        else if (value._defaultValue.size() == 1)
            node->set(value._defaultValue[0]);
        else
            node->set(nullptr);
    }
    this->_config.save(path);
}

configuration::Value &configuration::ConfigHandler::add(const std::string &key)
{
    this->_values.emplace(std::make_pair(key, Value(key, this->_arguments)));
    return this->_values.at(key);
}

void configuration::ConfigHandler::parse(int argc, const char * const argv[])
{
    for (auto &[_, value]: this->_values)
        value.addToParser();

    this->_arguments.parse(argc, argv);

    for (auto &[_, value]: this->_values)
        value.parse(this->_config);
}

configuration::Value &configuration::ConfigHandler::operator[](const std::string &key)
{ return this->_values.at(key); }

const configuration::Value &configuration::ConfigHandler::operator[](const std::string &key) const
{ return this->_values.at(key); }


std::ostream &configuration::operator<<(std::ostream &os, const configuration::ConfigHandler &config)
{ return os << config._arguments; }
