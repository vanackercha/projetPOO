#include "Grid.h"
#include <iostream>

Grid::Grid(int rows, int cols, float cellSize) : rows(rows), cols(cols), cellSize(cellSize), previousHoveredCell(nullptr), railMode(false), score(0) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells.emplace_back(j * cellSize, i * cellSize, cellSize);
        }
    }
}

void Grid::draw(sf::RenderWindow& window) {
    for (auto& cell : cells) {
        cell.draw(window);
    }
}

void Grid::handleClick(sf::Vector2f mousePos) {
    for (auto& cell : cells) {
        if (cell.contains(mousePos)) {
            //Train sur Rail Depuis Station
            if (cell.hasStation()) {
                cell.getStationFromCell();
                cell.debugStation();
                std::vector<Cell*> adacentCellsFromStation = getNeighbourHood(mousePos);
                for (auto& adj : adacentCellsFromStation) {
                    if (adj->getValue() == 1) {
                        Train* train = cell.moveTrainToRail(adj, cell.getStationFromCell());
                        addTrainToVector(train);
                    }
                }
            }
            else if (cell.hasSwitch()) {
                RailSwitch* railS = cell.getSwitchFromCell();
                railS->changeMode();
                int nextCell= railS->getNextCell();
                for (auto& cell : cells) {
                    if (cell.hasRail()) {
                        Rail* rail = cell.getRailFromCell();
                        if (rail->getId() == nextCell) {
                            std::vector<Cell*> adjacentCells = getNeighbourHood(mousePos);
                            for (auto& cell : adjacentCells) {
                                cell->setColor(sf::Color(0, 0, 0, 150));
                            }
                            cell.setColor(sf::Color(200,200,150));
                        }
                    }
                }

            }
            //Placer Rail Horiz.
             else if (railMode == 1 && cell.getValue() == 0) {
                 std::vector<Cell*> adjacentCells = getNeighbourHood(mousePos);
                 for (auto& adjCell : adjacentCells) {
                     if (adjCell->getValue() == 2) {
                         Station* currentStation = adjCell->getStationFromCell();
                         if (!currentStation->getHasRail()) {
                             currentStation->setHasRail();
                             idRail++;
                             cell.addRail(idRail, 0);
                         }
                     }
                     else if(adjCell->getValue() == 1){
                         idRail++;
                         cell.addRail(idRail, 0);
                     }
                 }
                 
            }
            //Placer Rail Vert.
             else if (railMode == 2 && cell.getValue() == 0) {
                 std::vector<Cell*> adjacentCells = getNeighbourHood(mousePos);
                 for (auto& adjCell : adjacentCells) {
                     if (adjCell->getValue() == 2) {
                         Station* currentStation = adjCell->getStationFromCell();
                         if (!currentStation->getHasRail()) {
                             currentStation->setHasRail();
                             idRail++;
                             cell.addRail(idRail, 1);
                         }
                     }
                     else if (adjCell->getValue() == 1) {
                         idRail++;
                         cell.addRail(idRail, 1);
                     }
                 }
             }
             else if (modeTrain == 1) {
                if (cell.hasRail()) {
                    //cell.addTrain();
                    sf::Vector2f trainpos = cell.getPosTrain();
                    for (auto& cell : cells) {
                        if (cell.contains(trainpos)) {
                            std::vector<Cell*> celladja = getNeighbourHood(trainpos);
                            sf::Vector2f nextCell = celladja[2]->getPosCell();
                             cell.TrainMoveTo(nextCell);
                            /*std::cout << trainpos.x << "//" << trainpos.y << std::endl;*/
                        }
                    }
                    
                 
                }
            }
             else if (switchMode == 1) {
                if (cell.getValue() == 0) {
                    std::vector<Rail*> railLink;
                    std::vector<Cell*> celladja = getNeighbourHood(mousePos);
                    for (auto& adjacell : celladja) {
                        if (adjacell->getValue() == 1) {
                            railLink.push_back(adjacell->getRailFromCell());
                        }

                    }
                    idSwitch++;
                    cell.addSwitch(idSwitch,railLink);
                    celladja[1]->setColor(sf::Color(200, 200, 150));
                }
            }
            std::cout << "(" << (mousePos.x) << ", " << mousePos.y<< ") Value: " << cell.getValue() << std::endl;
            
            break;
        }
    }
}

void Grid::handleHover(sf::Vector2f mousePos) {
    Cell* hoveredCell = nullptr;
    for (auto& cell : cells) {
        if (cell.contains(mousePos)) {
            hoveredCell = &cell;
            break;
        }
    }

    if (previousHoveredCell && previousHoveredCell != hoveredCell) {
        previousHoveredCell->viewStatus(false);
    }

    if (hoveredCell) {
        hoveredCell->viewStatus(true);
    }

    previousHoveredCell = hoveredCell;
}

void Grid::setRailMode(int mode) {
    railMode = mode;
}

void Grid::setSwitchMode(bool sMode) {
    switchMode = sMode;
}
//Placement d'une station sur une cell
void Grid::placeStation(float x, float y, sf::Color color) {
    Cell* cell = getCellAt(x, y);
    cell->addStation(color);
}
void Grid::setTrainMode(bool trainMode) {
    modeTrain = trainMode;
}
//Mise à jour de la Grid en fonction du temps
void Grid::update(sf::Time time) {
    float deltaTime = time.asSeconds();
    i++;
    if (i > 50) {
        for (size_t i = 0; i < trains.size(); ++i) {
            for (size_t j = i + 1; j < trains.size(); ++j) {
                if (trains[i]->getPosition() == trains[j]->getPosition()) {
                    gameLose = true;
                    return;
                }
            }
        }
        for (auto& train : trains) {
            if (train) {
                Cell* currentCell = getCellAt(train->getPosition().x, train->getPosition().y);
                std::vector<Cell*> adjactentCells = getNeighbourHood(train->getPosition());
                sf::Vector2f nextCell;

                if(currentCell->hasRail()){
                    Rail* currentRail = currentCell->getRailFromCell();
                    int currentRailId = currentRail->getId();
                    
                    sf::Vector2f previous = train->getPreviousPosition();
                    
                    int previousId = train->getPrevId();
                    i = 0;
                    for (auto& adjactentCell : adjactentCells) {
                    
                        if (adjactentCell->hasRail()) {
                            Rail* nextRail = adjactentCell->getRailFromCell();
                            int nextRailId = nextRail->getId();
                            if (previousId != nextRailId && nextRailId != currentRailId) {
                                std::cout << "suivant==" << nextRailId << std::endl;
                                std::cout << "actuelle==" << currentRailId << std::endl;
                                std::cout << "precedent==" << previousId << std::endl;
                                sf::Vector2f current = currentCell->getPosCell();
                                nextCell = adjactentCell->getPosCell();
                                train->updatePos(nextCell, current);
                                train->setIdRail(nextRailId);
                                train->setPrevId(currentRailId);
                                i = 1;
                                break;
                            }
                        }
                    
                        else if (adjactentCell->getValue() == 2) {
                        Station* nextStation = adjactentCell->getStationFromCell();
                        if (nextStation->getColor() == train->getColor()) {
                            this->score++;
                            currentCell->destroyTrain();
                        }
                    }
                    }    
                    if(i==0){
                        int j = 0;
                        for (auto& adjactentCell : adjactentCells) {
                             if (adjactentCell->hasSwitch()) {
                                 j = 1;
                                sf::Vector2f current = currentCell->getPosCell();
                                nextCell = adjactentCell->getPosCell();
                                train->updatePos(nextCell, current);
                                train->setPrevId(currentRailId);
                                
                             }
                        }
                        if (j == 0) {
                            gameLose = true;
                        }
                    }
                }
                else if (currentCell->hasSwitch()) {
                    RailSwitch* railS = currentCell->getSwitchFromCell();
                    int idnexCell = railS->getNextCell();
                    for (auto& adjactentCell : adjactentCells) {

                        if (adjactentCell->hasRail()) {
                            Rail* nextRail = adjactentCell->getRailFromCell();
                            int nextRailId = nextRail->getId();
                            std::cout << "suivant==" << nextRailId << std::endl;
                            std::cout << "actuelle==" << idnexCell << std::endl;

                            if (nextRailId == idnexCell) {
                                sf::Vector2f current = currentCell->getPosCell();
                                nextCell = adjactentCell->getPosCell();
                                train->updatePos(nextCell, current);

                            }

                     }
                    
                    }
                    
                    }

                }
            }
            i = 0;
        }
        for (auto& cell : cells) {
            if (cell.hasStation()) {
                Station* station = cell.getStationFromCell();
                station->update(time);
            }
        }
        checkVictoryCondition();
    }
std::vector<Cell*> Grid::getNeighbourHood(sf::Vector2f mousePos) {
    std::vector<Cell*> neighbourhood;

    Cell* cell0 = getCellAt(mousePos.x, mousePos.y);
    if (cell0) neighbourhood.push_back(cell0);

    Cell* cell1 = getCellAt(mousePos.x - cellSize, mousePos.y);
    if (cell1) neighbourhood.push_back(cell1);

    Cell* cell2 = getCellAt(mousePos.x + cellSize, mousePos.y);
    if (cell2) neighbourhood.push_back(cell2);

    Cell* cell3 = getCellAt(mousePos.x, mousePos.y - cellSize);
    if (cell3) neighbourhood.push_back(cell3);

    Cell* cell4 = getCellAt(mousePos.x, mousePos.y + cellSize);
    if (cell4) neighbourhood.push_back(cell4);

    return neighbourhood;
}
Cell* Grid::getCellAt(float x, float y) {
    for (auto& cell : cells) {
        if (cell.contains(sf::Vector2f(x, y))) {
            return &cell;
        }
    }
    return nullptr;
}

void Grid::addTrainToVector(Train* train) {
    trains.push_back(train);
}
int Grid::getScore() {
    return score;
}
void Grid::checkVictoryCondition() {
    if (score >= 1) {
        this->gameWon = true;
    }
}
bool Grid::getGameWon() {
    return this->gameWon;
}
void Grid::setScore(int score) {
    this->score = score;
}
bool Grid::getGameLose() {
    return this->gameLose;
}