#ifndef WORKPUBLISHDIALOG_H
#define WORKPUBLISHDIALOG_H
#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QRadioButton>
#include <QCheckBox>
#include <QHBoxLayout>

//class MainWindow;
class TemporaryUserPublishDiaog : public QDialog
{
    Q_OBJECT

public:
    TemporaryUserPublishDiaog(QWidget *parent = Q_NULLPTR);
    ~TemporaryUserPublishDiaog();

    /**
     * @brief getUserPublishInfo 传出用户发布信息
     */
    void getUserPublishInfo(QString UserStr);

    void updateUI(QStringList str);

public slots:
    void describeEdit();
    void titleEdit();

    void addTag();
    void deleteTag();

    void radioButtonClicked();
    void showNotice();
    void priceLineEditTextChanged(QString text);

    void checkBoxClicked();

    void accept();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

    void showEvent(QShowEvent *event);

private:
//    MainWindow                  *m_mainWindow;

    QLabel                      *m_icon;
    QString                     m_descText;
    QLabel                      *m_descLabel;

    QLineEdit                   *m_titleEdit;
    QLabel                      *m_titleError;

    QTextEdit             *m_describeEdit;
    QLabel                      *m_describeError;

    QLineEdit                   *m_tagEdit;
    QLabel                      *m_tagError;
    QList<QToolButton*>          m_tagList;
    QWidget                     *m_tagWidget;
    QHBoxLayout                 *m_tagLayout;

    QRadioButton                *m_freeBtn;
    QRadioButton                *m_payBtn;
    QLineEdit                   *m_priceLineEdit;
    QLabel                      *m_priceError;

    QLabel                      *m_noticeError;

    QCheckBox                    *m_checkBox;
    QStringList                  *TagList;

    int                          m_clonePrice;
};
class PublishLabel : public QWidget
{
    Q_OBJECT

public:
    PublishLabel(QWidget *parent = Q_NULLPTR);
    ~PublishLabel();

    int setLabelText(QString text);

    void setStarShow(bool show);

private:
    QLabel          *m_starLabel;
    QLabel          *m_textLabel;
};
#endif // WORKPUBLISHDIALOG_H
