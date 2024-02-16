#ifndef CMD_FACTORY_H
#define CMD_FACTORY_H

#include <QDebug>
#include <QCoreApplication>
#include <QMap>
#include <QString>
#include <token.h>

#define STR_PTR(ptr) QString("0x%1").arg(reinterpret_cast<quintptr>(ptr), QT_POINTER_SIZE * 2, 16, QChar('0'))

class Commande {
    QString _type;

public:
    virtual ~Commande() {
        qDebug() << __FUNCTION__;
    }

    virtual void parse(QList<Token *> tokens) = 0;
    virtual void run() = 0;

};

typedef Commande *(*CreateCmdFn)();

/**
 * Ce template ou modèle de classe permet de rajouter la méthode statique Create à n'importe quelle classe Cmd
 */
template <class T>
class TCmdFactory : public Commande {
public:
    static Commande *create() {
        qDebug() << __FUNCTION__ << "constructs";
        return new T;
    }
};


class CommandeSearch : public TCmdFactory<CommandeSearch> {

    QString filename;
    QString lastModified;
    QString created;
    QString maxSize;
    QString minSize;
    QString size;
    QString ext;
    QString type;

public:
    CommandeSearch();


    void parse(QList<Token *> tokens);
    void run();

};

class CommandeGet : public TCmdFactory<CommandeGet> {
    QString folderType;
public:
    CommandeGet();
    void get() {
        qDebug() << __FUNCTION__;
    }

    void parse(QList<Token *> tokens);
    void run();
};

class CommandeAdd: public TCmdFactory<CommandeAdd> {
    QString folderType;
    QString folderPath;

public:
    CommandeAdd();

    void parse(QList<Token *> tokens);
    void run();
};

class CommandeClear : public TCmdFactory<CommandeClear> {
    QString folderType;
public:
    CommandeClear();
    void get() {
        qDebug() << __FUNCTION__;
    }

    void parse(QList<Token *> tokens);
    void run();
};

class CommandeFactory {
    QMap<QString, CreateCmdFn> m_factoryMap;

public:
    QList<Commande *>               cmdList;
    /**
     * le destructeur doit aussi detruire tous les animaux que la factory a créé
     */
    ~CommandeFactory() {
        foreach (auto cmd, cmdList) { delete cmd; }
    }


    /**
     * @brief Register
     * @param cmdName
     * @param fn
     * La fonction register ssocie le nom de la clases Cmd à l'action a effectuer pour la creer
     */
    void Register(QString cmdName, CreateCmdFn fn) {
        qDebug() << __FUNCTION__ << cmdName << fn;
        m_factoryMap[cmdName] = fn;
    }

    /**
     * @brief CmdFactory
     * le constructeur inscrit les classes de command connues
     */
    CommandeFactory() {
        qDebug() << __FUNCTION__;
        Register("CmdSearch", &CommandeSearch::create);
        Register("CmdGet", &CommandeGet::create);
        Register("CmdAdd", &CommandeAdd::create);
        Register("CmdClear", &CommandeClear::create);
    }

    Commande *create(QString cmdName) {
        qDebug() << __FUNCTION__ << cmdName;

        CreateCmdFn fn = m_factoryMap[cmdName];
        if (fn == nullptr) {
        }
        Commande *cmd = fn();

        cmdList.append(cmd);
        return cmd;
    }

};

#endif // CMD_FACTORY_H
