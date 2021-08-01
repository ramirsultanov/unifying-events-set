#ifndef MARKER_H
#define MARKER_H

#include "user.h"

#include <WDateTime.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/SqlTraits.h>
#include <string>
#include <utility>

namespace dbo = Wt::Dbo;

class User;

class Event
{
public:
  double x;
  double y;
  Wt::WDateTime datetime;
  int participantsLimit; // "0" is for "no limit" | "1" is for "unknown"
  dbo::collection<dbo::ptr<User> > participants;
  std::string title;
  std::string description;

  template <class Action>
  void
  persist (Action &a)
  {
    dbo::field (a, x, "x");
    dbo::field (a, y, "y");
    dbo::field (a, datetime, "datetime");
    dbo::field (a, participantsLimit, "participantsLimit");
    dbo::hasMany (a, participants, dbo::ManyToMany, "participant_event");
    dbo::field (a, title, "title");
    dbo::field (a, description, "description");
  }
};

#endif // MARKER_H
