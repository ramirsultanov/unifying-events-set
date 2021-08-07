#ifndef MARKERINFOWIDGET_H
#define MARKERINFOWIDGET_H

#include <Wt/WSignal.h>

#include "event.h"

class MarkerInfoWidget
{
public:
  Wt::Signals::Signal<const std::shared_ptr<Event> > showEventInfo;

  MarkerInfoWidget (const Event &event);

private:
  std::shared_ptr<Event> event_;
};

#endif // MARKERINFOWIDGET_H
