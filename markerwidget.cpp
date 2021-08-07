#include "markerwidget.h"
#include "markerinfowidget.h"

MarkerWidget::MarkerWidget (const Event &event)
    : Wt::WPushButton (event.title), event_ (event)
{
  this->clicked ().connect (this, &MarkerWidget::info);
  this->setStyle ();
}

void
MarkerWidget::info ()
{
  MarkerInfoWidget info (this->event_);
}

void
MarkerWidget::setStyle ()
{
}
