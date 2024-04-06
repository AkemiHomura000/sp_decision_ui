#include "sim_referee.h"
#include "ui_sim_referee.h"

referee_gui::referee_gui(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::referee_gui)
{
  ui->setupUi(this);

  nh_.reset(new ros::NodeHandle("~"));
  referee_info_init();
  enemy_hp_init();
  // setup the timer that will signal ros stuff to happen
  ros_timer = new QTimer(this);
  connect(ros_timer, SIGNAL(timeout()), this, SLOT(spinOnce()));
  ros_timer->start(100);  // set the rate to 100ms  You can change this if you want to increase/decrease update rate
  last_time=ros::Time::now();
  match_timer = new QTimer(this);
  connect(match_timer, SIGNAL(timeout()), this, SLOT(countdown()));
  match_timer->start(100);
  // setup subscriber by according to the ~/chatter_topic param
  // std::string listen_topic;
  // nh_->param<std::string>("listen_topic",listen_topic,"/talker/chatter");
  // chatter_sub_ = nh_->subscribe<std_msgs::String>(listen_topic, 1, &referee_gui::chatterCallback, this);

  // publish a message on the channel specified by ~/hello_topic param
  // std::string hello_topic;
  // nh_->param<std::string>("hello_topic",hello_topic,"chatter");
  // hello_pub_ = nh_->advertise<std_msgs::String>(hello_topic,1);

  referee_info_pub_ = nh_->advertise<robot_msg::RefereeInfoMsg>("/referee_info",1);
  enemy_hp_pub_ = nh_->advertise<robot_msg::RobotHP>("/enemy_hp",1);
}

referee_gui::~referee_gui()
{
  delete ui;
  delete ros_timer;
}


void referee_gui::spinOnce(){
  if(ros::ok()){
    ros::spinOnce();
    referee_info_pub_.publish(referee_info);
    enemy_hp_pub_.publish(enemy_hp);
    std::stringstream ss;
    ss << "stage:"<<static_cast<double>(referee_info.game_progress);
    QString qstr = QString::fromStdString(ss.str());
    ui->label_stage->setText(qstr);//显示比赛阶段
    std::stringstream ss_1;
    ss_1 << "rfid1:"<<static_cast<int>(referee_info.rfid_remedy_state);
    QString qstr_1 = QString::fromStdString(ss_1.str());
    ui->label_rfid1->setText(qstr_1);//显示rfid1状态
    std::stringstream ss_2;
    ss_2 << "rfid2:"<<static_cast<int>(referee_info.rfid_centerpoint_state);
    QString qstr_2 = QString::fromStdString(ss_2.str());
    ui->label_rfid2->setText(qstr_2);//显示rfid2状态
    std::stringstream ss_3;
    ss_3 <<static_cast<int>(enemy_hp.Hero_HP);
    QString qstr_3 = QString::fromStdString(ss_3.str());
    ui->label_enemy_hero_hp->setText(qstr_3);//敌方血量1
    std::stringstream ss_4;
    ss_4 <<static_cast<int>(enemy_hp.Engineer_HP);
    QString qstr_4 = QString::fromStdString(ss_4.str());
    ui->label_enemy_engineer_hp->setText(qstr_4);//敌方血量2
    std::stringstream ss_5;
    ss_5 <<static_cast<int>(enemy_hp.Infantry_3_HP);
    QString qstr_5 = QString::fromStdString(ss_5.str());
    ui->label_enemy_infantry_3_hp->setText(qstr_5);//敌方血量3
    std::stringstream ss_6;
    ss_6 <<static_cast<int>(enemy_hp.Infantry_4_HP);
    QString qstr_6 = QString::fromStdString(ss_6.str());
    ui->label_enemy_infantry_4_hp->setText(qstr_6);//敌方血量4
    std::stringstream ss_7;
    ss_7 <<static_cast<int>(enemy_hp.Infantry_5_HP);
    QString qstr_7 = QString::fromStdString(ss_7.str());
    ui->label_enemy_infantry_5_hp->setText(qstr_7);//敌方血量5
    std::stringstream ss_8;
    ss_8 <<static_cast<int>(enemy_hp.Sentry_HP);
    QString qstr_8 = QString::fromStdString(ss_8.str());
    ui->label_enemy_sentry_hp->setText(qstr_8);//敌方血量6
    std::stringstream ss_9;
    ss_9 <<static_cast<int>(enemy_hp.OutPose_HP);
    QString qstr_9 = QString::fromStdString(ss_9.str());
    ui->label_enemy_outpose_hp->setText(qstr_9);//敌方血量7
    std::stringstream ss_10;
    ss_10 <<static_cast<int>(enemy_hp.Base_HP);
    QString qstr_10 = QString::fromStdString(ss_10.str());
    ui->label_enemy_base_hp->setText(qstr_10);//敌方血量8
  }
  else
      QApplication::quit();
}


// void referee_gui::chatterCallback(const std_msgs::String::ConstPtr &msg){
//   auto qstring_msg = QString::fromStdString( msg->data.c_str() );

//   ui->chatter->setText(qstring_msg);
// }

// void referee_gui::on_hi_button_clicked()
// {
//   std_msgs::String msg;
//   std::stringstream ss;
//   ss << "hello world " << ui->hi_num->value();
//   msg.data = ss.str();

//   hello_pub_.publish(msg);

//   ui->hi_num->setValue(ui->hi_num->value()+1);
// }
// void referee_gui::on_start_button_clicked()
// {
//     robot_msg::RefereeInfoMsg referee_info;
//     referee_info.robot_HP=0;
//     referee_info.base_HP=1;
//     referee_info.game_progress=1;
//     std::stringstream ss;
//         int sliderValue = ui->slider->value();
    // ss << "hp:"<<sliderValue<<"baseHP:"<<referee_info.base_HP;
    // QString qstr = QString::fromStdString(ss.str());
    // ui->label->setText(qstr);
//     referee_info_pub_.publish(referee_info);
// }

void referee_gui::on_slider_time_sliderMoved(int position)
{
    referee_info.stage_remain_time=position;
}
void referee_gui::countdown()
{
    if(referee_info.stage_remain_time==0)//倒计时为0自动进入下一阶段
    {
        switch(static_cast<int>(referee_info.game_progress))
        {
        case 1:
            on_button_stage2_clicked();
            break;
        case 2:
            on_button_stage3_clicked();
            break;
        case 3:
            on_button_stage4_clicked();
            break;
        case 4:
            on_button_stage5_clicked();
            break;
        default:
            break;
        }
    }
    if((ros::Time::now().sec-last_time.sec)>0.5&&referee_info.stage_remain_time>0)
    {
        referee_info.stage_remain_time--;
        ui->slider_time->setValue(referee_info.stage_remain_time);
        last_time=ros::Time::now();
    }

    std::stringstream ss;
    ss << "remainder"<<referee_info.stage_remain_time;
    QString qstr = QString::fromStdString(ss.str());
    ui->label_time->setText(qstr);
}
void referee_gui::referee_info_init()
{
    referee_info.base_HP=4000;
    referee_info.game_progress=1;
    referee_info.robot_HP=400;
    referee_info.stage_remain_time=180;
    referee_info.rfid_centerpoint_state=0;
    referee_info.rfid_remedy_state=0;
}
void referee_gui::enemy_hp_init()
{
    enemy_hp.Hero_HP=500;
    enemy_hp.Engineer_HP=250;
    enemy_hp.Infantry_3_HP=400;
    enemy_hp.Infantry_4_HP=400;
    enemy_hp.Infantry_5_HP=400;
    enemy_hp.Sentry_HP=400;
    enemy_hp.OutPose_HP=1500;
    enemy_hp.Base_HP=5000;
    update_enemy_hp();
}
void referee_gui::on_button_stage1_clicked()
{
    referee_info.base_HP=5000;
    referee_info.game_progress=1;
    referee_info.robot_HP=400;
    referee_info.stage_remain_time=180;
    referee_info.rfid_centerpoint_state=0;
    referee_info.rfid_remedy_state=0;
}

void referee_gui::update_enemy_hp()
{
    ui->slider_enemy_hero->setValue(enemy_hp.Hero_HP);
    ui->slider_enemy_engineer->setValue(enemy_hp.Engineer_HP);
    ui->slider_enemy_infantry_3->setValue(enemy_hp.Infantry_3_HP);
    ui->slider_enemy_infantry_4->setValue(enemy_hp.Infantry_4_HP);
    ui->slider_enemy_infantry_5->setValue(enemy_hp.Infantry_5_HP);
    ui->slider_enemy_sentry->setValue(enemy_hp.Sentry_HP);
    ui->slider_enemy_outpose->setValue(enemy_hp.OutPose_HP);
    ui->slider_enemy_base->setValue(enemy_hp.Base_HP);
}

void referee_gui::on_button_stage2_clicked()
{
    referee_info.base_HP=5000;
    referee_info.game_progress=2;
    referee_info.robot_HP=400;
    referee_info.stage_remain_time=15;
    referee_info.rfid_centerpoint_state=0;
    referee_info.rfid_remedy_state=0;
}


void referee_gui::on_button_stage3_clicked()
{
    referee_info.base_HP=5000;
    referee_info.game_progress=3;
    referee_info.robot_HP=400;
    referee_info.stage_remain_time=5;
    referee_info.rfid_centerpoint_state=0;
    referee_info.rfid_remedy_state=0;
}


void referee_gui::on_button_stage4_clicked()
{
    referee_info.base_HP=5000;
    referee_info.game_progress=4;
    referee_info.robot_HP=400;
    referee_info.stage_remain_time=420;
    referee_info.rfid_centerpoint_state=0;
    referee_info.rfid_remedy_state=0;
}


void referee_gui::on_button_stage5_clicked()
{
    referee_info.base_HP=5000;
    referee_info.game_progress=5;
    referee_info.robot_HP=400;
    referee_info.stage_remain_time=10;
    referee_info.rfid_centerpoint_state=0;
    referee_info.rfid_remedy_state=0;
}


void referee_gui::on_button_rfid1_clicked()
{
    if(referee_info.rfid_remedy_state)
    {
        referee_info.rfid_remedy_state=0;
    }
    else
    {
        referee_info.rfid_remedy_state=1;
    }
}


void referee_gui::on_button_rfid2_clicked()
{
    if(referee_info.rfid_centerpoint_state)
    {
        referee_info.rfid_centerpoint_state=0;
    }
    else
    {
        referee_info.rfid_centerpoint_state=1;
    }
}


void referee_gui::on_slider_enemy_hero_sliderMoved(int position)
{
    enemy_hp.Hero_HP=position;
}


void referee_gui::on_slider_enemy_engineer_sliderMoved(int position)
{
    enemy_hp.Engineer_HP=position;
}


void referee_gui::on_slider_enemy_infantry_3_sliderMoved(int position)
{
    enemy_hp.Infantry_3_HP=position;
}


void referee_gui::on_slider_enemy_infantry_4_sliderMoved(int position)
{
    enemy_hp.Infantry_4_HP=position;
}


void referee_gui::on_slider_enemy_infantry_5_sliderMoved(int position)
{
    enemy_hp.Infantry_5_HP=position;
}


void referee_gui::on_slider_enemy_sentry_sliderMoved(int position)
{
    enemy_hp.Sentry_HP=position;
}


void referee_gui::on_slider_enemy_outpose_sliderMoved(int position)
{
    enemy_hp.OutPose_HP=position;
}


void referee_gui::on_slider_enemy_base_sliderMoved(int position)
{
    enemy_hp.Base_HP=position;
}

