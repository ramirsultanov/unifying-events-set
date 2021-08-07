#ifndef MARKERWIDGET_H
#define MARKERWIDGET_H

#include <Wt/WPushButton.h>
#include <Wt/WSignal.h>
#include <string>

#include "event.h"

class MarkerWidget : public Wt::WPushButton
{
public:
  Wt::Signals::Signal<const std::shared_ptr<Event> > showInfo;

  MarkerWidget (const Event &event);

private:
  void info ();
  const Event &event_;
  void setStyle ();
};

#endif // MARKERWIDGET_H
