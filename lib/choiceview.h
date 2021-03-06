#ifndef CHOICEVIEW_H
#define CHOICEVIEW_H

#include <QtCore>
#include <QWidget>

class QKeyEvent;
class QPaintEvent;

#define NUM_CHOICES 10
/*
 * A simple value class that represents a choice in the ChoiceView.
 */
class Choice {
  public:
    Choice(const QString &title, const QString &id, const QStringList &params = QStringList());

    const QString &id() const;
    const QString &title() const;
    const QStringList &params() const;

  private:
    QString _id, _title;
    QStringList _params;
};
bool operator<(Choice a, Choice b);


/*
 * A specialized view that presents a menu of ten Choice items
 * at a time.  Items can be selected using 0-9, or paged through
 * using Up/Down.
 */
class ChoiceView : public QWidget {
  Q_OBJECT

public:
  ChoiceView(QWidget *parent = 0);
  virtual ~ChoiceView();


public slots:
  void choose(int);
  void setChoices(const QList<Choice> &);
  void pageUp();
  void pageDown();

signals:
  void morePages(int);
  void switchedToPage(int);

  void choiceMade(const Choice);

protected:
  virtual void keyPressEvent(QKeyEvent *);
  virtual void paintEvent(QPaintEvent *event);

private:
  void refreshLabels();

  QList<Choice> _choices;
  int _offset;
};

#endif // CHOICEVIEW_H
