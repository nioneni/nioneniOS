//
//   Copyright 2022 Nioneni Corporation Limited
//

#include <unistd.h>

#include <QApplication>
#include <QFont>
#include <QString>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

#include "mmain.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("/usr/share/icons/msystem.png"));

    QTranslator qtTran;
    qtTran.load(QString("qt_") + QLocale::system().name());
    a.installTranslator(&qtTran);

    QTranslator appTran;
    appTran.load(QString("minstall_") + QLocale::system().name(), "/usr/share/nioneniOS-installer/locale");
    a.installTranslator(&appTran);

    //exit if "minstall" is already running
    if (system("ps -C minstall | sed '0,/minstall/{s/minstall//}' | grep minstall") == 0) {
        QMessageBox::critical(0, QString::null,
                              QApplication::tr("The installer won't launch because it appears to be running already in the background.\n\n"
                                               "Please close it if possible, or run 'pkill minstall' in terminal."));
        return 1;
    }

    // check if 32bit on UEFI
    if (system("uname -m | grep -q i686") == 0 && system("test -d /sys/firmware/efi") == 0)
    {        
        int ans = QMessageBox::question(0, QString::null, QApplication::tr("You are running 32bit OS started in UEFI mode, the system will not be able to boot"
                                                                           " unless you select Legacy Boot or similar at restart.\n"
                                                                           "We recommend you quit now and restart in Legacy Boot\n\n"
                                                                           "Do you want to continue the installation?"),
                                    QApplication::tr("Yes"), QApplication::tr("No"));
        if (ans != 0) {
            return 1;
        }
    }


    if (getuid() == 0) {
        MMain mmain;
        mmain.show();
        return a.exec();
    } else {
        QApplication::beep();
        QMessageBox::critical(0, QString::null,
                              QApplication::tr("You must run this app as root."));
        return 1;
    }
}


