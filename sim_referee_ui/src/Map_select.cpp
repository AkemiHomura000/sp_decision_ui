#include "Map_select.h"
#include "ui_Map_select.h"

Map_select::Map_select(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map_select)
{
    ui->setupUi(this);

    // 创建一个 QLabel 控件来显示图片
    imageLabel = new QLabel(this);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    ui->verticalLayout->addWidget(imageLabel); // 这里假设你在 UI 设计中使用了垂直布局

    // 加载图片
    loadImage("path/to/image.jpg");
    target_x=0;
    target_y=0;
}

Map_select::~Map_select()
{
    delete ui;
}

void Map_select::loadImage(const QString &filePath)
{
    // 创建一个 QPixmap 对象来加载图片
    QPixmap pixmap;

    // 加载图片文件
    pixmap.load(filePath);

    // 将图片显示在 QLabel 上
    imageLabel->setPixmap(pixmap);
}
void Map_select::mousePressEvent(QMouseEvent *event)
{
    // 获取鼠标点击的坐标
    QPoint clickPos = event->pos();
    int x = clickPos.x();
    int y = clickPos.y();

    // 将 x 和 y 值转换为 double 类型
    double x_double = (static_cast<double>(x)-245)*0.0241379;
    double y_double = (-static_cast<double>(y)+327)*0.023659;
    // 输出鼠标点击的坐标
    target_x=x_double;
    target_y=y_double;
    std::cout<< "鼠标点击坐标：" << target_x<<"   "<<target_y<<std::endl;

    // 如果需要，可以在这里添加处理鼠标点击事件的代码
}
