#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QDir>
#include <QCoreApplication>

const QString PREV_BTN_ICON_PATH = QString(":/assets/previous-button.png");
const QString PLAY_BTN_ICON_PATH = QString(":/assets/play-button.png");
const QString PAUSE_BTN_ICON_PATH = QString(":/assets/pause-button.png");
const QString RESET_BTN_ICON_PATH = QString(":/assets/reset-button.png");
const QString RANDOM_BTN_ICON_PATH = QString(":/assets/random-button.png");
const QString NEXT_BTN_ICON_PATH = QString(":/assets/next-button.png");
const QString DB_PATH = QDir("../DBB.db").absolutePath();

#endif // CONSTANTS_H
