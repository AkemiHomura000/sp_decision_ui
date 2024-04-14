#ifndef MAP_SELECT_H
#define MAP_SELECT_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <iostream>
namespace Ui {
class Map_select;
}

class Map_select : public QWidget
{
    Q_OBJECT

public:
    explicit Map_select(QWidget *parent = nullptr);
    ~Map_select();

    void loadImage(const QString &filePath);
    double target_x;
    double target_y;
protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Map_select *ui;
    QLabel *imageLabel;
};

#endif // MAP_SELECT_H
