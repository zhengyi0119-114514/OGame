#include "SDL.h"
#include "log4cplus/log4cplus.h"


int main(int argc, char **args)
{
    log4cplus::initialize();
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    log4cplus::BasicConfigurator config;
    config.configure();
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("init"));
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world!"));
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Log4Cplus Init"));
}