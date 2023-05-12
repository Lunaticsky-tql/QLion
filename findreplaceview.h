//
// Created by LENOVO on 2023/5/12.
//

#ifndef QLION_FINDREPLACEVIEW_H
#define QLION_FINDREPLACEVIEW_H

#include <QWidget>
class MainWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class FindReplaceView; }
QT_END_NAMESPACE

class FindReplaceView : public QWidget {
Q_OBJECT

public:
    explicit FindReplaceView(MainWindow *parent = nullptr);

    ~FindReplaceView() override;

private:
    Ui::FindReplaceView *ui;
    MainWindow* mainWindow;
    void setToolButtons(bool isEnable);
private slots:
    void onFindTextChanged(const QString& text);
};


#endif //QLION_FINDREPLACEVIEW_H
