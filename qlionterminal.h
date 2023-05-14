//
// Created by LENOVO on 2023/5/13.
//

#ifndef QLION_QLIONTERMINAL_H
#define QLION_QLIONTERMINAL_H

#include <QWidget>
#include <QProcess>


QT_BEGIN_NAMESPACE
namespace Ui { class QLionTerminal; }
QT_END_NAMESPACE

class QLionTerminal : public QWidget {
Q_OBJECT

public:
    explicit QLionTerminal(QWidget *parent = nullptr);

    ~QLionTerminal() override;

    void setCommand(const QString &command, const QStringList &args);

    void readData();
    void initConnections();
    void hideTerminal();

    void showError(QProcess::ProcessError errorCode);

    void showFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void stopCommand();

private:
    Ui::QLionTerminal *ui;
    QProcess *process;
    QString command;
    QStringList args;
public slots:

    void runCommand();
};


#endif //QLION_QLIONTERMINAL_H
