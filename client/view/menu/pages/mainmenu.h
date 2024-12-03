#pragma once

#include "ui_mainMenu.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class mainMenu;
}
QT_END_NAMESPACE

class mainMenu: public QWidget {
    Q_OBJECT

public:
    explicit mainMenu(QWidget* parent = nullptr);
    ~mainMenu() override;

signals:
    void play(); /** se emite al apretar el boton Play */
    void exitGameRequested(); /** se emite al apretar el boton Exit */

private:
    Ui::mainMenu* ui;

    /**
     *  Si se presiona el boton de Exit, se handlea en este metodo.
     *  Se le pregunta al usuario si esta seguro de salir.
     *  Si quiere salir, emite exitGameRequested() para que el QWidget principal se encargue de cerrar la aplicacion
     */
    void handleExit();
};
