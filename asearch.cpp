#include "mission.h"

int main(int argc, char* argv[])
{
    char * path;
    if(argc < 2) {
        char pathstr[12] = "example.xml";
        path = pathstr;
        //std::cout << "Error! Pathfinding task file (XML) is not specified!"<<std::endl;
        //return 0;
    } else {
        path = argv[1];
    }

    Mission mission(path);

    std::cout<<path<<std::endl;
    std::cout<<"Parsing the map from XML:"<<std::endl;

    if(!mission.getMap()) {
        std::cout<<"Incorrect map! Program halted!"<<std::endl;
    }
    else {
        std::cout<<"Map OK!"<<std::endl<<"Parsing configurations (algorithm, log) from XML:"<<std::endl;
        if(!mission.getConfig())
            std::cout<<"Incorrect configurations! Program halted!"<<std::endl;
        else {
            std::cout<<"Configurations OK!"<<std::endl<<"Creating log channel:"<<std::endl;

            if(!mission.createLog())
                std::cout<<"Log channel has not been created! Program halted!"<<std::endl;
            else {
                std::cout<<"Log OK!"<<std::endl<<"Start searching the path:"<<std::endl;

                mission.createEnvironmentOptions();
                mission.createSearch();
                mission.startSearch();

                std::cout<<"Search is finished!"<<std::endl;

                mission.printSearchResultsToConsole();
                mission.saveSearchResultsToLog();

                std::cout<<"Results are saved (if chosen) via created log channel."<<std::endl;
            }
        }
    }
    return 0;
}

