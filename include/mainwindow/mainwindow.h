﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDialog>
#include <QProgressDialog>
#include <QProgressBar>
#include <QMessageBox>
#include <QTimer>
#include "./global/stdafx.h"
#include "./utils/csvreader/csvreader.h"
#include "./core/all.h"
#include "energyform.h"
#include "set_rate_diaglog.h"
#include "quarter_dialog.h"
#include "./utils/custom_widget.h"

#define MIN_WIDTH 1200
#define MIN_HEIGHT 650

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void pSig(int stepId, QString detail);
private:
    //初始化函数
    void init();
    //初始化控件状态函数
    void initWidgetState();
    //初始化控件的验证器
    void initWidgetValidator();
    //初始化CoreData
    void initCoreData();

    void initProcessDialog();

    //清除之前的数据
    void clear();
    //检查用户的输入
    bool checkUserInput();
    //准备关键数据
    void preImpData();

    //开始调用Eplus输出文件
    void callEplus();
    //分离 models 的步骤
    void lStep();
    //models 分离完成后的步骤
    void zStep();
    //节能率计算步骤
    void rStep();
    //结果显示步骤
    void showStep();

private slots:
    void on_btn_start_clicked();

    void on_radioButton_sec2_year_toggled(bool checked);

    void on_radioButton_sec2_quarter_toggled(bool checked);

    void on_radioButton_sec4_useCard_toggled(bool checked);

    void on_radioButton_sec4_useCardAndId_toggled(bool checked);

    void on_checkBox_sec6_keepHeat_toggled(bool checked);

    void on_checkBox_sec6_airconTempSet_toggled(bool checked);

    void on_checkBox_sec6_nightSETT_toggled(bool checked);

    void on_radioButton_sec6_ETM_toggled(bool checked);

    void on_radioButton_sec6_keepHeatNR_toggled(bool checked);

    void on_radioButton_sec6_newWind_toggled(bool checked);

    void on_radioButton_sec6_keepTempOffset_toggled(bool checked);

    void on_radioButton_sec6_keepTempSet_toggled(bool checked);

    //更新房间总量
    void updateRoomNumber();


public:
    explicit MainWindow(QWidget *parent = 0);
    enum Language { Chinese, English };
    //分为4个地区(1->0.38, 2->0.5, 3->0.8, 4->1.5)
    enum City { Harbin = 1, Beijing = 2, Lanzhou = 2, XiAn = 2,
                Chengdu = 3, Chongqing = 3, Hangzhou = 3, Nanchang = 3,
                Nanjing = 3, Shanghai = 3, Wuhan = 3,
                Guangzhou = 4, Guiyang = 4, Shenzhen = 4, Xiamen = 4 };
    ~MainWindow();
    void setLanguage(Language lang = Chinese);

private:
    Ui::MainWindow *ui;
    CustomProgressDialog *pdlg;
    QTimer *timer;
    SetRateDialog *_pRateDialog;
    QuarterDialog *_pQuaterDialog;
    Language _language;

    //CoreData
private:
    QMap<int, double> _heatProNumMap; //区域与隔热系数的对应关系
    QMap<QString, City> _citySecMap; //城市区域对应关系(English-City)
    QMap<QString, QString> _cityNameMap; //在不同语言下的城市对应关系(other-English)
    QString _city; //城市英文名
    QVector<int> _roomSizeVec; //可选房间面积数组
    QMap<int, double> _coolLoadReducePercentMap; //空调制冷下限温度与冷负荷百分比缩减关系
    QMap<int, double> _heatLoadReducePercentMap; //空调供热上限温度与热负荷百分比缩减关系
    QStringList _noticeList; //所有已翻译的提示信息列表

    //ImportantData
private:
    int _roomSize; //房间面积
    int _sumRoomNum; //总房间数
    QStringList _result; //结果数组
};

#endif // MAINWINDOW_H
