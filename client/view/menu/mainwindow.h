#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    QButtonGroup* grupoJugadores;

    void irASeleccionJugadores();
    void salirDelJuego();
    void crearPartida();
    void unirseAPartida();
    void menuAnterior();
    void iniciarPartida();

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif  // MAINWINDOW_H
