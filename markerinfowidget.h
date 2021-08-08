#ifndef MARKERINFOWIDGET_H
#define MARKERINFOWIDGET_H

#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>

#include "event.h"

class MarkerInfoWidget
{
public:
  Wt::Signals::Signal<const std::shared_ptr<Event> > showEventInfo;
  Wt::Signals::Signal<const std::shared_ptr<Event> > hideEventInfo;
  Wt::Signals::Signal<const std::shared_ptr<Event> > showParticipants;

  MarkerInfoWidget (const Event &event);
  std::unique_ptr<Wt::WContainerWidget> createWidget () const;

private:
  std::shared_ptr<Event> event_;
};

#endif // MARKERINFOWIDGET_H
