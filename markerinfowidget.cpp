#include "markerinfowidget.h"

MarkerInfoWidget::MarkerInfoWidget (const Event &event)
{
  this->event_ = std::make_shared<Event> (event);
  showEventInfo.emit (event_);
}
