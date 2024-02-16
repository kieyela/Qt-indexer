#ifndef COMMANDEFACTORY_H
#define COMMANDEFACTORY_H
#include <QDebug>
#include <QCoreApplication>
#include <QMap>
#include <QString>

#define STR_PTR(ptr) QString("0x%1").arg(reinterpret_cast<quintptr>(ptr), QT_POINTER_SIZE * 2, 16, QChar('0'))

class Commande {
    QString _type;

public:
    virtual ~Commande() {
        qDebug() << __FUNCTION__;
    }
    // Méthode virtuelle, qui n'est pas implémentée dans la classe
    // animal mais qui devra impérativement l'être dans les classes
    // filles
    virtual void parse() = 0;
    virtual void run() = 0;

    QString type() const {
        return _type;
    }

    void setType(const QString &type) {
        _type = type;
    }

};

// alias 'CreateCmdFn' pour un pointeur de fonction de type 'Cmd* ma_fonction()'
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

//#define CREATE_CMD_CLASS(cmd)                                                                                    \
//class cmd : public TCmdFactory<cmd> {}


class CommandeSearch : public TCmdFactory<CommandeSearch> {
public:
    CommandeSearch();
    // Attributes


    // Implement virtual method
    void parse();
    void run();

};

// CmdGet : on declare la classe et on lui rajoute une méthode 'myFunc'
class CommandeGet : public TCmdFactory<CommandeGet> {
public:
    CommandeGet();
    void get() {
        qDebug() << __FUNCTION__;
    }

    // Implement virtual method
    void parse();
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
    }

    Commande *create(QString cmdName) {
        qDebug() << __FUNCTION__ << cmdName;

        // on recupere le pointeur sur fonction de la Map
        CreateCmdFn fn = m_factoryMap[cmdName];
        if (fn == nullptr) {
            //throw AnimalException("Unable to create " + cmdName);
        }
        // on appel la fonction désignée par le pointeur 'fn'
        Commande *cmd = fn();

        // on assigne le type de l'objet
        //cmd->setType(cmdName);

        //cmd->parse();

        // on le rajoute à la liste des objets de la Factory
        cmdList.append(cmd);
        return cmd;
    }

};
#endif // COMMANDEFACTORY_H
