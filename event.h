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
  Wt::WDateTime datetimeStart;
  /// Null DateTime is for "unknown"
  Wt::WDateTime datetimeFinish;
  /// "0" is for "no limit" | "1" is for "unknown"
  int participantsLimit;
  dbo::collection<dbo::ptr<User> > participants;
  std::string title;
  std::string description; // ! limit 255 symbols

  Wt::WString datetimeFinish_to_string ();
  Wt::WString participantsLimit_to_string ();

  constexpr static double xMin = -90;
  constexpr static double xMax = 90;
  constexpr static double yMin = 0;
  constexpr static double yMax = 180;
  constexpr static int participantsLimitMin = 2;
  constexpr static unsigned int descriptionMaxLength = 255; // ? enough

  template <class Action>
  void
  persist (Action &a)
  {
    dbo::field (a, x, "x");
    dbo::field (a, y, "y");
    dbo::field (a, datetimeStart, "datetimeStart");
    dbo::field (a, datetimeFinish, "datetimeFinish");
    dbo::field (a, participantsLimit, "participantsLimit");
    dbo::hasMany (a, participants, dbo::ManyToMany, "participant_event");
    dbo::field (a, title, "title");
    dbo::field (a, description, "description");
  }
};

#endif // MARKER_H
