#ifndef MARKERFORMWIDGET_H
#define MARKERFORMWIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>

#include "event.h"
#include "eventdatabase.h"

class MarkerFormWidget : Wt::WContainerWidget
{
public:
  MarkerFormWidget ();

private:
  Wt::WLineEdit *titleEdit_;

  Event &&event ();
};

#endif // MARKERFORMWIDGET_H
