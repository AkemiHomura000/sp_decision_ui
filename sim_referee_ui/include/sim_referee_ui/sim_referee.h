#ifndef REFEREE_GUI_H
#define REFEREE_GUI_H

#include <QWidget>
#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>
#include <robot_msg/RefereeInfoMsg.h>
#include <robot_msg/RobotHP.h>
namespace Ui {
class referee_gui;
}

class referee_gui : public QWidget
{
  Q_OBJECT

public:
  explicit referee_gui(QWidget *parent = nullptr);
  ~referee_gui();
  robot_msg::RefereeInfoMsg referee_info;
  robot_msg::RobotHP enemy_hp;
public slots:
  void spinOnce();//更新label信息
  void countdown();//倒计时
private slots:
  void on_slider_time_sliderMoved(int position);

    void on_button_stage1_clicked();

  void on_button_stage2_clicked();

    void on_button_stage3_clicked();

  void on_button_stage4_clicked();

    void on_button_stage5_clicked();

  void on_button_rfid1_clicked();

    void on_button_rfid2_clicked();

  void on_slider_enemy_hero_sliderMoved(int position);

    void on_slider_enemy_engineer_sliderMoved(int position);

  void on_slider_enemy_infantry_3_sliderMoved(int position);

    void on_slider_enemy_infantry_4_sliderMoved(int position);

  void on_slider_enemy_infantry_5_sliderMoved(int position);

    void on_slider_enemy_sentry_sliderMoved(int position);

  void on_slider_enemy_outpose_sliderMoved(int position);

    void on_slider_enemy_base_sliderMoved(int position);

private:
  Ui::referee_gui *ui;
  QTimer *ros_timer;
  QTimer *match_timer;//用于比赛计时
  ros::Time last_time;
  void referee_info_init();//初始化裁判系统消息
  void enemy_hp_init();//初始化敌方血量
  void update_enemy_hp();//更新敌方血量滑条
  ros::NodeHandlePtr nh_;
  ros::Publisher  referee_info_pub_;//发布referee_info数据
  ros::Publisher  enemy_hp_pub_;//发布enemy_hp数据，40hz
};

#endif // REFEREE_GUI_H
