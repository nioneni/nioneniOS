//
//  Copyright (C) 2022
//

#include "mmain.h"
#include "minstall.h"

MInstall *minstall;
bool firstShow;

MMain::MMain()
{
    setupUi(this);
    minstall = new MInstall(mainFrame);
    minstall->move(5,0);
    firstShow = true;
}

MMain::~MMain() {
}

/////////////////////////////////////////////////////////////////////////

void MMain::setHelpText(const QString &text)
{
    mainHelp->setText(text);
}

void MMain::closeEvent(QCloseEvent *e)
{
    system("mv /etc/udev/rules.d/90-fstab-automount.rules.live /etc/udev/rules.d/90-fstab-automount.rules >/dev/null 2>&1");
    system("umount -l /mnt/nioneniOS/home >/dev/null 2>&1");
    system("umount -l /mnt/nioneniOS >/dev/null 2>&1");
    system("rm -r /mnt/nioneniOS >/dev/null 2>&1");
    QWidget::closeEvent(e);
}

/////////////////////////////////////////////////////////////////////////
// public slots

void MMain::closeClicked()
{
    close();
}

void MMain::showEvent(QShowEvent *e)
{
    if (firstShow) {
        firstShow = false;
        minstall->firstRefresh(this);
    }
}
