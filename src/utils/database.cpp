#include"database.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <iostream>
#include"neighborhood_factory.h"

DBManager* DBManager::DBManInstance = nullptr;

DBManager::DBManager(const QString& path) {

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if(!db.open())
        throw DBException("Error : failed to access database !");
    else {
        QMessageBox window;
        window.setText("Connection with database correctly established !");
        window.exec();
    }
}

std::pair<int , CellState**> DBManager::loadStatesfromDB() const{
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT COUNT(*) FROM State");
    query.exec();
    query.next();
    int nb=query.value(0).toInt();
    CellState** Statetab= new CellState*[nb];
    query.prepare("SELECT * FROM State");
    query.exec();
    int i =0;
    while(query.next()) {
        QString label,direction;
        QString col;
        QColor color;
        int id;
        label = query.value("label").toString();
        col = query.value("color").toString();
        direction = query.value("direction").toString();
        id=query.value("id").toInt();
        color= toColor(col);
        Statetab[i]=new CellState(id, label.toStdString(), color);
        i++;}
    return {nb,Statetab};
}

DBManager& DBManager::getDB() {
    if(DBManInstance == nullptr)
        DBManInstance = new DBManager(DB_PATH);
    return *DBManInstance;
}

void DBManager::loadAutomatasFromDB() const {
    AutomataManager* automataManager = AutomataManager::getAutomataManager();
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT * FROM Automata");
    query.exec();
    QSqlQuery queryAux(QSqlDatabase::database());
    while(query.next()) {
        // Infos that are easy to take from DB :
        QString name, description, author;
        int nbStates, creationYear;

        name = query.value("name").toString();
        description = query.value("description").toString();
        author = query.value("author").toString();
        nbStates = query.value("nbStates").toInt();
        creationYear = query.value("creationYear").toInt();

        //Slightly more difficult infos :
        // Available states
        CellState** availableStates = new CellState*[nbStates];
        queryAux.prepare(QString("SELECT stateID FROM AutomataState WHERE automataName = :name"));
        queryAux.bindValue(":name", name);
        queryAux.exec();

        int i = 0;

        QSqlQuery queryAuxState(QSqlDatabase::database());
        while(queryAux.next()) { //Take infos about the concerned states to dynamically create those objects
            int stateID = queryAux.value("stateID").toInt();
            queryAuxState.prepare(QString("SELECT * FROM State WHERE id = :stateID"));
            queryAuxState.bindValue(":stateID", stateID);
            queryAuxState.exec();
            queryAuxState.next();
            QString label = queryAuxState.value("label").toString();
            QString col = queryAuxState.value("color").toString();
            QColor color = toColor(col);
            //See how to handle direction

            availableStates[i] = new CellState(stateID, label.toStdString(), color);

            i++;
        }
        queryAux.finish();
        queryAuxState.finish();

        QString rule = query.value("transition").toString();
        QString neighborhood = query.value("neighborhood").toString();

        automataManager->addAutomata(availableStates,
                                     transitionFac.production(rule.toStdString()),
                                     neighborFac.production(neighborhood.toStdString()),
                                     nbStates, name.toStdString(), description.toStdString(),
                                     author.toStdString(), creationYear);

    }
}

void DBManager::insertAutomataIntoDB(QString name,int nbStates, QString transitionName, QString neighborhoodName, CellState** chosenStates, QString description, QString author, int year){
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Automata(name,description,author,creationYear,nbStates,transition,neighborhood) VALUES(:name,:description,:author,:creationYear,:nbStates,:transition,:neighborhood)");
    query.bindValue(":name",name);
    query.bindValue(":description",description);
    query.bindValue(":author",author);
    query.bindValue(":creationYear",year);
    query.bindValue(":nbStates",nbStates);
    query.bindValue(":transition",transitionName);
    query.bindValue(":neighborhood",neighborhoodName);
    bool test = query.exec();
    query.finish();

    if(!test){
        throw DBException("Error while trying to create a new automaton. This may be due to an already used name.");
    }

    for(int i = 0; i < nbStates; i++){
        QSqlQuery queryBis(QSqlDatabase::database());
        queryBis.prepare("INSERT INTO AutomataState(stateID, automataName) VALUES(:stateID,:name)");
        queryBis.bindValue(":stateID",chosenStates[i]->getId());
        queryBis.bindValue(":name",name);
        queryBis.exec();
        queryBis.finish();
    }
}

QColor DBManager::toColor(const QString& col) const {
    if(col == "black") return Qt::black;
    if(col == "white") return Qt::white;
    if(col == "yellow") return Qt::yellow;
    if(col == "blue") return Qt::blue;
    if(col == "cyan") return Qt::cyan;
    if(col == "darkcyan") return Qt::darkCyan;
    if(col == "red") return Qt::red;
    if(col == "green") return Qt::green;
    if(col == "magenta") return Qt::magenta;
    return Qt::white;
}

/*QColor DBManager::toName(const QString& col) const {
    if(col == "black") return Qt::black;
    if(col == "white") return Qt::white;
    if(col == "yellow") return Qt::yellow;
    if(col == "blue") return Qt::blue;
    if(col == "cyan") return Qt::cyan;
    if(col == "darkcyan") return Qt::darkCyan;
    if(col == "red") return Qt::red;
    if(col == "green") return Qt::green;
    if(col == "magenta") return Qt::magenta;
    return Qt::white;
}
*/

DBManager::~DBManager() {
    db.close();
}

void DBManager::DbaddState(const QString label, const int id , const QString color) const {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO State(id,label,color) VALUES(:id,:label,:color)");
    query.bindValue(":id",id);
    query.bindValue(":label",label);
    query.bindValue(":color", color);
    if(!query.exec()) {
        qDebug() << "addState error:"
                 << query.lastError().text();
    }




}

void DBManager::insertNeighborhoodIntoDB(const QString name, const int radius) const {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Neighborhood(name, radius) VALUES (:name,:radius)");
    query.bindValue(":name", name);
    query.bindValue(":radius", radius);
    if(!query.exec()) {
        qDebug() << "addNeighborhood error:"
                 << query.lastError().text();
    }
}

void DBManager::insertNeighborhoodIntoDB(const QString name, int nbNeighbors, const int* dx, const int* dy) const {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Neighborhood(name) VALUES (:name)");
    query.bindValue(":name", name);
    if(!query.exec()) {
        qDebug() << "addNeighborhood error:"
                 << query.lastError().text();
    }
    int n = 0;
    while(n < nbNeighbors) {
        QSqlQuery query(QSqlDatabase::database());
        query.prepare("INSERT INTO Neighbor VALUES(:dx,:dy, :name)");
        query.bindValue(":name", name);
        query.bindValue(":dx", dx[n]);
        query.bindValue(":dy", dy[n]);
        if(!query.exec()) {
            qDebug() << "addNeighbor error:"
                     << query.lastError().text();
        }

        n++;
    }


}


std::pair<int, NeighborhoodStrategy**> DBManager::loadNeighborhoodsFromDB() const {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT COUNT(*) FROM Neighborhood");
    query.exec();
    query.next();
    int n = query.value(0).toInt();
    NeighborhoodStrategy** res = new NeighborhoodStrategy*[n];
    NeighborhoodStrategy* neighborhood;
    query.finish();
    QSqlQuery queryAux(QSqlDatabase::database());
    queryAux.prepare("SELECT name, radius FROM Neighborhood");
    queryAux.exec();
    int i = 0;
    while(queryAux.next()) {
        QString name = queryAux.value(0).toString();
        int radius = queryAux.value(1).toInt();
        QSqlQuery query1(QSqlDatabase::database());
        query1.prepare("SELECT COUNT(dx) FROM Neighborhood JOIN Neighbor ON Neighborhood.name=Neighbor.neighborhood WHERE Neighborhood.name=:name");
        query1.bindValue(":name", name);
        query1.exec();
        query1.next();
        int nbNeighbors=query1.value(0).toInt();
        query1.prepare("SELECT dx,dy FROM Neighborhood JOIN Neighbor ON Neighborhood.name=Neighbor.neighborhood WHERE Neighborhood.name=:name");
        query1.bindValue(":name", name);
        query1.exec();
        std::string stringName = name.toStdString();
        if(nbNeighbors == 0) {
            if(radius == 0) {
                neighborhood = neighborFac.production(name.toStdString());
            } else {
                neighborhood = neighborFac.production(name.toStdString(), radius);
            }
        } else {
            int* dx = new int[nbNeighbors];
            int* dy = new int[nbNeighbors];
            int j = 0;
            while (query1.next()) {
                dx[j] = query1.value(0).toInt();
                dy[j] = query1.value(1).toInt();
                j++;
            }
            neighborhood = neighborFac.production(name.toStdString(), nbNeighbors, dx, dy);
        }
        res[i] = neighborhood;
        i++;
    }
    query.finish();
    return {n, res};
}

std::pair<int, TransitionStrategy**> DBManager::loadTransitionsFromDB() const {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("SELECT COUNT(*) FROM Transition");
    query.exec();
    query.next();
    int n = query.value(0).toInt();
    TransitionStrategy** res = new TransitionStrategy*[n];
    TransitionStrategy* transition;
    query.finish();
    QSqlQuery queryAux(QSqlDatabase::database());
    queryAux.prepare("SELECT name FROM Transition");
    queryAux.exec();


    int i = 0;
    while(queryAux.next()) {
        QString name=queryAux.value(0).toString();
        std::string nameString=name.toStdString();
        transition = transitionFac.production(nameString);
        res[i] = transition;
        i++;
    }
    queryAux.finish();
    return {n, res};
}

void DBManager::insertConfigIntoDB(const QString &name, Grid *config, Automata* automata) const {
    if (config == nullptr) {
        throw DBException("No grid to save");
    }
    if (automata == nullptr) {
        throw DBException("No automata selected");
    }
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Grid VALUES (:name, :width, :height, :automata)");
    query.bindValue(":name", name);
    query.bindValue(":width", config->getWidth());
    query.bindValue(":height", config->getHeight());
    query.bindValue(":automata", automata->getName().c_str());
    if (!query.exec()) {
        throw DBException("Duplicate config name!!!");
    }
    QString insertQuery = "INSERT INTO Cell(x, y, state, grid) VALUES (:x0, :y0, :state0, :grid)";
    for (int i = 1; i < config->getHeight() * config->getWidth(); i ++) {
        insertQuery += QString((",(:x" + std::to_string(i) + ", :y" + std::to_string(i) + ", :state" + std::to_string(i) + ", :grid)").c_str());
    }
    query.prepare(insertQuery);
    for (int r = 0; r < config->getHeight(); r ++) {
        for (int c = 0; c < config->getWidth(); c ++) {
            query.bindValue((":x" + std::to_string(r * config->getWidth() + c)).c_str(), r);
            query.bindValue((":y" + std::to_string(r * config->getWidth() + c)).c_str(), c);
            query.bindValue((":state" + std::to_string(r * config->getWidth() + c)).c_str(), config->getCell(r, c)->getState()->getId());
            query.bindValue(":grid", name);
        }
    }
    if (!query.exec()) {
        throw DBException("Error saving cells");
    }
}

std::pair<int, Grid**> DBManager::loadConfigsFromDB(Automata* automata) const {
    QSqlQuery queryAll(QSqlDatabase::database());
    queryAll.prepare("SELECT COUNT(*) FROM Grid WHERE automata=:automata");
    queryAll.bindValue(":automata", automata->getName().c_str());
    if (!queryAll.exec()) {
        throw DBException("Error counting configs");
    }
    queryAll.next();
    int n = queryAll.value(0).toInt();
    Grid** res = new Grid*[n];

    queryAll.prepare("SELECT * FROM Grid WHERE automata = :automata");
    queryAll.bindValue(":automata", automata->getName().c_str());
    if (!queryAll.exec()) {
        throw DBException("Error loading config");
    }

    int i = 0;

    while (queryAll.next()) {
        QString gridName = queryAll.value("name").toString();
        int width = queryAll.value("width").toInt();
        int height = queryAll.value("height").toInt();

        res[i] = gridFac.generateGrid(EMPTY, width, height, automata);

        QSqlQuery queryCell(QSqlDatabase::database());

        for (int r = 0; r < res[i]->getHeight(); r ++) {
            for (int c = 0; c < res[i]->getWidth(); c ++) {
                queryCell.prepare("SELECT * FROM Cell WHERE grid = :grid AND x = :x AND y = :y");
                queryCell.bindValue(":grid", gridName);
                queryCell.bindValue(":x", r);
                queryCell.bindValue(":y", c);
                queryCell.exec();
                queryCell.next();
                int cellStateID = queryCell.value("state").toInt();
                int cellStatePos = 0;
                for (cellStatePos = 0; cellStatePos < automata->getNbStates(); cellStatePos ++) {
                    if (automata->getAvailableState(cellStatePos)->getId() == cellStateID) {
                        break;
                    }
                }
                res[i]->setCell(new Cell(automata->getAvailableState(cellStatePos), r, c), r, c);
                res[i]->setName(gridName.toStdString());
            }
        }

        i ++;
    }

    return {n, res};
}
