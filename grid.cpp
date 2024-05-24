#include "Grid.h"
#include <iostream>

Grid::Grid(int rows, int cols, float cellSize) : rows(rows), cols(cols), cellSize(cellSize), previousHoveredCell(nullptr), railMode(false) {
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
                        cell.moveTrainToRail(adj, cell.getStationFromCell());
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
                    cell.addTrain();
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
            std::cout << "(" << (mousePos.x / cellSize) << ", " << mousePos.y / cellSize << ") Value: " << cell.getValue() << std::endl;
            
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
    for (auto& cell : cells) {
        if (cell.hasStation()) {
            Station* station = cell.getStationFromCell();
            station->update(time);
        }
    }
    for (auto& cell : cells) {
        if (cell.hasTrain()) {
            //if(i>50){

            std::cout << cell.getPosCell().x << "////" << cell.getPosCell().y<<std::endl;
               
            Train* train = cell.getTrainFromCell();
            Rail* railcurrent = cell.getRailFromCell();
            int idCurrent = railcurrent->getId();
            sf::Vector2f trainpos = cell.getPosTrain();
            std::vector<Cell*> celladja = getNeighbourHood(trainpos);
            
            sf::Vector2f nextCell;
            sf::Vector2f prev = train->getPreviousPosition();
            int idPrev = train->getPrevId();
            for (auto& cella : celladja) {
                 if (cella->hasRail() /*&& !cell->contains(prev) && !celladja[0]*/) {
                     Rail* rail = cella->getRailFromCell(); 
                     int idrail = rail->getId();
                     

                     if (idrail == idCurrent || idrail == idPrev) {


                     }
                     else {

                         std::cout << "suivant==" << idrail << std::endl;
                         std::cout << "actuelle==" << idCurrent << std::endl;
                         std::cout << "precedent ==" << idPrev << std::endl;
                        
                       
                        sf::Vector2f current = celladja[0]->getPosCell();
                        train->setPrevId(idCurrent);
                    
                        nextCell = cella->getPosCell();
                        train->updatePos(nextCell,current);
                        break;
                     }
                     
                    
                    
                    /*std::cout << "posCellule regardée: " << cell->getPosCell().x <<"///" << cell->getPosCell().y << std::endl;
                    std::cout << "position précédente: " << train->getPreviousPosition().x <<"///"<< train->getPreviousPosition().y << std::endl;*/

                }
            }
           // i = 0;}
            break;
        }
    }
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

