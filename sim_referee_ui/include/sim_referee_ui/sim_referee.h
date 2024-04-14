#ifndef REFEREE_GUI_H
#define REFEREE_GUI_H

#include <QWidget>
#include <ros/ros.h>
#include <qtimer.h>
#include <std_msgs/String.h>
#include <robot_msg/RefereeInfoMsg.h>
#include <robot_msg/RobotHP.h>
#include "Map_select.h"
namespace Ui
{
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
  robot_msg::RobotHP team_hp;
public slots:
  void spinOnce();  // 更新label信息
  void countdown(); // 倒计时
private slots:
  void on_slider_time_sliderMoved(int position);

  void on_button_stage1_clicked();

  void on_button_stage2_clicked();

  void on_button_stage3_clicked();

  void on_button_stage4_clicked();

  void on_button_stage5_clicked();

  void on_slider_enemy_hero_sliderMoved(int position);

  void on_slider_enemy_engineer_sliderMoved(int position);

  void on_slider_enemy_infantry_3_sliderMoved(int position);

  void on_slider_enemy_infantry_4_sliderMoved(int position);

  void on_slider_enemy_infantry_5_sliderMoved(int position);

  void on_slider_enemy_sentry_sliderMoved(int position);

  void on_slider_enemy_outpose_sliderMoved(int position);

  void on_slider_enemy_base_sliderMoved(int position);

  void on_target_x_valueChanged(double arg1);


  void on_slider_team_hero_sliderMoved(int position);

  void on_slider_team_engineer_sliderMoved(int position);

  void on_slider_team_infantry_3_sliderMoved(int position);

  void on_slider_team_infantry_4_sliderMoved(int position);


  void on_slider_team_infantry_5_sliderMoved(int position);

  void on_slider_team_sentry_sliderMoved(int position);

  void on_slider_team_outpose_sliderMoved(int position);

  void on_slider_team_base_sliderMoved(int position);

  void on_botto_target_clicked();

  void on_target_y_valueChanged(double arg1);

  void on_key_edit_windowIconTextChanged(const QString &iconText);

  void on_botton_key_clicked();

  void on_key_edit_textChanged();

  void on_pushButton_3_clicked();

  private:
  Ui::referee_gui *ui;
  QTimer *ros_timer;
  QTimer *match_timer; // 用于比赛计时
  ros::Time last_time;
  double target_x_;
  double target_y_;
  char key_;
  void referee_info_publish(); // 发布referee_info数据
  void referee_info_init(); // 初始化裁判系统消息
  void enemy_hp_init();     // 初始化敌方血量
  void update_enemy_hp();   // 更新敌方血量滑条
  void team_hp_init();     // 初始化敌方血量
  void update_team_hp();   // 更新敌方血量滑条
  void target_pos_update();//更新目标点坐标
  double last_target_x_;
  double last_target_y_;
  double current_target_x_;
  double current_target_y_;
  ros::NodeHandlePtr nh_;
  ros::Publisher referee_info_pub_; // 发布referee_info数据
  ros::Publisher enemy_hp_pub_;     // 发布enemy_hp数据，40hz
  ros::Publisher team_hp_pub_;
  Map_select *configWindow;
};

#endif // REFEREE_GUI_H
