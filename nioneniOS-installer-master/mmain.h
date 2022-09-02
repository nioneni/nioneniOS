//
//  Copyright (C) 2022
//

#include "ui_memain.h"

class MMain : public QDialog, public Ui::MeMain {
    Q_OBJECT

public:
    MMain();
    ~MMain();

    void setHelpText(const QString &text);
    void closeEvent(QCloseEvent * e);

public slots:
    virtual void closeClicked();
    virtual void showEvent(QShowEvent *e);
};


