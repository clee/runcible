#include <QApplication>
#include <choiceview.h>
#include "tocman.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  if (argc != 2) {
    fprintf(stderr, "Usage: runcible-contents-pdf <file>");
    return -1;
  }

  QString path(argv[1]);

  TocManager tocman(path);
  ChoiceView view;

  view.setWindowTitle("Contents of " + QFileInfo(path).fileName());

  QObject::connect(&view, SIGNAL(back()), &app, SLOT(quit()));
  QObject::connect(&view, SIGNAL(choiceMade(Choice)), &tocman, SLOT(activate(Choice)));
  QObject::connect(&tocman, SIGNAL(contentsChanged(QList<Choice>)), &view, SLOT(setChoices(QList<Choice>)));

  tocman.refresh();
  view.showMaximized();

  return app.exec();
}