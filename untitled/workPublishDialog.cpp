#include "workPublishDialog.h"
#include <QPushButton>
#include <QToolButton>
#include <QFont>
TemporaryUserPublishDiaog::TemporaryUserPublishDiaog(QWidget *parent)
{
   qreal rate = 1;

    this->setWindowTitle(tr("Publish"));
    this->installEventFilter(this);


    QFont font;
    font.setFamily("宋体");
#ifdef Q_OS_MAC
            font.setPointSize(12);
#else
            font.setPointSize(9);
#endif

    QFont errorFont = font;
#ifdef Q_OS_MAC
            errorFont.setPointSize(11);
#else
            errorFont.setPointSize(8);
#endif

    PublishLabel *titleLabel = new PublishLabel(this);
    titleLabel->setStarShow(false);
    int titleLabelWidth = titleLabel->setLabelText(tr("Title"));

    PublishLabel *describeLabel = new PublishLabel(this);
    describeLabel->setStarShow(false);
    int describeLabelWidth = describeLabel->setLabelText(tr("Description"));

    PublishLabel *tagLabel = new PublishLabel(this);
    tagLabel->setStarShow(false);
    int tagLabelWidth = tagLabel->setLabelText(tr("Tag"));

    PublishLabel *copyLabel = new PublishLabel(this);
    copyLabel->setStarShow(true);
    int copyLabelWidth = copyLabel->setLabelText(tr("Copy"));

    int width = titleLabelWidth;

    width = qMax(width, describeLabelWidth);
    width = qMax(width, tagLabelWidth);
    width = qMax(width, copyLabelWidth);

    titleLabel->setFixedWidth(width);
    describeLabel->setFixedWidth(width);
    tagLabel->setFixedWidth(width);
    copyLabel->setFixedWidth(width);


    int lineEditWidth = 452 * rate;

    m_freeBtn = new QRadioButton(this);
    m_freeBtn->setText(tr("Allow copy"));
    m_freeBtn->setFixedHeight(24 * rate);
    m_freeBtn->setChecked(true);
    connect(m_freeBtn, SIGNAL(clicked(bool)), this, SLOT(radioButtonClicked()));

    QLabel *freeBtnLabel = new QLabel(this);
    freeBtnLabel->setFont(font);
    freeBtnLabel->setText(tr("All users can use your file immediately"));
    freeBtnLabel->setStyleSheet("QLabel{color: #7F7F7F;}");
    freeBtnLabel->setFixedWidth(freeBtnLabel->fontMetrics().width(freeBtnLabel->text()));

    m_payBtn = new QRadioButton(this);
    m_payBtn->setText(tr("Pay to copy"));
    m_payBtn->setFixedHeight(24 * rate);
    connect(m_payBtn, SIGNAL(clicked(bool)), this, SLOT(radioButtonClicked()));

    m_priceLineEdit = new QLineEdit(this);
    m_priceLineEdit->setFixedHeight(24 * rate);
    m_priceLineEdit->setPlaceholderText(tr("Range: 1~20 RMB"));
    m_priceLineEdit->setStyleSheet( "QLineEdit{border: 0.5px solid #DCDEE2; border-radius: 2px; padding-left: 5px;}"
                                    "QLineEdit:hover{border: 1px solid #57A3F3; border-radius: 2px;}"
                                    "QLineEdit:!enabled{background-color: #EEEEEE;}");

    int priceLineEditWidth = m_priceLineEdit->fontMetrics().width(m_priceLineEdit->placeholderText()) + 15 * rate;
    if (priceLineEditWidth < 88 * rate)
        priceLineEditWidth = 88 * rate;

    m_priceLineEdit->setFixedWidth(priceLineEditWidth);

    m_priceLineEdit->hide();
    connect(m_priceLineEdit, SIGNAL(textChanged(QString)), this, SLOT(priceLineEditTextChanged(QString)));

    QLabel *payBtnLabel = new QLabel(this);
    payBtnLabel->setFont(font);
    payBtnLabel->setText(tr("Users should pay for using your file"));
    payBtnLabel->setStyleSheet("QLabel{color: #7F7F7F;}");
    payBtnLabel->setFixedWidth(payBtnLabel->fontMetrics().width(payBtnLabel->text()));

    int firstWidth = m_freeBtn->sizeHint().width() + freeBtnLabel->width();
    int secondWidth = m_freeBtn->sizeHint().width() + 5 * rate + priceLineEditWidth + 5 * rate + payBtnLabel->width();

    lineEditWidth = qMax(lineEditWidth, firstWidth);
    lineEditWidth = qMax(lineEditWidth, secondWidth);

    m_descText = tr("You can publish your file to our Template Center for users to learn and communicate. Also, you can set a price for your file to get some profits.");

    m_descLabel = new QLabel(this);
    m_descLabel->setFixedWidth(width + 15 * rate + lineEditWidth);
    m_descLabel->setFont(font);
    m_descLabel->setWordWrap(true);
    m_descLabel->setText(m_descText);

    qreal pr = 1;
    QString Icompath = ":/image/income.png";
    QPixmap pix;
    pix.load(Icompath);

    QSize pixSize = pix.size() / pr;

    m_icon = new QLabel(this);
    m_icon->setFixedSize(pixSize);
    m_icon->setPixmap(pix);
    m_icon->hide();

    m_titleEdit = new QLineEdit(this);
    m_titleEdit->setFixedSize(lineEditWidth, 32 * rate);
    m_titleEdit->setStyleSheet("QPushButton{border: none; background-color: #017FFF; color: #FFFFFF; border-radius: 3px;}"
                              "QPushButton:hover{background-color: #056BD3;}");
    m_titleEdit->setPlaceholderText(tr("Please enter the title (less than 80 characters)"));
    connect(m_titleEdit, SIGNAL(textChanged(QString)), this, SLOT(titleEdit()));

    QString fileName = QString("%1").arg(tr("person replace work"));
    m_titleEdit->blockSignals(true);
    m_titleEdit->setText(fileName);
    m_titleEdit->blockSignals(false);


    QHBoxLayout *titileLayout = new QHBoxLayout();
    titileLayout->setSpacing(0);
    titileLayout->setMargin(0);
    titileLayout->addWidget(titleLabel);
    titileLayout->addSpacing(15 * rate);
    titileLayout->addWidget(m_titleEdit);

    m_titleError = new QLabel(this);
    m_titleError->setStyleSheet(QString("QLabel{color: red; padding-left: %1px;}").arg(width + 15 * rate));
    m_titleError->setFixedHeight(24 * rate);
    m_titleError->setFont(errorFont);
    m_titleError->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_describeEdit = new QTextEdit(this);
    m_describeEdit->setFixedSize(lineEditWidth, 72 * rate);
    m_describeEdit->setPlaceholderText(tr("Please enter a detailed description for your file"));
    connect(m_describeEdit, SIGNAL(textChanged()), this, SLOT(describeEdit()));

    QVBoxLayout *describeLabelLayout = new QVBoxLayout();
    describeLabelLayout->setSpacing(0);
    describeLabelLayout->setMargin(0);
    describeLabelLayout->addSpacing(5 * rate);
    describeLabelLayout->addWidget(describeLabel);
    describeLabelLayout->addStretch();

    QHBoxLayout *describeLayout = new QHBoxLayout();
    describeLayout->setSpacing(0);
    describeLayout->setMargin(0);
    describeLayout->addLayout(describeLabelLayout);
    describeLayout->addSpacing(15 * rate);
    describeLayout->addWidget(m_describeEdit);

    m_describeError = new QLabel(this);
    m_describeError->setStyleSheet(QString("QLabel{color: red; padding-left: %1px;}").arg(width + 15 * rate));
    m_describeError->setFixedHeight(24 * rate);
    m_describeError->setFont(errorFont);
    m_describeError->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_tagWidget = new QWidget();

    m_tagLayout = new QHBoxLayout();
    m_tagLayout->setContentsMargins(width + 15 * rate, 0, 0, 5 * rate);
    m_tagLayout->setSpacing(5 * rate);
    m_tagLayout->addStretch();

    m_tagWidget->setLayout(m_tagLayout);
    m_tagWidget->setFixedHeight(0);

    m_tagEdit = new QLineEdit(this);
    m_tagEdit->setPlaceholderText(tr("Please enter a tag, and press Enter to save your tag"));
    m_tagEdit->setFixedSize(lineEditWidth, 32 * rate);
    m_tagEdit->setStyleSheet( "QLineEdit{border: 0.5px solid #DCDEE2; border-radius: 2px; padding-left: 5px;}"
                              "QLineEdit:hover{border: 1px solid #57A3F3; border-radius: 2px;}"
                              "QLineEdit:!enabled{background-color: #EEEEEE;}");
    connect(m_tagEdit, SIGNAL(returnPressed()), this, SLOT(addTag()));

    QHBoxLayout *tagLayout = new QHBoxLayout();
    tagLayout->setSpacing(0);
    tagLayout->setMargin(0);
    tagLayout->addWidget(tagLabel);
    tagLayout->addSpacing(15 * rate);
    tagLayout->addWidget(m_tagEdit);

    m_tagError = new QLabel(this);
    m_tagError->setStyleSheet(QString("QLabel{color: red; padding-left: %1px;}").arg(width + 15 * rate));
    m_tagError->setFixedHeight(24 * rate);
    m_tagError->setFont(errorFont);
    m_tagError->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_priceError = new QLabel(this);
    m_priceError->setStyleSheet(QString("QLabel{color: red; padding-left: %1px;}").arg(width + 15 * rate));
    m_priceError->setFixedHeight(24 * rate);
    m_priceError->setFont(errorFont);
    m_priceError->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QHBoxLayout *radioLayout = new QHBoxLayout();
    radioLayout->setSpacing(0);
    radioLayout->setMargin(0);
    radioLayout->addWidget(copyLabel);
    radioLayout->addSpacing(15 * rate);
    radioLayout->addWidget(m_freeBtn);
    radioLayout->addStretch();
    radioLayout->addWidget(freeBtnLabel);

    QHBoxLayout *payButtonLayout = new QHBoxLayout();
    payButtonLayout->setSpacing(0);
    payButtonLayout->setMargin(0);
    payButtonLayout->addSpacing(width + 15 * rate);
    payButtonLayout->addWidget(m_payBtn);
    payButtonLayout->addSpacing(5 * rate);
    payButtonLayout->addWidget(m_priceLineEdit);
    payButtonLayout->addSpacing(5 * rate);
    payButtonLayout->addStretch();
    payButtonLayout->addWidget(payBtnLabel);

    m_checkBox = new QCheckBox(tr("I agree to the"), this);
    m_checkBox->setFixedHeight(24 * rate);
    connect(m_checkBox, SIGNAL(clicked(bool)), this, SLOT(checkBoxClicked()));

    QLabel *label = new QLabel(this);

    label->setText(QString("<a style=\"text-decoration: none\" href=\"javascript:void(0)\">%1</a>").arg(tr("Template Publishing Agreement")));
    connect(label, SIGNAL(linkActivated(QString)), this, SLOT(showNotice()));

    m_noticeError = new QLabel(this);
    m_noticeError->setStyleSheet("QLabel{color: red;}");
    m_noticeError->setFixedHeight(24 * rate);
    m_noticeError->setFont(errorFont);
    m_noticeError->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    QHBoxLayout *noticeLayout = new QHBoxLayout();
    noticeLayout->setMargin(0);
    noticeLayout->setSpacing(0);
    noticeLayout->addWidget(m_checkBox);
    noticeLayout->addWidget(label);
    noticeLayout->addStretch();

    QPushButton *buttonBoxOk = new QPushButton(this);
    buttonBoxOk->setText(tr("Ok"));
    buttonBoxOk->setFixedSize(75*rate,27*rate);
    buttonBoxOk->setStyleSheet("QPushButton{border: none; background-color: #017FFF; color: #FFFFFF; border-radius: 3px;}"
                                                           "QPushButton:hover{background-color: #056BD3;}");
    QPushButton *buttonBoxCancel = new QPushButton(this);
    buttonBoxCancel->setText(tr("Cancel"));
    buttonBoxCancel->setFixedSize(75*rate,25*rate);
    buttonBoxCancel->setStyleSheet("QPushButton{background-color: #D5D7DB; color: #000000; border-radius: 3px;}"
                                                               "QPushButton:hover{background-color: #C5C6C9;}");
    connect(buttonBoxOk, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(buttonBoxCancel, SIGNAL(clicked(bool)), this, SLOT(reject()));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(0);
    buttonLayout->setMargin(0);
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonBoxOk);
    buttonLayout->addSpacing(5*rate);
    buttonLayout->addWidget(buttonBoxCancel);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(32 * rate + 5, 24 * rate + 5, 32 * rate + 5, 24 * rate + 5);
    vLayout->setSpacing(0);
    vLayout->addWidget(m_descLabel);
    vLayout->addSpacing(16*rate);
    vLayout->addLayout(titileLayout);
    vLayout->addWidget(m_titleError);
    vLayout->addLayout(describeLayout);
    vLayout->addWidget(m_describeError);
    vLayout->addWidget(m_tagWidget);
    vLayout->addLayout(tagLayout);
    vLayout->addWidget(m_tagError);
    vLayout->addLayout(radioLayout);
    vLayout->addLayout(payButtonLayout);

    vLayout->addLayout(noticeLayout);
    vLayout->addWidget(m_noticeError);
    vLayout->addLayout(buttonLayout);
    this->setLayout(vLayout);
}

TemporaryUserPublishDiaog::~TemporaryUserPublishDiaog()
{

}

void TemporaryUserPublishDiaog::getUserPublishInfo(QString UserStr)
{

}

void TemporaryUserPublishDiaog::updateUI(QStringList str)
{
    m_titleEdit->blockSignals(true);
    m_titleEdit->setText(tr("* work Name"));
    m_titleEdit->blockSignals(false);

    m_describeEdit->blockSignals(true);
    m_describeEdit->setText(tr("* Describe"));
    m_describeEdit->blockSignals(false);

    for (int i = 0; i < str.count(); i++) {
        m_tagEdit->setText(str.at(0));
        addTag();
    }
    m_tagEdit->setText("");

    m_tagError->setText("");

   if (m_clonePrice == 0) {
        m_freeBtn->setChecked(true);
        m_priceLineEdit->hide();
    } else {
        m_payBtn->setChecked(true);
        m_priceLineEdit->show();
        m_priceLineEdit->blockSignals(true);
        m_priceLineEdit->setText(QString::number(m_clonePrice));
        m_priceLineEdit->blockSignals(false);
   }
}

void TemporaryUserPublishDiaog::describeEdit()
{
    QString plainText = m_describeEdit->toPlainText();

    if (plainText.count() > 300) {
        m_describeError->setText(tr("Description cannot be more than %1 characters!").arg(300));
    } else {
        m_describeError->setText("");
    }
}

void TemporaryUserPublishDiaog::titleEdit()
{
    QString title = m_titleEdit->text();

    int count = title.count();

    if (count > 80) {
        m_titleError->setText(tr("The title cannot be more than 80 characters!"));
    } else {
        QRegExp rx("[?*:\"<>/|$%^#&+]");

        if (rx.indexIn(m_titleEdit->text()) != -1 || m_titleEdit->text().indexOf("\\") != -1) {
            QString str = tr("The title cannot contain any of the following characters:");
            str = str + " ? * : \" < > \\ / | $ % ^ # & +";
            m_titleError->setText(str);
        } else {
            m_titleError->setText("");
        }
    }
}

void TemporaryUserPublishDiaog::addTag()
{
    qreal rate = 1;
    if (m_tagList.count() >= 5) {
        m_tagError->setText(tr("You cannot add more than 5 tags!"));
        return;
    }

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString text = m_tagEdit->text();
    if (button) {
        text = button->text();
    }

    if (!button && m_tagEdit && m_tagEdit->text().trimmed().isEmpty()) {
        m_tagEdit->setText("");
        return;
    }

    for (int i = 0; i < m_tagList.count(); i++) {
        if (m_tagList[i] && m_tagList[i]->text() == text) {
            if (!button)
                m_tagEdit->setText("");
            return;
        }
    }

    QToolButton *btn = new QToolButton(this);
    btn->setText(text);
    btn->setMaximumWidth(100 * rate);
    btn->setFixedHeight(30 * rate);
    btn->setMouseTracking(true);
    btn->setStyleSheet(QString("QToolButton{border: 1px solid #E0E0E0; background: #FFFFFF; border-radius: %1px; padding: 0px %1px;}")
                        .arg(30 * rate * 0.5));
    btn->setToolTip(text);
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(deleteTag()));

    m_tagList.append(btn);

    m_tagLayout->insertWidget(m_tagLayout->count() - 1, btn);

    m_tagWidget->setFixedHeight((5 + 30) * rate);

    if (!button)
        m_tagEdit->setText("");

    m_tagError->setText("");
}

void TemporaryUserPublishDiaog::deleteTag()
{
    QToolButton *btn = qobject_cast<QToolButton*>(sender());

    int index = m_tagList.indexOf(btn);
    if (!btn || index < 0 || index >= m_tagList.count())
        return;

    m_tagLayout->removeWidget(btn);
    m_tagList.removeAt(index);

    if (m_tagList.count() == 0) {
        if (m_tagEdit->text().isEmpty())
            m_tagEdit->setText(btn->text());

        m_tagWidget->setFixedHeight(0);
        this->adjustSize();
    }
    m_tagError->setText("");

    btn->deleteLater();
}

void TemporaryUserPublishDiaog::radioButtonClicked()
{
    QRadioButton *radioButton = qobject_cast<QRadioButton*>(sender());
    if (radioButton == m_freeBtn) {
        m_priceLineEdit->hide();
    } else if (radioButton == m_payBtn) {
        m_priceLineEdit->show();
    }

    m_priceError->setText("");
}

void TemporaryUserPublishDiaog::showNotice()
{
    qreal rate =1.0;
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle(tr("Work Publishing Agreement"));
    dialog->setFixedWidth(520 * rate);
    int shadowWidth =5;

    int width = 520 * rate - (15 * rate + shadowWidth) * 2;

    QLabel *titleLabel = new QLabel(dialog);
    titleLabel->setText(tr("Welcome to here!you have to know there:"));

    QLabel *firstLabel = new QLabel(dialog);
    firstLabel->setText(tr("1. The first is.................."));
    firstLabel->setWordWrap(firstLabel->fontMetrics().width(firstLabel->text()) > width);

    QLabel *secondLabel = new QLabel(dialog);
    secondLabel->setText(tr("2. The second...................."));
    secondLabel->setWordWrap(secondLabel->fontMetrics().width(secondLabel->text()) > width);

    QLabel *thirdLabel = new QLabel(dialog);
    thirdLabel->setText(tr("3. The third......................"));
    thirdLabel->setWordWrap(thirdLabel->fontMetrics().width(thirdLabel->text()) > width);

    QLabel *fourthLabel = new QLabel(dialog);
    fourthLabel->setText(tr("4. The fourth............................"));
    fourthLabel->setWordWrap(fourthLabel->fontMetrics().width(fourthLabel->text()) > width);


    QLabel *seventhLabel = new QLabel(dialog);
    seventhLabel->setText(tr("After, Tank you."));
    seventhLabel->setWordWrap(seventhLabel->fontMetrics().width(seventhLabel->text()) > width);


    QPushButton *buttonBoxOk = new QPushButton(dialog);
    QPushButton *buttonBoxCancel = new QPushButton(dialog);
    buttonBoxCancel->setText(tr("Cancel"));
    buttonBoxOk->setText(tr("Ok"));
    buttonBoxOk->setMinimumSize(75 * rate, 27 * rate);
    buttonBoxOk->setMaximumSize(75 * rate, 27 * rate);
    buttonBoxCancel->setMinimumSize(75 * rate, 27 * rate);
    buttonBoxCancel->setMaximumSize(75 * rate, 27 * rate);
    buttonBoxOk->setStyleSheet("QPushButton{border: none; background-color: #017FFF; color: #FFFFFF; border-radius: 3px;}"
                                                           "QPushButton:hover{background-color: #056BD3;}");

    buttonBoxCancel->setStyleSheet("QPushButton{background-color: #D5D7DB; color: #000000; border-radius: 3px;}"
                                                               "QPushButton:hover{background-color: #C5C6C9;}");
    connect(buttonBoxOk, SIGNAL(clicked(bool)), dialog, SLOT(accept()));
    connect(buttonBoxCancel, SIGNAL(clicked(bool)), dialog, SLOT(reject()));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->setMargin(5);
    buttonLayout->addWidget(buttonBoxOk);
    buttonLayout->addSpacing(5);
    buttonLayout->addWidget(buttonBoxCancel);

    QVBoxLayout *vLayout =  new QVBoxLayout();
    vLayout->setContentsMargins(15 * rate + shadowWidth, 15 * rate + shadowWidth, 15 * rate + shadowWidth, 10 * rate + shadowWidth);
    vLayout->setSpacing(5 * rate);
    vLayout->addWidget(titleLabel);
    vLayout->addWidget(firstLabel);
    vLayout->addWidget(secondLabel);
    vLayout->addWidget(thirdLabel);
    vLayout->addWidget(fourthLabel);
    vLayout->addSpacing(15 * rate);
    vLayout->addLayout(buttonLayout);

    dialog->setLayout(vLayout);

    dialog->exec();
    dialog->deleteLater();
}

void TemporaryUserPublishDiaog::priceLineEditTextChanged(QString text)
{
    if (text.isEmpty()) {
        m_priceError->setText(tr("The price can not be empty!"));
        return;
    } else {
        m_priceError->setText("");
    }

    int price = text.toInt();
    if (price <= 0)
        price = 1;
    else if (price > 20)
        price = 20;

    m_priceLineEdit->blockSignals(true);
    m_priceLineEdit->setText(QString::number(price));
    m_priceLineEdit->blockSignals(false);
}

void TemporaryUserPublishDiaog::checkBoxClicked()
{
    if (!m_checkBox)
        return;

    if (!m_checkBox->isChecked()) {
        m_noticeError->setText(tr("Please agree to the Template Publishing Agreement!"));
    } else {
        m_noticeError->setText("");
    }
}

void TemporaryUserPublishDiaog::accept()
{
    bool flag = true;

    QString title = m_titleEdit->text();

    int count = title.count();

    if (count > 80) {
        m_titleError->setText(tr("The title cannot be more than 80 characters!"));
        flag = false;
    } else {
        QRegExp rx("[?*:\"<>/|$%^#&+]");

        if (rx.indexIn(m_titleEdit->text()) != -1 || m_titleEdit->text().indexOf("\\") != -1) {
            QString str = tr("The title cannot contain any of the following characters:");
            str = str + " ? * : \" < > \\ / | $ % ^ # & +";
            m_titleError->setText(str);
            flag = false;
        }
    }

    int max = 300;

    if (m_describeEdit->toPlainText().count() > max) {
        m_describeError->setText(tr("Description cannot be more than %1 characters!").arg(max));
        flag = false;
    }

    if (m_payBtn->isChecked() && m_priceLineEdit->text().isEmpty()) {
        m_priceError->setText(tr("The price can not be empty!"));
        flag = false;
    }

    if (!m_checkBox->isChecked()) {
        m_noticeError->setText(tr("Please agree to the Template Publishing Agreement!"));
        flag = false;
    }

    if (flag) {
        QDialog::accept();
    }
}

bool TemporaryUserPublishDiaog::eventFilter(QObject *obj, QEvent *event)
{
//    if (event->type() == QEvent::) {
//        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
//        if (keyEvent && (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)) {
//            return true;
//        }
//    }

    return QDialog::eventFilter(obj, event);
}

void TemporaryUserPublishDiaog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    bool showFlag = false;
    if (m_icon && m_descLabel && !m_descText.isEmpty()) {
        QString html = QString("<html><body><p><span style=\"font-size: %1pt;\">%2</span></p></body></html>")
                       .arg(m_descLabel->font().pointSize())
                       .arg(m_descText);

        QTextDocument textDoc;
        textDoc.setHtml(html);
        textDoc.setTextWidth(m_descLabel->width());
        textDoc.setDocumentMargin(0);
        QTextCursor cursor(&textDoc);
        cursor.movePosition(QTextCursor::End);

        QRectF rect =QRectF(5,5,5,5);

        QPoint pos1 = m_descLabel->mapTo(this, rect.topRight().toPoint());
        QPoint pos2 = m_descLabel->mapTo(this, rect.bottomRight().toPoint());
        int x = pos1.x() + 5;
        int y = pos2.y() - m_icon->height();
        if (y < pos1.y()) {
            y = pos1.y();
        }

        m_icon->show();
        m_icon->move(x, y);
        showFlag = true;
    }

    if (!showFlag && m_icon) {
        m_icon->hide();
    }
}

PublishLabel::PublishLabel(QWidget *parent):QWidget(parent)
{
    qreal rate = 1;
    QFont font;
    font.setFamily("宋体");
#ifdef Q_OS_MAC
    font.setPointSize(13);
#else
    font.setPointSize(10);
#endif

    m_starLabel = new QLabel(this);
    m_starLabel->setText("*");
    m_starLabel->setFont(font);
    m_starLabel->setStyleSheet("QLabel{color: red;}");
    m_starLabel->setFixedWidth(m_starLabel->fontMetrics().width(m_starLabel->text()));

#ifdef Q_OS_MAC
    font.setPointSize(12);
#else
    font.setPointSize(9);
#endif

    m_textLabel = new QLabel(this);
    m_textLabel->setFont(font);


    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(m_starLabel);
    layout->addSpacing(3 * rate);
    layout->addWidget(m_textLabel);
    layout->addStretch();

    this->setLayout(layout);
}

PublishLabel::~PublishLabel()
{

}

int PublishLabel::setLabelText(QString text)
{
    m_textLabel->setText(text);
    int width = m_starLabel->width() + 3;
    width += m_textLabel->fontMetrics().width(m_textLabel->text());

    return width;
}

void PublishLabel::setStarShow(bool show)
{
    if(show){
        m_starLabel->setText("*");
    }else{
        m_starLabel->setText("");
    }
}
