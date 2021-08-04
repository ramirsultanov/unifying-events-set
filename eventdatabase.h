#ifndef MARKERDATABASE_H
#define MARKERDATABASE_H

#include "event.h"

#include <Wt/Dbo/Session.h>
#include <vector>

class EventDatabase
{
private:
  Wt::Dbo::Session &s_;

public:
  EventDatabase (Wt::Dbo::Session &);
  bool addEvent (const Event &);
  std::vector<Event>
  getEvents (const std::pair<double, double> upLeftBorder,
             const std::pair<double, double> downRightBorder) const;
};

#endif // MARKERDATABASE_H
